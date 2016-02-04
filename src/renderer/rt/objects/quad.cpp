#include "quad.hpp"

namespace renderer {

namespace rt {

Quad::Quad(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d, const glm::vec4 & col) {
	m_vertices = std::vector<float>{
		a.x, a.y, a.z, 0.f,
		b.x, b.y, b.z, 0.f,
		c.x, c.y, c.z, 0.f,

		a.x, a.y, a.z, 0.f,
		c.x, c.y, c.z, 0.f,
		d.x, d.y, d.z, 0.f
	};
	const glm::vec3 n {glm::normalize(glm::cross(b - a, c - a))};
	const glm::vec3 n2 {glm::normalize(glm::cross(c - a, d - a))};
	m_normals = std::vector<float>{
		n.x, n.y, n.z, 0.f,
		n.x, n.y, n.z, 0.f,
		n.x, n.y, n.z, 0.f,

		n2.x, n2.y, n2.z, 0.f,
		n2.x, n2.y, n2.z, 0.f,
		n2.x, n2.y, n2.z, 0.f
	};
	m_colors = std::vector<float>{
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a
	};
}

}

} // namespace renderer