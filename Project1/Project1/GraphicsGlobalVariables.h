#pragma once
#include "IchenLib/GLCommon.h"
#include "IchenLib/Camera.h"
#include "DrawObjects/GraphicsBase.h"
#include <unordered_map>
#include <map>
#include "MeshSkeleton.h"
#include "MeshMotionFlow.h"

class GraphicsGlobalVariables
{
public:
public:
	static GraphicsGlobalVariables* Instance();

	// Imgui 
	bool isImguiOpen;

	// Resolution
	int width;
	int height;
	glm::vec2 windowPos;
	int mouseX;
	int mouseY;

	// Camera properties
	Camera* current_camera;

	// Control Varibles
	bool isLBtnressed;  // is left mouse button pressed
	bool isRBtnPressed; // is right mouse button pressed
	glm::vec2 lastMousePos;
	glm::vec2 lastMMovement; // last mouse movement
	glm::vec2 lastPressedMovement;

	// Variables
	std::vector<GraphicsBase*> graphics;

	// Global variables
	std::unordered_map<std::string, float> float_uniforms;
	std::unordered_map<std::string, bool> bool_uniforms;
	std::unordered_map<std::string, int> int_uniforms;
	std::unordered_map<std::string, glm::vec2> vec2_uniforms;
	std::unordered_map<std::string, glm::vec3> vec3_uniforms;
	std::unordered_map<std::string, glm::vec4> vec4_uniforms;

	std::string light_vs;
	std::string light_fs;

	std::string light_model;
	std::string model_dir;
	std::string fish_model;
	std::string fish_texture;
	std::string fish_vs;
	std::string fish_fs;

	// Template
	std::string template_vs;
	std::string template_fs;

	// Shader toy
	std::string shadertoy_vs;
	std::string shadertoy_fs;
	std::string raymarching_fs;

	// Framebuffer object
	std::string framebuffer_vs;
	std::string framebuffer_fs;

	std::string skeleton_vs;
	std::string skeleton_fs;

	// Time 
	int last_frame_time;
	int delta_time;

	// Is first Operations
	bool isF_MouseMovement;
	bool isInstance;

	// Attrib locations:
	GLint pos_attrib_loc;
	GLint texture_loc;
	GLint normal_loc;

	// Uniform locations:
	GLint PVM_loc;
	GLint time_loc;
	GLint resolution_loc;
	GLint mouse_loc;

	// Skeleton and animation
	MeshSkeleton currentSkeleton;
	MeshMotionFlow currentAnimation;

	// math
	float PI;
private:
	GraphicsGlobalVariables();
	GraphicsGlobalVariables(GraphicsGlobalVariables const&) {};
	GraphicsGlobalVariables& operator=(GraphicsGlobalVariables const&) const { return *m_instance; };

	static GraphicsGlobalVariables* m_instance;
};

