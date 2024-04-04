#pragma once
#include "Scene.h"
#include "Shapes2D.h"
class MipMapScene : public Scene
{
protected:
    virtual void LoadShaders();
    virtual void CreateShaderPrograms();
    virtual void VerticeInformationSlicer();
public:
    MipMapScene(std::string nameP = "MipMap"):Scene(nameP){}
    ~MipMapScene();
	
    virtual void SetupScene();
    virtual void UpdateScene();
private:
    Shader m_vertexShader, m_fragmentShader;
    ShaderProgram m_shaderProgram;
};
