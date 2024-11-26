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
#define MULTI_FFT_CHOICE 0x40 // 高精度字符串乘法的FFT算法选择阈值
#define PI 0x1.921fb54442d18p+1 // PI的十六进制宏定义
#define HEX_10_pow_19 0x8ac7230489e80000 // 10^19的十六进制值


// 宏定义部分*************************************************************************************************************
//***********************************************************************************************************************

#define VEC_BITSET_BITLEN 512 //用于vec_bitset类，vec_bitset组中的单个bitset的长度
#define LOG10_2 0.30102999    //用于估计二进制和十进制转换时的估位


//***********************************************************************************************************************
//***********************************************************************************************************************


// vec_bitset类
// 实现可动态分配的二进制串，主要用于规避bitset组太长的情况
class vec_bitset {
private:
	std::vector<std::bitset<VEC_BITSET_BITLEN>> bits;
	size_t bits_size; //比特位长度（绝对长度）
	size_t vec_size;  //向量组长度（绝对长度）

public:

	//构造函数
	vec_bitset();
	vec_bitset(const size_t size);
	vec_bitset(const std::string val);
	/*vec_bitset(const short val);
	vec_bitset(const int val);
	vec_bitset(const long int val);
	vec_bitset(const unsigned short int val);
	vec_bitset(const unsigned val);
	vec_bitset(const unsigned long int val);*/
	//拷贝构造函数
	vec_bitset(const vec_bitset& other);


	//性质和转换操作
	//获取大小
	size_t size();
	//返回 1 的个数
	size_t count();
	//返回最高位的 1 的下标，没有 1 返回 -1
	int top();
	//返回最低位的 1 的下标，没有 1 返回 -1
	int base();
	//转换成字符
	std::string to_string();
	std::string binary_val(const unsigned val);



	//比特操作
	//设置比特
	void set();
	void set(size_t pos, bool value = true);
	//重设置比特
	void reset();
	void reset(size_t pos);
	//翻转
	void flip();
	//获取
	bool get(size_t pos);

	//重载和逻辑操作
	//重载赋值运算符
	vec_bitset& operator = (const vec_bitset& other);
	//重载[] (无法修改)
	bool operator [](size_t pos);
	//重载按位与 &
	vec_bitset operator& (const vec_bitset& other) const;
	//重载按位或 |
	vec_bitset operator| (const vec_bitset& other) const;
	//重载按位异或 ^
	vec_bitset operator^ (const vec_bitset& other) const;
	//存在 1 返回真
	bool any();
};



#endif#pragma once
