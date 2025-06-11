#pragma once

#include <vector>
#include <deque>

namespace sl
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		stack()
		{}

		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}
        
		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

		T& top()
		{
			return _con.back();
		}

		const T& top() const
		{
			return _con.back();
		}

	private:
		Container _con;
	};
}
