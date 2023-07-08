
#include "resourceManager.h"

void ResourceManager::LoadResources(Shader& shader, Texture& texture)
{
	std::vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};


	std::vector<const char*>texturePath;
	texturePath.push_back("resources/bricks2.jpg");
	texturePath.push_back("resources/bricks2_normal.jpg");
	texturePath.push_back("resources/bricks2_disp.jpg");

	/*texturePath.push_back("resources/GravelBig01_2K_BaseColor.png");
	texturePath.push_back("resources/GravelBig01_2K_Normal.png");
	texturePath.push_back("resources/GravelBig01_2K_Height.png");*/

	shader.LoadShader("src/resources/parallaxMapping.vert", "src/resources/parallaxMapping.frag");
	shader.CompileShader();

	texture.LoadTexture(texturePath, shader);
	//texture.LoadCubemap(faces);
}