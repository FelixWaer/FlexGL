#include "FlexMath.h"

bool calculate_PointOnTriangle(glm::vec3& x, const glm::vec3& P, const glm::vec3& Q, const glm::vec3& R, const glm::vec3& position)
{
	glm::vec3 tempVector = x;
	tempVector.y -= 0.5;

	float A = calculate_Normal(Q - P, R - P);

	float U = calculate_Normal((Q + position) - tempVector, (R + position) - tempVector);
	float V = calculate_Normal((R + position) - tempVector, (P + position) - tempVector);
	float W = 1 - U - V;

	if (U >= 0 && V >= 0 && W >= 0)
	{
		float triangleHeight = U * (P.y) + V * (Q.y) + W * (R.y);
		x.y = (triangleHeight + position.y);
		return true;
	}
	else
	{
		return false;
	}
}

float calculate_Normal(const glm::vec3& AB, const glm::vec3& AC)
{
	return AB[0] * AC[2] - AC[0] * AB[2];
}

float calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC)
{
	return AB[0] * AC[2] - AC[0] * AB[2];
}

void switch_YZ(glm::vec3& vector)
{
	float tempValue = vector.z;
	vector.z = vector.y;
	vector.y = tempValue;
}
