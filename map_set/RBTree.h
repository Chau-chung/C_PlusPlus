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

	T& operator*()
	{
		return _node->_data;
	}

	Ref operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	
	Ref operator++()
	{
		// 1. If there is a right subtree, go down to leftmost node in right subtree
		if (_node->_right)
		{
			Node* leftMin = _node->_right;
			while (leftMin && leftMin->_left)
			{
				leftMin = leftMin->_left;
			}

			_node = leftMin;
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
};

template <class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;

public:
	typedef __RBTreeIterator<T, T&, T*> Iterator;

	Iterator Begin()
	{
		Node* leftMin = _root;
		while (leftMin && leftMin->_left)
		{
			leftMin = leftMin->_left;
		}

		return Iterator(leftMin);
	}

	Iterator End()
	{
		return Iterator(nullptr);
	}

	Node* Find(const K& key);

	bool Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return true;
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
				return false;
			}
		}

		cur = new Node(data);
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

		return true;
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

		if(root->_col == BLACK) ++blackNum;

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