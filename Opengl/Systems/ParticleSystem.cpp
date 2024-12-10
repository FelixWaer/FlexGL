#include "ParticleSystem.h"

#include "../Components/ParticleComponent.h"

void ParticleSystem::init()
{
	srand(time(NULL));
}

void ParticleSystem::update(float deltaTime)
{
	Timer += deltaTime;

	ComponentHandler<ParticleComponent>* particleHandler = get_ComponentHandler<ParticleComponent>();

	for (auto& ps : particleHandler->IndexMap)
	{
		ParticleComponent& particleComp = particleHandler->get_Component(ps.first);

		if (particleComp.ParticlePositions.size() < particleComp.MaxParticleCount && Timer >= particleComp.SpawnInterval)
		{
			glm::vec3 newPosition((rand() % 200) - 100, 20.f, (rand() % 200) - 100);
			newPosition = glm::normalize(newPosition);

			float length = rand() % static_cast<int>(particleHandler->Components[0].Radius * 10);
			length *= 0.1f;

			newPosition *= length;
			newPosition.y = 20.f;

			particleComp.ParticlePositions.emplace_back(newPosition);
			particleComp.ParticleLifeTime.emplace_back();
			particleComp.ParticleCount++;

			Timer = 0.f;
		}

		for (int i = 0; i < particleComp.ParticleCount; i++)
		{
			particleComp.ParticleLifeTime[i] += deltaTime;

			if (particleComp.ParticleLifeTime[i] >= particleComp.MaxLifeTime)
			{
				glm::vec3 newPosition((rand() % 200) - 100, 0.f, (rand() % 200) - 100);
				newPosition = glm::normalize(newPosition);

				float length = rand() % static_cast<int>(particleHandler->Components[0].Radius * 10);
				length *= 0.1f;

				newPosition *= length;
				newPosition.y = 20.f;

				particleComp.ParticlePositions[i] = newPosition;
				particleComp.ParticleLifeTime[i] = 0.f;
			}

			particleComp.ParticlePositions[i] += particleComp.Direction * particleComp.ParticleSpeed * deltaTime;
		}
	}
}
