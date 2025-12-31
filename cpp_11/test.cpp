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
//void func1(const string& s);
//string& func2();
// 左值引用返回值的问题没有彻底解决，如果返回值是func2的局部对象，不能引用返回

//int main()
//{
//	// 右值引用
//	std::string&& s1 = std::string("hello");
//	// s1是左值（右值引用本身是左值）-- 右值引用属性是左值 意义-> 为了移动构造移动赋值，转移资源的语法逻辑自洽
//	// 只有右值引用本身处理成左值，才能实现移动构造和移动赋值，转移资源
//	cout << &s1 << endl;
//	//cout<<&std::string("hello")<<endl; // 不能取地址
//
//	std::string& s2 = s1;
//	
//	//std::string& s3 = (std::string&)std::string("hello");
//	std::string&& s3 = std::string("hello");
//	std::string& s4 = s3;
//	
//
//	return 0;
//}

//void Func(int& x) { cout << "左值引用" << endl; }
//void Func(const int& x) { cout << "const 左值引用" << endl; }
//void Func(int&& x) { cout << "右值引用" << endl; }
//void Func(const int&& x) { cout << "const 右值引用" << endl; }
//
//// 函数模板 -- 万能引用 std::forward<T>(t)在传参的过程中保持了t的原生类型属性
//template <typename T>
//void PerfectForward(T&& t)
//{
//	//Func((T&&)t);
//	Func(std::forward<T>(t));
//}

//int main()
//{
//	PerfectForward(10); // 右值
//
//	int a;
//	PerfectForward(a); // 左值
//	PerfectForward(std::move(a)); // 右值
//
//	const int b = 20;
//	PerfectForward(b); // const 左值
//	PerfectForward(std::move(b)); // const 右值
//
//	return 0;
//}

#include <algorithm>

struct Goods
{
	string _name; // 名字
	double _price; // 价格
	int _evaluate; // 评价

	Goods(const char* str, double price, int evaluate)
		:_name(str)
		, _price(price)
		, _evaluate(evaluate)
	{}
};

struct ComparePriceLess
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price < gr._price;
	}
};

struct ComparePriceGreater
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price > gr._price;
	}
};

int main()
{
	vector<Goods> v = { { "苹果", 2.1, 5 }, { "香蕉", 3, 4 }, { "橙子", 2.2,
	3 }, { "菠萝", 1.5, 4 } };

	sort(v.begin(), v.end(), ComparePriceLess());
	sort(v.begin(), v.end(), ComparePriceGreater());

	auto priceLess = [](const Goods& g1, const Goods& g2) 
	{
		return g1._price < g2._price; 
	};

	sort(v.begin(), v.end(), priceLess);
	cout << typeid(priceLess).name() << endl;

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2) 
		{
			return g1._price < g2._price; 
		});

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._price > g2._price;
		});

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._evaluate < g2._evaluate;
		});

	sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2)
		{
			return g1._evaluate > g2._evaluate;
		});


	// lambda表达式 -- 匿名函数

	return 0;
}

//int main()
//{
//	// lambda
//	auto add1 = [](int a, int b)->int { return a + b; };
//	auto add2 = [](int a, int b){ return a + b; };
//	auto func1 = [] {cout << "hello" << endl; };
//
//	cout << add1(1, 2) << endl;
//	cout << add2(3, 4) << endl;
//	func1();
//
//	return 0;
//}

//int main()
//{
//	int a = 1, b = 2;
//	auto swap1 = [](int& x, int& y)
//	{
//		int tmp = x;
//		x = y;
//		y = tmp;
//	};
//
//	swap1(a, b);
//
//	// 捕捉a b对象给lambda
//	// mutable可以修改传值捕捉对象 -- 一般不常用
//	// a b是拷贝过来的 不改变外面的a b
//	auto swap2 = [a, b]() mutable
//	{
//			int tmp = a;
//			a = b;
//			b = tmp;
//	};
//
//	swap2();
//
//	// 引用方式捕捉
//	auto swap3 = [&a, &b]()
//	{
//		int tmp = a;
//		a = b;
//		b = tmp;
//	};
//
//	swap3();
//
//	return 0;
//}

