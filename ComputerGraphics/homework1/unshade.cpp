#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define M_PI 3.14159265358979323846

typedef struct {
    float x, y, z;
} Vertex;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); 
}

int gNumVertices = 0; // Number of 3D vertices.
int gNumTriangles = 0; // Number of triangles.
int* gIndexBuffer = NULL; // Vertex indices for the triangles.

Vertex* vertices = NULL;

void generateSphere(float radius, int width, int height) {
    gNumVertices = (height - 2) * width + 2; 
    gNumTriangles = (height - 2) * (width - 1) * 2;

    vertices = (Vertex*)malloc(gNumVertices * sizeof(Vertex));
    gIndexBuffer = new int[3 * gNumTriangles];
    float theta, phi;
    int t;

    t = 0;
    for (int j = 1; j < height - 1; ++j) {
        for (int i = 0; i < width; ++i) {
            theta = (float)j / (height - 1) * M_PI;
            phi = (float)i / (width - 1) * 2 * M_PI;
            vertices[t].x = radius * sinf(theta) * cosf(phi);
            vertices[t].y = radius * cosf(theta);
            vertices[t].z = radius * -sinf(theta) * sinf(phi);
            t++;
        }
    }

    vertices[t].x = 0;
    vertices[t].y = radius;
    vertices[t].z = 0;
    int northPoleIndex = t;
    t++;

    vertices[t].x = 0;
    vertices[t].y = -radius;
    vertices[t].z = 0;
    int southPoleIndex = t;
    t++;

    t = 0;
    for (int j = 0; j < height - 3; ++j) {
        for (int i = 0; i < width - 1; ++i) {
            gIndexBuffer[t++] = j * width + i;
            gIndexBuffer[t++] = (j + 1) * width + (i + 1);
            gIndexBuffer[t++] = j * width + (i + 1);

            gIndexBuffer[t++] = j * width + i;
            gIndexBuffer[t++] = (j + 1) * width + i;
            gIndexBuffer[t++] = (j + 1) * width + (i + 1);
        }
    }

    for (int i = 0; i < width - 1; ++i) {
        gIndexBuffer[t++] = northPoleIndex;
        gIndexBuffer[t++] = i;
        gIndexBuffer[t++] = i + 1;

        gIndexBuffer[t++] = southPoleIndex;
        gIndexBuffer[t++] = (height - 3) * width + i + 1;
        gIndexBuffer[t++] = (height - 3) * width + i;
    }
}

void drawSphere() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glDrawElements(GL_TRIANGLES, 3 * gNumTriangles, GL_UNSIGNED_INT, gIndexBuffer);

    glDisableClientState(GL_VERTEX_ARRAY);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,  
        0.0, 0.0, -1.0, 
        0.0, 1.0, 0.0); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000.0);

    glViewport(0, 0, 512, 512);

    //glColor3f(1.0, 1.0, 1.0); 
    glTranslatef(0.0, 0.0, -7.0); 
    //glutSolidSphere(2.0, 20, 16); 
    drawSphere();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Unshaded");
    generateSphere(1.0, 32, 16);

    init();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST); 
    glutMainLoop();
    return 0;
}
