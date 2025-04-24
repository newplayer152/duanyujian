#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Student {
    std::string name;
    int score;
};
//PrintStudentFunctor();
struct PrintStudentFunctor {
    //函数对象的用法
    void operator()(const Student& student) const {
        std::cout << "Name: " << student.name << ", Score: " << student.score << std::endl;
    }
};
//寻找分数大于60分的人
struct ScoreGreaterThan60Functor {
    bool operator()(const Student& student) const {
        return student.score >= 60;
    }
};

//求总分数
struct SumScore {
    int operator()(int& sum, const Student& student) const {
        return sum + student.score;
    }
};


//比较两个分数的大小(升序)
struct CompareByScoreFunctor {//在 std::max_element 的上下文中，“最大”的元素是使得比较函数对象对于该元素和范围内的其他所有元素都返回 false 的元素。
    bool operator()(const Student& student1, const Student& student2) const {
        return student1.score < student2.score;//如果返回true我就拿返回true的元素  
    }
};


//比较两个分数的大小(降序)
struct CompareByScoreDown {
    bool operator()(const Student& student1, const Student& student2) const {
        return student1.score > student2.score;
    }
};

int main()
{
    std::vector<Student> students = {
        {"Alice", 85},
        {"Bob", 72},
        {"Charlie", 90},
        {"David", 68},
        {"Eve", 77}
    };

    // 输出每个学生的姓名和分数
    std::cout << "Students:" << std::endl;
    std::for_each(students.begin(), students.end(), PrintStudentFunctor());
    std::cout << std::endl;

    // 统计分数大于等于60分的学生人数
    int passedCount = std::count_if(students.begin(), students.end(), ScoreGreaterThan60Functor());
    std::cout << "Number of students passed: " << passedCount << std::endl;

    // 找到分数最高的学生  //在 std::max_element 的上下文中，“最大”的元素是使得比较函数对象对于该元素和范围内的其他所有元素都返回 false 的元素。
    std::vector<Student>::iterator maxElement = std::max_element(students.begin(), students.end(),//可认为排序后取最后元素
        CompareByScoreFunctor());
    std::cout << "Max score: " << maxElement->score << ", Student: " << maxElement->name << std::endl;


    //算法计算所有学生的总分，并输出结果
    int sumScore = std::accumulate(students.begin(), students.end(), 0,SumScore());
    std::cout << "Student sum sorce:" << sumScore<<std::endl;

    //算法对学生按照分数进行降序排序，并输出排序后的学生信息（姓名和分数）
    std::sort(students.begin(), students.end(), CompareByScoreDown());
    std::cout << "Sorted students:" << std::endl;
    std::for_each(students.begin(), students.end(), PrintStudentFunctor());
    std::cout << std::endl;
    return 0;
}