#include "geometrybuffer.hpp"

#include <MonoEngine/core/log.hpp>

namespace renderer {

namespace rt {

constexpr unsigned int k_triSize {12u * static_cast<unsigned int>(sizeof(float))};
constexpr unsigned int k_stepSize {10u * k_triSize};

GeometryBuffer::GeometryBuffer()
  : m_numTris{0u},
	m_vertexBuffer{"GeometryVertexBuffer"},
	m_normalBuffer{"GeometryNormalBuffer"},
	m_colorBuffer{"GeometryColorBuffer"}
{
	m_vertexBuffer.createImmutableStorage(k_stepSize, GL_MAP_WRITE_BIT /*| GL_MAP_READ_BIT*/ | GL_DYNAMIC_STORAGE_BIT);
	m_normalBuffer.createImmutableStorage(k_stepSize, GL_MAP_WRITE_BIT /*| GL_MAP_READ_BIT*/ | GL_DYNAMIC_STORAGE_BIT);
	m_colorBuffer.createImmutableStorage(k_stepSize, GL_MAP_WRITE_BIT /*| GL_MAP_READ_BIT*/ | GL_DYNAMIC_STORAGE_BIT);
}

void GeometryBuffer::add(const Object & object) {
	m_objects.emplace_back(std::make_unique<Object>(object));
	const auto num {m_numTris};
	m_numTris += object.getNumTriangles();
	const auto bufSize {static_cast<unsigned int>(m_vertexBuffer.getSize())};
	// LOG("bufSize: " + std::to_string(bufSize));
	const auto offset {num * k_triSize};
	const auto size {object.getNumTriangles() * k_triSize};
	// LOG("offset + size: " + std::to_string(offset + size));
	if (offset + size > bufSize) {
		const auto newSize {((offset + size) / k_stepSize + 1) * k_stepSize};
		// LOG("newSize: " + std::to_string(newSize));

		gl::Buffer newVertexBuffer;
		newVertexBuffer.createImmutableStorage(newSize, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
		glCopyNamedBufferSubData(m_vertexBuffer, newVertexBuffer, 0, 0, bufSize);
		std::swap(newVertexBuffer, m_vertexBuffer);

		gl::Buffer newNormalBuffer;
		newNormalBuffer.createImmutableStorage(newSize, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
		glCopyNamedBufferSubData(m_normalBuffer, newNormalBuffer, 0, 0, bufSize);
		std::swap(newNormalBuffer, m_normalBuffer);

		gl::Buffer newColorBuffer;
		newColorBuffer.createImmutableStorage(newSize, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
		glCopyNamedBufferSubData(m_colorBuffer, newColorBuffer, 0, 0, bufSize);
		std::swap(newColorBuffer, m_colorBuffer);
	}

	m_vertexBuffer.setData(offset, size, object.getVertices().data());
	m_normalBuffer.setData(offset, size, object.getNormals().data());
	m_colorBuffer.setData(offset, size, object.getColors().data());
}

} // namespace rt

} // namespace renderer