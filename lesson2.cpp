// 【要求】
// 1. 创建 vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6}
// 2. 用 lambda 配合 std::sort 实现降序排序，打印结果
// 3. 用 lambda 配合 std::sort 实现 "偶数在前、奇数在后，同类内部升序 "，打印结果
// 4. 用 std::count_if + lambda 统计大于4的元素个数并打印

// 【预期输出】
// 降序 : 9 6 5 4 3 2 1 1 分类 : 2 4 6 1 1 3 5 9 大于4的个数 : 3

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

    // 1.降序排序 : 如果 a > b，则 a 排在前面
    // 另外这个sort是 C++ STL 的核心设计思想——策略模式（把算法和策略分离），使用者只关注抽象
    // sort 文档详见：https://zh.cppreference.com/w/cpp/algorithm/sort.html：
    // comparison function object (i.e. an object that satisfies the requirements of Compare)
    // which returns ​true if the first argument is less than (i.e. is ordered before) the second.
    std::sort(v.begin(), v.end(), [](int a, int b)
              { return a > b; });
    std::cout << "降序: ";
    for (auto i : v)
    {
        std::cout << i << " ";
    };
    std::cout << std::endl;

    // 2."偶数在前、奇数在后，同类内部升序 "
    /*
    逻辑判断：
        1).偶数优先，奇数在后(a%2=0 , b%2=1)
        2).数值小者在前(a<b)
    */
    std::sort(v.begin(), v.end(), [](int a, int b)
              {
        if(a % 2 != b % 2){//所选二者一奇一偶：偶数排前
            return a % 2 < b % 2;
        } 
        return a < b; }); // 所选二者同为奇偶：数值小者在前

    std::cout << "分类: ";
    for (int n : v)
        std::cout << n << " ";
    std::cout << std::endl;

    // 3.统计大于4的元素个数并打印
    int count = std::count_if(v.begin(), v.end(), [](int n)
                              { return n > 4; });
    std::cout << "大于4的个数: " << count << std::endl;
    return 0;
}