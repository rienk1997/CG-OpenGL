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
#include "Camera.h"
#include "House.cpp"
#include "Grass.cpp"
#include "Windmill.cpp"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;
const int CENTER_X = WIDTH / 2, CENTER_Y = HEIGHT / 2;
const char * fragshader_name = "fragmentshader.fsh";
const char * fragshader_name2 = "fragmentshader-nonspecular.fsh";
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
Shader* shader2;
House* house1;
House* house2;
Grass* grass;
Windmill* windmill1;

GLuint texture_id;
GLuint vao;
GLuint uniform_mv;

glm::mat4 model, view, projection;
glm::mat4 mv;

LightSource light;
Material material;

// Camera.
Camera camera(glm::vec3(0, 1, -8));
int currentZoom = 0;

// Timing.
float deltaTime = 0.0f;	// Time between current frame and last frame.
float lastFrame = 0.0f;

//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

vector<glm::vec3> vertices;
vector<glm::vec3> normals;
vector<glm::vec2> uvs;


void mouseHandler(int x, int y) {
	camera.ProcessMouseMovement(x - CENTER_X, CENTER_Y - y);

	// If not already, warp the cursor to the center.
	if (x != CENTER_X || y != CENTER_Y)
	{
		glutWarpPointer(CENTER_X, CENTER_Y);
	}
}
//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27) {
		glutExit();
	}
	if (key == 99) {
		// C.
		camera.SceneFromAbove();
	}
	if (key == 119) {
		// W
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (key == 97) {
		// A
		camera.ProcessKeyboard(LEFT, deltaTime);

	}
	if (key == 115) {
		// S
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (key == 100) {
		// D
		camera.ProcessKeyboard(RIGHT, deltaTime);

	}
}


void UpdateView() {

}

//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	const float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 100.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	shader->useShader();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//house1->Move(glm::vec3(0.0, 0.01, 0.0));
	view = camera.GetViewMatrix();
	grass->Render(view);
	house1->Render(view);
	house2->Render(view);
	windmill1->Render(view);
	   
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
	glutMotionFunc(mouseHandler);
    glutTimerFunc(DELTA, Render, 0);

	glutSetCursor(GLUT_CURSOR_NONE);
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
        glm::vec3(1.0, 1.0, 20.0),
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

void InitBuffers(Shader* shader)
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

int main(int argc, char ** argv)
{
     InitGlutGlew(argc, argv);
	 shader = new Shader(vertexshader_name, fragshader_name);
	 shader2 = new Shader(vertexshader_name, fragshader_name2);
     InitMatrices();
	 house1 = new House(shader, glm::vec3(0.0f, 0.0f, 0.0f));
	 house2 = new House(shader2, glm::vec3(2.0f, 0.0f, 0.0f));
	 grass = new Grass(shader, 20, 2);
	 windmill1 = new Windmill(shader2, glm::vec3(5.0f, 0.0f, 0.0f));
	 InitMaterialsLight();
     InitBuffers(shader);
     InitBuffers(shader2);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);

    glutMainLoop();

    return 0;
}
