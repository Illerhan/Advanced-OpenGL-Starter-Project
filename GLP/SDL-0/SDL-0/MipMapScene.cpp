#include "MipMapScene.h"

void MipMapScene::LoadShaders()
{
    m_vertexShader.LoadFrom("vertexMove.shader", VERTEX);
    m_fragmentShader.LoadFrom("simpleFragment.shader", FRAGMENT);
}

void MipMapScene::CreateShaderPrograms()
{
    m_shaderProgram.Compose(vector<Shader*>{&m_vertexShader, &m_fragmentShader});
}

void MipMapScene::VerticeInformationSlicer()
{
    float* verticeArray = new float[m_vertices.size()]();
    std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), verticeArray, GL_STATIC_DRAW);
    //Now we split informations of the array : 2 float infos for the position / vertex
    // Position attribute												
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //const POSITION = 0
    delete [] verticeArray;
}

void MipMapScene::SetupScene()
{
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.25f,-0.5f),Vector2(0.5f,0.2f));
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.5f,0.f),Vector2(0.5f,0.2f));
    Shape2D::CreateRectangle(m_vertices,Vector2(0.5f,0.f),Vector2(0.5,0.25f));
    Shape2D::CreateRectangle(m_vertices,Vector2(0.5f,0.75f),Vector2(0.5,0.25f));

    LoadShaders();
    CreateShaderPrograms();
    VerticeInformationSlicer();
}

void MipMapScene::UpdateScene()
{

    int current = 0;
    for (int s =0; s<4; s++)
    {
        current = Shape2D::DrawRectangle(current);
    }
}
