#include "custom.hpp"

#include <MonoEngine/core/log.hpp>

namespace renderer {

namespace rt {

Custom::Custom(const std::vector<glm::vec3> & vertices, const glm::vec4 & col) {
	LOG_ASSERT(vertices.size() % 3 == 0, "number of vertices is not a multiple of 3");

	m_vertices.clear();
	m_normals.clear();
	m_colors.clear();

	for (const auto & vertex : vertices) {
		m_vertices.emplace_back(vertex.x);
		m_vertices.emplace_back(vertex.y);
		m_vertices.emplace_back(vertex.z);
		m_vertices.emplace_back(0.f);
		m_colors.emplace_back(col.r);
		m_colors.emplace_back(col.g);
		m_colors.emplace_back(col.b);
		m_colors.emplace_back(col.a);
	}
	
	for (unsigned int i {0u}; i < vertices.size(); i += 3) {
		const auto a {vertices[i]};
		const auto b {vertices[i + 1]};
		const auto c {vertices[i + 2]};
		const auto n {glm::normalize(glm::cross(b - a, c - a))};
		m_normals.emplace_back(n.x);
		m_normals.emplace_back(n.y);
		m_normals.emplace_back(n.z);
		m_normals.emplace_back(0.f);
		m_normals.emplace_back(n.x);
		m_normals.emplace_back(n.y);
		m_normals.emplace_back(n.z);
		m_normals.emplace_back(0.f);
		m_normals.emplace_back(n.x);
		m_normals.emplace_back(n.y);
		m_normals.emplace_back(n.z);
		m_normals.emplace_back(0.f);
	}
}

}

} // namespace renderer