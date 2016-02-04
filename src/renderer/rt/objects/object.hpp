#pragma once

#include <MonoEngine/object.hpp>

#include <vector>

namespace renderer {

namespace rt {

class Object {

	public:

		void move(float val, const glm::vec3 & dir) { m_obj.move(val, dir); }
		void moveLocal(float val, const glm::vec3 & dir) { m_obj.moveLocal(val, dir); }
		void moveTo(const glm::vec3 & to) { m_obj.moveTo(to); }
		void resetMoves() { m_obj.resetMoves(); }

		void scale(const glm::vec3 & val) { m_obj.scale(val); }
		void resetScale() { m_obj.resetScale(); }

		void rotate(float radians, const glm::vec3 & axis) {m_obj.rotate(radians, axis); }
		void rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point = {0.f, 0.f, 0.f}) { m_obj.rotateAround(radians, axis, point); }

		unsigned int getNumTriangles() const;
		const std::vector<float> & getVertices() const;
		const std::vector<float> & getNormals() const;
		const std::vector<float> & getColors() const;

	protected:

		Object() {}
		Object(const std::vector<float> & vertices, const std::vector<float> & normals, const std::vector<float> & colors);

		std::vector<float> m_vertices;
		std::vector<float> m_normals;
		std::vector<float> m_colors;

	private:

		engine::Object m_obj;
		
};

static_assert(std::is_nothrow_move_constructible<Object>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Object>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Object>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Object>(), "Should be CopyAssignable");

} // namespace rt

} // namespace renderer