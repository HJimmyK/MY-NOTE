#include <iostream>  
#include <vector>  
#include <bitset>  
#include <stdexcept>  
#include <string>  
#include <sstream> // std::ostringstream
#include <iomanip>
#include <complex>
#include <fstream>  
#include <iomanip> // 用于 std::setprecision
#include <cstdlib> // 用于 std::rand() 和 std::srand()  
#include "vec_bitset.h"
#include<chrono>



#define MAX_BIT_TO_STRING_LEN 20000
#define TEN_POW_EIGHT 0x5f5e100
#define TEN_POW_EIGHTTEEN 0xde0b6b3a7640000

// high precision multiplication using native multiplication
std::string multiplyStrings1(const std::string& num1, const std::string& num2)
{
    // if either num is zero, return zero
    if (num1 == "0" || num2 == "0")
    {
        return "0";
    }

    size_t len1 = num1.size();
    size_t len2 = num2.size();
    size_t len_sum = len1 + len2;
    std::vector<unsigned short> result(len_sum, 0);

    for (size_t i = 0; i < len1; i++)
    {
        for (size_t j = 0; j < len2; j++)
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j];
            result[i + j] = sum % 10;      // remainder
            result[i + j + 1] += sum / 10; // carry
        }
    }
    // build reslutstr
    std::string resultStr(len_sum, '0');
    size_t index = len_sum - 1;
    bool isLeadingZero = true;
    // from high to low, remove backing zero
    for (int i = len_sum - 1; i >= 0; i--)
    {
        if (result[i] != 0)
        {
            isLeadingZero = false; // found non-zero digit
        }
        if (!isLeadingZero)
        {
            resultStr[index] = result[i] + '0';
        }
        index--;
    }
    return resultStr.empty() ? "0" : resultStr; // if empty, return "0"
}

// high precision multiplication using FFT multiplication 
std::string multiplyStrings2(const std::string& num1, const std::string& num2) {
    const size_t len1 = num1.size();
    const size_t len2 = num2.size();
    const size_t len_sum = len1 + len2;
    const unsigned short depth = floor(log2(len_sum)) + 1;
    const size_t len_new = 1ULL << static_cast<size_t>(depth);

    std::vector<std::complex<double>> val(len_new, 0);
    // transform num1 and num2 to complex val
    for (int i = 0; i < len_new; i++) {
        if (i >= len1 && i >= len2) {
            break;
        }
        else if (i >= len1 && i < len2) {
            val[i] = std::complex<double>(0, num2[i] - '0');
        }
        else if (i >= len2 && i < len1) {
            val[i] = std::complex<double>(num1[i] - '0', 0);
        }
        else {
            val[i] = std::complex<double>(num1[i] - '0', num2[i] - '0');
        }
    }

    for (int k = 0; k < len_new; ++k) {
        // reserve the index of the reversed index
        int reversedIndex = 0;
        for (int i = 0; i < depth; ++i) {
            reversedIndex |= ((k >> i) & 1) << (depth - 1 - i);
        }
        if (k < reversedIndex) {
            swap(val[k], val[reversedIndex]);
        }
    }

    // positive transform
    std::complex<double> temp1, temp2;
    size_t layer_half = 1; // copy the last layer value
    double angle;          // depth for angle
    for (size_t layer = 2; layer <= len_new; layer <<= 1) {
        angle = 2.0 * PI / layer;
        std::complex<double> omega_pri(cos(angle), sin(angle));
        for (size_t k = 0; k < len_new; k += layer) {
            std::complex<double> omega0(1, 0);
            for (size_t j = 0; j < layer_half; ++j) {
                temp1 = omega0 * val[k + j + layer_half];
                temp2 = val[k + j];
                val[k + j] = temp1 + temp2;
                val[k + j + layer_half] = temp2 - temp1;
                omega0 *= omega_pri;
            }
        }
        layer_half = layer;
    }

    // calculate the square of val
    std::vector<std::complex<double>> val_multi(len_new, 0);
    for (size_t index = 0; index < len_new; index++) {
        val_multi[index] = val[index] * val[index];
    }


    for (int k = 0; k < len_new; ++k) {
        // reserve the index of the reversed index
        int reversedIndex = 0;
        for (int i = 0; i < depth; ++i) {
            reversedIndex |= ((k >> i) & 1) << (depth - 1 - i);
        }
        if (k < reversedIndex) {
            swap(val_multi[k], val_multi[reversedIndex]);
        }
    }

    // nagetive transform
    layer_half = 1; // copy the last layer value
    for (size_t layer = 2; layer <= len_new; layer <<= 1) {
        angle = -2.0 * PI / layer;
        std::complex<double> omega_pri(cos(angle), sin(angle));
        for (size_t k = 0; k < len_new; k += layer) {
            std::complex<double> omega0(1, 0);
            for (size_t j = 0; j < layer_half; ++j) {
                temp1 = omega0 * val_multi[k + j + layer_half];
                temp2 = val_multi[k + j];
                val_multi[k + j] = temp1 + temp2;
                val_multi[k + j + layer_half] = temp2 - temp1;
                omega0 *= omega_pri;
            }
        }
        layer_half = layer;
    }

    std::vector<unsigned> result_unsigned(len_new, 0);
    for (size_t index = 0; index < len_new; index++) {
        result_unsigned[index] = round(val_multi[index].imag() / (2.0 * len_new));
    }

    // the result is in the first len_sum digits of result_unsigned
    std::string result_str(len_sum, '0');
    unsigned carry = 0, i = 0;
    for (size_t index = 0; index < len_sum; index++) {
        result_str[index] = (result_unsigned[i] + carry) % 10 + '0';
        carry = (result_unsigned[i++] + carry) / 10;
    }
    // delete lasting zeros
    size_t lastNonZero = result_str.find_last_not_of('0');
    if (lastNonZero != std::string::npos) {
        return result_str.substr(0, lastNonZero + 1);  // delete lasting zeros
    }
    return "0";  // if all digits are zero, return "0"
}

