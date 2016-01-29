#pragma once

#include "util/configreader.hpp"

#include <MonoEngine/engine.hpp>

#include <memory>

namespace renderer {

class Renderer {

	public:

		Renderer(const std::string & path);
		Renderer(const glm::uvec2 & size, const std::string & title);
		Renderer(const Renderer &) = delete;
		Renderer(Renderer &&) = default;
		Renderer & operator=(const Renderer &) = delete;
		Renderer & operator=(Renderer &&) & = default;
		~Renderer() = default;

		bool render();

	private:

		std::unique_ptr<ConfigReader> m_configReader;
		engine::Engine m_engine;

};

static_assert(std::is_nothrow_move_constructible<Renderer>(), "Should be noexcept MoveConstructible");
static_assert(!std::is_copy_constructible<Renderer>(), "Should not be CopyConstructible");
static_assert(std::is_nothrow_move_assignable<Renderer>(), "Should be noexcept MoveAssignable");
static_assert(!std::is_copy_assignable<Renderer>(), "Should not be CopyAssignable");

} // namespace renderer
