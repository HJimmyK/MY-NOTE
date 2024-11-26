#include "vec_bitset.h"

// vec_bitset ���ʵ��***********************************************************************

//���캯����������Ϊ 0 
vec_bitset::vec_bitset() {
	bits_size = 0;
	vec_size = 1;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(vec_size);
	bits = temp;
}

// ���캯��������Ϊsize��ȫ��bit
vec_bitset::vec_bitset(const size_t size) {
	bits_size = size;
	vec_size = size / VEC_BITSET_BITLEN + 1;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(vec_size);
	bits = temp;
}

//ʹ��ȫΪ���ֵ��ַ������죨ʮ���ƣ�
vec_bitset::vec_bitset(const std::string val) {
	size_t val_size = val.length();
	bits_size = (size_t)val_size / LOG10_2 + 1; //ת��Ϊ�����ƺ�ĳ���
	vec_size = bits_size / VEC_BITSET_BITLEN + 1;

	std::vector<std::bitset<VEC_BITSET_BITLEN>> result(vec_size);
	bits = result;

	//ʹ��һ��С���飬����val��ʮ������

	short* short_val = (short*)malloc(sizeof(short) * val_size);
	if (short_val == NULL) {
		printf("����ռ����������\n");
		system("pause"); exit(0);
	}
	else {

		for (size_t i = 0; i < val_size; i++) {
			if (std::isdigit(val[i])) {
				short_val[i] = val[i] - '0';
			}
			else {
				printf("�޷�����������ַ���\n");
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
			//�ж��Ƿ������
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

//�������캯��
vec_bitset::vec_bitset(const vec_bitset& other) {
	bits_size = other.bits_size;
	vec_size = other.vec_size;
	std::vector<std::bitset<VEC_BITSET_BITLEN>> temp(other.vec_size);
	for (size_t vec_index = 0; vec_index < vec_size; vec_index++) {
		temp.at(vec_index) = other.bits.at(vec_index);
	}
	bits = temp;
}

//��ȡ��С(���Դ�С)
size_t vec_bitset::size() {
	return bits_size;
}

//���� 1 �ĸ���
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

//�������λ 1 ���±꣬û�� 1 ���� -1
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

//�������λ 1 ���±꣬û�� 1 ���� -1
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

//ת����ʮ�����ַ���
std::string vec_bitset::to_string() {

	size_t str_len = (size_t)bits_size * LOG10_2 + 1;
	std::string initial_str(str_len, '0'); // ����һ���� '0' ��ɵ��ַ���
	std::string temp_str_pri;
	std::string temp_str_bina(str_len, '0'); // ��¼��ǰ��������
	short pri_ = 0, fro_ = 0;
	for (size_t p_index = 0; p_index < bits_size; p_index++) {
		int tim = 0;  //��¼��i֮ǰ�������Ƴ���1���±�

		if (this->get(p_index)) {

			// ���㵱ǰλ��ʮ�����µ� 2^i
			if (tim == 0) {//�״ζ����Ƴ���1
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
			//���˶��Ĵη����뵽 initial_str ��
			for (size_t j = 0; j < str_len; j++) {
				pri_ = (temp_str_bina[j] - '0') + (initial_str[j] - '0');
				pri_ += fro_;
				fro_ = pri_ / 10;
				pri_ = pri_ % 10;
				initial_str[j] = pri_ + '0';
			}
		}
	}

	//ɾȥ�������
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

//����2��val�η���ʮ��������ʹ��string���沢����
std::string vec_bitset::binary_val(const unsigned val) {
	size_t str_size = (size_t)val * LOG10_2 + 1;
	std::string decimal(str_size, '0'); // ��ʼʮ������Ϊ 0 
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

//��ת���е�λ
void vec_bitset::flip() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).flip();
	}
}

//���ñ��أ�ȫΪ 1
void vec_bitset::set() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).set();
	}
}

//���ñ��أ���һ������Ϊ�±꣬�ڶ���Ϊ����Ϊ 1 ���� 0��Ĭ�� 1
void vec_bitset::set(size_t pos, bool value) {
	if (pos >= bits_size) {
		printf("�±�Խ�磡\n");
		system("pause"); exit(0);
	}
	else {
		size_t vec_pos = pos / VEC_BITSET_BITLEN, bit_pos = pos % VEC_BITSET_BITLEN;
		bits.at(vec_pos).set(bit_pos, value);
	}
}

//�����ñ��أ�ȫΪ 0
void vec_bitset::reset() {
	for (size_t index = 0; index < vec_size; index++) {
		bits.at(index).reset();
	}
}

//�����ñ��أ���һ������Ϊ�±꣬�ڶ���Ϊ����Ϊ 1 ���� 0��Ĭ�� 1
void vec_bitset::reset(size_t pos) {
	if (pos >= bits_size) {
		printf("�±�Խ�磡\n");
		system("pause"); exit(0);
	}
	else {
		size_t vec_pos = pos / VEC_BITSET_BITLEN, bit_pos = pos % VEC_BITSET_BITLEN;
		bits.at(vec_pos).reset(bit_pos);
	}
}

//��ȡ��λ
bool vec_bitset::get(size_t pos) {
	if (pos >= bits_size) {
		printf("�±�Խ�磡\n");
		system("pause"); exit(0);
	}
	return bits.at(pos / VEC_BITSET_BITLEN)[pos % VEC_BITSET_BITLEN];
}

//���ظ�ֵ�����
vec_bitset& vec_bitset::operator =(const vec_bitset& other) {
	this->bits_size = other.bits_size;
	this->vec_size = other.vec_size;
	for (size_t vec_index = 0; vec_index < other.vec_size; vec_index++) {
		this->bits.at(vec_index) = other.bits.at(vec_index);
	}
	return *this;
}

//����[]�������޸ģ�
bool vec_bitset::operator[](size_t pos) {
	return this->get(pos);
}

//���ذ�λ�� &
vec_bitset vec_bitset::operator&(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit�鳤�Ȳ�һ�£��޷���λ�� &\n");
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

//���ذ�λ�� |
vec_bitset vec_bitset::operator|(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit�鳤�Ȳ�һ�£��޷���λ�� |\n");
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

//���ذ�λ��� ^
vec_bitset vec_bitset::operator^(const vec_bitset& other) const {
	if (this->bits_size != other.bits_size) {
		printf("bit�鳤�Ȳ�һ�£��޷���λ��� ^\n");
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

//���� 1 ������
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

//vec_bitset���ʵ��-------------------------------------------------------------------------------------




