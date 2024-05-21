#pragma once
#include "Scene.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"

class SphereScene : public Scene
{
private:
    Texture2D m_WallTexture;
    Shader m_tessVertexShader, m_tessFragShader, m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader,m_geometryShader;
    ShaderProgram m_Program, m_tessProgram;
    Matrix4 m_projection, m_mv, m_rotation;
    Vector3 m_position;
    unsigned int m_vboV, m_vboI;

    unsigned int m_vboV2, m_vboI2;
    ShaderProgram m_Program2;
    
    std::vector<unsigned int> m_indicies2, m_lineIndices2;
    std::vector<unsigned int> m_indicies, m_lineIndices;
protected:
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;
public:
    SphereScene();
    ~SphereScene() = default;
    void SetupScene() override;
    void UpdateScene() override;
public:
    
};
