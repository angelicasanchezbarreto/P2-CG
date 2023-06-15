//
// Created by angel_rarmbt1 on 8/06/2023.
//

#include "SistemaSolar.h"

SistemaSolar::SistemaSolar() {
    sun = new Esfera(vec3(0),10,50,50);
    sun->bs = new BoundingSphere(sun->centro,sun->radius);
    lightPos = vec3(0);
    sunColor = vec3(1.0f, 1.0f, 0.0f);
}

void SistemaSolar::createPlanets(){
    sun->setup();
    for (int i=0; i<planetRadius.size();i++) {
        Esfera *pE = new Esfera(glm::vec3(0),planetRadius[i],20,20);
        pE->v0 = 20;
        pE->a0 = 40 + rand() % 20;
        pE->bs = new BoundingSphere(pE->centro,pE->radius);
        pE->color = colors[i];
        pE->tiempoInicial = static_cast<float>(glfwGetTime());
        planets.emplace_back(pE);
        planets[i]->setup();
    }
    //setting distances from sun
    for(int i=1; i<planetRadius.size(); i++){
        float dist = planetDistances[i-1].x + planetRadius[i-1] + planetRadius[i] + 2;
        vec2 planetDist = vec2(dist,dist);
        planetDistances.emplace_back(planetDist);
    }
}

void SistemaSolar::showPlanets(Shader& lightingShader){
    int i=0;
    sun->display(lightingShader);
    float currentFrame = static_cast<float>(glfwGetTime());
    for(auto planet:planets){
        float tiempoTranscurrido = currentFrame - planet->tiempoInicial;
        lightingShader.setVec3("objectColor", planet->color);
        if(!planet->falling)
            planet->orbit(tiempoTranscurrido, planetDistances[i], planetSpeeds[i]);
        else {
            planet->drop(tiempoTranscurrido);
        }
        planet->display(lightingShader);
        i++;
    }
}

void SistemaSolar::createMeteorite(Camera camera){
    Model_PLY* pE = new Model_PLY();
    pE->Load(archivo);
    pE->escala = 0.5;
    pE->v0 = 20;
    pE->a0 = 40 + rand() % 20;
    pE->x0 = camera.Position.x;
    pE->y0 = camera.Position.y;
    pE->z0 = camera.Position.z;
    pE->obtenerBS();
    //pE->centro = camera.Position;
    pE->tiempoInicial = static_cast<float>(glfwGetTime());
    pE->setup();
    meteorites.emplace_back(pE);
}

void SistemaSolar::shotMeteorite(Shader& lightingShader){
    int i=0;
    float currentFrame = static_cast<float>(glfwGetTime());
    for(auto& meteorite:meteorites){
        float tiempoTranscurrido = currentFrame - meteorites[i]->tiempoInicial;
        lightingShader.setVec3("objectColor", vec3(0.2f,0.2f,0.2f));
        meteorite->actualizarPosicion(tiempoTranscurrido);
        meteorite->display(lightingShader);
        if(meteorite->centro.z< -60)
            meteorites.erase(meteorites.begin()+i);

        for (auto  planet : planets) {
            if (meteorite->bs->intersecta(*(planet->bs))) {
                cout << "COLLISION" << endl;
                planet->falling=true;
            }
        }
        i++;
    }
}
