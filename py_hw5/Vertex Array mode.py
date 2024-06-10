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
vao = None
vbo_positions = None
vbo_normals = None
ebo = None
indices = None 

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


def setup_buffers():
    global vao, vbo_positions, vbo_normals, ebo, indices

    vertices, normals, faces = load_obj('bunny.obj')

    vertices = vertices.flatten()
    normals = normals.flatten()
    indices = []

    for face in faces:
        for vertex, _ in face:
            indices.append(vertex)

    indices = np.array(indices, dtype=np.uint32)

    vao = glGenVertexArrays(1)
    glBindVertexArray(vao)

    vbo_positions = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_positions)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, None)
    glEnableVertexAttribArray(0)

    vbo_normals = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals)
    glBufferData(GL_ARRAY_BUFFER, normals.nbytes, normals, GL_STATIC_DRAW)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, None)
    glEnableVertexAttribArray(1)

    ebo = glGenBuffers(1)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.nbytes, indices, GL_STATIC_DRAW)

    glBindVertexArray(0)


def display():
    global gTotalTimeElapsed, gTotalFrames
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    setup_camera()

    start_time = glfw.get_time()

    glTranslatef(0.1, -1.0, -1.5)
    glScalef(10.0, 10.0, 10.0)

    glBindVertexArray(vao)
    glDrawElements(GL_TRIANGLES, len(indices), GL_UNSIGNED_INT, None)
    glBindVertexArray(0)

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

    global window
    window = glfw.create_window(window_width, window_height, "Bunny Vertex Array", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.make_context_current(window)
    glfw.set_framebuffer_size_callback(window, reshape)

    glEnable(GL_DEPTH_TEST)
    glEnable(GL_NORMALIZE)
    setup_material()
    setup_lighting()
    setup_buffers()

    while not glfw.window_should_close(window):
        display()
        glfw.poll_events()

    glfw.terminate()


if __name__ == "__main__":
    main()
