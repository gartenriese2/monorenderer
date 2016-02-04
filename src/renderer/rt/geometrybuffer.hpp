#pragma once

#include <MonoEngine/gl/buffer.hpp>
#include <memory>

#include "objects/object.hpp"

namespace renderer {

namespace rt {

class GeometryBuffer {

	public:

		GeometryBuffer();

		void add(const Object & object);

		unsigned int getNumTriangles() const { return m_numTris; }
		const gl::Buffer & getVertexBuffer() const { return m_vertexBuffer; }
		gl::Buffer & getVertexBuffer() { return m_vertexBuffer; }
		const gl::Buffer & getNormalBuffer() const { return m_normalBuffer; }
		gl::Buffer & getNormalBuffer() { return m_normalBuffer; }
		const gl::Buffer & getColorBuffer() const { return m_colorBuffer; }
		gl::Buffer & getColorBuffer() { return m_colorBuffer; }

	private:

		std::vector<std::unique_ptr<Object>> m_objects;
		unsigned int m_numTris;
		gl::Buffer m_vertexBuffer;
		gl::Buffer m_normalBuffer;
		gl::Buffer m_colorBuffer;

};

static_assert(std::is_nothrow_move_constructible<GeometryBuffer>(), "Should be noexcept MoveConstructible");
static_assert(!std::is_copy_constructible<GeometryBuffer>(), "Should not be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<GeometryBuffer>(), "Should be noexcept MoveAssignable");
static_assert(!std::is_copy_assignable<GeometryBuffer>(), "Should not be CopyAssignable");

} // namespace rt

} // namespace renderer