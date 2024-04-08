#pragma once
#include "Scene.h"
#include "Texture.h"

class GrassScene: public Scene
{
private:
    Shader m_vertexShader, m_animVertexShader, m_fragmentShader;
    ShaderProgram m_shaderProgram, m_animShaderProgram;
    Texture2D m_WallTexture, m_GrassTexture;
    bool mipmap = false;
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;
public:
    GrassScene():Scene("Texture Scene"){}
    ~GrassScene() {}
    void SetupScene() override;
    void UpdateScene() override;
    void HandleInputs(SDL_Event& e) override;
};
