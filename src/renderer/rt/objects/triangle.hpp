#pragma once

#include "object.hpp"

#include <glm/glm.hpp>

namespace renderer {

namespace rt {

class Triangle : public Object {

	public:

		Triangle(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec4 & col = {1.f, 1.f, 1.f, 1.f});

};

static_assert(std::is_nothrow_move_constructible<Triangle>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Triangle>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Triangle>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Triangle>(), "Should be CopyAssignable");

}

} // namespace renderer