//
// Created by Gustavo Novais on 18/04/2025.
//

#include "Triangle.h"
#include <GLFW/glfw3.h>

Triangle::Triangle(const vector<vector<GLfloat> > &vertices) {
    this->vertices = vertices;
}

void Triangle::draw() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.0, 0.5); // roxo
    for (const auto& v : this->vertices) {
        glVertex2f(v[0], v[1]);
    }
    glEnd();
}

