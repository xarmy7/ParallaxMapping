#pragma once

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <cmath>

#include "maths/vec3.h"
#include "maths/maths.h"

#include "shader.h"
#include "camera.h"

class Light
{
	float3 ambientColor = { 0.2f, 0.2f, 0.2f };
	float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
	float3 specularColor = { 1.0f, 1.0f, 1.0f };

	float3 lightColor = { 1.0f, 0.5f, 0.31f };

	float3 lightPos = { -2.333f, 3.667f, 1.613f };

	float sharpnessLight = 5;
	float outerCutOff = 5;

	float heightScale = 0.f;

public:
	void showImGuiControls();
	void LoadLight(int shaderProgram, Camera& cam);
};