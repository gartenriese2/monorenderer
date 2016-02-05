#include "renderer/renderer.hpp"
#include "renderer/rt/objects/box.hpp"
#include "renderer/rt/objects/quad.hpp"
#include "renderer/rt/objects/extern.hpp"
#include "renderer/rt/renderer.hpp"

#include <MonoEngine/core/log.hpp>


#include <cstdlib>

int main() {

	renderer::Renderer renderer("config.xml");

	renderer::rt::Box boxLeft({-2.f, -4.5f, -4.f}, {-1.f, -4.5f, -5.f}, {-2.f, -2.5f, -4.f}, {-3.f, -4.5f, -5.f}, {1.f, 0.f, 0.f, 1.f});
	renderer::rt::Box boxRight({1.f, -1.f, -4.f}, {2.f, -1.f, -4.f}, {1.f, 0.f, -4.f}, {1.f, -1.f, -5.f}, {1.f, 1.f, 0.f, 1.f});

	renderer::rt::Quad wallLeft({-5.f, -5.f, 0.f}, {-5.f, -5.f, -10.f}, {-5.f, 5.f, -10.f}, {-5.f, 5.f, 0.f}, {0.5f, 0.5f, 0.5f, 1.f});
	renderer::rt::Quad wallDown({-5.f, -5.f, 0.f}, {5.f, -5.f, 0.f}, {5.f, -5.f, -10.f}, {-5.f, -5.f, -10.f}, {0.5f, 0.5f, 0.5f, 1.f});
	renderer::rt::Quad wallRight({5.f, -5.f, -10.f}, {5.f, -5.f, 0.f}, {5.f, 5.f, 0.f}, {5.f, 5.f, -10.f}, {0.5f, 0.5f, 0.5f, 1.f});
	renderer::rt::Quad wallUp({-5.f, 5.f, -10.f}, {5.f, 5.f, -10.f}, {5.f, 5.f, 0.f}, {-5.f, 5.f, 0.f}, {0.5f, 0.5f, 0.5f, 1.f});
	renderer::rt::Quad wallBack({-5.f, -5.f, -10.f}, {5.f, -5.f, -10.f}, {5.f, 5.f, -10.f}, {-5.f, 5.f, -10.f}, {0.5f, 0.5f, 0.5f, 1.f});

	renderer::rt::Extern dragon("assets/dragon/dragon_vrip_res2.ply");

	renderer::rt::Renderer rtRenderer;
	// rtRenderer.add(boxLeft);
	rtRenderer.add(boxRight);
	rtRenderer.add(wallLeft);
	rtRenderer.add(wallDown);
	rtRenderer.add(wallRight);
	rtRenderer.add(wallUp);
	rtRenderer.add(wallBack);

	rtRenderer.add(dragon);

	while (renderer.render()) {
		rtRenderer.render();
	}

	return EXIT_SUCCESS;

}
