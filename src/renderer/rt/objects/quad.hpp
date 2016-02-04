#pragma once

#include "object.hpp"

#include <glm/glm.hpp>

namespace renderer {

namespace rt {

class Quad : public Object {

	public:

		Quad(const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c, const glm::vec3 & d, const glm::vec4 & col = {1.f, 1.f, 1.f, 1.f});

};

static_assert(std::is_nothrow_move_constructible<Quad>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Quad>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Quad>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Quad>(), "Should be CopyAssignable");

}

} // namespace renderer