#include "application.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Application::InitGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int Application::CreateWindow()
{
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ParallaxMapping", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, 1920, 1080);
}

GLFWwindow* Application::GetWindow()
{
    return window;
}

void Application::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	if (mouseCaptured)
		ImGui::GetIO().MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	ImGui::NewFrame();
}

void Application::endFrame(GLFWwindow* window)
{
	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Application::showImGuiControl(GLFWwindow* window, Camera& camera, Transform& transform, Light& light)
{
	//Display debug controls
	if (ImGui::Begin("Config"))
	{
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			camera.showImGuiControls();
		}

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			transform.showImGuiControls();
		}

		if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
		{
			light.showImGuiControls();
		}
	}
	ImGui::End();
}