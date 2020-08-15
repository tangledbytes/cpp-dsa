#pragma once

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
}