//int main()
//{
//	int a = 1, b = 2, c = 3, d = 4;
//	auto func1 = [=]()
//	{
//		return a + b - c * d;
//	};
//
//	auto func2 = [&]()
//	{
//		++a;
//		++b;
//		++c;
//		++d;
//	};
//
//	// 混合捕捉，传引用捕捉所有对象，但是c d传值捕捉
//	auto func3 = [&, c, d]
//	{
//		++a;
//		++b;
//		//++c; // error
//		//++d; // error
//	};
//
//	return 0;
//}
//
//class HeapOnly
//{
//public:
//	static HeapOnly* CreateObj()
//	{
//		return new HeapOnly;
//	}
//
//	// C++11
//	HeapOnly(const HeapOnly&) = delete;
//
//	// C++98 私有+只声明不实现
//private:
//	//HeapOnly(const HeapOnly&);
//
//	HeapOnly()
//	{}
//	
//	int _a = 1;
//};
//
//int main()
//{
//	//HeapOnly ho1;
//	//HeapOnly* p1 = new HeapOnly;
//	HeapOnly* p2 = HeapOnly::CreateObj();
//
//	//不能被拷贝，才能禁止
//	HeapOnly obj(*p2);
//	
//	return 0;
//}

// 编译时，参数推导递归
void _Cpp_Printf()
{
	cout << endl;
}

template <class T, class ...Args>
void _Cpp_Printf(const T& val, Args... args)
{
	cout << val << endl;

	_Cpp_Printf(args...);
}

template <class ...Args>
void Cpp_Printf(Args... args)
{
	_Cpp_Printf(args...);
}

template <class T>
int PrintArg(T t)
{
	cout << t << " ";
	return 0;
}

template <class ...Args>
void Cpp_Printf2(Args... args)
{
	// 编译时推导，args...参数有几个值，PrintArg就会调用几次，就有几个返回值，arr就开多大
	int arr[] = { PrintArg(args)... };
	cout << endl;
}

#include <functional>

// 不是定义可调用对象，包装可调用对象

//int f(int a, int b)
//{
//	return a + b;
//}
//
//struct Functor
//{
//public:
//	int operator()(int a, int b)
//	{
//		return a + b;
//	}
//};
//
//int main()
//{
//	function<int(int, int)> fc1;
//
//	//function<int(int, int)> fc2(f);
//	function<int(int, int)> fc2 = f;
//	function<int(int, int)> fc3 = Functor();
//	function<int(int, int)> fc4 = [](int x, int y) { return x + y; };
//
//	cout << fc2(1, 2) << endl;
//	cout << fc3(3, 4) << endl;
//	cout << fc4(5, 6) << endl;
//
//	return 0;
//}

//class Plus
//{
//public:
//	static int plusi(int a, int b)
//	{
//		return a + b;
//	}
//
//	double plusd(double a, double b)
//	{
//		return a + b;
//	}
//};
//
//int main()
//{
//	// 成员函数的函数指针 &类型::函数名
//	function<int(int, int)> fc1 = &Plus::plusi;
//	cout << fc1(1, 2) << endl;
//
//	function<double(Plus*, double, double)> fc2 = &Plus::plusd;
//	Plus plus;
//	cout << fc2(&plus, 1.1, 2.2) << endl;
//
//	function<double(Plus, double, double)> fc3 = &Plus::plusd;
//	cout << fc3(Plus(), 1.1, 2.2) << endl;
//
//	return 0;
//}

//int Sub(int a, int b)
//{
//	return a - b;
//}

class Sub
{
public:
	int sub(int a, int b)
	{
		return a - b;
	}
};

void fx(const string& name, int x, int y)
{
	cout << name << "->[" << "血量：" << x << " 蓝：" << y << "]" << endl;
}

// 调整可调用对象的参数个数或者顺序

// int main()
// {
// 	//auto f1 = Sub;
// 	//cout << f1(10, 5) << endl;

