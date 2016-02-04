#pragma once

#include "object.hpp"

#include <glm/glm.hpp>

namespace renderer {

namespace rt {

class Box : public Object {

	public:

		Box(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & d, const glm::vec3 & f, const glm::vec4 & col = {1.f, 1.f, 1.f, 1.f});

};

static_assert(std::is_nothrow_move_constructible<Box>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Box>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Box>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Box>(), "Should be CopyAssignable");

}

} // namespace renderer