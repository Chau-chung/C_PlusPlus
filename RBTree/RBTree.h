#pragma once

enum Colour
{
	RED,
	BLACK
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	Colour _col;

	RBTreeNode(const pair<K, V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;

public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		cur->_col = RED; // New nodes are red
		if (kv.first < parent->_kv.first)
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