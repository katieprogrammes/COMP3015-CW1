#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "helper/objmesh.h"
#include "helper/skybox.h"

class SceneBasic_Uniform : public Scene
{
private:
    SkyBox sky;
    float rotSpeed;
    std::unique_ptr<ObjMesh> zombie; //zombie mesh
    std::unique_ptr<ObjMesh> mimi; //mimikyu mesh
    float tPrev;
    float angle;
    GLSLProgram skyboxprog;
    GLSLProgram prog;
    glm::mat4 rotationMatrix;

    GLuint zombieTex;
    GLuint mimiTex;

    void compile();
    void setSkyboxMatrices();
    void setMatrices();




public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