std::string multiplyStrings(const std::string& num1, const std::string& num2) {
    size_t len1 = num1.size(), len2 = num2.size();
    if (len1 <= MULTI_FFT_CHOICE || len2 <= MULTI_FFT_CHOICE) {
        return multiplyStrings1(num1, num2);
    }
    else {
        return multiplyStrings2(num1, num2);
    }
}

// high precision addition
std::string addStrings(const std::string& num1, const std::string& num2) {
    unsigned short carry = 0; // carry
    size_t len1 = num1.size(), len2 = num2.size();
    std::string result(((len1 > len2) ? len1 : len2) + 1, '0'); // result string
    size_t i = 0, j = 0, resulIndex = 0;
    // frome back to front
    while (i < len1 || j < len2 || carry > 0) {
        unsigned short digit1 = (i < len1) ? num1[i++] - '0' : 0; // get num1 current digit
        unsigned short digit2 = (j < len2) ? num2[j++] - '0' : 0; // get num2 current digit
        unsigned short sum = digit1 + digit2 + carry; // calculate sum
        carry = sum / 10; // update carry
        result[resulIndex++] = (sum % 10) + '0'; // push sum to result
    }
    // delete lasting zeros
    size_t lastNonZero = result.find_last_not_of('0');
    if (lastNonZero != std::string::npos) {
        return result.substr(0, lastNonZero + 1);  // delete lasting zeros
    }
    return "0";  // if all digits are zero, return "0"
}

// 计算 2 的十进制下的正整数次幂结果，返回一个string
std::string unsigned_pow2_str1(unsigned index) {
    if (index == 0) {
        return "1";
    }
    std::string result("1");
    for (size_t i = 0; i < index; i++) {
        result = multiplyStrings(result, result);
    }
    return result;
}

