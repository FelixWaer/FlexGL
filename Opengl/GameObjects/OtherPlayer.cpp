#include "OtherPlayer.h"

#include "../Engine/EngineManager.h"
#include "../Rendering/Renderer.h"

void OtherPlayer::game_Start()
{
	OtherPlayerModel.init_Model();
	OtherPlayerModel.set_ModelMesh(&Renderer::get()->Cube);
	OtherPlayerModel.set_ModelTexture(&Renderer::get()->TestTexture);
	OtherPlayerModel.bind_ToGameObject(this);
	OtherPlayerModel.set_ModelPosition(glm::vec3(0.f));
}

void OtherPlayer::tick(float deltaTime)
{
	if (EngineManager::get_Engine()->flexClient.data_HasArrived() == true)
	{
		if (EngineManager::get_Engine()->flexClient.Message_Type() == "player")
		{
			MessageBuffer dataReceived = EngineManager::get_Engine()->flexClient.receive_Message();
			glm::vec3 playerData = convert_FromMessageData<glm::vec3>(&dataReceived);
			set_GameObjectPosition(playerData);
		}
		else
		{
			MessageBuffer dataReceived = EngineManager::get_Engine()->flexClient.receive_Message();
		}
	}
}

void OtherPlayer::on_Collision(GameObject* otherGameObject)
{

}
