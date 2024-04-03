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
    // 뷰포트 설정
    glViewport(0, 0, (GLsizei)x, (GLsizei)y);

    // 투영 매트릭스 모드 선택
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 뷰잉 볼륨 설정: glFrustum을 사용
    GLfloat l = -0.1f, r = 0.1f, b = -0.1f, t = 0.1f, n = 0.1f, f = 100.0f;
    glFrustum(l, r, b, t, n, f);

    // 모델뷰 매트릭스 모드로 돌아감
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 카메라 위치 설정: gluLookAt을 사용
    // 여기서 카메라의 위치는 (0, 0, 0), 바라보는 점은 z축을 따라 -1 (즉, (0, 0, -1)),
    // 그리고 상방 벡터는 y축 (0, 1, 0) 입니다.
    gluLookAt(0.0, 0.0, 0.0,   
        0.0, 0.0, -1.0,  
        0.0, 1.0, 0.0);  
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 카메라 설정
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    // 평면 P 그리기
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -2.0, -10.0);
    glVertex3f(5.0, -2.0, -10.0);
    glVertex3f(5.0, -2.0, -4.0);
    glVertex3f(-5.0, -2.0, -4.0);
    glEnd();

    // 구 S1 그리기
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-4.0, 0.0, -7.0); // S1의 중심으로 이동
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    // 구 S2 그리기
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, -7.0); // S2의 중심으로 이동
    glutSolidSphere(2.0, 20, 20);
    glPopMatrix();

    // 구 S3 그리기
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(4.0, 0.0, -7.0); // S3의 중심으로 이동
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();



}