// divide and conquer calculate 2 power index, return a string
std::string unsigned_pow2_str2(const unsigned index) {
    if (index <= 32) {
        switch (index) { // simple cases reduce calculation time
        case 0:
            return STR_2_POW_0;
        case 1:
            return STR_2_POW_1;
        case 2:
            return STR_2_POW_2;
        case 3:
            return STR_2_POW_3;
        case 4:
            return STR_2_POW_4;
        case 5:
            return STR_2_POW_5;
        case 6:
            return STR_2_POW_6;
        case 7:
            return STR_2_POW_7;
        case 8:
            return STR_2_POW_8;
        case 9:
            return STR_2_POW_9;
        case 10:
            return STR_2_POW_10;
        case 11:
            return STR_2_POW_11;
        case 12:
            return STR_2_POW_12;
        case 13:
            return STR_2_POW_13;
        case 14:
            return STR_2_POW_14;
        case 15:
            return STR_2_POW_15;
        case 16:
            return STR_2_POW_16;
        case 17:
            return STR_2_POW_17;
        case 18:
            return STR_2_POW_18;
        case 19:
            return STR_2_POW_19;
        case 20:
            return STR_2_POW_20;
        case 21:
            return STR_2_POW_21;
        case 22:
            return STR_2_POW_22;
        case 23:
            return STR_2_POW_23;
        case 24:
            return STR_2_POW_24;
        case 25:
            return STR_2_POW_25;
        case 26:
            return STR_2_POW_26;
        case 27:
            return STR_2_POW_27;
        case 28:
            return STR_2_POW_28;
        case 29:
            return STR_2_POW_29;
        case 30:
            return STR_2_POW_30;
        case 31:
            return STR_2_POW_31;
        default:
            return STR_2_POW_32;
        }
    }
    else {
        unsigned mid = index / 2;
        unsigned remain = index - mid;
        if (index % 2 == 0) {
            std::string left = unsigned_pow2_str2(mid);
            std::string right = left;
            return multiplyStrings(left, right);
        }
        else {
            std::string left = unsigned_pow2_str2(mid);
            std::string right = addStrings(left, left);
            return multiplyStrings(left, right);
        }
    }
}

// Iterative method to calculate 2 raised to the power of index, return a string
std::string unsigned_pow2_str3(unsigned index) {
    std::string ans = "1";
    std::string temp = "2";
    while (index) {
        if (index & 1) {
            ans = multiplyStrings(ans, temp);
        }
        temp = multiplyStrings(temp, temp);
        index >>= 1;
    }
    return ans;
}



// 储存二的幂的基数
// 计算2的val次方的十进制数，使用string储存
std::string binary_to_decimal2(vec_bitset val) {
    const size_t len = val.size();
    const size_t top = val.top();
    const size_t depth = floor(log2(top)) + 1;
    std::vector<std::string> _2pow2(depth, "2");
    for (size_t i = 1; i < depth; i++) {
        _2pow2[i] = multiplyStrings(_2pow2[i - 1], _2pow2[i - 1]);
    }

    std::string result;
    for (int i = 0; i <= top; i++) {
        if (!val[i]) {
            continue;
        }
        int j = i;
        int k = 0;
        std::string temp = "1";
        while (j) {
            if (j & 1) {
                temp = multiplyStrings(temp, _2pow2[k]);
            }
            j >>= 1;
            k++;
        }
        result = addStrings(result, temp);
    }
    // 删去多余的零
    std::string::iterator topptr = result.end() - 1;
    for (; *topptr == '0'; topptr--) {
        ;
    }
    result.erase(topptr + 1, result.end());
    std::reverse(result.begin(), result.end());
    return result;
}

// 以10为基数，计算2的val次方的十进制数，使用string储存（有位翻转）
std::string binary_to_decimal3(vec_bitset binary_put) {
    size_t length = binary_put.size();
    int top = 0;
    short ten = 10;
    const size_t bina_size = (size_t)floor(length * LOG10_2) + 1;
    vec_bitset binary(length);
    for (size_t i = 0; i < length; i++) {
        if (binary_put[length - 1 - i]) {
            binary.set(i);
        }
    }

    vec_bitset next_binary(length);
    std::string decimal_string(bina_size, '0');	// decimal_string is used to store the decimal equivalent of the binary number
    size_t decimal_i = bina_size - 1;	// decimal_i is used to store the index of the decimal_string where the next digit should be added
    // Convert binary to decimal
    while (binary.any()) {
        for (; top < length; top++) {
            if (binary[top]) {
                break;
            }
        }
        short temp = 0;	// temp is used to store the decimal remainder of the current binary number

        for (size_t index = top; index < length; index++) {
            if (temp == 0 && binary[index]) {
                temp++;
                continue;
            }
            temp <<= 1;
            if (binary[index]) {
                temp += 1;
            }

            if (temp < 10) {
                continue;
            }
            else {
                temp -= 10;
                next_binary.set(index);
            }
        }
        decimal_string[decimal_i--] = temp + '0';
        binary = next_binary;
        next_binary.reset();
    }
    size_t firstNonZero = decimal_string.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        return decimal_string.substr(firstNonZero);  // Return the decimal equivalent of the binary number as a string
    }
    return "0";  // If all the digits are zero, return "0"
}

