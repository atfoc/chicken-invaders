#include <iostream>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>
#include <algorithm>
#include <GL/gl.h>
#include "engine/model.hpp"
#include "engine/application.hpp"
#include "engine/log.hpp"

namespace rg
{
namespace engine
{

	static void load_textures(const aiScene* scene, texture_loader* tl, const std::string& path_to_model);
	static void recursive_render (const struct aiScene *sc, const struct aiNode* nd, texture_loader* tl, const std::string& path_to_model);

	model::model(const std::string& path, texture_loader* tl)
		:	tl_{tl},
			path_to_model_(path.substr(0,path.find_last_of("/")))
	{
		scene_ = importer_.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
		load_textures(scene_, tl, path.substr(0, path.find_last_of("/")));
	}

	void model::render(void)
	{
	//	clock_t c;
	//	c = std::clock();
		recursive_render(scene_, scene_->mRootNode, tl_, path_to_model_);
	//	c = std::clock() - c;

//		(*application::logger()) << log::priority::debug << path_to_model_<< " " << c << " " << static_cast<float>(c)/CLOCKS_PER_SEC<< log::end_log;
	}

	bool model::has_textures(void)
	{
		return scene_->HasTextures();
	}

	static void load_textures(const aiScene* scene, texture_loader* tl, const std::string& path_to_model)
	{
		for (unsigned int m=0; m<scene->mNumMaterials; m++)
		{
			int texIndex = 0;
			aiReturn texFound = AI_SUCCESS;

			aiString path;	// filename

			std::vector<std::string> texture_to_wait;

			while (true)
			{
				texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
				if(AI_SUCCESS == texFound)
				{
					texIndex++;
					auto res = tl->try_to_load(path_to_model+"/"+path.data);

					if(!res.first)
					{
						texture_to_wait.push_back(path.data);						
					}
				}
				else
				{
					break;
				}
			}
			
			std::for_each(texture_to_wait.begin(), texture_to_wait.end(), [&](const auto& s){tl->load(s);});
		}
	}

	void Color4f(const aiColor4D *color)
	{
		glColor4f(color->r, color->g, color->b, color->a);
	}
	
	void set_float4(float f[4], float a, float b, float c, float d)
	{
		f[0] = a;
		f[1] = b;
		f[2] = c;
		f[3] = d;
	}
	
	void color4_to_float4(const aiColor4D *c, float f[4])
	{
		f[0] = c->r;
		f[1] = c->g;
		f[2] = c->b;
		f[3] = c->a;
	}
	
	void apply_material(const aiMaterial *mtl, texture_loader* tl, const std::string& path_to_model)
	{
		float c[4];
	
		GLenum fill_mode;
		int ret1, ret2;
		aiColor4D diffuse;
		aiColor4D specular;
		aiColor4D ambient;
		aiColor4D emission;
		ai_real shininess, strength;
		int two_sided;
		int wireframe;
		unsigned int max;	// changed: to unsigned
	
		int texIndex = 0;
		aiString texPath;	//contains filename of texture
	
		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
		{
			//bind texture
			unsigned int texId = tl->load(path_to_model + "/" + texPath.data).second;
			glBindTexture(GL_TEXTURE_2D, texId);
		}
	
		set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
		if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
			color4_to_float4(&diffuse, c);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);
	
		set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
		if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
			color4_to_float4(&specular, c);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	
		set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
		if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
			color4_to_float4(&ambient, c);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);
	
		set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
		if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
			color4_to_float4(&emission, c);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);
	
		max = 1;
		ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
		max = 1;
		ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
		else {
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
			set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
		}
	
		max = 1;
		if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
			fill_mode = wireframe ? GL_LINE : GL_FILL;
		else
			fill_mode = GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
	
		max = 1;
		if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
	
	
	static void recursive_render (const struct aiScene *sc, const struct aiNode* nd, texture_loader* tl, const std::string& path_to_model)
	{
		unsigned int i;
		unsigned int n=0, t;
		aiMatrix4x4 m = nd->mTransformation;
	
		// update transform
		m.Transpose();
		glPushMatrix();
		glMultMatrixf((float*)&m);
	
		// draw all meshes assigned to this node
		for (; n < nd->mNumMeshes; ++n)
		{
			const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
	
			apply_material(sc->mMaterials[mesh->mMaterialIndex], tl, path_to_model);
	
	
			if(mesh->mNormals == NULL)
			{
				glDisable(GL_LIGHTING);
			}
			else
			{
				glEnable(GL_LIGHTING);
			}
	
			if(mesh->mColors[0] != NULL)
			{
				glEnable(GL_COLOR_MATERIAL);
			}
			else
			{
				glDisable(GL_COLOR_MATERIAL);
			}
	
			for (t = 0; t < mesh->mNumFaces; ++t) {
				const struct aiFace* face = &mesh->mFaces[t];
				GLenum face_mode;
	
				switch(face->mNumIndices)
				{
					case 1: face_mode = GL_POINTS; break;
					case 2: face_mode = GL_LINES; break;
					case 3: face_mode = GL_TRIANGLES; break;
					default: face_mode = GL_POLYGON; break;
				}
	
				glBegin(face_mode);
	
				for(i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
				{
					int vertexIndex = face->mIndices[i];	// get group index for current index
					if(mesh->mColors[0] != NULL)
					{

						Color4f(&mesh->mColors[0][vertexIndex]);
					}
	
					if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}
	
					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
				}
				glEnd();
			}
		}
	
		// draw all children
		for (n = 0; n < nd->mNumChildren; ++n)
		{
			recursive_render(sc, nd->mChildren[n], tl, path_to_model);
		}
	
		glPopMatrix();
	}

}
}
