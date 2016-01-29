#include "configreader.hpp"

#include <MonoEngine/core/log.hpp>

#include "../extern/tinyxml2.h"

namespace renderer {

ConfigReader::ConfigReader(const std::string & path) {
	tinyxml2::XMLDocument doc;
	const auto err = doc.LoadFile(path.c_str());
	if (err != tinyxml2::XML_NO_ERROR) {
		doc.PrintError();
		setDefaults();
	} else {
		if (!readConfig(doc)) {
			setDefaults();
		}
	}
}

bool ConfigReader::readConfig(const tinyxml2::XMLDocument & doc) {
	const auto * rootElem {doc.RootElement()};
	if (!rootElem || std::strcmp(rootElem->Name(), "config") != 0 || rootElem->NoChildren())
		return false;

	const auto * elem {rootElem->FirstChildElement("title")};
	if (elem == nullptr) {
		return false;
	}
	m_title = elem->GetText();

	elem = rootElem->FirstChildElement("width");
	if (elem == nullptr) {
		return false;
	}
	auto width {0u};
	elem->QueryUnsignedText(&width);

	elem = rootElem->FirstChildElement("height");
	if (elem == nullptr) {
		return false;
	}
	auto height {0u};
	elem->QueryUnsignedText(&height);

	if (width == 0 || height == 0)
		return false;
	m_size = glm::uvec2(width, height);

	return true;
}

void ConfigReader::setDefaults() {
	LOG_WARNING("setting default config settings");
	m_size = glm::uvec2(640, 480);
	m_title = "Default";
}

const glm::uvec2 & ConfigReader::getSize() const {
	return m_size;
}

const std::string & ConfigReader::getTitle() const {
	return m_title;
}

} // namespace renderer
