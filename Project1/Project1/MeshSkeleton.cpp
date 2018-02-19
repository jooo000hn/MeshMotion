#include "MeshSkeleton.h"
#include <queue>
#include "Tool.h"


MeshSkeleton::MeshSkeleton()
{
}


MeshSkeleton::~MeshSkeleton()
{
	//std::for_each(_bonedata.begin(), _bonedata.end(), [](SkeletonNode* s) {delete s; });
}
