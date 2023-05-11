#include "floor.h"

const int size = 4;

std::string readText(const char* textFile)
{
	FILE* fp = nullptr; // initialize to nullptr to avoid potential issues
	if (fopen_s(&fp, textFile, "rb") == 0)
	{
		std::string contents;
		std::fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp));
		std::rewind(fp);
		std::fread(&contents[0], 1, contents.size(), fp);
		std::fclose(fp);
		return(contents);
	}
	throw(errno);
}

Floor::Floor() {
	point4 points[size] = {
		point4(-0.5, 0, .5, 1.0),
		point4(0.5, 0, .5, 1.0),
		point4(0.5, 0, -.5, 1.0),
		point4(-0.5, 0, -.5, 1.0)
	};

	floorShader = new Shader({
			{ "floor.vert.glsl" },
			{ "floor.frag.glsl" },
			{ "floor.tesc.glsl" },
			{ "floor.tese.glsl" },
		});


	//array object
	glGenVertexArrays(1, &arrayBuffer);
	glBindVertexArray(arrayBuffer);


	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// load and create a texture
	// -------------------------
	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, channels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* image = stbi_load("assets/floor/albedo.jpg", &width, &height, &channels, STBI_rgb);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Enable texture mapping in the shader
	glUniform1i(glGetUniformLocation(floorShader->Id, "texture"), 0);

	//Bind the texture to texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_image_free(image);

	floorShader->Use();
	// Initialize shader lighting parameters
	point4 light_position(0, 7, -4, 0.0);
	color4 light_ambient(0.2, 0.2, 0.2, 1.0);
	color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
	color4 light_specular(1.0, 1.0, 1.0, 1.0);

	color4 material_ambient(1.0, 0.0, 1.0, 1.0);
	color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
	color4 material_specular(1.0, 0.8, 0.0, 1.0);
	float material_shininess = 200.0;

	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;


	glUniform4fv(glGetUniformLocation(floorShader->Id, "AmbientProduct"), 1, glm::value_ptr(ambient_product));
	glUniform4fv(glGetUniformLocation(floorShader->Id, "DiffuseProduct"), 1, glm::value_ptr(diffuse_product));
	glUniform4fv(glGetUniformLocation(floorShader->Id, "SpecularProduct"), 1, glm::value_ptr(specular_product));

	glUniform1f(glGetUniformLocation(floorShader->Id, "Shininess"), material_shininess);

	glUniform4fv(glGetUniformLocation(floorShader->Id, "LightPosition"), 1, glm::value_ptr(light_position));
}


void Floor::run(glm::mat4 projection, glm::mat4 view) {
	floorShader->Use();
	floorShader->SetInt("subdivision", 4);
	floorShader->SetMat4("Projection", projection);
	floorShader->SetMat4("View", view);

	glm::mat4 trans, model_view;
	for (int i = 3; i < 20; i++) {
		for (int j = -5; j <= 5; j++) {
			model_view = glm::mat4(1.0f);
			trans = glm::mat4(1.0f);
			trans = glm::translate(trans, glm::vec3(float(j), -1, float(-i)));
			model_view = trans;
			floorShader->SetMat4("ModelView", model_view);

			glDrawArrays(GL_PATCHES, 0, size);
		}
	}
}