// 以十为基数，计算2的val次方的十进制数，使用string储存（无位翻转）
std::string binary_to_decimal3_(vec_bitset binary) {
    size_t length = binary.size();
    int top = length - 1;
    short ten = 10;
    const size_t bina_size = (size_t)floor(length * LOG10_2) + 1;

    vec_bitset next_binary(length);
    std::string decimal_string(bina_size, '0');	// decimal_string is used to store the decimal equivalent of the binary number
    size_t decimalstr_i = bina_size - 1;	// decimal_i is used to store the index of the decimal_string where the next digit should be added
    // Convert binary to decimal
    while (binary.any()) {
        for (; top >= 0; top--) {
            if (binary[top]) {
                break;
            }
        }
        short temp = 0;	// temp is used to store the decimal remainder of the current binary number

        for (int index = top; index >= 0; index--) {
            if (temp == 0 && binary[index]) {
                temp++;
                continue;
            }
            temp <<= 1;
            if (binary[index]) {
                temp += 1;
            }

            if (temp < 10) {
                continue;
            }
            else {
                temp -= 10;
                next_binary.set(index);
            }
        }
        decimal_string[decimalstr_i--] = temp + '0';
        binary = next_binary;
        next_binary.reset();
    }
    size_t firstNonZero = decimal_string.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        return decimal_string.substr(firstNonZero);  // Return the decimal equivalent of the binary number as a string
    }
    return "0";  // If all the digits are zero, return "0"
}

// 以十的8次方为基数，计算2的val次方的十进制数，使用string储存（无位翻转）
std::string binary_to_decimal4(vec_bitset binary) {
    size_t length = binary.size();
    int top = length - 1;
    const size_t bina_size = (size_t)floor(length * LOG10_2) + 1;
    //const size_t decimal_size = (bina_size / 8 + 1) * 8;
    vec_bitset next_binary(length);
    std::string decimal_string(bina_size, '0');	// decimal_string is used to store the decimal equivalent of the binary number
    size_t decimalstr_i = bina_size - 1;	// decimal_i is used to store the index of the decimal_string where the next digit should be added


    int carry = 0;
    std::string temp;
    // Convert binary to decimal
    while (binary.any()) {
        for (; top >= 0; top--) {
            if (binary[top]) {
                break;
            }
        }
        carry = 0;	// temp is used to store the decimal remainder of the current binary number

        for (int index = top; index >= 0; index--) {
            if (carry == 0 && binary[index]) {
                carry++;
                continue;
            }
            carry <<= 1;
            if (binary[index]) {
                carry += 1;
            }

            if (carry < TEN_POW_EIGHT) {
                continue;
            }
            else {
                carry -= TEN_POW_EIGHT;
                next_binary.set(index);
            }
        }

        temp = std::to_string(carry);
        std::reverse(temp.begin(), temp.end());
        for (int i = 0; i < 8 && i < temp.size(); i++) {
            decimal_string[decimalstr_i - i] = temp[i];
        }
        decimalstr_i = decimalstr_i - 8;
        binary = next_binary;
        next_binary.reset();
    }

    size_t firstNonZero = decimal_string.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        return decimal_string.substr(firstNonZero);  // Return the decimal equivalent of the binary number as a string
    }
    return "0";  // If all the digits are zero, return "0"
}

// 以十的18次方为基数，计算2的val次方的十进制数，使用string储存（无位翻转）
std::string binary_to_decimal5(vec_bitset binary) {
    size_t length = binary.size();
    int top = length - 1;
    const size_t bina_size = (size_t)floor(length * LOG10_2) + 1;
    const size_t decimal_size = (bina_size / 19 + 1) * 19;
    vec_bitset next_binary(length);
    std::string decimal_string(decimal_size, '0');	// decimal_string is used to store the decimal equivalent of the binary number
    size_t decimalstr_i = decimal_size - 1;	// decimal_i is used to store the index of the decimal_string where the next digit should be added


    unsigned long long carry = 0;
    std::string temp;
    // Convert binary to decimal
    while (binary.any()) {
        for (; top >= 0; top--) {
            if (binary[top]) {
                break;
            }
        }
        carry = 0;	// temp is used to store the decimal remainder of the current binary number

        for (int index = top; index >= 0; index--) {
            if (carry == 0 && binary[index]) {
                carry++;
                continue;
            }
            carry <<= 1;
            if (binary[index]) {
                carry += 1;
            }

            if (carry < TEN_POW_EIGHTTEEN) {
                continue;
            }
            else {
                carry -= TEN_POW_EIGHTTEEN;
                next_binary.set(index);
            }
        }

        temp = std::to_string(carry);
        std::reverse(temp.begin(), temp.end());
        for (short i = 0; i < 18 && i < temp.size(); i++) {
            decimal_string[decimalstr_i - i] = temp[i];
        }
        decimalstr_i = decimalstr_i - 18;
        binary = next_binary;
        next_binary.reset();
    }

    size_t firstNonZero = decimal_string.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        return decimal_string.substr(firstNonZero);  // Return the decimal equivalent of the binary number as a string
    }
    return "0";  // If all the digits are zero, return "0"
}

