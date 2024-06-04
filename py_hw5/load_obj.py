import numpy as np

def load_obj(file_path):
    vertices = []
    normals = []
    faces = []

    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith('v '):
                parts = line.split()
                vertices.append([float(parts[1]), float(parts[2]), float(parts[3])])
            elif line.startswith('vn '):
                parts = line.split()
                normals.append([float(parts[1]), float(parts[2]), float(parts[3])])
            elif line.startswith('f '):
                parts = line.split()
                face = []
                for part in parts[1:]:
                    indices = part.split('//')
                    vertex_index = int(indices[0]) - 1
                    normal_index = int(indices[1]) - 1
                    face.append((vertex_index, normal_index))
                faces.append(face)

    vertices = np.array(vertices, dtype=np.float32)
    normals = np.array(normals, dtype=np.float32)
    return vertices, normals, faces
