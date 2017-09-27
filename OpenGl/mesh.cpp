#include "mesh.h"
#include <vector>
#include <glm\glm.hpp>
#include "obj_loader.h"
#include "transform.h"
#include <glm\gtx\transform.hpp>

//load obj
Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}


//Constructor
Mesh::Mesh(Vertex* vertices, unsigned int numVerticies, unsigned int* indices, unsigned int numIndicess)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVerticies; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}
	for (unsigned int i = 0; i < numIndicess; i++)
	{
		model.indices.push_back(indices[i]);
	}



	InitMesh(model);

	/// This is for hard coded vertices

	//m_drawCount = numIndicess;
	/*
	//m_drawCount = numVerticies;
	
	glGenVertexArrays(1,&m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	//reserve the memory of x number of num verticies
	positions.reserve(numVerticies);
	texCoords.reserve(numVerticies);
	for (unsigned int i = 0; i < numVerticies; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}
	// blocks of data on the gpu
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ARRAY_BUFFER, numVerticies*sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
	//vertex attrubes (position)
	glEnableVertexAttribArray(0);
	// Where data starts, how many pieces 3 (vec3),type,normalise,how many it has to skip to next same data,how much it needs to start at the beginning of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ARRAY_BUFFER, numVerticies*sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	//vertex attrubes (position)
	glEnableVertexAttribArray(1);
	// Where data starts, how many pieces 3 (vec3),type,normalise,how many it has to skip to next same data,how much it needs to start at the beginning of data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicess*sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);*/
}

//Deconstructor
Mesh::~Mesh()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//delete array
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	
}


void Mesh::InitMesh(const IndexedModel& model)
{
	m_drawCount = model.indices.size();
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// blocks of data on the gpu
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	
	//size of buffer, all the vertices in the array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	
	//vertex attrubes (position)
	glEnableVertexAttribArray(0);
	// Where data starts, how many pieces 3 (vec3),type,normalise,how many it has to skip to next same data,how much it needs to start at the beginning of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	//vertex attrubes (position)
	glEnableVertexAttribArray(1);
	// Where data starts, how many pieces 3 (vec3),type,normalise,how many it has to skip to next same data,how much it needs to start at the beginning of data
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

	//vertex attrubes (position)
	glEnableVertexAttribArray(2);
	// Where data starts, how many pieces 3 (vec3),type,normalise,how many it has to skip to next same data,how much it needs to start at the beginning of data
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//bind buffer to pos, take buffer as an array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//size of buffer, all the vertices in the array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);



	

	glBindVertexArray(0);

}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	
	//draw type, where to start, where to end
	//glDrawArrays(GL_TRIANGLES, 0, 0);
	//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glDrawElementsBaseVertex(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}