// 使用朴素乘法计算2的val次方的十进制数，使用string储存
std::string to_string(vec_bitset val) {
    size_t str_len = (size_t)val.size() * LOG10_2 + 1;
    std::string initial_str(str_len, '0'); // 创建一个由 '0' 组成的字符串
    std::string temp_str_pri;
    std::string temp_str_bina(str_len, '0'); // 记录当前二进制数
    short pri_ = 0, fro_ = 0;
    for (size_t p_index = 0; p_index < val.size(); p_index++) {

        int tim = 0;  //记录在i之前，二进制出现1的下标

        if (val.get(p_index)) {

            // 计算当前位数十进制下的 2^i
            if (tim == 0) {//首次二进制出现1
                tim = p_index;
                temp_str_pri = unsigned_pow2_str2(tim);
                for (size_t i = 0; i < str_len; i++) {
                    if (temp_str_pri[i] != '\0') {
                        temp_str_bina[i] = temp_str_pri[i];
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                short pri = 0, fro = 0;
                for (size_t index = tim; index <= p_index; index++) {
                    pri = 0; fro = 0;
                    for (unsigned j = 0; j < str_len && j <= LOG10_2 * p_index; j++) {
                        pri = (temp_str_bina[j] - '0') * 2;
                        pri += fro;
                        fro = pri / 10;
                        pri = pri % 10;
                        temp_str_bina[j] = pri + '0';
                    }
                }
                tim = p_index;
            }

            pri_ = 0, fro_ = 0;
            //将此二的次方加入到 initial_str 中
            for (size_t j = 0; j < str_len; j++) {
                pri_ = (temp_str_bina[j] - '0') + (initial_str[j] - '0');
                pri_ += fro_;
                fro_ = pri_ / 10;
                pri_ = pri_ % 10;
                initial_str[j] = pri_ + '0';
            }
        }
    }

    //删去多余的零
    int top = str_len - 1;
    for (int i = str_len - 1; i >= 0; i--) {
        if (initial_str[top] == '0') {
            top--;
        }
    }
    std::string final_str(initial_str, 0, top + 1);
    std::reverse(final_str.begin(), final_str.end());

    //让空字符输出零
    if (final_str[0] == '\0') {
        final_str.insert(final_str.begin(), '0');
    }
    return final_str;
}


std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    for (int& element : vec) {
        element = rand() % 10; // 生成 0 到 9 的随机正整数  
    }
    return vec;
}

std::string generateRandomString(int size) {
    std::string vec(size, '0');
    for (int i = 0; i < size; i++) {
        vec[i] = (rand() % 10) + '0'; // 生成 0 到 9 的随机正整数  
    }
    return vec;
}

// 测试朴素转换的性能
void time_test() {

    int num = 100;
    std::vector<double> times1(num);
    std::vector<double> times2(num);

    for (int i = 0; i < num; i++) {

        std::string mother = generateRandomString(10 * i + 100);
        //std::cout << mother << std::endl;
        // 获取开始时间  
        auto start_time = std::chrono::high_resolution_clock::now();

        vec_bitset a(mother);
        // 获取结束时间 
        auto end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间  
        std::chrono::duration<double> duration = end_time - start_time;
        // 输出运行时间  
        times1[i] = duration.count();

        //std::cout << "程序运行时间: " << duration.count() << "秒" << std::endl;
        //std::cout << l << std::endl;


        // 获取开始时间  
        start_time = std::chrono::high_resolution_clock::now();
        std::string n = a.to_string();
        // 获取结束时间  
        end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间  
        duration = end_time - start_time;
        // 输出运行时间  
        times2[i] = duration.count();
        //std::cout << "程序运行时间: " << duration.count() << "秒" << std::endl;
        //std::cout << n << std::endl;
        std::cout << i << std::endl;
    }



    std::ofstream file("times.csv");
    if (!file.is_open())
    {
        std::cerr << "无法打开文件: " << std::endl;
    }
    for (int i = 0; i < num; ++i)
    {
        file << std::setprecision(9) << std::fixed << times1[i]; // 设置输出格式
        file << ","; // 除最后一列外，每列后面添加逗号
    }
    file << "\n"; // 每行结束后换行
    for (int i = 0; i < num; ++i)
    {
        file << std::setprecision(9) << std::fixed << times2[i]; // 设置输出格式
        file << ","; // 除最后一列外，每列后面添加逗号
    }
    file << "\n"; // 每行结束后换行
    file.close(); // 关闭文件
}

// 测试改进转换的性能
void time_test() {

    int num = 100;
    std::vector<double> advanced_times1(num);
    std::vector<double> advanced_times2(num);

    for (int i = 0; i < num; i++) {

        std::string mother = generateRandomString(100 * i + 100);
        vec_bitset a(mother);
        // 获取开始时间  
        auto start_time = std::chrono::high_resolution_clock::now();
        std::string l = to_string(a);

        // 获取结束时间 
        auto end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间  
        std::chrono::duration<double> duration = end_time - start_time;
        // 输出运行时间  
        advanced_times1[i] = duration.count();

        //std::cout << "程序运行时间: " << duration.count() << "秒" << std::endl;
        //std::cout << l << std::endl;


        // 获取开始时间  
        start_time = std::chrono::high_resolution_clock::now();
        std::string n = binary_to_decimal2(a);
        // 获取结束时间  
        end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间  
        duration = end_time - start_time;
        // 输出运行时间  
        advanced_times2[i] = duration.count();
        //std::cout << "程序运行时间: " << duration.count() << "秒" << std::endl;
        //std::cout << n << std::endl;
        std::cout << i << std::endl;
    }



    std::ofstream file("advacned_times.csv");
    if (!file.is_open())
    {
        std::cerr << "无法打开文件: " << std::endl;
    }
    for (int i = 0; i < num; ++i)
    {
        file << std::setprecision(9) << std::fixed << advanced_times1[i]; // 设置输出格式
        file << ","; // 除最后一列外，每列后面添加逗号
    }
    file << "\n"; // 每行结束后换行
    for (int i = 0; i < num; ++i)
    {
        file << std::setprecision(9) << std::fixed << advanced_times2[i]; // 设置输出格式
        file << ","; // 除最后一列外，每列后面添加逗号
    }
    file << "\n"; // 每行结束后换行
    file.close(); // 关闭文件
}


void writeArrayToCSV_(const std::vector<double> array, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }
    for (int i = 0; i < 200; ++i)
    {
        file << std::setprecision(6) << std::fixed << array[i]; // 设置输出格式
        file << ","; // 除最后一列外，每列后面添加逗号
    }
    file << "\n"; // 每行结束后换行
    file.close(); // 关闭文件
}


