#pragma once

namespace sl
{
	template <class K>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key) 
			{
				return key;
			}
		};

	public:
		typedef typename RBTree<K, const K, SetKeyOfT>::Iterator iterator;

		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		bool insert(const K& key)
		{
			return _t.Insert(key);
		}

	private:
		RBTree<K, const K, SetKeyOfT> _t;
	};
}