#pragma once
#include "DrawObjects\GraphicsBase.h"
#include "MeshSkeleton.h"
#include "MeshMotionFlow.h"

class GraphicsSkeleton :
	public GraphicsBase
{
public:
	GraphicsSkeleton(MeshSkeleton skeleton, MeshMotionFlow meshMotion);
	~GraphicsSkeleton();

	void Draw() override;
	void Draw_Shader_Uniforms() override;
	void Reload() override;
	void Init_Buffers() override;
	void BufferManage() override;
	void ReleaseBuffers() override;
private:
	GLuint vao, vbo, ebo;
	MeshSkeleton _skeleton;
	MeshMotionFlow _meshMotion;

	std::vector<glm::vec3> _jointsPos;
	std::vector<unsigned int> _topoOrder;
};

