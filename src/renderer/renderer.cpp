#include "renderer.hpp"

namespace renderer {

Renderer::Renderer(const std::string & path)
  : m_configReader{new ConfigReader(path)},
  	m_engine{m_configReader->getSize(), m_configReader->getTitle(), true}
{

}

Renderer::Renderer(const glm::uvec2 & size, const std::string & title)
  : m_engine{size, title}
{

}

bool Renderer::render() {
	return m_engine.render();
}

} // namespace renderer