import sys
import numpy as np
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import glfw
from load_obj import load_obj

window_width, window_height = 512, 512

gTotalTimeElapsed = 0
gTotalFrames = 0
vertices, normals, faces = None, None, None


def setup_lighting():
    glEnable(GL_LIGHTING)

    light_ambient_0 = [0.2, 0.2, 0.2, 1.0]
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_0)

    light_direction = [-1.0, -1.0, -1.0, 0.0]
    light_ambient = [0.0, 0.0, 0.0, 1.0]
    light_diffuse = [1.0, 1.0, 1.0, 1.0]
    light_specular = [0.0, 0.0, 0.0, 1.0]

    glEnable(GL_LIGHT1)
    glLightfv(GL_LIGHT1, GL_POSITION, light_direction)
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse)
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular)


def setup_material():
    ka = [1.0, 1.0, 1.0, 1.0]
    kd = [1.0, 1.0, 1.0, 1.0]
    ks = [0.0, 0.0, 0.0, 1.0]
    p = 0.0

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd)
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks)
    glMaterialf(GL_FRONT, GL_SHININESS, p)


def setup_camera():
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0)


def display():
    global gTotalTimeElapsed, gTotalFrames
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    setup_camera()

    start_time = glfw.get_time()

    glTranslatef(0.1, -1.0, -1.5)
    glScalef(10.0, 10.0, 10.0)

    glBegin(GL_TRIANGLES)
    for face in faces:
        for vertex, normal in face:
            glNormal3fv(normals[normal])
            glVertex3fv(vertices[vertex])
    glEnd()

    end_time = glfw.get_time()
    timeElapsed = end_time - start_time

    gTotalFrames += 1
    gTotalTimeElapsed += timeElapsed
    fps = gTotalFrames / gTotalTimeElapsed if gTotalTimeElapsed > 0 else 0
    print(f"FPS: {fps:.2f}")

    glfw.swap_buffers(window)


def reshape(window, w, h):
    global window_width, window_height
    window_width, window_height = w, h
    glViewport(0, 0, w, h)
    setup_camera()


def main():
    if not glfw.init():
        return

    global window, vertices, normals, faces
    window = glfw.create_window(window_width, window_height, "Bunny Immediate Mode", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.make_context_current(window)
    glfw.set_framebuffer_size_callback(window, reshape)

    glEnable(GL_DEPTH_TEST)
    glEnable(GL_NORMALIZE)
    setup_material()
    setup_lighting()

    vertices, normals, faces = load_obj("bunny.obj")

    while not glfw.window_should_close(window):
        display()
        glfw.poll_events()

    glfw.terminate()


if __name__ == "__main__":
    main()
