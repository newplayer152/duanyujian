此目录存放课堂作业，可以在此文件添加作业题目、解题思路和对题目的看法

课堂练习：
==============01：练习：按照你的理解，请将下面代码改为RAII的方式，写一个伪代码出来。
int main() {

    FILE* fileHandle;
    std::string filename = "file.txt";
    fileHandle = fopen(filename.c_str(), "r");
    //read & write file
    fclose(fileHandle);
    return 0;
}

==============02：练习：大家自己设计一个模板类MySharedPtr类,要求实现shared_ptr引用计数的相关功能。

==============03：练习:
写一个简单的KString类。要求实现main函数中的功能。
class KString{
public:
KString(); //变量都初始化为0
//堆区申请len个空间,把str字符串内容给m_data,并设置长度
KString(const char *str,int len)
KString(KString&& str);
char * getString();
}
private: 
char *m_data; 
int m_size; 
} 
int main()
{ 
KString str1(“hello”);
KString str2 = std::move(str1);
cout << str2.getString();
} 

==============04：课堂练习：
要求自己实习一个简易的vecotr，不用实现动态扩容,实习下面main()函数的输出。【利用重载和模板的思想实现】

==============05：写一个代码实现下列功能:
有n只猴子，按顺时针方向围成一圈选大王（编号为1-n）,从第一号开始报数，一直数到m,数到m的猴子退出圈外，剩下的猴子再接着从1开始报数，就这样，直到圈中只剩下一只猴子时，这个猴子就是猴王。编程输入n,m后，输出最后猴王的编号。
例如：输入样例： 6 5
输出样例：5，4，6，2，3

==============06：题目：学生成绩统计 
描述：
你作为一名教师，需要统计学生的成绩并进行分析。请使用C++ STL中的算法来完成以下任务。完成上述未完成的功能。
任务：
1. 创建一个学生类(Student)，包含以下成员变量：
o std::string name：学生姓名
o int score：学生分数
2. 在 main 函数中创建一个 std::vector<Student> 容器，并添加至少5个学生对象。
3. 使用 std::for_each 算法和一个自定义的打印函数，输出每个学生的姓名和分数。
4. 使用 std::accumulate 算法计算所有学生的总分，并输出结果。
5. 使用 std::count_if 算法统计分数大于等于60分的学生人数，并输出结果。
6. 使用 std::max_element 算法找到分数最高的学生，并输出该学生的姓名和分数。
7. 使用 std::sort 算法对学生按照分数进行降序排序，并输出排序后的学生信息（姓名和分数）。

