#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

// Biblioteca "GL/freeglut.h" � inclu�da para utilizar a API do FreeGLUT, que fornece uma interface para OpenGL no contexto do sistema de janelas.
// Essa biblioteca � usada para criar e gerenciar janelas, controlar eventos de entrada e renderizar gr�ficos 2D e 3D.

// Biblioteca "cmath" � inclu�da para utilizar fun��es matem�ticas como std::cos() e std::sin() que s�o usadas para calcular coordenadas de pontos em formas geom�tricas.

// Biblioteca "cstdlib" � inclu�da para utilizar a fun��o rand() que � usada para gerar n�meros aleat�rios usados ??para definir cores aleat�rias para as formas geom�tricas.

float shapeX = 0.0f; // Posi��o X da forma
float shapeY = 0.0f; // Posi��o Y da forma

const int screenWidth = 800;  // Largura da janela
const int screenHeight = 600; // Altura da janela

int shapeType = 0; // Tipo de forma: 0 = tri�ngulo, 1 = c�rculo, 2 = quadrado

GLfloat shapeColorR = 1.0f; // Componente de cor vermelha da forma
GLfloat shapeColorG = 1.0f; // Componente de cor verde da forma
GLfloat shapeColorB = 1.0f; // Componente de cor azul da forma

bool isKeyPressed = false; // Flag para verificar se uma tecla est� pressionada

void drawSquare()
{
    glColor3f(shapeColorR, shapeColorG, shapeColorB); // Define a cor do quadrado

    glBegin(GL_QUADS); // Inicia o desenho do quadrado

    // Define os v�rtices do quadrado no sentido anti-hor�rio
    glVertex2f(shapeX - 0.1f, shapeY + 0.1f); // Canto superior esquerdo
    glVertex2f(shapeX + 0.1f, shapeY + 0.1f); // Canto superior direito
    glVertex2f(shapeX + 0.1f, shapeY - 0.1f); // Canto inferior direito
    glVertex2f(shapeX - 0.1f, shapeY - 0.1f); // Canto inferior esquerdo
    
    glEnd(); // Finaliza o desenho do quadrado
}

void drawCircle()
{
    glColor3f(shapeColorR, shapeColorG, shapeColorB); // Define a cor do c�rculo

    const int numSegments = 36; // N�mero de segmentos que comp�em o c�rculo
    const float radius = 0.1f; // Raio do c�rculo

    glBegin(GL_TRIANGLE_FAN); // Inicia o desenho do c�rculo como um leque de tri�ngulos

	glVertex2f(shapeX, shapeY); // Centro do c�rculo

    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0f * M_PI * static_cast<float>(i) / numSegments; // Calcula o �ngulo do segmento
        float x = shapeX + radius * std::cos(theta); // Calcula a coordenada X do ponto no c�rculo
        float y = shapeY + radius * std::sin(theta); // Calcula a coordenada Y do ponto no c�rculo
        glVertex2f(x, y); // Adiciona o ponto ao c�rculo
    }

    glEnd(); // Finaliza o desenho do c�rculo
}

void drawTriangle()
{
    glColor3f(shapeColorR, shapeColorG, shapeColorB); // Define a cor do tri�ngulo

    glBegin(GL_TRIANGLES); // Inicia o desenho do tri�ngulo

    // Define os v�rtices do tri�ngulo no sentido anti-hor�rio
    glVertex2f(shapeX, shapeY + 0.1f);        // V�rtice superior
    glVertex2f(shapeX - 0.1f, shapeY - 0.1f); // V�rtice inferior esquerdo
    glVertex2f(shapeX + 0.1f, shapeY - 0.1f); // V�rtice inferior direito
    
    glEnd(); // Finaliza o desenho do tri�ngulo
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor com a cor de fundo definida

    if (shapeType == 0)
        drawTriangle(); // Desenha um tri�ngulo se o tipo de forma for 0
    else if (shapeType == 1)
        drawCircle(); // Desenha um c�rculo se o tipo de forma for 1
    else if (shapeType == 2)
        drawSquare(); // Desenha um quadrado se o tipo de forma for 2

    glutSwapBuffers(); // Troca os buffers de desenho (buffer duplo) para exibir a cena atualizada
}

