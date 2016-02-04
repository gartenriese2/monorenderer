#include "box.hpp"

namespace renderer {

namespace rt {

Box::Box(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & d, const glm::vec3 & f, const glm::vec4 & col) {
	const glm::vec3 c {b + d - a};
	const glm::vec3 e {b + f - a};
	const glm::vec3 g {d + f - a};
	const glm::vec3 h {e + d - a};

	m_vertices = std::vector<float>{
		// front
		a.x, a.y, a.z, 0.f,
		b.x, b.y, b.z, 0.f,
		c.x, c.y, c.z, 0.f,
		a.x, a.y, a.z, 0.f,
		c.x, c.y, c.z, 0.f,
		d.x, d.y, d.z, 0.f,
		// back
		e.x, e.y, e.z, 0.f,
		f.x, f.y, f.z, 0.f,
		g.x, g.y, g.z, 0.f,
		e.x, e.y, e.z, 0.f,
		g.x, g.y, g.z, 0.f,
		h.x, h.y, h.z, 0.f,
		// left
		f.x, f.y, f.z, 0.f,
		a.x, a.y, a.z, 0.f,
		d.x, d.y, d.z, 0.f,
		f.x, f.y, f.z, 0.f,
		d.x, d.y, d.z, 0.f,
		g.x, g.y, g.z, 0.f,
		// right
		b.x, b.y, b.z, 0.f,
		f.x, f.y, f.z, 0.f,
		h.x, h.y, h.z, 0.f,
		b.x, b.y, b.z, 0.f,
		h.x, h.y, h.z, 0.f,
		c.x, c.y, c.z, 0.f,
		// top
		d.x, d.y, d.z, 0.f,
		c.x, c.y, c.z, 0.f,
		h.x, h.y, h.z, 0.f,
		d.x, d.y, d.z, 0.f,
		h.x, h.y, h.z, 0.f,
		g.x, g.y, g.z, 0.f,
		// bottom
		e.x, e.y, e.z, 0.f,
		f.x, f.y, f.z, 0.f,
		a.x, a.y, a.z, 0.f,
		e.x, e.y, e.z, 0.f,
		a.x, a.y, a.z, 0.f,
		b.x, b.y, b.z, 0.f
	};
	const glm::vec3 nFront {glm::normalize(glm::cross(b - a, c - a))};
	const glm::vec3 nLeft {glm::normalize(glm::cross(a - f, d - f))};
	const glm::vec3 nTop {glm::normalize(glm::cross(c - d, h - d))};
	m_normals = std::vector<float>{
		nFront.x, nFront.y, nFront.z, 0.f,
		nFront.x, nFront.y, nFront.z, 0.f,
		nFront.x, nFront.y, nFront.z, 0.f,
		nFront.x, nFront.y, nFront.z, 0.f,
		nFront.x, nFront.y, nFront.z, 0.f,
		nFront.x, nFront.y, nFront.z, 0.f,

		-nFront.x, -nFront.y, -nFront.z, 0.f,
		-nFront.x, -nFront.y, -nFront.z, 0.f,
		-nFront.x, -nFront.y, -nFront.z, 0.f,
		-nFront.x, -nFront.y, -nFront.z, 0.f,
		-nFront.x, -nFront.y, -nFront.z, 0.f,
		-nFront.x, -nFront.y, -nFront.z, 0.f,

		nLeft.x, nLeft.y, nLeft.z, 0.f,
		nLeft.x, nLeft.y, nLeft.z, 0.f,
		nLeft.x, nLeft.y, nLeft.z, 0.f,
		nLeft.x, nLeft.y, nLeft.z, 0.f,
		nLeft.x, nLeft.y, nLeft.z, 0.f,
		nLeft.x, nLeft.y, nLeft.z, 0.f,

		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,
		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,
		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,
		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,
		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,
		-nLeft.x, -nLeft.y, -nLeft.z, 0.f,

		nTop.x, nTop.y, nTop.z, 0.f,
		nTop.x, nTop.y, nTop.z, 0.f,
		nTop.x, nTop.y, nTop.z, 0.f,
		nTop.x, nTop.y, nTop.z, 0.f,
		nTop.x, nTop.y, nTop.z, 0.f,
		nTop.x, nTop.y, nTop.z, 0.f,

		-nTop.x, -nTop.y, -nTop.z, 0.f,
		-nTop.x, -nTop.y, -nTop.z, 0.f,
		-nTop.x, -nTop.y, -nTop.z, 0.f,
		-nTop.x, -nTop.y, -nTop.z, 0.f,
		-nTop.x, -nTop.y, -nTop.z, 0.f,
		-nTop.x, -nTop.y, -nTop.z, 0.f
	};
	m_colors = std::vector<float>{
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,
		col.r, col.g, col.b, col.a,

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