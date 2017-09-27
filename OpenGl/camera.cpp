#include "camera.h"
#include <glm\gtx\transform.hpp>
//Camera::Camera() :
//	viewDirection(0.0f, 0.0f, -1.0f),
//	UP(0.0f, 1.0f, 0.0f),
//	position(0.1, -1.5, -300),
//	
//{
//}

//Camera(glm::vec3 position, float fov, float aspect, float zNear, float zFar)
//	{
//		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
//		m_position = pos;
//		hardcoded straight down the z, and straight on the z
//		m_forward = glm::vec3(0, 0, 1);
//		m_up = glm::vec3(0, 1, 0);
//	}
//
//glm::mat4 Camera::getWorldToViewMatrix() const
//{
//	return m_perspective * glm::lookAt(position, position + viewDirection, UP);
//}
//
//
//void Camera::mouseUpdate(const glm::vec2 & newMousePosition)
//{
//	
//	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
//	if (glm::length(mouseDelta) > 50.0f)
//	{
//		oldMousePosition = newMousePosition;
//		return;
//}
//	viewDirection = glm::mat3(glm::rotate(mouseDelta.x * 0.5f, UP))*viewDirection;
//	oldMousePosition = newMousePosition;
//}
//
//
//
//const float MOVEMENTSPEED = 0.1f;
////
////void Camera::moveForward()
////{
////	position += MOVEMENTSPEED *  viewDirection;
////}
//
//void Camera::moveBackward()
//{
//	position += -MOVEMENTSPEED *  viewDirection;
//}
//void Camera::moveLeft()
//{
//	position -= MOVEMENTSPEED *  viewDirection;
//}
//void Camera::moveRight()
//{
//	position -= MOVEMENTSPEED *  viewDirection;
//}
//

