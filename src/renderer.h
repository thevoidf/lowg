#pragma once

#include "renderable.h"

class Renderer
{
	public:
		virtual void submit(const Renderable* renderable) = 0;
		virtual void flush() = 0;
};
