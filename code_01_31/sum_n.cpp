//class Solution
//{
//public:
//	int Sum_Solution(int n)
//	{
//		n && (n += Sum_Solution(n - 1));
//
//		return n;
//	}
//private:
//	static int sum;
//};

//int Solution::sum = 0;

//class Sum
//{
//public:
//	Sum()
//	{
//		_ret += _i;
//		++_i;
//	}
//
//	static int GetRet()
//	{
//		return _ret;
//	}
//
//private:
//	static int _i;
//	static int _ret;
//};
//
//int Sum::_i = 1;
//int Sum::_ret = 0;
//
//class Solution
//{
//public:
//	int Sum_Solution(int n)
//	{
//		Sum[n];
//
//		return Sum::GetRet();
//	}
//};

class Solution
{
	class Sum
	{
	public:
		Sum()
		{
			_ret += _i;
			++_i;
		}
	private:
	};

public:
	int Sum_Solution(int n)
	{
		Sum[n];

		return _ret;
	}

private:
	static int _i;
	static int _ret;
};

int Solution::_i = 1;
int Solution::_ret = 0;