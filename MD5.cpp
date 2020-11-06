#include "MD5.h"    
#include <stdio.h>  
  
// F, G, H, I 函数表达式
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {  
	return (x & y) | (~x & z);  
}  
  
inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {  
	return (x & z) | (y & ~ z);  
}  
  
inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {  
	return (x ^ y ^ z);  
}  
  
inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {  
	return y ^ (x | ~ z);  
}  
  
//左移,用于每步运算
inline MD5::uint4 MD5::Rotate(uint4 x, int n) {
	return (x << n) | (x >> (32-n));  
}  
  
//FF, GG, HH, II 函数式
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = Rotate(a+ F(b,c,d) + x + ac, s) + b;  
}  
  
inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {  
	a = Rotate(a + G(b,c,d) + x + ac, s) + b;  
}  
  
inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {  
	a = Rotate(a + H(b,c,d) + x + ac, s) + b;  
}  
  
inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {  
	a = Rotate(a + I(b,c,d) + x + ac, s) + b;  
}  
   
MD5::MD5()  
{  
	Resulted=false;  
  
	count[0] = 0;  
	count[1] = 0;  

	state[0] = 0x67452301;  //已进行过大小端转换
	state[1] = 0xefcdab89;  
	state[2] = 0x98badcfe;  
	state[3] = 0x10325476;  
}  
  
MD5::MD5(const string &text)  
{  
	Resulted=false;  
	  
	count[0] = 0;  
	count[1] = 0;  

	state[0] = 0x67452301;  
	state[1] = 0xefcdab89;  
	state[2] = 0x98badcfe;  
	state[3] = 0x10325476; 
	update(text.c_str(), text.length());  
	Result();  
}
  
//将64个char输入转16个int(分组)输出(同时进行大小端转换）
void MD5::decode(uint4 output[], const uint1 input[], unsigned int len)  
{  
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)  
		output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |  
		(((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);  
}
  
//将32bit每个的int输入以8bit间隔存储(同时进行大小端转换)
void MD5::encode(uint1 output[], const uint4 input[], unsigned int len)  
{  
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {  
		output[j] = input[i] & 0xff;  
		output[j+1] = (input[i] >> 8) & 0xff;  
		output[j+2] = (input[i] >> 16) & 0xff;  
		output[j+3] = (input[i] >> 24) & 0xff;  
	}  
}  

  
//四轮运算，代入64位char即512 bit
void MD5::transform(const uint1 block[64])  
{  
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];  
	decode (x, block, 64);  
  
    //ROUND1
	FF (a, b, c, d, x[ 0], 7, 0xd76aa478);   
	FF (d, a, b, c, x[ 1], 12, 0xe8c7b756);   
	FF (c, d, a, b, x[ 2], 17, 0x242070db);   
	FF (b, c, d, a, x[ 3], 22, 0xc1bdceee);  
	FF (a, b, c, d, x[ 4], 7, 0xf57c0faf);  
	FF (d, a, b, c, x[ 5], 12, 0x4787c62a);   
	FF (c, d, a, b, x[ 6], 17, 0xa8304613);   
	FF (b, c, d, a, x[ 7], 22, 0xfd469501);   
	FF (a, b, c, d, x[ 8], 7, 0x698098d8);  
	FF (d, a, b, c, x[ 9], 12, 0x8b44f7af);   
	FF (c, d, a, b, x[10], 17, 0xffff5bb1);   
	FF (b, c, d, a, x[11], 22, 0x895cd7be);  
	FF (a, b, c, d, x[12], 7, 0x6b901122);  
	FF (d, a, b, c, x[13], 12, 0xfd987193);  
	FF (c, d, a, b, x[14], 17, 0xa679438e);   
	FF (b, c, d, a, x[15], 22, 0x49b40821);
  
    //ROUND2
	GG (a, b, c, d, x[ 1], 5, 0xf61e2562);   
	GG (d, a, b, c, x[ 6], 9, 0xc040b340);   
	GG (c, d, a, b, x[11], 14, 0x265e5a51); 
	GG (b, c, d, a, x[ 0], 20, 0xe9b6c7aa);   
	GG (a, b, c, d, x[ 5], 5, 0xd62f105d);   
	GG (d, a, b, c, x[10], 9,  0x2441453);   
	GG (c, d, a, b, x[15], 14, 0xd8a1e681);   
	GG (b, c, d, a, x[ 4], 20, 0xe7d3fbc8);   
	GG (a, b, c, d, x[ 9], 5, 0x21e1cde6);  
	GG (d, a, b, c, x[14], 9, 0xc33707d6);   
	GG (c, d, a, b, x[ 3], 14, 0xf4d50d87);   
	GG (b, c, d, a, x[ 8], 20, 0x455a14ed);  
	GG (a, b, c, d, x[13], 5, 0xa9e3e905);   
	GG (d, a, b, c, x[ 2], 9, 0xfcefa3f8);  
	GG (c, d, a, b, x[ 7], 14, 0x676f02d9);  
	GG (b, c, d, a, x[12], 20, 0x8d2a4c8a);
  
    //ROUND3
	HH (a, b, c, d, x[ 5], 4, 0xfffa3942);   
	HH (d, a, b, c, x[ 8], 11, 0x8771f681); 
	HH (c, d, a, b, x[11], 16, 0x6d9d6122);
    HH (b, c, d, a, x[14], 23, 0xfde5380c);
	HH (a, b, c, d, x[ 1], 4, 0xa4beea44);   
	HH (d, a, b, c, x[ 4], 11, 0x4bdecfa9);
    HH (c, d, a, b, x[ 7], 16, 0xf6bb4b60);
    HH (b, c, d, a, x[10], 23, 0xbebfbc70);
	HH (a, b, c, d, x[13], 4, 0x289b7ec6);   
	HH (d, a, b, c, x[ 0], 11, 0xeaa127fa);   
	HH (c, d, a, b, x[ 3], 16, 0xd4ef3085);
	HH (b, c, d, a, x[ 6], 23,  0x4881d05);
	HH (a, b, c, d, x[ 9], 4, 0xd9d4d039);
	HH (d, a, b, c, x[12], 11, 0xe6db99e5);
	HH (c, d, a, b, x[15], 16, 0x1fa27cf8);
	HH (b, c, d, a, x[ 2], 23, 0xc4ac5665);
  
    //ROUND4
	II (a, b, c, d, x[ 0], 6, 0xf4292244);   
	II (d, a, b, c, x[ 7], 10, 0x432aff97);  
	II (c, d, a, b, x[14], 15, 0xab9423a7); 
	II (b, c, d, a, x[ 5], 21, 0xfc93a039); 
	II (a, b, c, d, x[12], 6, 0x655b59c3); 
	II (d, a, b, c, x[ 3], 10, 0x8f0ccc92); 
	II (c, d, a, b, x[10], 15, 0xffeff47d);  
	II (b, c, d, a, x[ 1], 21, 0x85845dd1); 
	II (a, b, c, d, x[ 8], 6, 0x6fa87e4f);   
	II (d, a, b, c, x[15], 10, 0xfe2ce6e0);  
	II (c, d, a, b, x[ 6], 15, 0xa3014314);
    II (b, c, d, a, x[13], 21, 0x4e0811a1);
	II (a, b, c, d, x[ 4], 6, 0xf7537e82);
	II (d, a, b, c, x[11], 10, 0xbd3af235);
	II (c, d, a, b, x[ 2], 15, 0x2ad7d2bb);
	II (b, c, d, a, x[ 9], 21, 0xeb86d391);
  
	state[0] += a;  
	state[1] += b;  
	state[2] += c;  
	state[3] += d;  
   
}  

