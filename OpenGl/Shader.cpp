#include "Shader.h"
#include <string>
#include <iostream>
#include "GL/glew.h"
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "camera.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

//Constructor
Shader::Shader(const std::string& fileName)
{
	//create a shader program
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glBindAttribLocation(m_program,0,"position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	// check link status, - check what, error type, inside, error message
	CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR:LINK FAILED");

	glValidateProgram(m_program);
	// validate program, - check what, error type, inside, error message
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR:LINK FAILED");

	// transform uniform
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

//Destructor
Shader::~Shader()
{
	//Delete Shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	//delete program
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	//bind shader to program
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	//mat4 
	//
	// update matrix 4 floating values
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	// uniform wanting to update, how many values to pass in, transpose ( not needed due to glm ), data
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cerr << "Error : No Shader Created" << std::endl;
	}
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR:Shader Error");
	return shader;

}


// load a text file
static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "unable to use shader: " << fileName << std::endl;
	}
	return output;
}

// FInd error messages and generate
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
