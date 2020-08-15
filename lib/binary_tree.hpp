#pragma once

#include <iostream>
#include <functional>

#include "queue.hpp"

namespace utstl
{
	template <typename T>
	struct TreeNode
	{
		T data;
		TreeNode<T> *lchild;
		TreeNode<T> *rchild;

		TreeNode() : data(), lchild(nullptr), rchild(nullptr) {}
		explicit TreeNode(T d) : data(d), lchild(nullptr), rchild(nullptr) {}
		explicit TreeNode(T d, TreeNode<T> *lc, TreeNode<T> *rc) : data(d), lchild(nullptr), rchild(nullptr) {}
	};

	template <typename T = int>
	class Tree
	{
		TreeNode<T> *root;

	public:
		enum class Traversal
		{
			PREORDER,
			INORDER,
			POSTORDER,
			LEVELORDER
		};

	private:
		void inorder_traversal(TreeNode<T> *node, const std::function<void(T)> &func)
		{
			if (node)
			{
				inorder_traversal(node->lchild, func);
				func(node->data);
				inorder_traversal(node->rchild, func);
			}
		}

		void preorder_traversal(TreeNode<T> *node, const std::function<void(T)> &func)
		{
			if (node)
			{
				func(node->data);
				preorder_traversal(node->lchild, func);
				preorder_traversal(node->rchild, func);
			}
		}

		void postorder_traversal(TreeNode<T> *node, const std::function<void(T)> &func)
		{
			if (node)
			{
				postorder_traversal(node->lchild, func);
				postorder_traversal(node->rchild, func);
				func(node->data);
			}
		}

		void levelorder_traversal(TreeNode<T> *node, const std::function<void(T)> &func)
		{
			if (!node)
				return;

			// Create a queue
			Queue<TreeNode<T> *> q;

			q.enqueue(node);

			while (!q.isEmpty())
			{
				node = q.dequeue();

				if (node->lchild)
					q.enqueue(node->lchild);
				if (node->rchild)
					q.enqueue(node->rchild);

				// Execute the function
				func(node->data);
			}
		}

		void levelorder_traversal(TreeNode<T> *node, const std::function<void(TreeNode<T> *)> &func)
		{
			if (!node)
				return;

			// Create a queue
			Queue<TreeNode<T> *> q;

			q.enqueue(node);

			while (!q.isEmpty())
			{
				node = q.dequeue();

				if (node->lchild)
					q.enqueue(node->lchild);
				if (node->rchild)
					q.enqueue(node->rchild);

				// Execute the function
				func(node);
			}
		}

	public:
		explicit Tree() : root(nullptr) {}

		template <Traversal tr = Traversal::INORDER>
		Tree<T> &traverse(const std::function<void(T)> &func)
		{
			if (tr == Traversal::INORDER)
				inorder_traversal(root, func);

			if (tr == Traversal::POSTORDER)
				postorder_traversal(root, func);

			if (tr == Traversal::PREORDER)
				preorder_traversal(root, func);

			if (tr == Traversal::LEVELORDER)
				preorder_traversal(root, func);

			return *this;
		}

		Tree<T> &insert(T data)
		{
			// If tree hasn't been created yet then create the root node
			if (!root)
			{
				root = new TreeNode<T>(data);
				return *this;
			}

			// If the tree already exists then perform level order
			// traversal and add the element
			Queue<TreeNode<T> *> q;
			TreeNode<T> *temp;

			q.enqueue(root);

			while (!q.isEmpty())
			{
				temp = q.dequeue();

				if (temp->lchild)
					q.enqueue(temp->lchild);
				else
				{
					temp->lchild = new TreeNode<T>(data);
					break;
				}

				if (temp->rchild)
					q.enqueue(temp->rchild);
				else
				{
					temp->rchild = new TreeNode<T>(data);
					break;
				}
			}

			return *this;
		}

		Tree<T> &remove(T data)
		{
			// node will store the node which is supposed to be
			// deleted. While lastNode will store the last node
			// of the tree.
			TreeNode<T> *node = nullptr, *lastNode = nullptr;
			levelorder_traversal(root, [&node, &lastNode, data](TreeNode<T> *currNode) {
				if (currNode->data == data)
					node = currNode;
				lastNode = currNode;
			});

			if (node && lastNode)
			{
				levelorder_traversal(root, [lastNode](TreeNode<T> *node) {
					if (node->lchild == lastNode)
						node->lchild = nullptr;
					else if (node->rchild == lastNode)
						node->rchild = nullptr;
				});

				node->data = lastNode->data;
				delete lastNode;
			}

			// If the deleted node is the root node
			if (root == lastNode)
				root = nullptr;

			return *this;
		}

		~Tree()
		{
			levelorder_traversal(root, [](TreeNode<T> *node) { delete node; });
		}
	};
} // namespace utstl