void test2()
{

    std::vector<double> pow2time1(200);
    std::vector<double> pow2time2(200);
    std::vector<double> pow2time3(200);


    std::string bb, aa;
    for (size_t i = 0; i < 200; i++)
    {
        unsigned index = 1000 * i + 10;
        // 获取开始时间
        auto start_time = std::chrono::high_resolution_clock::now();
        bb = unsigned_pow2_str2(index);
        // 获取结束时间
        auto end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间
        std::chrono::duration<double> duration = end_time - start_time;
        // 输出运行时间
        pow2time1[i] = duration.count();
        // 获取开始时间
        start_time = std::chrono::high_resolution_clock::now();
        aa = unsigned_pow2_str3(index);
        // 获取结束时间
        end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间
        duration = end_time - start_time;
        pow2time2[i] = duration.count();
        // 获取开始时间
        start_time = std::chrono::high_resolution_clock::now();
        aa = unsigned_pow2_str1(index);
        // 获取结束时间
        end_time = std::chrono::high_resolution_clock::now();
        // 计算持续时间
        duration = end_time - start_time;
        pow2time3[i] = duration.count();
        std::cout << i << std::endl;
    }
    writeArrayToCSV_(pow2time1, "pow2time_3.csv");
    writeArrayToCSV_(pow2time3, "pow2time_3.csv");
    writeArrayToCSV_(pow2time2, "pow2time_2.csv");
}


int main() {

    return 0;
}