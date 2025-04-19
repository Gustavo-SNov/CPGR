//
// Created by Gustavo Novais on 18/04/2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <GL/glu.h>
using namespace std;

class Triangle {
    vector<vector<GLfloat>> vertices;

    public:
      Triangle(const vector<vector<GLfloat>>& vertices);
      void draw();


};


#endif //TRIANGLE_H