void checkCollision()
{
    const float shapeRadius = 0.1f; // Raio da forma

    // Verifica se a forma colidiu com as bordas da tela
    if (shapeX - shapeRadius < -1.0f || shapeX + shapeRadius > 1.0f ||
        shapeY - shapeRadius < -1.0f || shapeY + shapeRadius > 1.0f)
    {
        shapeType = (shapeType + 1) % 3; // Alterna para a pr�xima forma

        // Gera cores aleat�rias para a nova forma
        shapeColorR = static_cast<GLfloat>(rand()) / RAND_MAX;
        shapeColorG = static_cast<GLfloat>(rand()) / RAND_MAX;
        shapeColorB = static_cast<GLfloat>(rand()) / RAND_MAX;

        // Ajusta a posi��o da forma para evitar que ela fique presa nas bordas da tela
        if (shapeX - shapeRadius < -1.0f)
            shapeX = -1.0f + shapeRadius; // Define a posi��o X no limite esquerdo permitido
        else if (shapeX + shapeRadius > 1.0f)
            shapeX = 1.0f - shapeRadius; // Define a posi��o X no limite direito permitido
        if (shapeY - shapeRadius < -1.0f)
            shapeY = -1.0f + shapeRadius; // Define a posi��o Y no limite inferior permitido
        else if (shapeY + shapeRadius > 1.0f)
            shapeY = 1.0f - shapeRadius; // Define a posi��o Y no limite superior permitido
    }
}

void update(int value)
{
    if (GetAsyncKeyState(VK_UP) & 0x8000) // Verifica se a tecla Seta para cima est� pressionada
    {
        shapeY += 0.01f; // Incrementa a posi��o Y da forma
        isKeyPressed = true; // Marca a flag indicando que uma tecla foi pressionada
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // Verifica se a tecla Seta para baixo est� pressionada
    {
        shapeY -= 0.01f; // Decrementa a posi��o Y da forma
        isKeyPressed = true; // Marca a flag indicando que uma tecla foi pressionada
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // Verifica se a tecla Seta para esquerda est� pressionada
    {
        shapeX -= 0.01f; // Decrementa a posi��o X da forma
        isKeyPressed = true; // Marca a flag indicando que uma tecla foi pressionada
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // Verifica se a tecla Seta para direita est� pressionada
    {
        shapeX += 0.01f; // Incrementa a posi��o X da forma
        isKeyPressed = true; // Marca a flag indicando que uma tecla foi pressionada
    }
    else
    {
        isKeyPressed = false; // Se nenhuma tecla de seta estiver pressionada, marca a flag como falsa
    }

    checkCollision(); // Verifica colis�es com as bordas da tela

    glutPostRedisplay(); // Solicita uma atualiza��o da tela para redesenhar a cena
    glutTimerFunc(16, update, 0); // Configura o temporizador para chamar a fun��o de atualiza��o novamente ap�s 16 milissegundos
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Inicializa o FreeGLUT e passa os argumentos de linha de comando
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Configura o modo de exibi��o para buffer duplo e RGB
    glutInitWindowSize(screenWidth, screenHeight); // Define o tamanho da janela
    glutCreateWindow("Moving shapes with collision and color changes"); // Cria uma janela com um t�tulo

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Define a cor de fundo para preto
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define as coordenadas do sistema de coordenadas projetado

    glutDisplayFunc(renderScene); // Registra a fun��o de callback para renderizar a cena
    glutTimerFunc(0, update, 0); // Configura o temporizador para chamar a fun��o de atualiza��o

    glutMainLoop(); // Inicia o loop principal do FreeGLUT para tratar eventos e chamar as fun��es de callback

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
