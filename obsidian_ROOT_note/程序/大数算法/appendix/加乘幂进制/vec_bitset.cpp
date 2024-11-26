#include "vec_bitset.h"

// vec_bitset 类的实现***********************************************************************

//构造函数，长度设为 0 
vec_bitset::vec_bitset() {
	bits_size = 0;
	vec_size = 1;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(vec_size);
	bits = temp;
}

// 构造函数，长度为size的全空bit
vec_bitset::vec_bitset(const size_t size) {
	bits_size = size;
	vec_size = size / VEC_BITSET_BITLEN + 1;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(vec_size);
	bits = temp;
}

//使用全为数字的字符串构造（十进制）
vec_bitset::vec_bitset(const std::string val) {
	size_t val_size = val.length();
	bits_size = (size_t)val_size / LOG10_2 + 1; //转换为二进制后的长度
	vec_size = bits_size / VEC_BITSET_BITLEN + 1;

	std::vector<std::bitset<VEC_BITSET_BITLEN>> result(vec_size);
	bits = result;

	//使用一个小数组，储存val的十进制数

	short* short_val = (short*)malloc(sizeof(short) * val_size);
	if (short_val == NULL) {
		printf("分配空间错误！请重试\n");
		system("pause"); exit(0);
	}
	else {

		for (size_t i = 0; i < val_size; i++) {
			if (std::isdigit(val[i])) {
				short_val[i] = val[i] - '0';
			}
			else {
				printf("无法接受输入的字符串\n");
				system("pause"); exit(0);
			}
		}

		for (size_t index = 0; index < bits_size; index++) {
			short temp = 0;
			for (size_t j = 0; j < val_size; j++) {
				temp = short_val[j] % 2;
				short_val[j] = short_val[j] / 2;
				if (j == val_size - 1) {
					continue;
				}
				else {
					short_val[j + 1] += temp * 10;
				}
			}

			this->set(index, temp);
			//判断是否除尽了
			bool isempty = 0;
			for (int i = 0; i < val_size; i++) {
				isempty = isempty || short_val[i];
			}
			if (isempty == 0) {
				break;
			}
		}
	}
}

//拷贝构造函数
vec_bitset::vec_bitset(const vec_bitset& other) {
	bits_size = other.bits_size;
	vec_size = other.vec_size;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(other.vec_size);
	for (size_t vec_index = 0; vec_index < vec_size; vec_index++) {
		temp.at(vec_index) = other.bits.at(vec_index);
	}
	bits = temp;
}

//获取大小(绝对大小)
size_t vec_bitset::size() {
	return bits_size;
}

//返回 1 的个数
size_t vec_bitset::count() {
	size_t sum = 0;
	for (size_t vec_index = 0; vec_index < vec_size - 1; vec_index++) {
		sum += bits.at(vec_index).count();
	}
	for (size_t bit_index = (vec_size - 1) * VEC_BITSET_BITLEN; bit_index < bits_size; bit_index++) {
		if (this->get(bit_index)) {
			sum++;
		}
	}
	return sum;
}

//返回最高位 1 的下标，没有 1 返回 -1
int vec_bitset::top() {
	for (int vec_index = vec_size - 1; vec_index >= 0; vec_index--) {
		if (bits.at(vec_index).any()) {
			for (int bit_index = VEC_BITSET_BITLEN - 1; bit_index >= 0; bit_index--) {
				if (bits.at(vec_index)[bit_index]) {
					return (int)vec_index * VEC_BITSET_BITLEN + bit_index;
				}
			}
		}
	}
	return -1;
}

//返回最低位 1 的下标，没有 1 返回 -1
int vec_bitset::base() {
	for (int vec_index = 0; vec_index < vec_size; vec_index++) {
		if (bits.at(vec_index).any()) {
			for (int bit_index = 0; bit_index < VEC_BITSET_BITLEN; bit_index++) {
				if (bits.at(vec_index)[bit_index]) {
					return (int)vec_index * VEC_BITSET_BITLEN + bit_index;
				}
			}
		}
	}
	return -1;
}

