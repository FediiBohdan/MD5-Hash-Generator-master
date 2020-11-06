#include <string>  
#include <iostream>  
using namespace std;
class MD5  
{  
public:
    MD5();
    MD5(const string& text);
    void update(const unsigned char *buf, unsigned int length);
    void update(const char *buf, unsigned int length);
    MD5& Result();
    string hexcipher16() const;
    string Hexcipher16() const;
    string hexcipher32() const;
    string Hexcipher32() const;
    friend ostream& operator<<(ostream&, MD5 md5);

    typedef unsigned char uint1;
    typedef unsigned int uint4;  //
    
    void transform(const uint1 block[64]);
    void decode(uint4 output[], const uint1 input[], unsigned int len);
    void encode(uint1 output[], const uint4 input[], unsigned int len);
    
    bool Resulted;
    uint1 buffer[64];//64bit char=512bit 每个分组
    uint4 count[2];
    uint4 state[4];//4个寄存器
    uint1 cipher[16];//16bit char =512bit 密文
    
    inline uint4 F(uint4 x, uint4 y, uint4 z);
    inline uint4 G(uint4 x, uint4 y, uint4 z);
    inline uint4 H(uint4 x, uint4 y, uint4 z);
    inline uint4 I(uint4 x, uint4 y, uint4 z);
    inline uint4 Rotate(uint4 x, int n);
    inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

string md5(string str);
