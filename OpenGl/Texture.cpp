#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

// Constructor takes filename using stb image
Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	//Load the texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width , &height, &numComponents,4);

	if (imageData == NULL)
	{
		std::cerr << "Texture Loading Failed" << fileName << std::endl;
	}

	//generate space for one texture
	glGenTextures(1, &m_texture);
	//Type of texture
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Texture wrapping Wrap_s = Height, wrap T = width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//How opengl deals with drawing the resolution of the texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//send data to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	//Delete texture data once delt with
	stbi_image_free(imageData);
}

//Deconstructor
Texture::~Texture()
{
	//Delete texture
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	//Keep within bounds
	assert(unit >= 0 && unit <= 31);
	//Sets the active to the default 0 + the index
	glActiveTexture(GL_TEXTURE0 + unit);
	// Bind texture to that unit
	glBindTexture(GL_TEXTURE_2D, m_texture);
}