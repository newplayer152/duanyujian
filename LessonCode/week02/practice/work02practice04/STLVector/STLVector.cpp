#include <iostream>
template <typename T>
class KVector
{
public:
    KVector(int len = 10);
    ~KVector();
    void push_back(const T& val);
    inline T pop_back();
    int size() const;

    T* begin();
    T* end();

    T operator[] (const int n);

protected:
    T* m_data;   //申请数组堆区空间的首地址
    T* start;    //保存数组的起始位置
    int m_len;         //数组的长度
    int pos;           //下一个数据要插入的位置,
};




template<typename T>
KVector<T>::KVector(int len)
{ 
    m_data = new int[len];
    m_len = len;
    start = m_data;
    pos = 0;
}

template<typename T>
KVector<T>::~KVector()
{
    if (m_len) {
        delete[] m_data;
    }
    m_data = nullptr;
    start = nullptr;
    m_len = 0;
    pos = 0;
}

template<typename T>
void KVector<T>::push_back(const T& val)
{
    *(start + pos++) = val;
}

template<typename T>
inline T KVector<T>::pop_back()
{
    if (pos<= 0) {
        std::cerr << "Not pop_back\n";
        return T();
    }
    return *(start + (--pos)); 
}

template<typename T>
int KVector<T>::size() const
{
    return m_len;
}

template<typename T>
T* KVector<T>::begin()
{
    return start;
}

template<typename T>
T* KVector<T>::end()
{
    return start+pos;
}

template<typename T>
T KVector<T>::operator[](const int n)
{
    if ((n>=pos) | (n<=0) ) {
        std::cerr << "Index Not Find\n";
        return T();
    }
    return *(start + n -1);
}

//template class KVector<int>;
int main()
{
    KVector<int> vt;

    for (int i = 0; i < vt.size(); ++i)
    {
        vt.push_back(i + 1);
    }

    std::cout << "pop_back = " << vt.pop_back() << std::endl;
    std::cout << "vt[3] = " << vt[3] << std::endl;
    for (auto it = vt.begin(); it != vt.end(); it++)
    {
        std::cout << *it << " ";
    }
    return 0;
}