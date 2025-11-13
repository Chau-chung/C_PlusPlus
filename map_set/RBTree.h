#pragma once

enum Colour
{
	RED,
	BLACK
};

template <class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	Colour _col;

	RBTreeNode(const T& data)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(RED)
	{}
};

template <class T, class Ref, class Ptr>
struct __RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;

	__RBTreeIterator(Node* node)
		: _node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		// 1. If there is a right subtree, go down to leftmost node in right subtree
		if (_node->_right)
		{
			Node* leftMost = _node->_right;
			while (leftMost->_left)
			{
				leftMost = leftMost->_left;
			}

			_node = leftMost;
		}
		else // 2. No right subtree, go up until we find a node that is left child of its parent
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	Self& operator--()
	{
		// 1. If there is a left subtree, go down to rightmost node in left subtree
		if (_node->_left)
		{
			Node* rightMost = _node->_left;
			while (rightMost && rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else // 2. No left subtree, go up until we find a node that is right child of its parent
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return *this;
	}
};

template <class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;

public:
	typedef __RBTreeIterator<T, T&, T*> Iterator;
	typedef __RBTreeIterator<T, const T&, const T*> ConstIterator;

	RBTree() = default;

	RBTree(const RBTree<K, T, KeyOfT>& t)
	{
		_root = Copy(t._root);
	}

	RBTree<K, T, KeyOfT>& operator=(const RBTree<K, T, KeyOfT>& t)
	{
		swap(_root, t._root); 

		return *this;
	}

	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

	Iterator Begin()
	{
		Node* leftMost = _root;
		while (leftMost && leftMost->_left)
		{
			leftMost = leftMost->_left;
		}

		return Iterator(leftMost);
	}

	Iterator End()
	{
		return Iterator(nullptr);
	}

	ConstIterator Begin() const
	{
		Node* leftMost = _root;
		while (leftMost && leftMost->_left)
		{
			leftMost = leftMost->_left;
		}

		return ConstIterator(leftMost);
	}

	ConstIterator End() const
	{
		return ConstIterator(nullptr);
	}

	Iterator* Find(const K& key)
	{
		KeyOfT kot;
		Node* cur = _root;

		while (cur)
		{
			if (key < kot(cur->_data))
			{
				cur = cur->_left;
			}
			else if (key > kot(cur->_data))
			{
				cur = cur->_right;
			}
			else
			{
				return Iterator(cur);
			}
		}

		return End();
	}

	std::pair<Iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return std::make_pair(Iterator(_root), true);
		}

		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			// kot对象，是用来取T类型的data中的key
			if (kot(data) < kot(cur->_data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kot(data) > kot(cur->_data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return std::make_pair(Iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newNode = cur;
		cur->_col = RED; // New nodes are red
		if (kot(data) < kot(parent->_data))
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		// parent is black, done
		while (parent && parent->_col == RED)
		{
			Node* grandparent = parent->_parent;

			// 关键看叔叔
			if (parent == grandparent->_left)
			{
				Node* uncle = grandparent->_right;
				// uncle is exist and red -> change colour
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					// upward handle
					cur = grandparent;
					parent = cur->_parent;
				}
				else // uncle is black or not exist
				{
					if (cur == parent->_left)
					{
						//     g
						//   p   u
						// c
						RotateR(grandparent);
						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						//     g
						//   p   u
						//     c
						RotateL(parent);
						RotateR(grandparent);
						cur->_col = BLACK;
						grandparent->_col = RED;
					}

					break;
				}
			}
			else
			{
				Node* uncle = grandparent->_left;
				// uncle is exist and red -> change colour
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandparent->_col = RED;

					// upward handle
					cur = grandparent;
					parent = cur->_parent;
				}
				else // uncle is black or not exist
				{
					if (cur == parent->_right)
					{
						//     g
						//   u   p
						//         c
						RotateL(grandparent);
						parent->_col = BLACK;
						grandparent->_col = RED;
					}
					else
					{
						//     g
						//   u   p
						//     c
						RotateR(parent);
						RotateL(grandparent);
						cur->_col = BLACK;
						grandparent->_col = RED;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return std::make_pair(Iterator(cur), true);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL) subRL->_parent = parent;

		subR->_left = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR) subLR->_parent = parent;

		subL->_right = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}
	}

	void InOrder()
	{
		_InOrder(_root);

		std::cout << std::endl;
	}

	bool IsBalanced()
	{
		if (_root->_col == RED) return false;

		int refNum = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK) ++refNum;

			cur = cur->_left;
		}

		return Check(_root, 0, refNum);
	}

private:
	Node* Copy(Node* root)
	{
		if (root == nullptr) return nullptr;

		Node* newroot = new Node(root->_data);
		newroot->_col = root->_col;

		newroot->_left = Copy(root->_left);
		if (newroot->_left) newroot->_left->_parent = newroot;

		newroot->_right = Copy(root->_right);
		if (newroot->_right) newroot->_right->_parent = newroot;

		return newroot;
	}

	void Destroy(Node* root)
	{
		if (root == nullptr) return;

		Destroy(root->_left);
		Destroy(root->_right);

		delete root;
		// root = nullptr;
	}

	bool Check(Node* root, int blackNum, const int refNum)
	{
		if (root == nullptr)
		{
			// std::cout << blackNum << std::endl;
			if (blackNum != refNum)
			{
				std::cout << "Black height violation, expected: "
					<< refNum << ", actual: " << blackNum << std::endl;
				return false;
			}

			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			std::cout << "Red violation at node: " << root->_kv.first << std::endl;
			return false;
		}

		if (root->_col == BLACK) ++blackNum;

		return Check(root->_left, blackNum, refNum)
			&& Check(root->_right, blackNum, refNum);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr) return;

		_InOrder(root->_left);
		std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
		_InOrder(root->_right);
	}

private:
	Node* _root = nullptr;
};