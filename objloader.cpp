#include <pch.h>
#include <glm/glm.hpp>
#include <boost/algorithm/string.hpp>
#include "tiny_obj_loader.h"
#include "iglmachine.h"
#define TINYOBJLOADER_IMPLEMENTATION

using namespace std;

void loadObjByTiny(const char* filename, std::vector<float> &verts, std::vector<float> &norms, std::vector<unsigned int> &facs){
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    tinyobj::attrib_t attrib;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename);

    if (!err.empty()) { // `err` may contain warning message.
      std::cerr << err << std::endl;
    }
    if (!ret) {
      exit(1);
    }
    verts.clear();norms.clear();facs.clear();
    for(int i=0;i<(int)attrib.vertices.size();i++){
        verts.push_back(attrib.vertices[i]);
    }
    for(int i=0;i<(int)attrib.normals.size();i++){
        norms.push_back(attrib.normals[i]);
    }
    for (size_t i = 0; i < shapes.size(); i++) {
        size_t indexOffset = 0;
        for (size_t n = 0; n < shapes[i].mesh.num_face_vertices.size(); n++) {
            int ngon = shapes[i].mesh.num_face_vertices[n];
            for (size_t f = 0; f < (size_t)ngon; f++) {
                unsigned int v = shapes[i].mesh.indices[indexOffset + f].vertex_index;
                facs.push_back(v);
            }
            indexOffset += ngon;
        }
    }
}
void IglMachine::loadObj(const char* filename, std::vector<float> &verts, std::vector<float> &norms, std::vector<unsigned int> &facs){
    loadObjByTiny(filename, verts, norms, facs);
}
