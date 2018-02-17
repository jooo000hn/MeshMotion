#pragma once
#include "SkeletonNode.h"

class MeshSkeleton
{
public:
	MeshSkeleton();
	~MeshSkeleton();

	// manage the tree
	void PrintCurrentSkeleton();

	// getter and setter
	SkeletonNode* TreeRoot() const
	{
		return _tree_root;
	}

	void SetTreeRoot(SkeletonNode* skeleton_node)
	{
		_tree_root = skeleton_node;
	}

private:
	void BfsTraverse();
	SkeletonNode* _tree_root;
};

