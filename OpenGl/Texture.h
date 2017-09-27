#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	//load texture from a filename
	Texture(const std::string& fileName);
	// can bind more than one texture
	void Bind(unsigned int unit);
	virtual ~Texture();
	
protected:
private:Texture(const Texture& other) {}
		Texture& operator=(const Texture& other) {}


		GLuint m_texture;
};

#endif // TEXTURE_H
