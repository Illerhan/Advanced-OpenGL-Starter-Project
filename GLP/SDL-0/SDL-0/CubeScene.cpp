#include "CubeScene.h"

#include "MeshObject.h"
#include "Window.h"
#include <vector>
#include <cmath>

std::vector<float> generateSphereVertices(int stacks, int slices, float radius) {
	std::vector<float> vertices;

	for (int i = 0; i <= stacks; ++i) {
		float phi = static_cast<float>(M_PI) * i / stacks;
		float sinPhi = std::sin(phi);
		float cosPhi = std::cos(phi);

		for (int j = 0; j <= slices; ++j) {
			float theta = 2 * static_cast<float>(M_PI) * j / slices;
			float sinTheta = std::sin(theta);
			float cosTheta = std::cos(theta);

			float x = radius * cosTheta * sinPhi;
			float y = radius * cosPhi;
			float z = radius * sinTheta * sinPhi;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}

	return vertices;
}
CubeScene::CubeScene()
{
	
}


void CubeScene::LoadShaders() {
	m_vertexShader.LoadFrom("cube.vert", VERTEX);
	m_fragmentCubeShader.LoadFrom("cube.frag", FRAGMENT);
	m_fragmentShader.LoadFrom("cubeColor.frag", FRAGMENT);
	m_tessControlShader.LoadFrom("tessControlCube.tesc", TESSELLATION_CONTROL);
	m_tessEvalShader.LoadFrom("tessCube.tese", TESSELLATION_EVALUATION);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

}

void CubeScene::CreateShaderPrograms()
{
	 m_Program.Compose(
	 	std::vector<Shader*>{
	 	&m_vertexShader,
		&m_fragmentCubeShader 
	 });
	m_ProgramTess.Compose(
		std::vector<Shader*>{
		&m_vertexShader,
		&m_fragmentShader ,
		&m_tessControlShader,
		&m_tessEvalShader
	});
}

void CubeScene::VerticeInformationSlicer()
{
	float* verticeArray = new float[m_vertices.size()]();
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), verticeArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	delete [] verticeArray;
}

void CubeScene::SetupScene()
{
	m_vertices = generateSphereVertices(25.0f, 150, 5);
	// m_vertices = {-0.5f,  0.5f, -0.5f,
	// 		  -0.5f, -0.5f, -0.5f,
	// 			0.5f, -0.5f, -0.5f,
	//
	// 			0.5f, -0.5f, -0.5f,
	// 			0.5f,  0.5f, -0.5f,
	// 		  -0.5f,  0.5f, -0.5f,
	//
	// 			0.5f, -0.5f, -0.5f,
	// 			0.5f, -0.5f,  0.5f,
	// 			0.5f,  0.5f, -0.5f,
	//
	// 			0.5f, -0.5f,  0.5f,
	// 			0.5f,  0.5f,  0.5f,
	// 			0.5f,  0.5f, -0.5f,
	//
	// 			0.5f, -0.5f,  0.5f,
	// 		  -0.5f, -0.5f,  0.5f,
	// 			0.5f,  0.5f,  0.5f,
	//
	// 		  -0.5f, -0.5f,  0.5f,
	// 		  -0.5f,  0.5f,  0.5f,
	// 			0.5f,  0.5f,  0.5f,
	//
	// 		  -0.5f, -0.5f,  0.5f,
	// 		  -0.5f, -0.5f, -0.5f,
	// 		  -0.5f,  0.5f,  0.5f,
	//
	// 		  -0.5f, -0.5f, -0.5f,
	// 		  -0.5f,  0.5f, -0.5f,
	// 		  -0.5f,  0.5f,  0.5f,
	//
	// 		  -0.5f, -0.5f,  0.5f,
	// 			0.5f, -0.5f,  0.5f,
	// 			0.5f, -0.5f, -0.5f,
	//
	// 			0.5f, -0.5f, -0.5f,
	// 		  -0.5f, -0.5f, -0.5f,
	// 		  -0.5f, -0.5f,  0.5f,
	//
	// 		  -0.5f,  0.5f, -0.5f,
	// 			0.5f,  0.5f, -0.5f,
	// 			0.5f,  0.5f,  0.5f,
	//
	// 			0.5f,  0.5f,  0.5f,
	// 		  -0.5f,  0.5f,  0.5f,
	// 		  -0.5f,  0.5f, -0.5f
	// 	};
	LoadShaders();
	CreateShaderPrograms();
	projection = Matrix4::createPerspectiveFOV(70.0f, Window::Dimension.x, Window::Dimension.y, 0.1f, 1000.0f);
	position = Vector3(0, 0, -8.0f);
	mv = Matrix4::createTranslation(position);

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	VerticeInformationSlicer();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Creating and loading the simple texture
	Texture2D m_WallTexture = Texture2D();
	m_WallTexture.load("Textures/wall.png");
	m_WallTexture.generate();
	m_WallTexture.use();
	glGenerateTextureMipmap(m_WallTexture.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

}

void CubeScene::UpdateScene() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue))/2.0f;
	
	position.y = sinusoidValue;
	m_Program.Use();
	mv = Matrix4::createTranslation(position -Vector3(2.f,0,-150));
	Matrix4 rotationX = Matrix4::createRotationX(0.01f );
	Matrix4 rotationY = Matrix4::createRotationY(0.005f );
	Matrix4 rotationZ = Matrix4::createRotationY(0.01f );
	rotation *= rotationX;
	rotation *= rotationY;
	rotation *= rotationZ;
	mv = mv * rotation;
	
	m_Program.setMatrix4("mv_matrix", mv);
	m_Program.setMatrix4("projection", projection);
	
	//glDrawArrays(GL_TRIANGLES, 0, 1500);
	
	
	mv = Matrix4::createTranslation(position + Vector3(2.f,0,-150));
	mv = mv * rotation;
	//m_ProgramTess.setMatrix4("mv_matrix", mv);
	
	m_ProgramTess.Use();
	m_ProgramTess.setMatrix4("mv_matrix", mv);
	m_ProgramTess.setMatrix4("projection", projection);
	m_ProgramTess.setFloat("ratioOuter", (sinusoidValue+1.1)*2);
	m_ProgramTess.setFloat("ratioInner", (sinusoidValue+1.0)*5);

	glPointSize(5.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_PATCHES, 0, 4000);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
