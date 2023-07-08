#pragma once

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "maths/vec3.h"
#include "maths/mat4.h"

using namespace Core::Maths::Mat4;

class Transform
{
	float3 s = { 1.0f,1.0f,1.0f };

	float3 pos = { 0.0f,0.0f,0.0f };
	float3 modelAngle = { 0.0f, 0.0f, 0.0f };

public:
	mat4x4 transform();
	void showImGuiControls();

};