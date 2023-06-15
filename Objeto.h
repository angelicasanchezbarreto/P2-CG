//
// Created by hgallegos on 5/10/2022.
//

#ifndef LEARNOPENGL_OBJETO_H
#define LEARNOPENGL_OBJETO_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader_m.h"
#include "BoundingVolume.h"

using namespace std;
using namespace glm;

class Objeto {
public:
    vector<vec3> positions;
    vector<vec3> normals;
    vector<vec2> textureCoords;
    vector<GLuint> indices;
    GLuint indices_size;
    float v0, x0, y0, z0, a0, xt, yt, zt;
    float tiempoInicial = 0.0f;
    GLuint vao;
    mat4 model;
    bool visible=true;
    vec3 color;
    bool falling=false;
    BoundingSphere *bs;
    bool mueve = true;
    float escala = 20;
    vec3 centro;
    //int ran = rand()%5+(-9);
    int ran = rand()%8+2;
    bool ranBool = rand() > (RAND_MAX / 2);

    GLint POSITION_ATTRIBUTE=0, NORMAL_ATTRIBUTE=1, TEXCOORD0_ATTRIBUTE=8;
    Objeto(){
        bs = new BoundingSphere;
    }
    virtual GLuint setup()=0;
    virtual void display(Shader &sh)=0;
    virtual void actualizarPosicion(float tiempo)=0;
    virtual void obtenerBS() {};
    virtual void actualizarBS() {};
    virtual void orbit(float tiempo,vec2 distances,float speed)=0;
};

class Esfera:public Objeto{
public:
    float radius;
    int slices, stacks;
    Esfera() {
        centro = vec3(0.0);
        escala = 0.5;
    }
    Esfera(vec3 _centro) {
        centro = _centro;
        escala = 0.5;
    }
    Esfera(vec3 _centro, float _radius, int _slices, int _stacks) {
        centro = _centro;
        radius = _radius;
        slices = _slices;
        stacks = _stacks;
        escala = 0.5;
    }
    Esfera& operator=(const Esfera& esfera){
        this->centro = esfera.centro;
        this->radius = esfera.radius;
        this->slices = esfera.slices;
        this->stacks = esfera.stacks;
    }
    GLuint setup();

    void display(Shader &sh);
    void actualizarPosicion(float tiempo);
    void actualizarBS();
    void orbit(float tiempo,vec2 distances,float speed);
    void drop(float tiempo);
};

#endif //LEARNOPENGL_OBJETO_H
