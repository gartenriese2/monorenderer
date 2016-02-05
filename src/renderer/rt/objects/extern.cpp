#include "extern.hpp"

#include <MonoEngine/core/log.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wconversion"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#pragma GCC diagnostic pop
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

namespace renderer {

namespace rt {

Extern::Extern(const std::string & path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	if (!scene) {
		LOG(importer.GetErrorString());
	} else {
		LOG_ASSERT(scene->HasMeshes(), "imported scene has no meshes");
		const auto * meshes = scene->mMeshes;
		LOG("numMeshes:" + std::to_string(scene->mNumMeshes));
		for (auto i {0u}; i < scene->mNumMeshes; ++i) {
			LOG_ASSERT(meshes[i]->HasPositions() && meshes[i]->HasFaces(), "mesh does not have positions or faces");

			const auto hasColors {meshes[i]->HasVertexColors(0)};

			const auto * faces = meshes[i]->mFaces;
			LOG("numFaces:" + std::to_string(meshes[i]->mNumFaces));
			// for (auto j {0u}; j < meshes[i]->mNumFaces; ++j) {
			for (auto j {0u}; j < 125000; ++j) {
				LOG_ASSERT(faces[j].mNumIndices == 3, "face is not a triangle");

				const auto aVec {meshes[i]->mVertices[faces[j].mIndices[0]]};
				auto a {glm::vec3(aVec[0], aVec[1], aVec[2])};
				const auto bVec {meshes[i]->mVertices[faces[j].mIndices[1]]};
				auto b {glm::vec3(bVec[0], bVec[1], bVec[2])};
				const auto cVec {meshes[i]->mVertices[faces[j].mIndices[2]]};
				auto c {glm::vec3(cVec[0], cVec[1], cVec[2])};

				// scaling
				a *= 30.f;
				b *= 30.f;
				c *= 30.f;

				// moving
				a += glm::vec3(0.f, -6.5f, -7.f);
				b += glm::vec3(0.f, -6.5f, -7.f);
				c += glm::vec3(0.f, -6.5f, -7.f);


				m_vertices.emplace_back(a.x);
				m_vertices.emplace_back(a.y);
				m_vertices.emplace_back(a.z);
				m_vertices.emplace_back(0.f);
				m_vertices.emplace_back(b.x);
				m_vertices.emplace_back(b.y);
				m_vertices.emplace_back(b.z);
				m_vertices.emplace_back(0.f);
				m_vertices.emplace_back(c.x);
				m_vertices.emplace_back(c.y);
				m_vertices.emplace_back(c.z);
				m_vertices.emplace_back(0.f);
				
				const auto n {glm::normalize(glm::cross(b - a, c - a))};

				m_normals.emplace_back(n.x);
				m_normals.emplace_back(n.y);
				m_normals.emplace_back(n.z);
				m_normals.emplace_back(0.f);
				m_normals.emplace_back(n.x);
				m_normals.emplace_back(n.y);
				m_normals.emplace_back(n.z);
				m_normals.emplace_back(0.f);
				m_normals.emplace_back(n.x);
				m_normals.emplace_back(n.y);
				m_normals.emplace_back(n.z);
				m_normals.emplace_back(0.f);

				glm::vec4 col;
				if (!hasColors) {
					col = glm::vec4(1.f, 0.f, 0.f, 1.f); // default color
				} else {
					const auto color {meshes[i]->mColors[0][faces[j].mIndices[0]]};
					col = glm::vec4(color.r, color.g, color.b, 1.f);
				}
				m_colors.emplace_back(col.r);
				m_colors.emplace_back(col.g);
				m_colors.emplace_back(col.b);
				m_colors.emplace_back(col.a);
				m_colors.emplace_back(col.r);
				m_colors.emplace_back(col.g);
				m_colors.emplace_back(col.b);
				m_colors.emplace_back(col.a);
				m_colors.emplace_back(col.r);
				m_colors.emplace_back(col.g);
				m_colors.emplace_back(col.b);
				m_colors.emplace_back(col.a);
			
			}
		}
		
	}
}

}

} // namespace renderer