#include "renderer.hpp"

#include <MonoEngine/gl/shader.hpp>
#include <MonoEngine/core/log.hpp>

namespace renderer {

namespace rt {

constexpr unsigned int screenWidth {800u};
constexpr unsigned int screenHeight {800u};
constexpr unsigned int k_maxLights {10u};

Renderer::Renderer()
  : m_isctProg{"isct prog"},
	m_ssqProg{"ssq prog"},
	m_vao{"ssq vao"},
	m_vbo{"ssq vbo"},
	m_ssbo{"ssbo"},
	m_lightBuffer{"lights"},
	m_hasTraced{false}
{
	gl::Shader isctShader("shader/rt/whitted.comp", "isct_comp");
	m_isctProg.attachShader(isctShader);

	gl::Shader ssqVert("shader/rt/ssq.vert", "ssq_vert");
	gl::Shader ssqFrag("shader/rt/ssq.frag", "ssq_frag");
	m_ssqProg.attachShader(ssqVert);
	m_ssqProg.attachShader(ssqFrag);

	std::vector<GLfloat> vec = {
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		-1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f
	};
	m_vbo.createImmutableStorage(static_cast<unsigned int>(vec.size() * sizeof(GLfloat)), 0, vec.data());

	m_vao.bind();
	m_vao.enableAttribBinding(0);
	m_vao.bindVertexBuffer(0, m_vbo, 0, 3 * sizeof(GLfloat));
	m_vao.bindVertexFormat(0, 0, 3, GL_FLOAT, GL_FALSE, 0);

	m_ssbo.createImmutableStorage(screenHeight * screenWidth * 4 * sizeof(GLfloat), GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_DYNAMIC_STORAGE_BIT);

	m_lightBuffer.createImmutableStorage(k_maxLights * 4 * sizeof(GLfloat), GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_DYNAMIC_STORAGE_BIT);
	const std::vector<float> lightPos {
		0.f, 3.5f, -0.5f, 0.f,
		4.5f, -4.5f, -0.5f, 0.f
	};
	m_lightBuffer.setData(0, 8 * sizeof(GLfloat), lightPos.data());
}

void Renderer::add(const Object & object) {
	m_buffer.add(object);
}

void Renderer::render() {
	

	if (!m_hasTraced) {

		m_gpuTimer.start();

		m_isctProg.use();
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_buffer.getVertexBuffer());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_buffer.getNormalBuffer());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_buffer.getColorBuffer());
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, m_lightBuffer);
		m_isctProg["numTris"] = m_buffer.getNumTriangles();
		m_isctProg["numLights"] = 1u;//static_cast<unsigned int>(m_lightBuffer.getSize() / 4 / sizeof(float));
		m_isctProg["eyePos"] = glm::vec3{0.f, 0.f, 10.f};
		m_isctProg["screenDim"] = glm::uvec2{screenWidth, screenHeight};
		m_isctProg["maxDepth"] = 2u;
		glDispatchCompute(screenWidth / 8, screenHeight / 8, 1);
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		m_hasTraced = true;

		auto t {m_gpuTimer.stop()};
		LOG("GPU Time in ms: " + std::to_string(static_cast<double>(t) / 1000000.));

	}

	// {
	//  	GLfloat * ptr = static_cast<GLfloat *>(m_buffer.getNormalBuffer().map(0, 24 * sizeof(GLfloat), GL_MAP_READ_BIT));
	//  	LOG("normal0 (" + std::to_string(ptr[0]) + "|" + std::to_string(ptr[1]) + "|" + std::to_string(ptr[2]) + "|" + std::to_string(ptr[3]) + ")");
	// 	LOG("normal1 (" + std::to_string(ptr[4]) + "|" + std::to_string(ptr[5]) + "|" + std::to_string(ptr[6]) + "|" + std::to_string(ptr[7]) + ")");
	// 	LOG("normal2 (" + std::to_string(ptr[8]) + "|" + std::to_string(ptr[9]) + "|" + std::to_string(ptr[10]) + "|" + std::to_string(ptr[11]) + ")");
	// 	LOG("normal3 (" + std::to_string(ptr[12]) + "|" + std::to_string(ptr[13]) + "|" + std::to_string(ptr[14]) + "|" + std::to_string(ptr[15]) + ")");
	// 	LOG("normal4 (" + std::to_string(ptr[16]) + "|" + std::to_string(ptr[17]) + "|" + std::to_string(ptr[18]) + "|" + std::to_string(ptr[19]) + ")");
	// 	LOG("normal5 (" + std::to_string(ptr[20]) + "|" + std::to_string(ptr[21]) + "|" + std::to_string(ptr[22]) + "|" + std::to_string(ptr[23]) + ")");
	// 	m_buffer.getNormalBuffer().unmap();
	// }

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ssqProg.use();
	m_vao.bind();
	m_ssqProg["width"] = screenWidth;
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

} // namespace rt

} // namespace renderer