#pragma once

#include "object.hpp"

#include <string>

namespace renderer {

namespace rt {

class Extern : public Object {

	public:

		Extern(const std::string & path);

};

static_assert(std::is_nothrow_move_constructible<Extern>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<Extern>(), "Should be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Extern>(), "Should be noexcept MoveAssignable");
static_assert(std::is_copy_assignable<Extern>(), "Should be CopyAssignable");

}

} // namespace renderer