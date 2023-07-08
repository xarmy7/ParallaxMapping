#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "maths/vec3.h"
#include "maths/mat4.h"

using namespace Core::Maths::Mat4;

class Shader
{
public:
	void LoadShader(const char* filenameV, const char* filenameF);
	void CompileShader();
	void UpdateShader(Shader shader, std::vector<unsigned int>textureObject, unsigned int VAO, unsigned int skyboxVAO, mat4x4 mvp, mat4x4 model);

	int shaderProgram;

private:
	std::string codeV;
	std::string codeF;

};