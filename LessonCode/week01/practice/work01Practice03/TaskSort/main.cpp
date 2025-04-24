
#include<iostream>
#include"task.h"
#include"scheduler.h"


int main() {
  
    Scheduler scheduler;

    // 添加任务
    scheduler.addTask(Task("Task A", 30, 2));
    scheduler.addTask(Task("Task B", 15, 3));
    scheduler.addTask(Task("Task C", 45, 1));
    scheduler.addTask(Task("Task D", 20, 2));
    scheduler.addTask(Task("Task E", 25, 4));

    // 输出未排序的任务列表
    std::cout << "Unsorted Tasks:" << std::endl;
    scheduler.printTasks();

    // 调用 sortTasks() 方法对任务进行排序
    scheduler.sortTasks();

    // 输出排序后的任务列表
    std::cout << "\nSorted Tasks:" << std::endl;
    scheduler.printTasks();

    //设计lambda表达式，输出scheduler中优先级 >2 的所有任务信息
    auto lambda = [](const std::vector<Task>& m_tasks)->void {
        for (const auto& task : m_tasks) {
            if (task.getPriority() <= 2)continue;
            std::cout << "Task Name: " << task.getName()
                << ", Duration: " << task.getDuration()
                << ", Priority: " << task.getPriority() << std::endl;
        }
    };
    std::cout << "\nSorted Tasks > 2:" << std::endl;
    lambda(scheduler.getTask());

    return 0;
}

