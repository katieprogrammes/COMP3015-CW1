#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <sstream>
#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include "helper/texture.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : tPrev(0), angle(90.0f), rotSpeed(glm::pi<float>()/16.0f), sky(100.0f)
{
    zombie = ObjMesh::load("media/zombie/Zumbi_Female.obj", true, true);
    mimi = ObjMesh::load("media/mimi/Mimikyu.obj", true, true);
}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    projection = mat4(1.0f);

    GLuint cubeTex = Texture::loadCubeMap("media/texture/cube/skybox/skybox", ".jpg");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);

    prog.use(); 
    prog.setUniform("Light.L", vec3(0.9f));
    prog.setUniform("Light.La", vec3(0.5f));
    prog.setUniform("Fog.MaxDist", 75.0f);
    prog.setUniform("Fog.MinDist", 1.0f);
    prog.setUniform("Fog.Color", vec3(0.5f, 0.5f, 0.5f));

    //zombie texture
    zombieTex = Texture::loadTexture("media/texture/pele.png");
    prog.setUniform("DiffuseTex", 1);

    //mimikyu texture
    mimiTex = Texture::loadTexture("media/texture/Mimigma.png");
    prog.setUniform("DiffuseTex", 1);


    //world fog
    skyboxprog.use();
    skyboxprog.setUniform("Fog.MaxDist", 120.0f);
    skyboxprog.setUniform("Fog.MinDist", 10.0f);
    skyboxprog.setUniform("Fog.Color", vec3(0.5f, 0.5f, 0.5f));
}

void SceneBasic_Uniform::compile()
{
	try {
		skyboxprog.compileShader("shader/skybox.vert");
		skyboxprog.compileShader("shader/skybox.frag");
		skyboxprog.link();

        prog.compileShader("shader/basic_uniform.vert");
        prog.compileShader("shader/basic_uniform.frag");
        prog.link();


	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;
    if (tPrev == 0.0f) deltaT = 0.0f;
    tPrev = t;
    if (cameraRotate) 
    {
        angle += rotSpeed * deltaT;
    }
    if (angle > glm::two_pi<float>())angle -= glm::two_pi<float>();
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos = vec3(7.0f*cos(angle), 2.0f, 7.0f*sin(angle));
    view = glm::lookAt(cameraPos, vec3(-3.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    //skybox
    skyboxprog.use();
    skyboxprog.setUniform("FogEnabled", fogEnabled);
    model = mat4(1.0f);
    setSkyboxMatrices();
    sky.render();

    //zombies
    prog.use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, zombieTex);
    prog.setUniform("DiffuseTex", 1);

    prog.setUniform("Material.Kd", vec3(0.8f));
    prog.setUniform("Material.Ka", vec3(0.2f));
    prog.setUniform("Material.Ks", vec3(0.1f));
    prog.setUniform("Material.Shininess", 32.0f);

    float dist = 0.0f;
    for (int i = 0; i < 5; i++)
    {
        model = mat4(1.0f);

        float x = i * 6.0f - 12.0f;  //horizontal across
        float y = 0.0f;
        float z = -30.0f;          //depth

        model = glm::translate(model, vec3(x, y, z));
        model = glm::rotate(model, glm::radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, vec3(0.04f));

        setMatrices();
        zombie->render();
    }

    //Mimikyu
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mimiTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    prog.setUniform("DiffuseTex", 1);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(4.0f, 0.0f, 14.0f));
    model = glm::rotate(model, glm::radians(110.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, vec3(15.0f));
    setMatrices();
    mimi->render();

}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);

}
void SceneBasic_Uniform::setSkyboxMatrices()
{
    mat4 mv = view * model;
    skyboxprog.setUniform("ModelViewMatrix", mv);
    skyboxprog.setUniform("NormalMatrix", mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    skyboxprog.setUniform("MVP", projection * mv);
}
void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view*model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}
