#include "renderer/renderer.hpp"

#include <cstdlib>

int main() {

	renderer::Renderer renderer("config.xml");

	while (renderer.render()) {

	}

	return EXIT_SUCCESS;

}
