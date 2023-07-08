#include "light.h"

#define PI 3.14159265358979323846

void Light::showImGuiControls()
{
	ImGui::SliderFloat3("LightPos", lightPos.e, -10, 10);
	ImGui::ColorEdit3("lightColor", lightColor.e);
	ImGui::SliderFloat("heightScale", &heightScale, -1.f, 1.f);

}

void Light::LoadLight(int shaderProgram, Camera& cam)
{
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, cam.pos.e);
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, lightPos.e);
	glUniform1f(glGetUniformLocation(shaderProgram, "heightScale"), heightScale);
	/*glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, lightColor.e);
	glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 1.0f);*/
}