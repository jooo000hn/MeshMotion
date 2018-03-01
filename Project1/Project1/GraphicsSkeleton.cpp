#include "GraphicsSkeleton.h"



GraphicsSkeleton::GraphicsSkeleton(MeshSkeleton& skeleton): vao(-1), vbo(-1), ebo(-1)
{
	_skeleton = skeleton;
}


GraphicsSkeleton::~GraphicsSkeleton()
{
}

void GraphicsSkeleton::Draw()
{
}

void GraphicsSkeleton::Draw_Shader_Uniforms()
{
}

void GraphicsSkeleton::Reload()
{
}

void GraphicsSkeleton::Init_Buffers()
{
	// Set skeleton information
	auto bonedata = _skeleton.Bonedata();
	std::unordered_map<std::string, SkeletonNode*> name2Bone;
	std::for_each(bonedata.begin(),bonedata.end(),[&](SkeletonNode* n)
	{
		name2Bone[n->Name()] = n;
	});

	std::vector<glm::vec3> jointsPos;    // First element is root
	std::vector<unsigned int> topoOrder;

	jointsPos.push_back(_skeleton.RootPosition());


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
}

void GraphicsSkeleton::BufferManage()
{
}

void GraphicsSkeleton::ReleaseBuffers()
{
}
