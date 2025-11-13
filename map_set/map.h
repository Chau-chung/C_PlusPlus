#pragma once

namespace sl
{
	template <class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::Iterator iterator;
		typedef typename RBTree<K, const K, MapKeyOfT>::ConstIterator const_iterator;

		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		const_iterator begin() const
		{
			return _t.Begin();
		}

		const_iterator end() const
		{
			return _t.End();
		}

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _t.Insert(std::make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _t;
	};
}