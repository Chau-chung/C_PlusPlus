#pragma once
#include "HashTable.h"

namespace sl
{
	template <class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::iterator iterator;
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::const_iterator const_iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		const_iterator begin() const
		{
			return _ht.begin();
		}

		const_iterator end() const
		{
			return _ht.end();
		}

		std::pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}

		bool erase(const K& key)
		{
			return _ht.Erase(key);
		}

	private:
		hash_bucket::HashTable<K, const K, SetKeyOfT, Hash> _ht;
	};

	void test_unordered_set()
	{
		unordered_set<int> uset;
		uset.insert(11);
		uset.insert(31);
		uset.insert(25);
		uset.insert(15);
		uset.insert(5);

		unordered_set<int>::iterator it = uset.begin();
		while (it != uset.end())
		{
			std::cout << *it << " ";
			++it;
		}
		std::cout << std::endl;

		/*for (auto& e : uset)
		{
			std::cout << e << " ";
		}

		std::cout << std::endl;*/
	}
}