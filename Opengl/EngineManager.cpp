#include "EngineManager.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 900;

std::string FilePathVert = "Shader/Vertex_Shader.txt";
std::string FilePathFrag = "Shader/Fragment_Shader.txt";

EngineManager* EngineManager::create_EngineManager()
{
	TheEngineManager = new EngineManager;
	return TheEngineManager;
}

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
	for (GameObject* gameObject : GameObjectHandler)
	{
		gameObject->game_Start();
	}
}

void EngineManager::tick_Engine()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	for (GameObject* gameObject  : GameObjectHandler)
	{
		gameObject->tick(DeltaTime);
	}

	TheGame.Input(TheWindow);
	check_Collision();
	TheGame.tick(this, DeltaTime);

	glClearColor(0.f, 0.f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(TheShader.ShaderProgram);
	glLineWidth(5);
	glPointSize(5);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(TheCamera->get_CameraView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.1f, 200.0f)));

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

void EngineManager::check_Collision()
{
	if(SphereCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < SphereCollisionHandler.size(); i++)
		{
			for (size_t j = 0; j < SphereCollisionHandler.size(); j++)
			{
				if (j == i)
				{
					continue;
				}
				if (calculate_SphereCollision(SphereCollisionHandler[i]->get_SpherePosition(), SphereCollisionHandler[j]->get_SpherePosition(),
					SphereCollisionHandler[i]->get_SphereRadius(), SphereCollisionHandler[j]->get_SphereRadius()))
				{
					SphereCollisionHandler[i]->run_CollisionFunction(SphereCollisionHandler[j]);
				}
			}
		}
	}
	if (BoxCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < BoxCollisionHandler.size(); i++)
		{
			for (size_t j = 0; j < BoxCollisionHandler.size(); j++)
			{
				if (j == i)
				{
					continue;
				}
				if (calculate_BoxCollision(BoxCollisionHandler[i]->get_BoxPosition(), BoxCollisionHandler[j]->get_BoxPosition(), 
					BoxCollisionHandler[i]->BoxHeight, BoxCollisionHandler[i]->BoxWidth, BoxCollisionHandler[i]->BoxDepth,
					BoxCollisionHandler[j]->BoxHeight, BoxCollisionHandler[j]->BoxWidth, BoxCollisionHandler[j]->BoxDepth))
				{
					BoxCollisionHandler[i]->run_CollisionFunction(BoxCollisionHandler[j]);
				}
			}
		}
	}
}

void EngineManager::add_ToModelHandler(Model* modelPtr)
{
	ModelHandler.emplace_back(modelPtr);
}

void EngineManager::add_ToLineModelHandler(Line* lineModelPtr)
{
	LineModelHandler.emplace_back(lineModelPtr);
}

void EngineManager::add_ToGameObjectHandler(GameObject* gameObjectPtr)
{
	GameObjectHandler.emplace_back(gameObjectPtr);
}

void EngineManager::add_ToSphereCollisionHandler(SphereCollision* sphereCollisionPtr)
{
	SphereCollisionHandler.emplace_back(sphereCollisionPtr);
}

void EngineManager::add_ToBoxCollisionHandler(BoxCollision* boxCollisionPtr)
{
	BoxCollisionHandler.emplace_back(boxCollisionPtr);
}

bool EngineManager::calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2)
{
	float distance = pow((spherePos_1.x - spherePos_2.x), 2) + pow((spherePos_1.y - spherePos_2.y), 2) + pow((spherePos_1.z - spherePos_2.z), 2);
	if (sqrt(distance) < sphereRadius_1 + sphereRadius_2)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

bool EngineManager::calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2)
{
	return (boxPos_1.x - boxWidth_1 / 2) <= (boxPos_2.x + boxWidth_2/2) &&
		(boxPos_1.x + boxWidth_1 / 2) >= (boxPos_2.x - boxWidth_2 / 2) &&
		(boxPos_1.y - boxHeight_1 / 2) <= (boxPos_2.y + boxHeight_2 / 2) &&
		(boxPos_1.y + boxHeight_1 / 2) >= (boxPos_2.y - boxHeight_2 / 2) &&
		(boxPos_1.z - boxDepth_1 / 2) <= (boxPos_2.z + boxDepth_2 / 2) &&
		(boxPos_1.z + boxDepth_1 / 2) >= (boxPos_2.z - boxDepth_2 / 2);
}
