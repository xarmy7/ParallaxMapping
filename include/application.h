#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "camera.h"
#include "transform.h"
#include "light.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

class Application
{
private:
	GLFWwindow* window = nullptr;

public:
	void newFrame();
	void endFrame(GLFWwindow* window);
	void showImGuiControl(GLFWwindow* window, Camera& camera, Transform& transform, Light& light);

	void InitGLFW();
	int CreateWindow();
	GLFWwindow* GetWindow();

	bool mouseCaptured = false;
};