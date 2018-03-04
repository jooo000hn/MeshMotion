#include <iostream>
#include "ASFParser.h"
#include "GlobalVariables.h"
#include "unit_test.h"
#include "Tool.h"
#include "AMCParser.h"
#include "IchenLib/GLCommon.h"
#include "IchenLib/IchenGlut.h"
#include "imgui/imgui_impl_glut.h"
#include "GraphicsGlobalVariables.h"
#include "GraphicsSkeleton.h"

// for unit test
void uni_test();
void Init_Global();
void ImGui_Update();

// Glut Functions
void InitOpenGL();
void Display();
void Keyboard(unsigned char key, int x, int y);
void Idle();
void MouseWheel(int butotm, int dir, int x, int y);
void ReloadShaders();


int main(int argc, char** argv)
{	
	InitDefaultGlutEnvironment(argc, argv);
	InitOpenGL();

	// Register callbacks
	RegisterImGuiCallbacks();
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutMouseWheelFunc(MouseWheel);

	GlutMainLoop();

	system("pause");
}

void uni_test()
{
	auto ut = unit_test::Instance();
	bool allTrue = true;
	bool flag = ut->TestCheckKeyword();
	allTrue = allTrue && flag;
	DEBUG("TestCheckKeyword", flag);
	flag = ut->TestGetKeyWordPosition();
	allTrue = allTrue && flag;
	DEBUG("TestGetKeyWordPosition", flag);

	DEBUG("All is ", allTrue);
}

void ImGui_Update()
{
	auto gv = GraphicsGlobalVariables::Instance();

	ImGui_ImplGlut_NewFrame();
	static bool isShown = true;
	auto isBegin = ImGui::Begin("Debug", &isShown, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::ColorEdit4("Background Color", &gv->vec4_uniforms["Backgound_Color"][0]);
	ImGui::SliderFloat3("Light Position", &gv->vec3_uniforms["light_position"][0], -20.0f, 20.0f);
	ImGui::ColorEdit3("Light Color", &gv->vec3_uniforms["light_color"][0]);
	ImGui::SliderFloat("Angle", &gv->float_uniforms["angle"], 0.0f, 360.0f);

#ifdef AUTO_GENERATE
	int i = 0;
	for (auto g : gv->graphics)
	{
		g->Generate_ImGui("test" + std::to_string(i++));
	}
#endif

	ImGui::End();
	ImGui::Render();

}

void InitOpenGL()
{
	glewInit();
#ifdef DEBUG_REGISTER
	RegisterOpenGLDebug();
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE); //allows us to set point size in vertex shader
	glEnable(GL_LINE_SMOOTH);

	ImGui_ImplGlut_Init();
	Init_Global();
}


void Init_Global()
{
	auto gv = GraphicsGlobalVariables::Instance();
	gv->current_camera->Position *= 1.0;
	gv->isImguiOpen = true;
	gv->vec3_uniforms["cameraPos"] = glm::vec3(0.0f, -0.2f, 3.0f);
	gv->vec3_uniforms["cameraFront"] = glm::vec3(0.0f, 0.0f, -1.0f);
	gv->vec3_uniforms["cameraUp"] = glm::vec3(0.0f, 1.0f, 0.0f);
	gv->vec3_uniforms["Billboard_Pos"] = glm::vec3(0.0f);
	gv->float_uniforms["cameraSpeed"] = 0.5f;
	gv->vec4_uniforms["Backgound_Color"] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gv->vec3_uniforms["light_position"] = glm::vec3(0.0f, 20.0f, 0.0);
	gv->vec3_uniforms["light_color"] = glm::vec3(1.0f);
	gv->current_camera->aspect = gv->float_uniforms["aspect"] = static_cast<float>(GetCurrentWindowWidth()) / static_cast<float>(GetCurrentWindowHeight());

	glClearColor(gv->vec4_uniforms["Backgound_Color"].x, gv->vec4_uniforms["Backgound_Color"].y,
		gv->vec4_uniforms["Backgound_Color"].z, gv->vec4_uniforms["Backgound_Color"].a);

	// Parsing
	auto gvv = GlobalVariables::Instance();

	std::cout << "Let's work on mesh extraction and motion!\n";
	auto p = ASFParser::Instance();
	gv->currentSkeleton = p->ParseASF(gvv->group1Dir + gvv->testASF);
	auto m = AMCParser::Instance();
	gv->currentAnimation = m->ParsAMC(gvv->group1Dir + gvv->testAMC);

	GraphicsBase* skeleton_render = new GraphicsSkeleton(gv->currentSkeleton, gv->currentAnimation);
	skeleton_render->Init_Shaders(gv->skeleton_vs, gv->skeleton_fs);
	skeleton_render->Init_Buffers();
	gv->graphics.push_back(skeleton_render);
}

void Display()
{
	auto gv = GraphicsGlobalVariables::Instance();
	gv->delta_time = glutGet(GLUT_ELAPSED_TIME) - gv->last_frame_time;
	gv->last_frame_time = glutGet(GLUT_ELAPSED_TIME);

	glClearColor(gv->vec4_uniforms["Backgound_Color"].x, gv->vec4_uniforms["Backgound_Color"].y,
		gv->vec4_uniforms["Backgound_Color"].z, gv->vec4_uniforms["Backgound_Color"].a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto g : gv->graphics)
	{
		g->Update_Uniforms();
		g->Draw();
	}

	if (gv->isImguiOpen)
		ImGui_Update();
	glutSwapBuffers();
}

void Idle()
{
	auto gv = GraphicsGlobalVariables::Instance();

	// Update all time variables
	const int time_ms = glutGet(GLUT_ELAPSED_TIME);
	gv->float_uniforms["time"] = 0.001f * time_ms;

	glutPostRedisplay();
}

void MouseWheel(int butotm, int dir, int x, int y)
{
	auto gv = GraphicsGlobalVariables::Instance();

	dir > 0
		? gv->current_camera->ProcessMouseScroll(gv->current_camera->MovementSpeed)
		: gv->current_camera->ProcessMouseScroll(-gv->current_camera->MovementSpeed);
}

void ReloadShaders()
{
	auto gv = GraphicsGlobalVariables::Instance();

	for (auto g : gv->graphics)
	{
		g->Reload();
		g->Get_Shader() == -1 ?
			glClearColor(1.0f, 0.0f, 1.0f, 0.0f) :
			glClearColor(gv->vec4_uniforms["Backgound_Color"].x, gv->vec4_uniforms["Backgound_Color"].y,
				gv->vec4_uniforms["Backgound_Color"].z, gv->vec4_uniforms["Backgound_Color"].a);
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	auto gv = GraphicsGlobalVariables::Instance();
	DEBUG("Pressed ", key);
	ImGui_ImplGlut_KeyCallback(key);

	switch (key)
	{
	case 'r':
	case 'R':
		ReloadShaders();
		break;

	default:
		break;
	}
}
