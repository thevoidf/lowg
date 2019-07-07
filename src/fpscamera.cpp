#include "fpscamera.h"
#include "../src/window.h"

namespace lowg {
	FPSCamera::FPSCamera(glm::vec2 dimension, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.5f), mouseSensitivity(0.1f),
			position(position), worldUp(up), yaw(yaw), pitch(pitch), firstMouse(true), constrainPitch(true)
	{
		lastX = dimension.x / 2.0f;
		lastY = dimension.y / 2.0f;
	}

	void FPSCamera::update(lowg::Window& window, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		glm::vec2 mousePos = window.getMousePosition();
		glm::vec3 mFront;

		if (window.isKeyPressed(GLFW_KEY_W))
			position += front * velocity;
		if (window.isKeyPressed(GLFW_KEY_S))
			position -= front * velocity;
		if (window.isKeyPressed(GLFW_KEY_A))
			position -= right * velocity;
		if (window.isKeyPressed(GLFW_KEY_D))
			position += right * velocity;

		float xpos = mousePos.x;
		float ypos = mousePos.y;

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch) {
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		mFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		mFront.y = sin(glm::radians(pitch));
		mFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(mFront);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
}
