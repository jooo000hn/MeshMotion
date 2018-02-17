#include "MeshSkeleton.h"
#include <queue>
#include "Tool.h"


MeshSkeleton::MeshSkeleton()
{
}


MeshSkeleton::~MeshSkeleton()
{
}

void MeshSkeleton::PrintCurrentSkeleton()
{
	// BFS
	BfsTraverse();
}

void MeshSkeleton::BfsTraverse()
{
	if (_tree_root == nullptr)
		return;

	std::queue<SkeletonNode*> next;
	next.push(_tree_root);
	while(next.size()!=0)
	{
		auto n = next.front();
		next.pop();
		std::for_each(n->ChildrenNodes().begin(), n->ChildrenNodes().end(), [&](SkeletonNode* _n)
		{
			DEBUG("Current ID: ", _n->Id());
			for(auto v:_n->ValuePair())
			{
				DEBUG(v.first.data(), v.second.data());
			}
			next.push(_n);
		});
	}
}
