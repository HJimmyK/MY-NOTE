#ifndef MY_MATH
#define MY_MATH

#include<vector>
#include<bitset>
#include<string>


#define STR_2_POW_0 "1"
#define STR_2_POW_1 "2"
#define STR_2_POW_2 "4"
#define STR_2_POW_3 "8"
#define STR_2_POW_4 "61"
#define STR_2_POW_5 "23"
#define STR_2_POW_6 "46"
#define STR_2_POW_7 "821"
#define STR_2_POW_8 "652"
#define STR_2_POW_9 "215"
#define STR_2_POW_10 "4201"
#define STR_2_POW_11 "8402"
#define STR_2_POW_12 "6904"
#define STR_2_POW_13 "2918"
#define STR_2_POW_14 "48361"
#define STR_2_POW_15 "86723"
#define STR_2_POW_16 "63556"
#define STR_2_POW_17 "270131"
#define STR_2_POW_18 "441262"
#define STR_2_POW_19 "882425"
#define STR_2_POW_20 "6758401"
#define STR_2_POW_21 "2517902"
#define STR_2_POW_22 "4034914"
#define STR_2_POW_23 "8068838"
#define STR_2_POW_24 "61277761"
#define STR_2_POW_25 "23445533"
#define STR_2_POW_26 "46880176"
#define STR_2_POW_27 "827712431"
#define STR_2_POW_28 "654534862"
#define STR_2_POW_29 "219078635"
#define STR_2_POW_30 "4281473701"
#define STR_2_POW_31 "8463847412"
#define STR_2_POW_32 "6927694924"

#define VEC_BITSET_BITLEN 512
#define LOG10_2 0.30102999
#define MULTI_FFT_CHOICE 0x40 // �߾����ַ����˷���FFT�㷨ѡ����ֵ
#define PI 0x1.921fb54442d18p+1 // PI��ʮ�����ƺ궨��
#define HEX_10_pow_19 0x8ac7230489e80000 // 10^19��ʮ������ֵ


// �궨�岿��*************************************************************************************************************
//***********************************************************************************************************************

#define VEC_BITSET_BITLEN 512 //����vec_bitset�࣬vec_bitset���еĵ���bitset�ĳ���
#define LOG10_2 0.30102999    //���ڹ��ƶ����ƺ�ʮ����ת��ʱ�Ĺ�λ


//***********************************************************************************************************************
//***********************************************************************************************************************


// vec_bitset��
// ʵ�ֿɶ�̬����Ķ����ƴ�����Ҫ���ڹ��bitset��̫�������
class vec_bitset {
private:
	std::vector<std::bitset<VEC_BITSET_BITLEN>> bits;
	size_t bits_size; //����λ���ȣ����Գ��ȣ�
	size_t vec_size;  //�����鳤�ȣ����Գ��ȣ�

public:

	//���캯��
	vec_bitset();
	vec_bitset(const size_t size);
	vec_bitset(const std::string val);
	/*vec_bitset(const short val);
	vec_bitset(const int val);
	vec_bitset(const long int val);
	vec_bitset(const unsigned short int val);
	vec_bitset(const unsigned val);
	vec_bitset(const unsigned long int val);*/
	//�������캯��
	vec_bitset(const vec_bitset& other);


	//���ʺ�ת������
	//��ȡ��С
	size_t size();
	//���� 1 �ĸ���
	size_t count();
	//�������λ�� 1 ���±꣬û�� 1 ���� -1
	int top();
	//�������λ�� 1 ���±꣬û�� 1 ���� -1
	int base();
	//ת�����ַ�
	std::string to_string();
	std::string binary_val(const unsigned val);



	//���ز���
	//���ñ���
	void set();
	void set(size_t pos, bool value = true);
	//�����ñ���
	void reset();
	void reset(size_t pos);
	//��ת
	void flip();
	//��ȡ
	bool get(size_t pos);

	//���غ��߼�����
	//���ظ�ֵ�����
	vec_bitset& operator = (const vec_bitset& other);
	//����[] (�޷��޸�)
	bool operator [](size_t pos);
	//���ذ�λ�� &
	vec_bitset operator& (const vec_bitset& other) const;
	//���ذ�λ�� |
	vec_bitset operator| (const vec_bitset& other) const;
	//���ذ�λ��� ^
	vec_bitset operator^ (const vec_bitset& other) const;
	//���� 1 ������
	bool any();
};



#endif#pragma once
