#pragma once

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include "shader.h"

class Texture
{
public:
	void LoadTexture(std::vector<const char*> filename, Shader& shader);
	unsigned int LoadCubemap(std::vector<std::string> faces);

	std::vector<unsigned int>textureObject;

	/*unsigned int texture1;
	unsigned int texture2;*/

	unsigned int texture;

	unsigned char* data;
	int width = 0, height = 0, nrChannels = 0;
};