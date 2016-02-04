#include "object.hpp"

#include <MonoEngine/core/log.hpp>

namespace renderer {

namespace rt {

Object::Object(const std::vector<float> & vertices, const std::vector<float> & normals, const std::vector<float> & colors)
  : m_vertices{vertices},
	m_normals{normals},
	m_colors{colors}
{
	LOG_ASSERT(m_vertices.size() == m_normals.size(), "number of vertices and normals are not equal");
	LOG_ASSERT(m_vertices.size() == m_colors.size(), "number of vertices and colors are not equal");
	LOG_ASSERT(m_vertices.size() % 12 == 0, "number of floats for vertices is not multiple of 12");
	LOG_ASSERT(m_vertices.size() >= 12, "number of vertices is smaller than 3");
}

unsigned int Object::getNumTriangles() const {
	return static_cast<unsigned int>(m_vertices.size()) / 12;
}

const std::vector<float> & Object::getVertices() const {
	return m_vertices;
}

const std::vector<float> & Object::getNormals() const {
	return m_normals;
}

const std::vector<float> & Object::getColors() const {
	return m_colors;
}

} // namespace rt

} // namespace renderer