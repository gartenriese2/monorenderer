#pragma once

#include <glm/glm.hpp>

#include <string>

namespace tinyxml2 {
	class XMLDocument;
}

namespace renderer {

class ConfigReader {

	public:

		ConfigReader(const std::string & path);
		ConfigReader(const ConfigReader & ) = default;
		ConfigReader(ConfigReader &&) = default;
		ConfigReader & operator=(const ConfigReader &) = default;
		ConfigReader & operator=(ConfigReader &&) & = default;
		~ConfigReader() = default;

		const glm::uvec2 & getSize() const;
		const std::string & getTitle() const;

	private:

		bool readConfig(const tinyxml2::XMLDocument & doc);
		void setDefaults();

		glm::uvec2 m_size;
		std::string m_title;

};

static_assert(std::is_nothrow_move_constructible<ConfigReader>(), "Should be noexcept MoveConstructible");
static_assert(std::is_copy_constructible<ConfigReader>(), "Should be CopyConstructible");
static_assert(std::is_move_assignable<ConfigReader>(), "Should be MoveAssignable");
static_assert(std::is_copy_assignable<ConfigReader>(), "Should be CopyAssignable");

} // namespace renderer