#pragma once

#include "object.hpp"

#include <glm/glm.hpp>

namespace renderer {

namespace rt {

class Custom : public Object {

	public:

		Custom(const std::vector<glm::vec3> & vertices, const glm::vec4 & col = {1.f, 1.f, 1.f, 1.f});

};

static_assert(std::is_nothrow_move_constructible<Custom>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Custom>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Custom>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Custom>(), "Should be CopyAssignable");

}

} // namespace renderer