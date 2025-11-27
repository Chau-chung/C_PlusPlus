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
			if (_n * 10 / _tables.size() >= 7)
			{
				//size_t = newsize = _tables.size() * 2;
				//std::vector<HashData<K, V>> newtables(newsize);

				//// 旧表重新计算负载到新表 
				//for (size_t i = 0; i < _tables.size(); i++)
				//{}

				HashTable<K, V, Hash> newHT;
				newHT._tables.resize(_tables.size() * 2);

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
	template <class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			: _data(data)
			, _next(nullptr)
		{}
	};

	// 前置声明
	template <class K, class T, class KeyOfT, class Hash>
	class HashTable;

	//template <class K, class T, class KeyOfT, class Hash>
	//struct __HtIterator
	//{
	//	typedef HashNode<T> Node;
	//	typedef __HtIterator<K, T, KeyOfT, Hash> Self;

	//	Node* _node;
	//	HashTable<K, T, KeyOfT, Hash>* _pht;

	//	__HtIterator(Node* node, HashTable<K, T, KeyOfT, Hash>* pht)
	//		: _node(node)
	//		, _pht(pht)
	//	{}

	//	T& operator*()
	//	{
	//		return _node->_data;
	//	}

	//	Self& operator++()
	//	{
	//		if (_node->_next)
	//		{
	//			// 当前桶没走完，取当前桶的下一个节点
	//			_node = _node->_next;
	//		}
	//		else
	//		{
	//			// 当前桶走完，找下一个非空桶的第一个节点
	//			KeyOfT kot;
	//			Hash hs;
	//			size_t i = hs(kot(_node->_data)) % _pht->_tables.size();
	//			++i;
	//			for (; i < _pht->_tables.size(); i++)
	//			{
	//				if (_pht->_tables[i]) break;
	//			}

	//			// 走到表尾了
	//			if (i == _pht->_tables.size()) _node = nullptr;
	//			else _node = _pht->_tables[i];
	//		}

	//		return *this;
	//	}

	//	bool operator!=(const Self& it)
	//	{
	//		return _node != it._node;
	//	}
	//};

	template <class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		typedef HashNode<T> Node;

	public:
		// 友元声明
		/*template <class K, class T, class KeyOfT, class Hash>
		friend struct __HtIterator;*/

		// 内部类
		template <class Ptr, class Ref>
		struct __HtIterator
		{
			typedef HashNode<T> Node;
			typedef __HtIterator Self;

			Node* _node;
			const HashTable* _pht;

			__HtIterator(Node* node, const HashTable* pht)
				: _node(node)
				, _pht(pht)
			{}

			Ref operator*()
			{
				return _node->_data;
			}

			Ptr operator->()
			{
				return &(_node->_data);
			}

			Self& operator++()
			{
				if (_node->_next)
				{
					// 当前桶没走完，取当前桶的下一个节点
					_node = _node->_next;
				}
				else
				{
					// 当前桶走完，找下一个非空桶的第一个节点
					KeyOfT kot;
					Hash hs;
					size_t i = hs(kot(_node->_data)) % _pht->_tables.size();
					++i;
					for (; i < _pht->_tables.size(); i++)
					{
						if (_pht->_tables[i]) break;
					}

					// 走到表尾了
					if (i == _pht->_tables.size()) _node = nullptr;
					else _node = _pht->_tables[i];
				}

				return *this;
			}

			bool operator!=(const Self& it)
			{
				return _node != it._node;
			}
		};

		typedef __HtIterator<T*, T&> iterator;
		typedef __HtIterator<const T*, const T&> const_iterator;

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator begin() const
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return const_iterator(_tables[i], this);
				}
			}

			return end();
		}

		const_iterator end() const
		{
			return const_iterator(nullptr, this);
		}

		HashTable()
		{
			_tables.resize(10, nullptr);
			_n = 0;
		}

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;

					cur = next;
				}

				_tables[i] = nullptr;
			}
		}

		std::pair<iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator it = Find(kot(data));
			if (it != end()) return std::make_pair(it, false);

			Hash hs;

			// 扩容
			// 负载因子为1时扩容
			if (_n == _tables.size())
			{
				//HashTable<K, V, Hash> newHT;
				//newHT._tables.resize(_tables.size() * 2);

				// 旧表重新计算负载到新表
				//for (size_t i = 0; i < _tables.size(); i++)
				//{
				//	if (_tables[i]._state == EXIST)
				//	{
				//		Node* cur = _tables[i];
				//		while (cur)
				//		{
				//			newHT.Insert(cur->_kv);
				//			cur = cur->_next;
				//		}
				//	}
				//}

				std::vector<Node*> newTables(_tables.size() * 2, nullptr);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						// 头插到新表的对应位置
						size_t hashi = hs(kot(cur->_data)) % newTables.size();
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}

				_tables.swap(newTables);
			}

			size_t hashi = hs(kot(data)) % _tables.size();

			Node* newnode = new Node(data);
			// 头插
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return std::make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key)
		{
			KeyOfT kot;
			Hash hs;

			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}

				cur = cur->_next;
			}

			return end();
		}

		bool Erase(const K& key)
		{
			KeyOfT kot;
			Hash hs;

			size_t hashi = hs(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					// 删除的是第一个
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					--_n;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}

				return false;
			}
		}
	private:
		std::vector<Node*> _tables;
		size_t _n;
	};
}