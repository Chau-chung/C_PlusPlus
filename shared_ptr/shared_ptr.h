#pragma once

#include <atomic>

namespace sl
{
	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			: _ptr(ptr)
			, _pcount(new atomic<int>(1))
		{}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pcount(sp._pcount)
		{
			++(*_pcount);
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (_ptr != sp._ptr)
			{
				this->release();

				_ptr = sp._ptr;
				_pcount = sp._pcount;

				++(*_pcount);
			}

			return *this;
		}

		void release()
		{
			if (--(*_pcount) == 0)
			{
				// 最后一个管理的对象，释放资源
				delete _ptr;
				delete _pcount;
			}
		}

		~shared_ptr()
		{
			release();
		}

		int use_count() const
		{
			return *_pcount;
		}

		T& operator*() const
		{
			return *_ptr;
		}

		T* operator->() const
		{
			return _ptr;
		}

	private:
		T* _ptr;
		atomic<int>* _pcount;
	};
}