// 	//// 调整顺序
// 	//auto f2 = bind(Sub, placeholders::_2, placeholders::_1);
// 	//cout << f2(10, 5) << endl;

// 	//cout << typeid(f1).name() << endl;
// 	//cout << typeid(f2).name() << endl;

// 	auto f3 = bind(&Sub::sub, placeholders::_1, placeholders::_2, placeholders::_3);
// 	cout << f3(Sub(), 10, 5) << endl;

// 	Sub sub;
// 	cout << f3(&sub, 10, 5) << endl;

// 	auto f4 = bind(&Sub::sub, Sub(), placeholders::_1, placeholders::_2);
// 	cout << f4(10, 5) << endl;

// 	auto f5 = bind(&Sub::sub, &sub, placeholders::_1, placeholders::_2);
// 	cout << f5(10, 5) << endl;

// 	fx("王昭君", 80, 20);
// 	fx("王昭君", 85, 10);
// 	fx("王昭君", 90, 0);
// 	fx("王昭君", 99, 99);

// 	fx("亚瑟", 99, 85);
// 	fx("亚瑟", 91, 80);
// 	fx("亚瑟", 5, 20);

// 	auto f6 = bind(fx, "王昭君", placeholders::_1, placeholders::_2);

// 	f6(80, 20);
// 	f6(85, 10);
// 	f6(90, 0);
// 	f6(99, 99);

// 	auto f7 = bind(fx, "亚瑟", placeholders::_1, placeholders::_2);

// 	f7(99, 85);
// 	f7(91, 80);
// 	f7(5, 20);
	

// 	return 0;
// }

#include<thread>
#include<mutex>
#include<atomic>
#include<condition_variable>

// void Print(int n, int i)
// {
// 	for (; i < n; i++)
// 	{
// 		cout << i << endl;
// 	}
//
// 	cout << endl;
// }

// int main()
// {
// 	thread t1(Print, 100, 0);
// 	thread t2(Print, 200, 100);

// 	cout << t1.get_id() << endl;
// 	cout << t2.get_id() << endl;

// 	t1.join();
// 	t2.join();

// 	cout << this_thread::get_id() << endl;

// 	return 0;
// }

//int x = 0;
//mutex mtx;
//void Print(int n, int& x, mutex& mtx)
//{
//	mtx.lock();
//
//	for (int i = 0; i < n; i++)
//	{
//		++x;
//	}
//
//	mtx.unlock();
//}
//
//int main()
//{
//	int x = 0;
//	mutex mtx;
//
//	thread t1(Print, 100, ref(x), ref(mtx));
//	thread t2(Print, 200, ref(x), ref(mtx));
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}

//int main()
//{
//	int x = 0;
//	mutex mtx;
//
//	thread t1([&] {
//
//		mtx.lock();
//		for (size_t i = 0; i < 10000; ++i)
//		{
//			++x;
//		}
//		mtx.unlock();
//
//		});
//
//	thread t2([&] {
//
//		mtx.lock();
//		for (size_t i = 0; i < 20000; ++i)
//		{
//			++x;
//		}
//		mtx.unlock();
//
//		});
//
//	t1.join();
//	t2.join();
//
//	cout << x << endl;
//
//	return 0;
//}

// class LockGuard
// {
// public:
// 	LockGuard(mutex& mtx)
// 		:_mtx(mtx)
// 	{
// 		_mtx.lock();
// 	}

// 	~LockGuard()
// 	{
// 		_mtx.unlock();
// 	}

// private:
// 	mutex& _mtx;
// };

