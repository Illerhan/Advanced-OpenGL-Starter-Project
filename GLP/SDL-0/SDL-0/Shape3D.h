#pragma once

#include <random>
#include <cmath>

#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Window.h"

using namespace std;

class NoiseTexture {
public:
	vector<vector<vector<float>>> noiseData; // 3D noise texture data

	NoiseTexture(int width, int height, int depth) {
		noiseData.resize(width);
		for (int i = 0; i < width; ++i) {
			noiseData[i].resize(height);
			for (int j = 0; j < height; ++j) {
				noiseData[i][j].resize(depth);
				for (int k = 0; k < depth; ++k) {
					// Generate noise values (in this example, using random values)
					noiseData[i][j][k] = static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f; // Range [-1, 1]
				}
			}
		}
	}

	float sample(float x, float y, float z) const {
		// Sample noise texture at given coordinates
		int width = noiseData.size();
		int height = noiseData[0].size();
		int depth = noiseData[0][0].size();

		// Map input coordinates to texture indices
		int i = static_cast<int>((x + 1.0f) / 2.0f * (width - 1));
		int j = static_cast<int>((y + 1.0f) / 2.0f * (height - 1));
		int k = static_cast<int>((z + 1.0f) / 2.0f * (depth - 1));

		// Clamp indices to valid range
		i = max(0, min(i, width - 1));
		j = max(0, min(j, height - 1));
		k = max(0, min(k, depth - 1));

		return noiseData[i][j][k];
	}
};

class Shape3D {
protected:

    public:
	static inline void CreateCube(vector<float>& vertices, Vector2 center, Vector3 dimensions) {
		
	}
    

    static inline void CreateSphere(vector<float>& vertices, vector<unsigned int>& indices, vector<unsigned int>& lineIndices, Vector3 center, float radius, int horizontalCount, int verticalCount)
	{
		const float pi = acos(-1.0f);

        float x, y, z, xy;                              // vertex position

        float horizontalStep = 2 * pi / horizontalCount;
        float verticalStep = pi / verticalCount;
        float horizontalAngle, verticalAngle;

        // Create noise texture (for demonstration purposes)
        NoiseTexture noiseTexture(64, 64, 64); // You can adjust dimensions as needed

		float displacementScale = 0.1f; // Define displacement scale

        for(int line = 0; line <= verticalCount; ++line)
        {
            verticalAngle = pi / 2 - line * verticalStep;        // starting from pi/2 to -pi/2
            xy = radius * cosf(verticalAngle);             // r * cos(u)
            z = radius * sinf(verticalAngle);              // r * sin(u)

            // add (sectorCount+1) vertices per stack
            // the first and last vertices have same position and normal, but different tex coords
            for(int col = 0; col <= horizontalCount; ++col)
            {
                horizontalAngle = col * horizontalStep;           // starting from 0 to 2pi

                x = xy * cosf(horizontalAngle);             // r * cos(u) * cos(v)
                y = xy * sinf(horizontalAngle);             // r * cos(u) * sin(v)

                // Sample noise texture to determine displacement
                float noise = noiseTexture.sample(x, y, z); // Sample noise texture
                float displacementScale = 0.1f; // Adjust this scale as needed
                x += noise * displacementScale;
                y += noise * displacementScale;
                z += noise * displacementScale;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }

        // Add lines for trees using geometry shader
        
    //Generate indicies for the order in which the triangles should be drawn
    // indices
    //  t--t+1
    //  |  / |
    //  | /  |
    //  b--b+1
    unsigned int top, bottom;
    for(int line = 0; line < verticalCount; ++line)
    {
        top = line * (horizontalCount + 1);     // beginning of current stack
        bottom = top + horizontalCount + 1;      // beginning of next stack

        for(int j = 0; j < horizontalCount; ++j, ++top, ++bottom)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(line != 0)
            {
                // t---b---t+1
            	indices.push_back(top);
            	indices.push_back(bottom);
            	indices.push_back(top+1);
            }

            if(line != (verticalCount-1))
            {
                //addIndices(t+1, b, b+1); // t+1---b---b+1
            	indices.push_back(top+1);
            	indices.push_back(bottom);
            	indices.push_back(bottom+1);
            }

            // vertical lines for all stacks
            lineIndices.push_back(top);
            lineIndices.push_back(bottom);
            if(line != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(top);
                lineIndices.push_back(top + 1);
            }
        }
    }

}

};