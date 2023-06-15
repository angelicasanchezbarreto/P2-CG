//
// Created by angel_rarmbt1 on 8/06/2023.
//

#ifndef LEARNOPENGL_SISTEMASOLAR_H
#define LEARNOPENGL_SISTEMASOLAR_H

#include "Objeto.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader_m.h"
#include "camera.h"
#include "BoundingVolume.h"
#include "glut_ply.h"

#include <iostream>

using namespace std;
using namespace glm;

class SistemaSolar {
private:
    char *archivo = "../models/rock.ply";

    vector<float> planetRadius = {1,2,2.5,2,5,4,2.5,2};
    vector<vec3> colors = {vec3(1.0f, 0.5f, 0.3f),
                           vec3(1.0f, 0.55f, 0.0f),
                           vec3(0.3f, 0.5f, 0.7f),
                           vec3(0.7f, 0.13f, 0.13f),
                           vec3(0.54f, 0.27f, 0.07f),
                           vec3(0.85f, 0.65f, 0.13f),
                           vec3(0.0, 0.75f, 1.0f),
                           vec3(0.0, 0.0f, 1.0f)};

                                        //  x     z
    vector<vec2> planetDistances = {vec2(12,12)};
    vector<float> planetSpeeds = {3,2.7,2.3,2,1.8,1.5,1,0.5};

public:
    vector<Esfera*> planets;
    vector<Objeto*> meteorites;
    Esfera* sun;
    vec3 lightPos;
    vec3 sunColor;

    SistemaSolar();
    void createPlanets();
    void showPlanets(Shader& lightingShader);
    void createMeteorite(Camera camera);
    void shotMeteorite(Shader& lightingShader);
};


#endif //LEARNOPENGL_SISTEMASOLAR_H
