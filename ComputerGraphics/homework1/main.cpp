#include <iostream>

#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;

void display(void);
void reshape(int x, int y);
void idle(void)
{
    xRotated += 0.01;
    //yRotated += 0.01;
    zRotated += 0.01;
    display();

}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(350, 350);
    glutCreateWindow("Solid Sphere");
    xRotated = yRotated = zRotated = 30.0;
    xRotated = 43;
    yRotated = 50;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}


//void display(void)
//{
//    glMatrixMode(GL_MODELVIEW);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();
//
//    glTranslatef(0.0, 0.0, -5.0);
//    glColor3f(0.9, 0.3, 0.2);
///*    glRotatef(xRotated, 1.0, 0.0, 0.0);
//    glRotatef(yRotated, 1.0, 0.0, 0.0);
//    glRotatef(zRotated, 1.0, 0.0, 0.0);
//*/
//    glScalef(1.0, 1.0, 1.0);
//    //glutSolidSphere(radius, 20, 20);
//    glutSolidSphere(radius, 25, 25);
//    glutSolidSphere(3, 50, 50);
//
//    glFlush();
//
//
//
//
//}

void reshape(int x, int y)
{
    // ����Ʈ ����
    glViewport(0, 0, (GLsizei)x, (GLsizei)y);

    // ���� ��Ʈ���� ��� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ���� ���� ����: glFrustum�� ���
    GLfloat l = -0.1f, r = 0.1f, b = -0.1f, t = 0.1f, n = 0.1f, f = 100.0f;
    glFrustum(l, r, b, t, n, f);

    // �𵨺� ��Ʈ���� ���� ���ư�
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ī�޶� ��ġ ����: gluLookAt�� ���
    // ���⼭ ī�޶��� ��ġ�� (0, 0, 0), �ٶ󺸴� ���� z���� ���� -1 (��, (0, 0, -1)),
    // �׸��� ��� ���ʹ� y�� (0, 1, 0) �Դϴ�.
    gluLookAt(0.0, 0.0, 0.0,   
        0.0, 0.0, -1.0,  
        0.0, 1.0, 0.0);  
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // ī�޶� ����
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    // ��� P �׸���
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -2.0, -10.0);
    glVertex3f(5.0, -2.0, -10.0);
    glVertex3f(5.0, -2.0, -4.0);
    glVertex3f(-5.0, -2.0, -4.0);
    glEnd();

    // �� S1 �׸���
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-4.0, 0.0, -7.0); // S1�� �߽����� �̵�
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // �� S2 �׸���
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, -7.0); // S2�� �߽����� �̵�
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();

    // �� S3 �׸���
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(4.0, 0.0, -7.0); // S3�� �߽����� �̵�
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();



}