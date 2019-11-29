/************************************************
 *NAME              : sangmin.kim
 *ASSIGNMENT NUMBER : 6
 *COURSE NAME       : CS230
 *TERM              : Spring 2019
 ************************************************/
#include "Image.hpp"
#include "Texture.hpp"
#include <cassert>
#include <filesystem>

bool Texture::LoadFromPNG(const std::filesystem::path& file_path) noexcept
{
	Image temp_image;
	if (temp_image.LoadFromPNG(file_path))
	{
		return LoadFromImage(temp_image);
	}
	return false;
}

bool Texture::LoadFromImage(const Image& image) noexcept
{
	return LoadFromMemory(image.GetWidth(), image.GetHeight(), image.GetPixelsPointer());
}

bool Texture::LoadFromMemory(const int image_width, const int image_height, const Color4ub* colors) noexcept
{
	assert(image_width > 0 && image_height > 0);
	assert(colors != nullptr);

	DeleteTexture();
	width = image_width;
	height = image_height;
	/*glCheck(glGenTextures(1, &textureHandle));
	glCheck(glBindTexture(GL_TEXTURE_2D, textureHandle));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, colors));
	glCheck(glBindTexture(GL_TEXTURE_2D, textureHandle));

	return glGetError() == GL_NO_ERROR;*/

	return false;
}

void Texture::SelectTextureForSlot(const Texture& texture, unsigned slot) noexcept
{
	if (texture.GetTextureHandle())
	{
		//glCheck(glActiveTexture(GL_TEXTURE0 + slot));
		//glCheck(glBindTexture(GL_TEXTURE_2D, texture.GetTextureHandle()));
	}
}


void Texture::DeleteTexture() noexcept
{
	if (GetTextureHandle() != 0)
	{
		/*glCheck(glDeleteTextures(1, &textureHandle));*/
		textureHandle = 0;
	}
}

Texture::~Texture() noexcept
{
	DeleteTexture();
}

Texture::Texture(Texture&& other) noexcept
	: textureHandle{ other.textureHandle }, width{ other.width }, height{ other.height }
{
	other.textureHandle = 0;
	other.width = 0;
	other.height = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this == &other)
		return *this;
	DeleteTexture();
	textureHandle = other.textureHandle;
	width = other.width;
	height = other.height;
	other.textureHandle = 0;
	other.width = 0;
	other.height = 0;
	return *this;
}