// //int main()
// //{
// //	vector<thread> vthd;
// //	int n;
// //	cin >> n;
// //
// //	vthd.resize(n);
// //
// //	atomic<int> x = 0;
// //	//int x = 0;
// //	mutex mtx;
// //
// //	auto func = [&](int n) {
// //		//mtx.lock();
// //		// 局部域
// //		{
// //			//LockGuard lock(mtx);
// //			//lock_guard<mutex> lock(mtx);
// //			for (size_t i = 0; i < n; ++i)
// //			{
// //				++x;
// //			}
// //			//mtx.unlock();
// //		}
// //
// //		//for (size_t i = 0; i < n; ++i)
// //		//{
// //		//	cout << i << endl;
// //		//}
// //
// //		};
// //
// //	for(auto& thd: vthd)
// //	{
// //		// 移动赋值
// //		thd = thread(func, 10000);
// //	}
// //
// //	for (auto& thd : vthd)
// //	{
// //		thd.join();
// //	}
// //
// //	cout << x << endl;
// //	printf("%d\n", x.load());
// //
// //	return 0;
// //}

// //int main()
// //{
// //	std::mutex mtx;
// //	condition_variable c;
// //	int n = 100;
// //	bool flag = true;
// //
// //	thread t2([&]() {
// //		int j = 1;
// //		while (j < n)
// //		{
// //			unique_lock<mutex> lock(mtx);
// //			//c.wait(lock, [&]()->bool {return !flag; });
// //			while (flag) c.wait(lock);
// //
// //			cout << j << endl;
// //
// //			j += 2; // 奇数
// //			flag = true;
// //
// //			c.notify_one();
// //		}
// //	});
// //
// //	// this_thread::sleep_for(chrono::milliseconds(2000));
// //
// //	thread t1([&]() {
// //		int i = 0;
// //		while (i < n)
// //		{
// //			unique_lock<mutex> lock(mtx);
// //			//c.wait(lock, [&]()->bool {return flag; });
// //			while (!flag) c.wait(lock);
// //
// //			cout << i << endl;
// //
// //			i += 2; // 偶数
// //			flag = false;
// //
// //			c.notify_one();
// //		}
// //	});
// //
// //	//thread t2([&]() {
// //	//	int j = 1;
// //	//	while (j < n)
// //	//	{
// //	//		unique_lock<mutex> lock(mtx);
// //	//		c.wait(lock, [&]()->bool {return !flag; });
// //	//		cout << j << endl;
// //	//		j += 2; // 奇数
// //	//		flag = true;
// //	//		c.notify_one();
// //	//	}
// //	//});
// //
// //	t1.join();
// //	t2.join();
// //
// //	return 0;
// //}

// //double Division(int a, int b)
// //{
// //	// 当b == 0时抛出异常
// //	if (b == 0)
// //		throw "Division by zero condition!";
// //	else
// //		return ((double)a / (double)b);
// //}
// //
// //void Func()
// //{
// //	int len, time;
// //	cin >> len >> time;
// //	cout << Division(len, time) << endl;
// //}
// //
// //int main()
// //{
// //	try 
// //	{
// //		Func();
// //	}
// //	catch (const char* errmsg)
// //	{
// //		cout << errmsg << endl;
// //	}
// //	catch (...) // 任意类型
// //	{
// //		cout << "unkown exception" << endl;
// //	}
// //
// //	return 0;
// //}

// class Exception
// {
// public:
// 	Exception(const string& errmsg, int id)
// 		:_errmsg(errmsg)
// 		, _id(id)
// 	{}

// 	virtual string what() const
// 	{
// 		return _errmsg;
// 	}

// protected:
// 	string _errmsg;
// 	int _id;
// };

// class SqlException : public Exception
// {
// public:
// 	SqlException(const string& errmsg, int id, const string& sql = "")
// 		:Exception(errmsg, id)
// 		, _sql(sql)
// 	{}

// 	virtual string what() const
// 	{
// 		string str = "SqlException:";
// 		str += _errmsg;
// 		str += "->";
// 		str += _sql;

// 		return str;
// 	}

// private:
// 	const string _sql;
// };

// class CacheException : public Exception
// {
// public:
// 	CacheException(const string& errmsg, int id)
// 		:Exception(errmsg, id)
// 	{}

// 	virtual string what() const
// 	{
// 		string str = "CacheException:";
// 		str += _errmsg;

// 		return str;
// 	}
// };

// class HttpServerException : public Exception
// {
// public:
// 	HttpServerException(const string& errmsg, int id, const string& type)
// 		:Exception(errmsg, id)
// 		, _type(type)
// 	{}