//转换成十进制字符串
std::string vec_bitset::to_string() {

	size_t str_len = (size_t)bits_size * LOG10_2 + 1;
	std::string initial_str(str_len, '0'); // 创建一个由 '0' 组成的字符串
	std::string temp_str_pri;
	std::string temp_str_bina(str_len, '0'); // 记录当前二进制数
	short pri_ = 0, fro_ = 0;
	for (size_t p_index = 0; p_index < bits_size; p_index++) {
		int tim = 0;  //记录在i之前，二进制出现1的下标

		if (this->get(p_index)) {

			// 计算当前位数十进制下的 2^i
			if (tim == 0) {//首次二进制出现1
				tim = p_index;
				temp_str_pri = binary_val(tim);
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

	return final_str;
}

//计算2的val次方的十进制数，使用string储存并返回
std::string vec_bitset::binary_val(const unsigned val) {
	size_t str_size = (size_t)val * LOG10_2 + 1;
	std::string decimal(str_size, '0'); // 初始十进制数为 0 
	if (val <= 63) {
		std::string temp = std::to_string((unsigned long long)pow(2, val));
		std::reverse(temp.begin(), temp.end());
		return temp;
	}
	else {
		std::string temp0 = std::to_string((unsigned long long)pow(2, 63));
		std::reverse(temp0.begin(), temp0.end());

		for (size_t i = 0; i < str_size; i++) {
			if (temp0[i] != '\0') {
				decimal[i] = temp0[i];
			}
			else {
				break;
			}
		}
		for (size_t i = 1; i <= val - 63; i++) {

			short pri = 0, fro = 0;
			for (size_t j = 0; j < str_size && j < LOG10_2 * (63 + i); j++) {
				pri = (decimal[j] - '0') * 2;
				pri += fro;
				fro = pri / 10;
				pri = pri % 10;
				decimal[j] = pri + '0';
			}
		}
		return decimal;
	}
}

//翻转所有的位
void vec_bitset::flip() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).flip();
	}
}

//设置比特，全为 1
void vec_bitset::set() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).set();
	}
}

//设置比特，第一个参数为下标，第二个为设置为 1 还是 0，默认 1
void vec_bitset::set(size_t pos, bool value) {
	if (pos >= bits_size) {
		printf("下标越界！\n");
		system("pause"); exit(0);
	}
	else {
		size_t vec_pos = pos / VEC_BITSET_BITLEN, bit_pos = pos % VEC_BITSET_BITLEN;
		bits.at(vec_pos).set(bit_pos, value);
	}
}

//重设置比特，全为 0
void vec_bitset::reset() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).reset();
	}
}

//重设置比特，第一个参数为下标，第二个为设置为 1 还是 0，默认 1
void vec_bitset::reset(size_t pos) {
	if (pos >= bits_size) {
		printf("下标越界！\n");
		system("pause"); exit(0);
	}
	else {
		size_t vec_pos = pos / VEC_BITSET_BITLEN, bit_pos = pos % VEC_BITSET_BITLEN;
		bits.at(vec_pos).reset(bit_pos);
	}
}

//获取此位
bool vec_bitset::get(size_t pos) {
	if (pos >= bits_size) {
		printf("下标越界！\n");
		system("pause"); exit(0);
	}
	return bits.at(pos / VEC_BITSET_BITLEN)[pos % VEC_BITSET_BITLEN];
}

//重载赋值运算符
vec_bitset& vec_bitset::operator =(const vec_bitset& other) {
	this->bits_size = other.bits_size;
	this->vec_size = other.vec_size;
	for (size_t vec_index = 0; vec_index < other.vec_size; vec_index++) {
		this->bits.at(vec_index) = other.bits.at(vec_index);
	}
	return *this;
}

//重载[]（不可修改）
bool vec_bitset::operator[](size_t pos) {
	return this->get(pos);
}

//重载按位与 &
vec_bitset vec_bitset::operator&(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit组长度不一致，无法按位与 &\n");
		system("pause"); exit(0);
	}
	else {
		vec_bitset temp(this->bits_size);
		for (size_t vec_index = 0; vec_index < this->vec_size; vec_index++) {
			temp.bits.at(vec_index) = this->bits.at(vec_index) & other.bits.at(vec_index);
		}
		return temp;
	}
}

//重载按位或 |
vec_bitset vec_bitset::operator|(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit组长度不一致，无法按位或 |\n");
		system("pause"); exit(0);
	}
	else {
		vec_bitset temp(this->bits_size);
		for (size_t vec_index = 0; vec_index < this->vec_size; vec_index++) {
			temp.bits.at(vec_index) = this->bits.at(vec_index) | other.bits.at(vec_index);
		}
		return temp;
	}
}

//重载按位异或 ^
vec_bitset vec_bitset::operator^(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit组长度不一致，无法按位异或 ^\n");
		system("pause"); exit(0);
	}
	else {
		vec_bitset temp(this->bits_size);
		for (size_t vec_index = 0; vec_index < this->vec_size; vec_index++) {
			temp.bits.at(vec_index) = this->bits.at(vec_index) ^ other.bits.at(vec_index);
		}
		return temp;
	}
}

//存在 1 返回真
bool vec_bitset::any() {
	for (size_t vec_index = 0; vec_index < vec_size - 1; vec_index++) {
		if (bits.at(vec_index).any()) {
			return true;
		}
	}
	for (size_t bit_index = 0; bit_index < bits_size - (vec_size - 1) * VEC_BITSET_BITLEN; bit_index++) {
		if (bits.at(vec_size - 1)[bit_index]) {
			return true;
		}
	}
	return false;
}

//vec_bitset类的实现-------------------------------------------------------------------------------------




