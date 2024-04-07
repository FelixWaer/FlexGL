#include "EngineManager.h"

#include <iostream>

const unsigned int SCR_WIDTH = 1800;
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

	ModelLoc = glGetUniformLocation(TheShader.ShaderProgram, "ModelMatrix");
	PositionLoc = glGetUniformLocation(TheShader.ShaderProgram, "PositionMatrix");
	CameraPosLoc = glGetUniformLocation(TheShader.ShaderProgram, "CameraPos");
	lightPosLoc = glGetUniformLocation(TheShader.ShaderProgram, "LightPos");
	lightColorLoc = glGetUniformLocation(TheShader.ShaderProgram, "LightColor");
	
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
	TheGame.tick(DeltaTime);

	glClearColor(0.f, 0.f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(TheShader.ShaderProgram);
	glLineWidth(5);
	glPointSize(5);

	glUniform3fv(CameraPosLoc, 1, glm::value_ptr(TheCamera->get_CameraPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(TheLight.get_LightPosition()));
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(TheLight.get_LightColor()));

	for (auto model : ModelHandler)
	{
		glUniformMatrix4fv(PositionLoc, 1, GL_FALSE, glm::value_ptr(model->get_ModelMatrix()));
		glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH / SCR_HEIGHT), 0.1f, 200.0f) * TheCamera->get_CameraView() * model->get_ModelMatrix()));

		model->draw_Model();
	}

	if (TheTerrain != nullptr)
	{
		for (const Triangle& triangle : TheTerrain->Indices)
		{
			if (calculate_PointOnTriangle(*CharacterPoint, TheTerrain->Vertices[triangle.FirstIndex].XYZ,
				TheTerrain->Vertices[triangle.SecondIndex].XYZ,
				TheTerrain->Vertices[triangle.ThirdIndex].XYZ, TheTerrain->get_WorldPosition()))
			{
				TheCamera->get_CameraPosition().y = CharacterPoint->y+3;
			}
		}
	}

	move_Light(DeltaTime);
}

void EngineManager::check_Collision()
{
	if(SphereCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < SphereCollisionHandler.size(); i++)
		{
			for (size_t j = i+1; j < SphereCollisionHandler.size(); j++)
			{
				if (calculate_SphereCollision(SphereCollisionHandler[i]->get_SpherePosition(), SphereCollisionHandler[j]->get_SpherePosition(),
					SphereCollisionHandler[i]->get_SphereRadius(), SphereCollisionHandler[j]->get_SphereRadius()))
				{
					SphereCollisionHandler[i]->run_CollisionFunction(SphereCollisionHandler[j]);
					SphereCollisionHandler[j]->run_CollisionFunction(SphereCollisionHandler[i]);
				}
			}
		}
	}
	if (BoxCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < BoxCollisionHandler.size(); i++)
		{
			for (size_t j = i+1; j < BoxCollisionHandler.size(); j++)
			{
				if (calculate_BoxCollision(BoxCollisionHandler[i]->get_BoxPosition(), BoxCollisionHandler[j]->get_BoxPosition(), 
					BoxCollisionHandler[i]->BoxHeight, BoxCollisionHandler[i]->BoxWidth, BoxCollisionHandler[i]->BoxDepth,
					BoxCollisionHandler[j]->BoxHeight, BoxCollisionHandler[j]->BoxWidth, BoxCollisionHandler[j]->BoxDepth))
				{
					BoxCollisionHandler[i]->run_CollisionFunction(BoxCollisionHandler[j]);
					BoxCollisionHandler[j]->run_CollisionFunction(BoxCollisionHandler[i]);
				}
			}
		}
	}
}

void EngineManager::add_ToModelHandler(Model* modelPtr)
{
	ModelHandler.emplace_back(modelPtr);
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

void EngineManager::turnOff_DebugMode(bool turnOff)
{
	for (SphereCollision* sphere : SphereCollisionHandler)
	{
		sphere->enable_SphereVisible(turnOff);
	}
	for (BoxCollision* sphere : BoxCollisionHandler)
	{
		sphere->enable_BoxVisible(turnOff);
	}
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

bool EngineManager::calculate_PointOnTriangle(glm::vec3& x, glm::vec3 P, glm::vec3 Q, glm::vec3 R, const glm::vec3& position)
{
	glm::vec3 tempVector = x;
	tempVector.y -= 0.5;

	P += position;
	Q += position;
	R += position;

	switch_YZ(P);
	switch_YZ(Q);
	switch_YZ(R);
	switch_YZ(tempVector);

	float A = glm::length(glm::cross(Q - P, R - P));

	float U, V, W;
	
	U = glm::cross(Q - tempVector, R - tempVector).z / A;
	V = glm::cross(R - tempVector, P - tempVector).z / A;
	W = glm::cross(P - tempVector, Q - tempVector).z / A;


	float triangleHeight = U * (P.z - position.y) + V * (Q.z - position.y) + W * (R.z - position.y);

	if (U >= 0 && V >= 0 && W >= 0)
	{
		x.y = (triangleHeight+position.y);
		return true;
	}
	else
	{
		return false;
	}
}

void EngineManager::switch_YZ(glm::vec3& vector)
{
	float tempValue = vector.z;
	vector.z = vector.y;
	vector.y = tempValue;
}

void EngineManager::move_Light(float deltaTime)
{
	TheLight.set_LightPosition(glm::vec3(Radius * sin(glm::radians(Degrees)), -10.f, Radius * cos(glm::radians(Degrees))));
	TheLight.set_LightColor(glm::vec3(sin(glm::radians(DegreesColor)), cos(glm::radians(DegreesColor)), cos(glm::radians(DegreesColor))));
	Degrees += 180.f * deltaTime;
	DegreesColor += 90.f * deltaTime * SmallerBiggerColor;
	Radius += 5.f * SmallerBigger * deltaTime;
	if (Degrees >= 360.f)
	{
		Degrees = 0.f;
	}

	if (DegreesColor >= 180.f)
	{
		SmallerBiggerColor = -1;
	}
	else if(DegreesColor <= 0.f)
	{
		SmallerBiggerColor = 1;
	}
	

	if (Radius >= 50.f || Radius <= 15.f)
	{
		SmallerBigger *= -1;
	}
}
