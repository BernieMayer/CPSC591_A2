/*
 * SceneShader.h
 *
 *  Created on: Nov 17, 2015
 *      Author: acarocha
 */

#ifndef SCENESHADER_H_
#define SCENESHADER_H_

#include "Shader.h"
#include "texture.h"
#include "lodepng.h"
#include <vector>

#define GLM_FORCE_RADIANS

#include "TriMesh.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SceneShader : public Shader
{
public:

	SceneShader();
	~SceneShader();

	void startup ();
	void shutdown ();
	void render();

	void renderPlane();
	void renderMesh();
	void renderLight();

	void setAspectRatio( float ratio );
	void setZTranslation(float z);
	void setRotationX( float x );
	void setRotationY( float y );

	void updateLightPositionX( float x );
	void updateLightPositionY( float y );
	void updateLightPositionZ( float z );

	void updateR_Value(float delta_r);

private:

	/*methods*/

	void calculateCylindricalUVCoordinates();
	void readMesh( std::string filename );
	void createVertexBuffer();


	/*variables*/
	GLuint _programLight;
	GLuint _programPlane;
	GLuint _programMesh;

	GLuint _planeVertexArray;
	GLuint _planeVertexBuffer;
	GLuint _planeTextureBuffer;

	GLuint _meshVertexArray;
	GLuint _meshVertexBuffer;
	GLuint _meshNormalBuffer;
	GLuint _meshIndicesBuffer;
	GLuint _meshTextureBuffer;

        GLint _mvUniform, _projUniform;

	/* Matrices */
	glm::mat4 _modelview;
	glm::mat4 _projection;

	//Textures
	GLuint _textureID;
	GLuint _texture2Did;
	Texture _texture;

	std::vector<glm::vec2> _uvs;

	std::vector<unsigned char> _image;
	unsigned int _imageWidth;
	unsigned int _imageHeight;

	float _zTranslation;
	float _xRot;
	float _yRot;
	float _aspectRatio;
	float _r;


	trimesh::TriMesh* _mesh;
	std::vector<unsigned int> _triangleIndices;

	glm::vec3 lightPosition;

};

#endif /* SCENESHADER_H_ */