// 	virtual string what() const
// 	{
// 		string str = "HttpServerException:";
// 		str += _type;
// 		str += ":";
// 		str += _errmsg;

// 		return str;
// 	}
// private:
// 	const string _type;
// };

// void SQLMgr()
// {
// 	srand(time(0));
// 	if (rand() % 7 == 0)
// 	{
// 		throw SqlException("权限不足", 100, "select * from name = '张三'");
// 	}
// 	else
// 	{
// 		cout << "执行sql成功" << endl;
// 	}

// }
// void CacheMgr()
// {
// 	srand(time(0));
// 	if (rand() % 5 == 0)
// 	{
// 		throw CacheException("权限不足", 100);
// 	}
// 	else if (rand() % 6 == 0)
// 	{
// 		throw CacheException("数据不存在", 101);
// 	}
// 	else
// 	{
// 		cout << "CacheMgr处理请求成功" << endl;
// 	}

// 	SQLMgr();
// }

// void HttpServer()
// {
// 	// ...
// 	srand(time(0));
// 	if (rand() % 3 == 0)
// 	{
// 		throw HttpServerException("请求资源不存在", 100, "get");
// 	}
// 	else if (rand() % 4 == 0)
// 	{
// 		throw HttpServerException("权限不足", 101, "post");
// 	}
// 	else
// 	{
// 		cout << "HttpServer处理请求成功" << endl;
// 	}

// 	CacheMgr();
// }

// int main()
// {
// 	while (1)
// 	{
// 		this_thread::sleep_for(chrono::seconds(1));

// 		try 
// 		{
// 			HttpServer();
// 		}	
// 		catch (const Exception& e) // 这里捕获父类对象就可以
// 		{
// 			// 多态
// 			cout << e.what() << endl;
// 		}
// 		catch (...)
// 		{
// 			cout << "Unkown Exception" << endl;
// 		}
// 	}

// 	return 0;
// }

#include <memory>

//int main()
//{
//	auto_ptr<int> sp1(new int(1));
//
//	// C++98 转移管理权，sp1对象悬空
//	auto_ptr<int> sp2(sp1);
//
//	*sp1 += 1;
//
//	return 0;
//}

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	
	~A()
	{
		cout << "~A()" << endl;
	}

private:
	int _a1 = 1;
	int _a2 = 2;
};

//int main()
//{
//	unique_ptr<A> sp1(new A());
//	// unique_ptr<A> sp2(sp1); // error 不能拷贝构造
//
//	A* p = sp1.get();
//	cout << p << endl;
//
//	return 0;
//}

//int main()
//{
//	shared_ptr<A> sp1(new A);
//	shared_ptr<A> sp2(sp1);
//
//	cout << sp1.use_count() << endl;
//	{
//		shared_ptr<A> sp3(sp1);
//		cout << sp1.use_count() << endl;
//	}
//
//	cout << sp1.use_count() << endl;
//
//	return 0;
//}

#include "shared_ptr.h"

mutex mtx;

// 智能指针对象本身拷贝析构是线程安全的
// 底层引用计数加减是线程安全的
// 指向的资源访问不是线程安全的

void func(sl::shared_ptr<list<int>> sp, int n)
{
	cout << sp.use_count() << endl;

	//mtx.lock();

	for (int i = 0; i < n; ++i)
	{
		sl::shared_ptr<list<int>> copy1(sp);
		sl::shared_ptr<list<int>> copy2(sp);
		sl::shared_ptr<list<int>> copy3(sp);

		mtx.lock();
		sp->emplace_back(i);
		mtx.unlock();
	}

	//mtx.unlock();
}

int main()
{
	sl::shared_ptr<list<int>> sp1(new list<int>);
	cout << sp1.use_count() << endl;


	thread t1(func, sp1, 1000);
	thread t2(func, sp1, 2000);

	t1.join();
	t2.join();

	cout << sp1->size() << endl;
	cout << sp1.use_count() << endl;

	return 0;
}