#pragma once
#include <vector>
#include <glm/vec3.hpp>

struct ParticleComponent
{
	float Radius = 1.f;
	int MaxParticleCount = 1;
	int ParticleCount = 0;
	float SpawnInterval = 1.f;
	float ParticleSpeed = 1.f;
	float MaxLifeTime = 1.f;
	glm::vec3 Direction = glm::vec3(0.f);

	std::vector<glm::vec3> ParticlePositions;
	std::vector<float> ParticleLifeTime;
};
