#pragma once
#include <vector>
#include <string>

template <class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化
template <>
struct HashFunc<std::string>
{
	// BKDR
	size_t operator()(const std::string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash *= 131;
			hash += ch;
		}

		return hash;
	}
};

namespace open_address
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};

	template <class K, class V>
	struct HashData
	{
		std::pair<K, V> _kv;
		State _state = EMPTY;
	};

	struct StringHashFunc
	{
		// BKDR
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;
			for (auto ch : key)
			{
				hash *= 131;
				hash += ch;
			}

			return hash;
		}
	};

	template <class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		HashTable()
		{
			_tables.resize(10);
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			if (Find(kv.first)) return false;

			// 扩容
			if (_n * 10 / _tabels.size() >= 7)
			{
				//size_t = newsize = _tables.size() * 2;
				//std::vector<HashData<K, V>> newtables(newsize);

				//// 旧表重新计算负载到新表 
				//for (size_t i = 0; i < _tables.size(); i++)
				//{}

				HashTable<K, V, Hash> newHT;
				newHt._tables.resize(_tables.size() * 2);

				// 旧表重新计算负载到新表
				for (size_t i = 0; i < _tables.size(); i++)
				{
					if (_tables[i]._state == EXIST)
					{
						newHT.Insert(_tables[i]._kv);
					}
				}

				_tables.swap(newHT._tables);
			}

			Hash hs;
			size_t hashi = hs(kv.first) % _tables.size();

			// 线性探测
			while (_tables[hashi]._state == EXIST)
			{
				++hashi;
				hashi %= _tables.size();
			}

			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();

			// 线性探测
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST &&
					_tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}

				++hashi;
				hashi %= _tables.size();
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret == nullptr)
			{
				return false;
			}

			ret->_state = DELETE;
			--_n;

			return true;
		}

	private:
		std::vector<HashData<K, V>> _tables;
		size_t _n = 0; // 有效数据个数
	};
}

namespace hash_bucket
{
	template <class K, class V>
	struct HashNode
	{
		std::pair<K, V> _kv;
		HashNode<K, V>* _next;
	};

	template <class K, class V>
	class HashTable
	{
		typedef HashNode<K, V> Node;

	public:
		HashTable()
		{
			_tables.resize(10, nullptr);
			_n = 0;
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			// 扩容
			if (_n == _tables.size())
			{
				// ..
			}

			size_t hashi = kv.first % _tables.size();

			Node* newnode = new Node(kv);
			// 头插
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}

		Node* Find(const K& key)
		{
			size_t hashi = key % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}

				cur = cur->_next;
			}

			return nullptr;
		}

	private:
		std::vector<Node*> _tables;
		size_t _n;
	};
}