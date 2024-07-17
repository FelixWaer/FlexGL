#pragma once
#include <glm/glm.hpp>

bool calculate_PointOnTriangle(glm::vec3& x, const glm::vec3& P, const glm::vec3& Q, const glm::vec3& R, const glm::vec3& position);

inline float calculate_Normal(const glm::vec3& AB, const glm::vec3& AC);

inline float calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC);

inline void switch_YZ(glm::vec3& vector);