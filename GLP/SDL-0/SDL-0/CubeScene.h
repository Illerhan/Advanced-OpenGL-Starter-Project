#pragma once
#include "BaseScene.h"
#include "Texture.h"

class CubeScene : public Scene
{
private:
    Texture2D texture;
    Shader m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader,m_geometryShader,m_fragmentCubeShader;
    ShaderProgram m_Program,m_ProgramTess;
    Matrix4 projection, mv, rotation;
    Vector3 position;
    bool wireframe;
protected:
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;
public:
    CubeScene();
    ~CubeScene() = default;
    void SetupScene() override;
    void UpdateScene() override;
protected:
    
};
