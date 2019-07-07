#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lowg {
	class Window;

	class FPSCamera {
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;
		float lastX;
		float lastY;
		bool firstMouse;
		bool constrainPitch;
		float yaw;
		float pitch;
		float movementSpeed;
		float mouseSensitivity;

	public:
		FPSCamera(glm::vec2 dimension, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		void update(lowg::Window& window, float deltaTime);

		const inline glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); }
	};
}
