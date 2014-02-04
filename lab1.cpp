#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>

#include "initShaders.h"
using namespace std;
int counter = 0;

//vertexIDs
GLuint vaoID, vboID; // the buffers that are going to be linked too
//vertices
GLfloat vertsTriangle[] = {
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};
GLfloat vertsSquare[] = {
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};
GLfloat vertsLine[] = {
    0.1f, -0.7f, 0.0f,
    0.8f, 0.6f, 0.0f,
    -0.2f, -0.3f, 0.0f
};
//indices of triangle
GLubyte indices[3] = {0, 1, 2};

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT); //clears the screen

    glGenVertexArrays(1, &vaoID); //generates object name for Vertex Array Objects
    glBindVertexArray(vaoID); //bind the object to the array

    glGenBuffers(1, &vboID); //generates object name for the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vboID); //bind the object to the array

    ShaderInfo shaders[] = {//create the shader specified by my initshaders 
        { GL_VERTEX_SHADER, "vertexshader.glsl"},
        { GL_FRAGMENT_SHADER, "fragmentshader.glsl"},
        { GL_NONE, NULL}
    };

    initShaders(shaders); //creates shaders

    glEnableVertexAttribArray(0); //enables the vertex attribute index 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); //specified the start the vertice array used to the draw

    switch(counter){
        case 0:
            glBufferData(GL_ARRAY_BUFFER, sizeof (vertsTriangle), vertsTriangle, GL_STATIC_DRAW); //allocates the memory of the vertices
            glDrawArrays(GL_TRIANGLES, 0, 3); //draws array
        break;
        case 1:
            glBufferData(GL_ARRAY_BUFFER, sizeof (vertsSquare), vertsSquare, GL_STATIC_DRAW); //allocates the memory of the vertices
            glDrawArrays(GL_QUADS, 0, 4); //draws array
        break;
        case 2:
            glBufferData(GL_ARRAY_BUFFER, sizeof (vertsLine), vertsLine, GL_STATIC_DRAW); //allocates the memory of the vertices
            glDrawArrays(GL_LINE_LOOP, 0, 3); //draws array
        break;
    }
    glFlush(); //makes sure the prcesses finish

    glutPostRedisplay();
}

//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//right click closes the screen
        exit(0);
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {//left click changes the shape color
        if(++counter >= 3){
            counter = 0;
        }
    }
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    //Freeglut window and context management	
    glutInit(&argc, argv);
    glutCreateWindow("Lab 1"); //creates the window with the specified name

    //initializes glew
    glewExperimental = GL_TRUE;
    if (glewInit()) {
        fprintf(stderr, "Unable to initalize GLEW");
        exit(EXIT_FAILURE);
    }

    glutInitContextVersion(4, 3); //specifies the version of opengl
    glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_COMPATIBILITY_PROFILE); //specifies what profile your using


    //retruns what version of opengl and glsl your computer can use
    const GLubyte* version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    fprintf(stderr, "Opengl glsl version %s\n", version);

    version = glGetString(GL_VERSION);
    fprintf(stderr, "Opengl version %s\n", version);

    glutDisplayFunc(drawScene); //displays callback draws the shapes
    glutMouseFunc(mousepress); //control callback specifies the mouse controls
    glutMainLoop(); //sets opengl state in a neverending loop
    return 0;
}

