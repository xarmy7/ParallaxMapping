
#include "shader.h"

void Shader::LoadShader(const char* filenameV, const char* filenameF)
{
	std::fstream v(filenameV, std::fstream::in);
	std::string a;
	std::getline(v, a, '\0');

	v.close();

	codeV = a;

	std::fstream f(filenameF, std::fstream::in);
	std::string s;
	std::getline(f, s, '\0');

	f.close();

	codeF = s;
}

void Shader::CompileShader()
{
	const char* codeArray2 = Shader::codeV.c_str();

	// check for shader compile errors
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &codeArray2, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* codeArray = Shader::codeF.c_str();

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &codeArray, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::UpdateShader(Shader shader, std::vector<unsigned int>textureObject, unsigned int VAO, unsigned int skyboxVAO, mat4x4 mvp, mat4x4 model)
{
	// render
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.shaderProgram);

	GLint mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
	GLint modelLocation = glGetUniformLocation(shaderProgram, "model");

	glUniformMatrix4fv(mvpLocation, 1, 0, mvp.e);
	glUniformMatrix4fv(modelLocation, 1, 0, model.e);

	// update the uniform color
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	/*int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureObject[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureObject[2]);

	// skybox cube
	/*glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureObject[3]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);*/

	/*glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

	// now render the triangle
	/*glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);*/
}