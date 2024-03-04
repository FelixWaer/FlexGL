#include "EngineManager.h"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::string FilePathVert = "Shader/Vertex_Shader.txt";
std::string FilePathFrag = "Shader/Fragment_Shader.txt";

void EngineManager::init_Window()
{
	TheWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle window", NULL, NULL);

}

void EngineManager::init_Engine()
{
	TheShader.set_ShaderPath(FilePathVert, FilePathFrag);
	TheShader.init_Shader();

	modelLoc = glGetUniformLocation(TheShader.ShaderProgram, "model");
	viewLoc = glGetUniformLocation(TheShader.ShaderProgram, "view");
	projLoc = glGetUniformLocation(TheShader.ShaderProgram, "projection");


	TheGame.game_Start(this);
}

void EngineManager::tick_Engine()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	TheGame.Input(TheWindow);
	TheGame.tick(DeltaTime);

	glClearColor(0.f, 0.f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(TheShader.ShaderProgram);
	glLineWidth(5);
	glPointSize(5);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(TheCamera->get_CameraView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f)));

	for (auto model : LineModelHandler)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model->get_LineMatrix()));
		model->draw_Line();
	}
	for (auto model : ModelHandler)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model->get_ModelMatrix()));
		model->draw_Model();
	}
}
