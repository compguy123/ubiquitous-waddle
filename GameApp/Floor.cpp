#include "floor.h"



const int size = 3;

Floor::Floor(){

    point4 points[3] = {
    point4(-0.5, 0, .5, 1.0),
    point4(0.5, 0, .5, 1.0),
    point4(0.5, 0, -.5, 1.0),
   // point4(-0.5, 0, -.5, 1.0)

    };

    floorShader = new Shader("floorVShader.glsl", "floorFShader.glsl");
    floorShader->Use();
    //array object
    glGenVertexArrays(1, &arrayBuffer);
    glBindVertexArray(arrayBuffer);


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points),
        points, GL_STATIC_DRAW);
   
    // position attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    
}


void Floor::run(glm::mat4 projection, glm::mat4 view) {

    floorShader->SetMat4("Projection", projection);
    floorShader->SetMat4("View", view);

    glm::mat4 trans, model_view;
    for (int i = 3; i < 20;i++) {
        for (int j = -5;j <= 5;j++) {
            model_view = glm::mat4(1.0f);
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(float(j), -1, float(-i)));
            model_view = trans;
            floorShader->SetMat4("ModelView", model_view);
            glDrawArrays(GL_TRIANGLES, 0, size);

        }
    }
}