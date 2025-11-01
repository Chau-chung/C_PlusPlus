#pragma once

namespace key
{
	template <class K>
	// struct BinarySearchTreeNode
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template <class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;

	public:
		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false; // Key already exists
				}
			}

			if (key < parent->_key)
			{
				parent->_left = new Node(key);
			}
			else
			{
				parent->_right = new Node(key);
			}

			return true;
		}

		bool Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					cur = cur->_right;
				}
				else
				{
					return true; // Key found
				}
			}

			return false; // Key not found
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					// 左为空，父亲指向我的右
					if (cur->_left == nullptr)
					{
						// if (parent == nullptr)
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}

						delete cur;
					}
					else if (cur->_right = nullptr)
					{
						// if (parent == nullptr)
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;
					}
					else
					{
						// 左右都不为空，替换法删除
						// 找右子树的最左节点替代删除
						Node* rightMinParent = cur;
						Node* rightMin = cur->_right;
						while (rightMin->_left)
						{
							rightMinParent = rightMin;
							rightMin = rightMin->_left;
						}

						swap(cur->_key, rightMin->_key);

						if (rightMin == rightMinParent->_left)
						{
							rightMinParent->_left = rightMin->_right;
						}
						else
						{
							rightMinParent->_right = rightMin->_right;
						}

						delete rightMin;
					}

					return true;
				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
		}

	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr) return;

			_InOrder(root->_left);
			std::cout << root->_key << " ";
			_InOrder(root->_right);
		}

	private:
		Node* _root = nullptr;
	};
}

namespace key_value
{
	template <class K, class V>
	struct BSTreeNode
	{
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key, const V& value)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	template <class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;

	public:
		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false; // Key already exists
				}
			}

			cur = new Node(key, value);
			if (key < parent->_key)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}

			return true;
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					cur = cur->_right;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					// 左为空，父亲指向我的右
					if (cur->_left == nullptr)
					{
						// if (parent == nullptr)
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}

						delete cur;
					}
					else if (cur->_right = nullptr)
					{
						// if (parent == nullptr)
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (cur == parent->_left)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;
					}
					else
					{
						// 左右都不为空，替换法删除
						// 找右子树的最左节点替代删除
						Node* rightMinParent = cur;
						Node* rightMin = cur->_right;
						while (rightMin->_left)
						{
							rightMinParent = rightMin;
							rightMin = rightMin->_left;
						}

						swap(cur->_key, rightMin->_key);

						if (rightMin == rightMinParent->_left)
						{
							rightMinParent->_left = rightMin->_right;
						}
						else
						{
							rightMinParent->_right = rightMin->_right;
						}

						delete rightMin;
					}

					return true;
				}
			}

			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
		}

	private:
		void _InOrder(Node* root)
		{
			if (root == nullptr) return;

			_InOrder(root->_left);
			std::cout << root->_key << ":" << root->_value << std::endl;
			_InOrder(root->_right);
		}
		
	private:
		Node* _root = nullptr;
	};
}