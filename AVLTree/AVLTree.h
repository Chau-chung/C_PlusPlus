#pragma once
#include <assert.h>

namespace key_value
{
	template <class K, class V>
	struct AVLTreeNode
	{
		AVLTreeNode<K, V>* _parent;
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		
		pair<K, V> _kv;

		int _bf; // balance factor

		AVLTreeNode(const pair<K, V>& kv)
			: _parent(nullptr)
			, _left(nullptr)
			, _right(nullptr)
			, _kv(kv)
			, _bf(0)
		{}
	};

	template <class K, class V>
	class AVLTree
	{
		typedef AVLTreeNode<K, V> Node;

	public:
		bool Insert(const pair<K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
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
					return false; // Key already exists
				}
			}

			cur = new Node(kv);
			if (kv.first < parent->_kv.first)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			cur->_parent = parent;

			// update balance factors
			while (parent)
			{
				if (cur == parent->_left)
				{
					parent->_bf--;
				}
				else
				{
					parent->_bf++;
				}

				if (parent->_bf == 0)
				{
					// update done
					break;
				}
				else if (parent->_bf == -1 || parent->_bf == 1)
				{
					// upward update
					cur = parent;
					parent = parent->_parent;
				}
				else if(parent->_bf == -2 || parent->_bf == 2)
				{
					// current is unbalanced, rotate to balance
					if (parent->_bf == -2 && cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						RotateLR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						RotateRL(parent);
					}

					break;
				}
				else
				{
					assert(false);
				}
			}

			return true;
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_kv.first)
				{
					cur = cur->_left;
				}
				else if (key > cur->_kv.first)
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

			parent->_bf = subR->_bf = 0;
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

			parent->_bf = subL->_bf = 0;
		}

		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			int bf = subLR->_bf;

			RotateL(subL);
			RotateR(parent);

			subLR->_bf = 0;
			if (bf == -1)
			{
				subL->_bf = 0;
				parent->_bf = 1;
			}
			else if (bf == 1)
			{
				subL->_bf = -1;
				parent->_bf = 0;
			}
			else if (bf == 0)
			{
				subL->_bf = 0;
				parent->_bf = 0;
			}
			else
			{
				assert(false);
			}
		}

		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			int bf = subRL->_bf;

			RotateR(subR);
			RotateL(parent);

			subRL->_bf = 0;
			if (bf == -1)
			{
				subR->_bf = 1;
				parent->_bf = 0;
			}
			else if (bf == 1)
			{
				subR->_bf = 0;
				parent->_bf = -1;
			}
			else if (bf == 0)
			{
				subR->_bf = 0;
				parent->_bf = 0;
			}
			else
			{
				assert(false);
			}
		}
  
		int Size()
		{
			return _Size(_root);
		}

		int Height()
		{
			return _Height(_root);
		}

		bool IsBalanced()
		{
			return _IsBalanced(_root);
		}

		void InOrder()
		{
			_InOrder(_root);

			std::cout << std::endl;
		}

	private:
		int _Size(Node* root)
		{
			return root == nullptr ? 0 : 1 + _Size(root->_left) + _Size(root->_right);
		}

		int _Height(Node* root)
		{
			if (root == nullptr) return 0;
			
			return 1 + max(_Height(root->_left), _Height(root->_right));
		}

		bool _IsBalanced(Node* root)
		{
			if (root == nullptr) return true;

			int leftHeight = _Height(root->_left);
			int rightHeight = _Height(root->_right);

			// unbalanced
			if (abs(leftHeight - rightHeight) > 1) return false;

			if (rightHeight - leftHeight != root->_bf) return false;

			return _IsBalanced(root->_left) 
				&& _IsBalanced(root->_right);
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
}