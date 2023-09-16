#include "GL_Texture.h"

#include <iostream>

#include <stb_image/stb_image.h>

#include "GL_gl.h"


namespace OpenGL
{
	Texture::Texture()
		:
		m_width(0),
		m_height(0),
		m_BPP(0)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
	}

	Texture::Texture(const std::string& path)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
		loadTexture(path);
	}

    Texture::Texture(const TextureData& texture_data)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        loadTexture(texture_data);
    }

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_id);
	}

	void Texture::loadTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);

        int width, height, bpp;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &bpp, 4);
		if (data) {
            loadTexture({ data, width, height });
			stbi_image_free(data);
		}
		else {
			std::cout << "[ERROR] Texture.cpp: Couldn't load texture because texture file was not found\n";
		}
	}

    void Texture::loadTexture(const TextureData& texture_data)
    {
        m_width = texture_data.width;
        m_height = texture_data.height;

        glBindTexture(GL_TEXTURE_2D, m_id);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        //glTextureStorage2D(m_id, 1, GL_RGBA, m_width, m_height);
        //glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_data.width, texture_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data.data);
    }
}