//更新消息组
void MD5::update(const unsigned char input[], unsigned int length)
{
    unsigned int index = count[0] >> 3 & 0x3F;  //求长度模64(one block)字节的余数
   
    if ((count[0] += (length *8)) < (length *8))//防止字节数溢出
        count[1]++;
    count[1] += (length >> 29); //先左移3位求出比特数，再右移32位求出左32位
  
    unsigned int firstpart = 64 - index;//第一块要填充的长度(字节),第一次总是64
  
	unsigned int i;  
    
	if (length >= firstpart)  
	{
		memcpy(&buffer[index], input, firstpart);  
		transform(buffer);  
        //持续读入block
		for (i = firstpart; i + 64 <= length; i += 64)  
			transform(&input[i]);
  
		index = 0;  
	}  
	else  
		i = 0;  
    //把最后一部分也读进去
	memcpy(&buffer[index], &input[i], length-i);  
}  
  
void MD5::update(const char input[], unsigned int length)
{  
	update((const unsigned char*)input, length);  
}

//生成最终密文
MD5& MD5::Result()  
{  
    //填充
    unsigned char padding[64] = { 0x80 };

	if (!Resulted) {
		unsigned char bits[8];  
        //将长度（的最后64bit）存储起来附加
        encode(bits, count, 8);

        unsigned int index = count[0] >> 3 & 0x3F;
        //添加的长度若448以下则添加到448，否则多附加一个512Bit
        unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);
        //更新填充
        update(padding, padLen);
        //更新长度
		update(bits, 8);  
        //将128bit散列值转化为16字节char
		encode(cipher, state, 16);
        
		Resulted=true;  
	}  
  
	return *this;  
}  

//将cipher数组中存储结果链接为字符串加入输出流
string MD5::hexcipher16() const
{
    if (!Resulted)
        return "";

    char buf[17];
    for (int i=4; i<12; i++)
        sprintf(buf+(i-4)*2, "%02x", cipher[i]);
    buf[16]=0;

    return string(buf);
}

string MD5::Hexcipher16() const
{
    if (!Resulted)
        return "";

    char buf[17];
    for (int i=4; i<12; i++)
        sprintf(buf+(i-4)*2, "%02X", cipher[i]);
    buf[16]=0;

    return string(buf);
}

string MD5::hexcipher32() const
{  
	if (!Resulted)  
		return "";  
  
	char buf[33];  
	for (int i=0; i<16; i++)  
        sprintf(buf+i*2, "%02x", cipher[i]);
	buf[32]=0;  
  
	return string(buf);
}

string MD5::Hexcipher32() const
{
    if (!Resulted)
        return "";

    char buf[33];
    for (int i=0; i<16; i++)
        sprintf(buf+i*2, "%02X", cipher[i]);
    buf[32]=0;

    return string(buf);
}

  
ostream& operator<<(ostream& out, MD5 md5)  
{  
    return out << md5.Hexcipher32();
}
  
string md5(const string str)  
{  
	MD5 md5 = MD5(str);  
  
    return md5.Hexcipher32();
}  
