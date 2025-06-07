#pragma once

#include <iostream>
#include <initializer_list>
#include <assert.h>

using namespace std;

namespace sl
{
	template<class T>
	class vector
	{
	public:
		// vector的迭代器就是原生态指针T*
		typedef T* iterator;
		typedef const T* const_iterator;

		// iterators
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}
		
		// constructor and destructor
		vector()
		{}

		/*vector()
			; _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}*/

		vector(size_t n, const T& val = T())
		{
			reserve(n);

			while (n--)
			{
				push_back(val);
			}
		}

		vector(int n, const T& val = T())
		{
			reserve(n);

			while (n--)
			{
				push_back(val);
			}
		}

		vector(initializer_list<T> il)
		{
			reserve(il.size());

			for (auto& e : il)
			{
				push_back(e);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(const vector<T>& v)
		{
			reserve(v.capacity());

			for (auto& e : v)
			{
				push_back(e);
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

		// capacity
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		size_t empty() const
		{
			return _start == _finish;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();  // _start改变，记录size
				
				T* tmp = new T[n];
				//memcpy(tmp, _start, size() * sizeof(T));  // 浅拷贝
				for (size_t i = 0; i < old_size; ++i)
				{
					tmp[i] = _start[i];  // 深拷贝 -- 赋值构造
				}
				delete[] _start;

				_start = tmp;
				//_finish = _start + size(); 
				_finish = _start + old_size;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n > size())
			{
				reserve(n);

				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}

		// element access
		T& operator[](size_t pos)
		{
			assert(pos < size());

			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < size());

			return _start[pos];
		}

		// modifiers
		void push_back(const T& val)
		{
			/*if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}

			*_finish = val;
			++_finish;*/

			insert(end(), val);
		}

		void pop_back()
		{
			/*assert(!empty());

			--_finish;*/

			erase(end() - 1);
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);

				pos = _start + len;  // 扩容后更新pos
			}

			iterator it = _finish;
			while (it > pos)
			{
				*it = *(it - 1);
				--it;
			}
			*pos = val;
			++_finish;

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator it = pos + 1;
			while (it < _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;

			return pos;
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};
}