#include "GraphicsGlobalVariables.h"
GraphicsGlobalVariables *GraphicsGlobalVariables::m_instance = nullptr;

GraphicsGlobalVariables* GraphicsGlobalVariables::Instance()
{
	if (!m_instance)
		m_instance = new GraphicsGlobalVariables();

	return m_instance;
}



GraphicsGlobalVariables::GraphicsGlobalVariables()
{
	width = 1200;
	height = 800;
	windowPos = glm::vec2(20, 20);

	isLBtnressed = false;
	isRBtnPressed = false;
	lastMMovement = glm::vec2(0.0f, 0.0f);
	lastMousePos = glm::vec2(0);

	current_camera = new Camera();

	template_vs = ".\\template_vs.glsl";
	template_fs = ".\\template_fs.glsl";

	light_vs = ".\\vs.glsl";
	light_fs = ".\\fs.glsl";

	light_model = ".\\Materials\\Sphere.obj";

	model_dir = ".\\Materials\\";
	fish_model = model_dir + "Amago0.obj";
	// fish_model = "cow.ply";
	fish_texture = model_dir + "AmagoT.bmp";
	fish_vs = ".\\fish_vs.glsl";
	fish_fs = ".\\fish_fs.glsl";

	shadertoy_vs = ".\\shadertoy_vs.glsl";
	shadertoy_fs = ".\\shadertoy_fs.glsl";
	raymarching_fs = ".\\raymarching_fs.glsl";

	framebuffer_vs = ".\\framebuffer_vs.glsl";
	framebuffer_fs = ".\\framebuffer_fs.glsl";

	skeleton_vs = ".\\skeleton_vs.glsl";
	skeleton_fs = ".\\skeleton_fs.glsl";

	isF_MouseMovement = true;
	isImguiOpen = true;
	isInstance = true;

	pos_attrib_loc = 0;
	texture_loc = 1;
	normal_loc = 2;

	PVM_loc = 0;
	time_loc = 1;
	resolution_loc = 2;
	mouse_loc = 3;

	PI = 3.14159265f;
}
