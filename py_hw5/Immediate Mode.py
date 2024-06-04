import glfw
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import numpy as np
import time
from load_obj import load_obj

if not glfw.init():
    raise Exception("GLFW cannot be initialized")

window = glfw.create_window(800, 600, "Bunny Renderer", None, None)
if not window:
    glfw.terminate()
    raise Exception("GLFW window cannot be created")

glfw.make_context_current(window)

glViewport(0, 0, 800, 600)
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000.0)

glMatrixMode(GL_MODELVIEW)
glLoadIdentity()
gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0)

glEnable(GL_LIGHTING)
glEnable(GL_LIGHT0)
glLightfv(GL_LIGHT0, GL_POSITION, np.array([1, 1, 1, 0], dtype=np.float32))
glLightfv(GL_LIGHT0, GL_AMBIENT, np.array([0.2, 0.2, 0.2, 1.0], dtype=np.float32))
glLightfv(GL_LIGHT0, GL_DIFFUSE, np.array([1, 1, 1, 1], dtype=np.float32))
glLightfv(GL_LIGHT0, GL_SPECULAR, np.array([0, 0, 0, 1], dtype=np.float32))

vertices, normals, faces = load_obj('bunny.obj')

scale_factor = 10
translation = (0.1, -1, -1.5)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)

    glPushMatrix()
    glScalef(scale_factor, scale_factor, scale_factor)
    glTranslatef(*translation)

    glBegin(GL_TRIANGLES)
    for face in faces:
        for vertex, normal in face:
            glNormal3fv(normals[normal])
            glVertex3fv(vertices[vertex])
    glEnd()

    glPopMatrix()
    glfw.swap_buffers(window)

def calculate_fps():
    frame_times = []
    while not glfw.window_should_close(window):
        start_time = time.time()
        display()
        glfw.poll_events()
        end_time = time.time()
        frame_time = end_time - start_time
        frame_times.append(frame_time)
        if len(frame_times) > 100:
            frame_times.pop(0)
        fps = len(frame_times) / sum(frame_times)
        print(f"FPS: {fps:.2f}")


calculate_fps()

glfw.terminate()
