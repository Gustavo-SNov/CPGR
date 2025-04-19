//
// Created by Gustavo Novais on 18/04/2025.
//

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <vector>
#include <functional>
#include <GL/glu.h>
using namespace std;

class Transformation {
  public:
    Transformation() = delete;

    static void escalaRelativaAoCentro();   // Exercício 1
    static void rotacaoDeObjeto();          // Exercício 2
    static void cisalhamento();             // Exercício 3
    static void escalaComPontoFixo();       // Exercício 4
    static void rotacaoComPontoFixo();      // Exercício 5
    static void distorcaoLinear();          // Exercício 7
    static void reflexaoLinear();           // Exercício 8
};

#endif //TRANSFORMATION_H
