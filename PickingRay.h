#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "Camera.h"
#include <iostream>

class PickingRay
{
public:
	PickingRay(int width, int height);
	void getRay(float mx, float my, Camera cam);
	bool intersect(glm::vec3, glm::vec3, glm::vec3, float mx, float my, Camera cam);
	glm::vec3 PickingRay::rayDir();
	glm::vec3 PickingRay::rayPos();
	~PickingRay(void);
private:

	void print(glm::vec3 p);

	int mW, mH;
	glm::vec3 m_clickpos;
	glm::vec3 m_clickEnd;
	glm::vec3 m_rayPos;
	glm::vec3 m_rayDir;
};

