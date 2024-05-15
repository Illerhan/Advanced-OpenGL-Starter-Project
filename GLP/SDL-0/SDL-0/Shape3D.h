#pragma once
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Window.h"

using namespace std;

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
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
        }
    }
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