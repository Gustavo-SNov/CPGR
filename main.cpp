#include <iostream>
#include <Transformation.h>
#include <Triangle.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <vector>
using namespace std;

GLfloat zoomLevel = 2.0f; // Quanto maior, mais afastada
vector<vector<GLfloat> > triangle = {{0.1f, 0.1f}, {0.4f, 0.1f}, {0.1f, 0.5f}};

enum TypeTransformation {
    TRANSLATION,
    ROTATION,
    SCALE,
    SHEAR,
    REFLEXION,
    EXECUTE,
    SAIR
};

struct operation {
    TypeTransformation type;
    GLfloat translateX = 0.0f, translateY = 0.0f;
    GLfloat scaleX = 1.0f, scaleY = 1.0f;
    GLfloat shearX = 0.0f, shearY = 0.0f;
    GLfloat reflexionX = 1.0f, reflexionY = 1.0f;
    GLfloat rotateAngle;
};

vector<operation> operations;

// Func. Callback -> Chamada sempre que a Janela for redimensionada
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void init();
void execute();
void draw();

void menu() {
    int option;
    do {
        cout << "[1] Translação" << endl;
        cout << "[2] Escala" << endl;
        cout << "[3] Rotação" << endl;
        cout << "[4] Executar" << endl;
        cout << "[5] Resetar" << endl;
        cout << "[6] Sair" << endl;
        cout << "Selecione a operação: ";
        cin >> option;
        operation oper;
        switch (option) {
            case 1:
                oper.type = TRANSLATION;
                cout << "Digite o vetor de translação de X: ";
                cin >> oper.translateX;
                cout << "Digite o vetor de translação de Y: ";
                cin >> oper.translateY;
                operations.push_back(oper);
                break;
            case 2:
                oper.type = SCALE;
                cout << "Digite o fator de escala de X: ";
                cin >> oper.scaleX;
                cout << "Digite o fator de escala de Y: ";
                cin >> oper.scaleY;
                operations.push_back(oper);
                break;
            case 3:
                oper.type = ROTATION;
                cout << "Digite o ângulo de rotação: ";
                cin >> oper.rotateAngle;
                operations.push_back(oper);
                break;
            case 4:
                execute();
                draw();
                break;
            case 5: {
                int tamanho = 0;
                if (!operations.empty()) {
                    tamanho = operations.size();
                    for (int i = 1; i <= tamanho; ++i) {
                        operations.pop_back();
                    }
                }

                break;
            }
            case 6:
                cout << "Saindo do Programa!";
                break;
            default:
                cout << "Operação Inválida!" << endl;
        }
    } while (option != 6);
}

int main() {
    menu();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // Ajusta a área de renderização
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, width, height);
}
// Callback para scroll do mouse
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // yoffset => Rolagem do Scroll do mouse => para cima: +1.0 , para baixo: -1.0
    zoomLevel += yoffset * 0.1f;
    zoomLevel = std::max(0.1f, zoomLevel); // Evitar zoom negativo
}

void init() {
    // Ajuste de Projeção Ortográfica(2D)
    glMatrixMode(GL_PROJECTION); // Matriz de Projeção: Como a câmera vê a cena
    glLoadIdentity(); // Reseta transformações anteriores
    glOrtho(-zoomLevel, zoomLevel, -zoomLevel, zoomLevel, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenhando o Plano Cartesiano (x,y)
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f); // Eixo X
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, -1.0f); // Eixo Y
    glEnd();

    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(0.1f, 0.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.0, 0.5);
    for (auto &vertice: triangle) {
        glVertex2f(vertice[0], vertice[1]);
    }
    glEnd();
}

void execute() {
    // Inicializa a biblioteca GLFW -> Criar Janelas e Gerenciar Contextos
    if (!glfwInit()) {
        cerr << "Erro ao inicializar o GLFW" << endl;
        return;
    }

    // Cria janela 800x600 pixels, com o título "Exemplo - GLFW" sem modo fullscreen(1º nullptr) e sem compartilhamento de contexto com outra janela(2º nullptr)
    GLFWwindow *window = glfwCreateWindow(1000, 800, "Exemplo - GLFW", nullptr, nullptr);
    if (!window) {
        cerr << "Erro ao criar a janela GLFW" << endl;
        glfwTerminate();
        return;
    }

    // Define contexto atual
    glfwMakeContextCurrent(window);

    // Define a função de callback para redimensionar a janela
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scrollCallback);

    while (!glfwWindowShouldClose(window)) {
        init();

        //triangle.draw();
        //Transformation::escala(centro,fatores, [ObjectPtr = &triangle] { ObjectPtr->draw(); });
        //Transformation::rotacaoDeObjeto();
        glPushMatrix();
        for (auto &operation: operations) {
            switch (operation.type) {
                case TRANSLATION:
                    glTranslatef(operation.translateX, operation.translateY, 0.0f);
                    break;
                case SCALE:
                    glScalef(operation.scaleX, operation.scaleY, 1.0f);
                    break;
                case ROTATION:
                    glRotatef(operation.rotateAngle, 0.0f, 0.0f, 1.0f);
                    break;
                default:
                    cerr << "Operação não identificada na execução!" << endl;
            }
        }
        draw();
        glPopMatrix();

        // Resetar transformações para evitar acumulação
        glLoadIdentity();

        // Troca os buffers da janela, exibindo o que foi renderizado na tela
        glfwSwapBuffers(window);

        // Processa eventos da janela. Ex: Teclas pressionadas,Movimento do mouse,Fechamento da janela e etc...
        glfwPollEvents();
    }

    glfwTerminate();
}
