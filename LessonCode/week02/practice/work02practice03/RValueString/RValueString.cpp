
#include <iostream>


class KString {
public:
    KString() :m_data(nullptr), m_size(0) {}; //变量都初始化为0
    //堆区申请len个空间,把str字符串内容给m_data,并设置长度
    KString(const char* str, int len) {
        m_data = new char[len + 1];
        for (int i = 0; i < len; i++) {
            m_data[i] = str[i];
        }
        m_data[len] = '\0';
        m_size = len;
    }
    KString(KString&& str) noexcept: m_data(str.m_data), m_size(str.m_size){
        str.m_data = nullptr;//避免悬空
        str.m_size = 0;
    };
    ~KString(){
        delete [] m_data;
    };
    char* getString() {
        return m_data;
    };

private:
    char* m_data;
    int m_size;
};

int main()
{
    KString  str1("hello",5);
    KString  str2 = std::move(str1);

    std::cout << str2.getString();
   

}


