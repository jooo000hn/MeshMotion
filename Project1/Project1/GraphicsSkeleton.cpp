#include "GraphicsSkeleton.h"
#include <queue>
#include "Tool.h"
#include "IchenLib/GLCommon.h"
#include "GraphicsGlobalVariables.h"


GraphicsSkeleton::GraphicsSkeleton(MeshSkeleton& skeleton): vao(-1), vbo(-1), ebo(-1)
{
	_skeleton = skeleton;
}


GraphicsSkeleton::~GraphicsSkeleton()
{
}

void GraphicsSkeleton::Draw()
{
	glUseProgram(shader_program);
	auto gv = GraphicsGlobalVariables::Instance();

	// PVM
	auto P = gv->current_camera->GetP();
	auto V = gv->current_camera->GetV();
	auto M = glm::translate(glm::vec3(0.0f)) * glm::scale(glm::vec3(0.1f));
	glUniformMatrix4fv(0, 1, false, glm::value_ptr(P*V*M));

	glBindVertexArray(vao);
	glDrawElements(GL_LINES, _topoOrder.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

void GraphicsSkeleton::Draw_Shader_Uniforms()
{
}

void GraphicsSkeleton::Reload()
{
	if (shader_program != -1)
	{
		glDeleteProgram(shader_program);
	}

	Init_Shaders(m_vs_file, m_fs_file);
	Init_Buffers();
}

void GraphicsSkeleton::Init_Buffers()
{
	_jointsPos.clear();
	_topoOrder.clear();

	_jointsPos.resize(_skeleton.Bonedata().size()); // bone id is the index

	// Set skeleton information
	auto bonedata = _skeleton.Bonedata();
	std::unordered_map<std::string, SkeletonNode*> name2Bone;
	std::for_each(bonedata.begin(), bonedata.end(), [&](SkeletonNode* n)
              {
	              name2Bone[n->Name()] = n;
              });

	// update position information
	for (auto b : name2Bone)
	{
		auto currentNode = b.second;
		glm::vec3 fromRootVector;
		while (currentNode->Parent())
		{
			currentNode = currentNode->Parent();
			fromRootVector += currentNode->Direction() * currentNode->Length();
		}

		// Root + from rootVector + current node's length
		_jointsPos[b.second->Id()] = _skeleton.RootPosition() + fromRootVector + b.second->Direction() * b.second->Length();
	}

	// BFS to all the nodes to get topo order
	std::queue<SkeletonNode*> next;
	next.push(name2Bone["root"]);
	while (!next.empty())
	{
		auto top = next.front();
		next.pop();

		for(auto c:top->Children())
		{
			_topoOrder.push_back(top->Id());
			_topoOrder.push_back(c->Id());

			// next BFS loop
			next.push(c);
		}

	}

	// Set up buffers for OpenGL
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _jointsPos.size() * sizeof(glm::vec3), &_jointsPos[0],GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _topoOrder.size() * sizeof(unsigned int), &_topoOrder[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void GraphicsSkeleton::BufferManage()
{
}

void GraphicsSkeleton::ReleaseBuffers()
{
}
