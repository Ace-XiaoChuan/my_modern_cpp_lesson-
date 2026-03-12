// 先读懂这段"问题代码"，然后改写
/*class Student
{
public:
    string name;
    int age;
    Student(string n, int a) : name(n), age(a)
    {
        cout << name << " 构造" << endl;
    }
    ~Student()
    {
        cout << name << " 析构" << endl;
    }
};

int main()
{
    Student *s1 = new Student("Alice", 20);
    Student *s2 = new Student("Bob", 21);
    // 假设这里抛了异常...
    // throw runtime_error("oops");
    delete s1;
    delete s2;
}
*/
/*
【要求】
1. 用 unique_ptr 改写上面代码（用 make_unique）
2. 去掉所有 delete
3. 取消注释 throw 那行，验证即使异常也能正确析构
4. 尝试把 unique_ptr 赋值给另一个变量，观察编译错误
5. 用 std::move 转移所有权，打印转移后原指针是否为空

【预期输出】
Alice 构造
Bob 构造
s1是否为空: 1
Bob 析构
Alice 析构
*/
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

using namespace std;

class Student
{
public:
    string name;
    int age;

    // 成员初始化列表
    Student(string n, int a) : name(n), age(a)
    {
        cout << name << " 构造" << endl;
    }
    ~Student()
    {
        cout << name << " 析构" << endl;
    }
};

int main()
{
    try
    {
        auto s1 = make_unique<Student>("Alice", 20);
        auto s2 = make_unique<Student>("Bob", 21);
        // 4. 尝试赋值（取消下面注释会编译报错，因为 unique_ptr 不允许拷贝）
        // unique_ptr<Student> s3 = s1;
        // 5.使用std::move 转移所有权
        unique_ptr<Student> s1_new = move(s1);
        cout << "s1是否为空: " << (s1 == nullptr) << endl;
        // 3. 模拟异常：即使抛出异常，s1_new 和 s2 也会在 try 块结束时自动析构
        // 错误分两类：编译时错误、运行时错误，
        // runtime_error 就是专门为了应对后面这种“只有跑起来才会发生”的突发状况而设计的。

        throw runtime_error("oops");
        // 2. 去掉了所有 delete
    }
    catch (const exception &e)
    {
    }
    return 0;
}