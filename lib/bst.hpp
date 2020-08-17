#pragma once

#include "binary_tree_node.hpp"
#include "binary_tree.hpp"

namespace utstl
{

	template <typename T = int>
	class BST : public BinaryTree<T>
	{
	public:
		BST() : BinaryTree<T>() {}

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

		TreeNode<T> *search(T data)
		{
			TreeNode<T> *node = BinaryTree<T>::root;

			while (node && node->data == data)
			{
				if (node->data > data)
					node = node->lchild;
				else
					node = node->rchild;
			}

			return node;
		}

		BST<T> &remove(T data) override
		{
			return *this;
		}
	};
} // namespace utstl