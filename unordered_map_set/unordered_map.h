#pragma once
#include "HashTable.h"

namespace sl
{
	template <class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename hash_bucket::HashTable<K, std::pair<const K, V>, MapKeyOfT, Hash>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _ht.Insert(std::make_pair(key, V()));
			return ret.first->second;
		}

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _ht.Insert(kv);
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
		hash_bucket::HashTable<K, std::pair<const K, V>, MapKeyOfT, Hash> _ht;
	};

	void test_unordered_map()
	{
		std::string arr[] = { "apple", "banana", "apple", "orange", "apple", "apple", "grape", "pear", "banana", "orange", "orange", "grape", "grape", "grape", "melon", "melon" };
		unordered_map<std::string, int> countMap;
		for (const auto& fruit : arr)
		{
			countMap[fruit]++;
		}

		unordered_map<std::string, int>::iterator it = countMap.begin();
		while (it != countMap.end())
		{
			std::cout << it->first << " : " << it->second << std::endl;
			++it;
		}
		std::cout << std::endl;

		for (auto& kv : countMap)
		{
			std::cout << kv.first << " : " << kv.second << std::endl;
		}
	}
}