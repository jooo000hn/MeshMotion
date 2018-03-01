#include "GraphicsLight.h"
#include "GraphicsGlobalVariables.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IchenLib/GLCommon.h"


GraphicsLight::GraphicsLight()
{
}


GraphicsLight::~GraphicsLight()
{
}

void GraphicsLight::Init_Buffers()
{
}

void GraphicsLight::Draw()
{
	glUseProgram(shader_program);
	auto gv = GraphicsGlobalVariables::Instance();

	// PVM
	glm::mat4 T = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 M = T * glm::scale(glm::vec3(m_mesh.mScaleFactor*0.1f));
	M = glm::rotate(float_uniforms["angle"], glm::vec3(0.0f, 1.0f, 0.0f)) * M;
	glm::mat4 V = gv->current_camera->GetV();
	glm::mat4 P = gv->current_camera->GetP();
	vec3_uniforms["light_position"] = gv->vec3_uniforms["light_position"];
	vec4_uniforms["light_color"] = gv->vec4_uniforms["light_color"];

	// variables
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "PVM"), 1, false, glm::value_ptr(P*V*M));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "P"), 1, false, glm::value_ptr(P));

	//m_mesh.Draw();
	glBindVertexArray(m_mesh.mVao);
	glDrawElements(GL_TRIANGLES, m_mesh.mNumIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void GraphicsLight::Reload()
{
	if(shader_program != -1)
	{
		glDeleteProgram(shader_program);
	}

	Init_Shaders(m_vs_file, m_fs_file);

	if(m_mesh.mVao != -1)
	{
		Load_Model(m_mesh_file);
	}
}

void GraphicsLight::Draw_Shader_Uniforms()
{

}

void GraphicsLight::BufferManage()
{

}

void GraphicsLight::ReleaseBuffers()
{

}
