//
// Created by Gustavo Novais on 18/04/2025.
//

#include "Transformation.h"
#include <vector>
#include <functional>
#include <GL/glu.h>

void Transformation::escalaRelativaAoCentro() {
    GLfloat h, k;
    GLfloat sx = 2, sy = 2;

    h = 0.1f;
    k = 0.1f;
    glPushMatrix();

    glTranslatef(h, k, 0.0f);
    glScalef(sx, sy, 1.0f);
    glTranslatef(-h, -k, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.2f, 0.1f);
    glEnd();

    glPopMatrix();


    // Deu certo com duas operações apenas pelo centro ser a origem? Sim
    // E se o centro for (0.2f, 0.2f) ? O centro sempre será a Origem(0,0)
    // A questão é definir o ponto fixo! Como assim?
    // Se não definirem um ponto fixo, então, será a origem.
    // Caso definam um ponto fixo, levar esse ponto fixo até a origem e transformar.
    h = 0.2f;
    k = 0.2f;
    glPushMatrix();

    glTranslatef(h, k, 0.0f);
    glScalef(sx, sy, 1.0f);
    glTranslatef(-h, -k, 0.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.4f, 0.4f);
    glVertex2f(0.3f, 0.4f);
    glEnd();

    glPopMatrix();
};

void Transformation::rotacaoDeObjeto() {
    GLfloat theta = 90.0f;

    glPushMatrix();

    //glTranslatef(0.1f, 0.1f, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    //glTranslatef(-0.1f, -0.1f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.2f, 0.1f);
    glEnd();

    glPopMatrix();
}

void Transformation::cisalhamento() {
    vector<vector<GLfloat> > meusVertices = {
        {0.0f, 0.0f},
        {0.2f, 0.0f},
        {0.2f, 0.2f},
        {0.0f, 0.2f}
    };
    GLfloat shx = 0.2f, shy = 0.0f;
    // Cisalhamento => P' ( (x + (y * SHx) ), (y + (x * SHy) ) )

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 1.0);

    for (auto &v: meusVertices) {
        //glVertex2f(v[0], v[1]);
        GLfloat x = v[0] + (v[1] * shx);
        GLfloat y = v[1] + (v[0] * shy);
        glVertex2f(x, y);
    }

    glEnd();
}

void Transformation::escalaComPontoFixo() {
    GLfloat h, k;
    GLfloat sx = 2, sy = 2;

    // Ponto B será fixo => (0.1f,0.1f)
    h = 0.1f;
    k = 0.1f;

    // Triângulo Original
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, 0.0f); // PONTO A
    glVertex2f(0.1f, 0.1f); // PONTO B
    glVertex2f(0.5f, 0.2f); // PONTO C
    glEnd();

    // Triângulo Escalado
    glPushMatrix();

    glTranslatef(h, k, 0.0f);
    glScalef(sx, sy, 1.0f);
    glTranslatef(-h, -k, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0f, 0.0f); // PONTO A
    glVertex2f(0.1f, 0.1f); // PONTO B
    glVertex2f(0.5f, 0.2f); // PONTO C
    glEnd();

    glPopMatrix();
}

void Transformation::rotacaoComPontoFixo() {
    GLfloat h, k;
    GLfloat sx = 2, sy = 2;
    GLfloat theta = 45.0f;

    // Triângulo Original
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0f, 0.0f); // PONTO A
    glVertex2f(0.1f, 0.1f); // PONTO B
    glVertex2f(0.5f, 0.2f); // PONTO C
    glEnd();

    h = 0.1f;
    k = 0.1f;
    glPushMatrix();

    glTranslatef(h, k, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glTranslatef(-h, -k, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0f, 0.0f); // PONTO A
    glVertex2f(0.1f, 0.1f); // PONTO B
    glVertex2f(0.5f, 0.2f); // PONTO C
    glEnd();
    glPopMatrix();
}

void Transformation::distorcaoLinear() {
    vector<vector<GLfloat> > meusVertices = {
        {0.0f, 0.0f},
        {0.2f, 0.0f},
        {0.2f, 0.2f},
        {0.0f, 0.2f}
    };

    // Quarado Original
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 1.0);
    for (auto &v: meusVertices) {
        glVertex2f(v[0], v[1]);
    }
    glEnd();

    GLfloat shx = 0.2f, shy = 0.0f;
    // Cisalhamento => P' ( (x + (y * SHx) ), (y + (x * SHy) ) )

    // a) Distorção em X (a = 2, b = 0)
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    for (auto &v: meusVertices) {
        GLfloat x = v[0] + (v[1] * shx);
        GLfloat y = v[1] + (v[0] * shy);
        glVertex2f(x, y);
    }
    glEnd();

    // b) Distorção em Y (a = 0, b = 3)
    shx = 0.0f, shy = 0.3f;
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.0, 0.5);
    for (auto &v: meusVertices) {
        GLfloat x = v[0] + (v[1] * shx);
        GLfloat y = v[1] + (v[0] * shy);
        glVertex2f(x, y);
    }
    glEnd();

    // c) Distorção em X e Y (a = 2, b = 3)
    shx = 0.2f, shy = 0.3f;
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 0.0);
    for (auto &v: meusVertices) {
        GLfloat x = v[0] + (v[1] * shx);
        GLfloat y = v[1] + (v[0] * shy);
        glVertex2f(x, y);
    }
    glEnd();
}

void Transformation::reflexaoLinear() {
    vector<vector<GLfloat> > meusVertices = {
        {0.1f, 0.1f},
        {0.4f, 0.1f},
        {0.1f, 0.5f}
    };

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for (auto &v: meusVertices) {
        glVertex2f(v[0], v[1]);
    }
    glEnd();

    char eixo = 'y';
    GLfloat sx = -1.0f, sy = 1.0f;

    if (eixo == 'x') {
        sx = 1.0f, sy = -1.0f;
    }

    glPushMatrix();
    glScalef(sx, sy, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (auto &v: meusVertices) {
        glVertex2f(v[0], v[1]);
    }
    glEnd();

    glPopMatrix();
}
