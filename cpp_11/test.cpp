#include <iostream>

using namespace std;

#include<array>
#include<vector>
#include<list>
#include<string>
#include<map>

#include<assert.h>

struct Point
{
	int _x;
	int _y;
};

class A
{
public:
	//explicit A(int x, int y) 禁止隐式类型转换发生
	A(int x, int y)
		: _x(x)
		, _y(y)
	{}

	A(int x)
		: _x(x)
		, _y(0)
	{}

private:
	int _x;
	int _y;
};

//int main()
//{
//	int array1[] = { 1,2,3,4,5 };
//	int array2[5] = { 0 };
//	int array3[5]{ 0 };
//
//	Point p = { 1,2 };
//
//	// 单参数的隐式类型转换
//	A aa2 = 1;
//	A aa4 = { 4 };
//	A aa5{ 5 };
//
//	// 多参数的隐式类型转换
//	A aa1 = { 2,2 };
//	A aa6{ 6,6 };
//
//	const A& aa3 = { 3,3 };
//
//	return 0;
//}

//int main()
//{
//	vector<int> v1;
//	vector<int> v2(10, 1);
//
//	// 构造
//	vector<int> v4({ 1,2,3,4,5 });
//
//	// 隐式类型转换
//	vector<int> v3 = { 1,2,3,4,5 };
//
//	auto il1 = { 10,20,30 };
//	initializer_list<int> il2 = { 10,20,30 };
//	cout << typeid(il1).name() << endl;
//	cout << sizeof(il1) << endl;
//	
//	pair<string, string> kv1 = { "hello", "world" };
//	pair<string, string> kv2 = { "void", "null" };
//	map<string, string> dict1 = { kv1, kv2 };
//
//	// 1. pair多参数隐式类型转换
//	// 2. initializer_list<pair>的构造
//	map<string, string> dict2 = { {"hello", "world"}, {"void", "null"} };
//
//	return 0;
//}

//int main()
//{
//	int i = 0;
//	auto x = i;
//	//auto& x = i;
//	x++;
//
//	int& j = i;
//	auto y = j;
//	auto& y = j;
//
//	return 0;
//}

//template <class T>
//class B
//{
//public:
//	T* New(int n)
//	{
//		return new T[n];
//	}
//};
//
//auto func1()
//{
//	list<int> lt;
//	auto ret = lt.begin();
//
//	return ret;
//}
//
//int main()
//{
//	list<int>::iterator it1;
//
//	// typeid推出的是一个单纯的字符串 -- 不能用来定义对象
//	cout << typeid(it1).name() << endl;
//
//	// 用来定义对象
//	decltype(it1) it2;
//	cout << typeid(it2).name() << endl;
//
//	auto it3 = it1;
//	cout << typeid(it3).name() << endl;
//
//	auto ret3 = func1();
//	B<decltype(ret3)> bb1;
//
//	map<string, string> dict2 = { {"hello", "world"}, {"void", "null"} };
//	auto it4 = dict2.begin();
//
//	B<decltype(it4)> bb2;
//
//	//auto和decltype有些时候增加代码可读性
//
//	return 0;
//}

//int main()
//{
//	array<int, 10> a1;
//	vector<int> a2(10, 0);
//
//	return 0;
//}

//int main()
//{
//	// 左值是一个表达式
//	// 左值和右值，能否取地址
//	// 左值：可以取地址
//	// 右值：不可以取地址
//	int a = 10;
//	int b = a;
//	const int c = 10;
//	int* p = &a;
//
//	int x = 1, y = 2;
//
//	// 右值引用，给右值取别名
//  // 纯右值 （内置类型）
//  // 将亡值 （自定义类型）
//	int&& rref1 = (x + y);
//	string&& rref2 = string("hello");
//	string&& rref3 = to_string(111);
//	int&& ref4 = 10;
//
//	// 左值能否给右值取别名 -- 不可以，但是const左值引用可以
//	const string& ref1 = string("hello");
//	const int& ref2 = 10;
//
//	// 右值引用能否给左值取别名 -- 不可以，但是可以通过std::move将左值转换为右值
//	string s1 = "hello";
//	string&& rref4 = move(s1);
//
//	return 0;
//}

// 右值引用意义
// 引用的意义是减少拷贝，提高效率

// 左值引用的场景
void func1(const string& s);
string& func2();
// 左值引用返回值的问题没有彻底解决，如果返回值是func2的局部对象，不能引用返回

int main()
{
	// 右值引用
	std::string&& s1 = std::string("hello");
	// s1是左值（右值引用本身是左值）-- 右值引用属性是左值 意义-> 为了移动构造移动赋值，转移资源的语法逻辑自洽
	// 只有右值引用本身处理成左值，才能实现移动构造和移动赋值，转移资源
	cout << &s1 << endl;
	//cout<<&std::string("hello")<<endl; // 不能取地址

	std::string& s2 = s1;
	
	//std::string& s3 = (std::string&)std::string("hello");
	std::string&& s3 = std::string("hello");
	std::string& s4 = s3;
	

	return 0;
}