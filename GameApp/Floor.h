


#pragma once 

#include "common.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

#include "stb_image.h"

typedef glm::vec4  color4;
typedef glm::vec4  point4;


class Floor {

public:
	Floor();
	void run(glm::mat4 projection, glm::mat4 view);
private:
	GLuint buffer;
	GLuint arrayBuffer;
	// Model-view and projection matrices uniform location
	
	Shader * floorShader;


};

