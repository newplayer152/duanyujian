#include <iostream>
#include <algorithm>
#include <map>  
#include <vector>  


std::map<std::string, double> averageMapValues(const std::map<std::string, std::vector<int>>& data) {
    std::map<std::string, double> averages;

    for (const auto& kv : data) {
        const std::string& key = kv.first;
        const std::vector<int>& values = kv.second;

        // 非空检查
        if (!values.empty()) {
            auto average = [values]() -> double {//lambda函数求平均
                auto sum = 0;
                for (auto value : values) {
                    sum += value;
                }
                return static_cast<double>(sum) / values.size();
            };

            averages[key] = average();
        }
        else {
            averages[key] = 0.0;  // 空的话加0  
        }
    }

    return averages;
}

int main() {
    std::map<std::string, std::vector<int>> data = {//例子
        {"a", {1, 2, 3}},
        {"b", {4, 5, 6}},
        {"d", {7, 8, 9}}
    };

    std::map<std::string, double> averages = averageMapValues(data);

    for (const auto& kv : averages) {// 输出结果
        std::cout << "\"" << kv.first << "\"," << kv.second << std::endl;
    }

    return 0;
}

