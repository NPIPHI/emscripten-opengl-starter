//
// Created by 16182 on 6/15/2020.
//

#include <iostream>
#include "render.h"

void render(GLuint program, const std::vector<GLuint>& VBOs, int first, int count){

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, first, count);
    glDisableVertexAttribArray(0);
}
