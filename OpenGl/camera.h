#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include<glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "display.h"



class Camera
{


public :
	//Camera(const glm::vec3&pos, float fov, float aspect, float zNear, float zFar);
	//Camera();

//public:

	Camera(const glm::vec3&pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		//hardcoded straight down the z, and straight on the z
		m_forward = glm::vec3(0, 0, 2);
		m_up = glm::vec3(0, 2, 0);
	}


	const float rotationspeed = 0.5f;
	const float movementspeed = 2.0f;
	void rotate(float delta)
	{
			m_forward = glm::mat3(glm::rotate(delta, m_up))*m_forward;
	}

	void rotateUp(float delta)
	{
		glm::vec3 torotatearound = glm::cross(m_forward, m_up);
		m_forward = glm::mat3(glm::rotate(-delta*rotationspeed, torotatearound))*m_forward;
	}



	inline glm::mat4 GetViewProjection() const
	{
		//starting pos of camera, position you want to look at , and what is up
	return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}


	void moveUp()
	{
		m_position += movementspeed * m_forward;
	}


	void moveBack()
	{
		m_position += -movementspeed * m_forward;
	}
	void moveLeft()
	{
		glm::vec3 straff = glm::cross(m_forward, m_up);
		m_position += -movementspeed * m_forward;
	}
	void moveRight()
	{
		glm::vec3 straff = glm::cross(m_forward, m_up);
		m_position += movementspeed * m_forward;
	}
	void height()
	{
		//glm::vec3 straff = glm::cross(m_forward, m_up);
		m_position += movementspeed * m_up;
	}
		
	void heightdown()
		{
			m_position += -movementspeed * m_up;
		}
	
	inline glm::vec3& GetPos() { return m_position; }
	inline void SetPos(glm::vec3& pos) { m_position = pos; }

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

};


#endif