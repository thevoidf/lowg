#pragma once

#include <vector>
#include <glm/mat4x4.hpp>
#include <string>
#include "font.h"

namespace lowg {

	class Renderable2D;

	class Renderer2D
	{
		protected:
			std::vector<glm::mat4> transformationStack;
			glm::mat4 *transformationBack;

			Renderer2D()
			{
				transformationStack.push_back(glm::mat4(1.0f));
				transformationBack = &transformationStack.back();
			}
		public:
			void push(const glm::mat4& matrix, bool override = false)
			{
				if (override)
					transformationStack.push_back(matrix);
				else
					transformationStack.push_back(transformationStack.back() * matrix);
				transformationBack = &transformationStack.back();
			}

			void pop()
			{
				if (transformationStack.size() > 1)
					transformationStack.pop_back();
				transformationBack = &transformationStack.back();
			}

			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const glm::vec3 position, const glm::vec4& color, const Font& font) {}
			virtual void flush() = 0;
	};
}
