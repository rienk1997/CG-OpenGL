#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.hpp"
#include "texture.hpp"

#include "Shader.h"
#include "Mesh.h"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;
const char * fragshader_name = "fragmentshader.fsh";
const char * vertexshader_name = "vertexshader.vsh";
unsigned const int DELTA = 10;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

struct LightSource {
	glm::vec3 position;
};

struct Material {
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float power;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

Shader* shader;
Mesh* mesh;
Mesh* mesh2;

GLuint texture_id;
GLuint vao;
GLuint uniform_mv;

glm::mat4 model, view, projection;
glm::mat4 mv;

LightSource light;
Material material;

//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

vector<glm::vec3> vertices;
vector<glm::vec3> normals;
vector<glm::vec2> uvs;

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	shader->useShader();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Send vao
	mesh->Render(view);
	mesh2->Render(view);

    glutSwapBuffers();

	shader->unuseShader();
}



//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL World");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(DELTA, Render, 0);

    glewInit();
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
    model = glm::mat4();
	model = glm::rotate(model, 0.3f, glm::vec3(0.0, 1.0, 0.0));
    view = glm::lookAt(
        glm::vec3(2.0, 2.0, 7.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);
    mv = view * model;
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
	shader->useShader();
    // Make uniform var
	shader->setMat4fv(mv, "mv");
	shader->setMat4fv(projection, "projection");

	shader->setVec3f(light.position, "light_pos");
	shader->setVec3f(material.ambient_color, "mat_ambient");
	shader->setVec3f(material.diffuse_color, "mat_diffuse");
	shader->setVec3f(material.specular, "mat_specular");

	shader->setVec1f(material.power, "mat_power");

	shader->unuseShader();
}

//------------------------------------------------------------
// void InitMaterialsLight()
// Inits Light
//------------------------------------------------------------

void InitMaterialsLight() {
	light.position = glm::vec3(4.0, 4.0, 4.0);
	material.ambient_color = glm::vec3(0.0, 0.0, 0.0);
	material.diffuse_color = glm::vec3(0.0, 0.0, 0.0);
	material.specular = glm::vec3(1.0);
	material.power = 128;
}

//------------------------------------------------------------
// void InitObjects()
// Inits Objects
//------------------------------------------------------------

void InitObjects() {
	bool res = loadOBJ("Objects/box.obj", vertices, uvs, normals);
	mesh = new Mesh(shader, vertices, normals, uvs);
	mesh2 = new Mesh(shader, vertices, normals, uvs);
	texture_id = loadBMP("Textures/Yellobrk.bmp");
}


int main(int argc, char ** argv)
{
     InitGlutGlew(argc, argv);
	 shader = new Shader(vertexshader_name, fragshader_name);
     InitMatrices();
	 InitObjects();
	 InitMaterialsLight();
     InitBuffers();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    glutMainLoop();

    return 0;
}
