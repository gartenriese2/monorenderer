#pragma once

#include "geometrybuffer.hpp"

#include <MonoEngine/gl/program.hpp>
#include <MonoEngine/gl/vertexarray.hpp>
#include <MonoEngine/gl/timer.hpp>

namespace renderer {

namespace rt {

class Renderer {

	public:

		Renderer();

		void add(const Object & object);

		void render();

	private:

		GeometryBuffer m_buffer;
		gl::Program m_isctProg;
		gl::Program m_ssqProg;
		gl::VertexArray m_vao;
		gl::Buffer m_vbo;
		gl::Buffer m_ssbo;
		gl::Buffer m_lightBuffer;

		gl::Timer m_gpuTimer;

		bool m_hasTraced;
};

} // namespace rt

} // namespace renderer