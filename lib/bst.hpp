#pragma once

#include "binary_tree_node.hpp"
#include "binary_tree.hpp"

namespace utstl
{

	template <typename T = int>
	class BST : public BinaryTree<T>
	{
	private:
		TreeNode<T> *remove(TreeNode<T> *root, T data)
		{
			if (!root)
				return root;

			if (root->data > data)
				root->lchild = remove(root->lchild, data);
			else if (root->data < data)
				root->rchild = remove(root->rchild, data);
			else
			{
				if (!root->lchild)
				{
					TreeNode<T> *temp = root->rchild;
					delete root;
					return temp;
				}
				else if (!root->rchild)
				{
					TreeNode<T> *temp = root->lchild;
					delete root;
					return temp;
				}
				else
				{
					TreeNode<T> *s = successor(root);
					root->data = s->data;
					root->rchild = remove(root->rchild, s->data);
				}
			}
			return root;
		}

	public:
		BST() : BinaryTree<T>() {}

		// insert adds a new node to the binary search tree
		// and returns a reference to the current object
		BST<T> &insert(T data) override
		{
			if (!BinaryTree<T>::root)
			{
				BinaryTree<T>::root = new TreeNode<T>(data);
				return *this;
			}

			TreeNode<T> *temp = BinaryTree<T>::root;

			while (temp)
			{
				if (data > temp->data)
				{
					if (temp->rchild == nullptr)
					{
						// Create the node
						temp->rchild = new TreeNode<T>(data);

						break;
					}

					temp = temp->rchild;
				}
				else if (data < temp->data)
				{
					if (temp->lchild == nullptr)
					{
						// Create the node
						temp->lchild = new TreeNode<T>(data);

						break;
					}

					temp = temp->lchild;
				}
				else
					break;
			}

			return *this;
		}

		// search searches a node with the provided key and returns
		// a pointer to that node if it exists. If it doesn't exists then
		// it returns a nullptr.
		TreeNode<T> *search(T data) const
		{
			auto node = BinaryTree<T>::root;

			while (node && node->data == data)
			{
				if (node->data > data)
					node = node->lchild;
				else
					node = node->rchild;
			}

			return node;
		}

		// min returns the node with minimum value as its data
		// it starts its search from the node passed in the parameter
		TreeNode<T> *min(TreeNode<T> *node) const
		{
			while (node && node->lchild)
			{
				node = node->lchild;
			}

			return node;
		}

		// min returns the minimum element of the current BST
		TreeNode<T> *min() const
		{
			return min(BinaryTree<T>::root);
		}

		// max returns the maximum element for the subtree
		// whose root node is passed as an argumen
		TreeNode<T> *max(TreeNode<T> *node) const
		{
			while (node->rchild)
			{
				node = node->rchild;
			}

			return node;
		}

		// max returns the maximum element of the current BST
		TreeNode<T> *max() const
		{
			return max(BinaryTree<T>::root);
		}

		// successor returns inorder successor for the passed node
		TreeNode<T> *successor(TreeNode<T> *node) const
		{
			if (node && node->rchild)
				return min(node->rchild);

			return nullptr;
		}

		// successor returns inorder successor of the root node
		// of the current BST
		TreeNode<T> *successor() const
		{
			return successor(BinaryTree<T>::root);
		}

		// predecessor returns the predecessor for the provided node considering
		// it as the root node of the tree. Hence it will not go to it's parent
		// node to find it's predecessor in case the right left tree of the node is nil.
		TreeNode<T> *predecessor(TreeNode<T> *node) const
		{
			if (node && node->lchild)
				return max(node->lchild);

			return nullptr;
		}

		// predecessor returns the predecessor of the root node of the current BST
		TreeNode<T> *predecessor() const
		{
			return predecessor(BinaryTree<T>::root);
		}

		BST<T> &remove(T data) override
		{
			BinaryTree<T>::root = remove(BinaryTree<T>::root, data);
			return *this;
		}
	};
} // namespace utstl