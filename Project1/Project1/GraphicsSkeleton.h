#pragma once
#include "DrawObjects\GraphicsBase.h"
#include "MeshSkeleton.h"

class GraphicsSkeleton :
	public GraphicsBase
{
public:
	GraphicsSkeleton(MeshSkeleton& skeleton);
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
};

