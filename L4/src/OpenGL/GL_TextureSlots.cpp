#include "GL_TextureSlots.h"

#include "GL_gl.h"


namespace OpenGL
{
	int32_t TextureSlots::m_max_concurrent_textures = 0;
	int32_t TextureSlots::m_max_combined_textures = 0;

	void TextureSlots::init()
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_max_concurrent_textures);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_max_combined_textures);
	}

	void TextureSlots::bindTexture(Texture* texture)
	{
		uint32_t texture_id = texture->m_id;

		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	void TextureSlots::setActiveTextureSlot(const uint32_t& slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	int32_t TextureSlots::getMaxConcurrentTextures()
	{
		return m_max_concurrent_textures;
	}

	int32_t TextureSlots::getMaxCombinedTextures()
	{
		return m_max_combined_textures;
	}
}


