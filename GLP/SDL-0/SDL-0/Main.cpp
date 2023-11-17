#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;



const float PADDLE_WIDTH = 0.05f;   // Width of the paddles
const float PADDLE_HEIGHT = 0.2f;  // Height of the paddles
const float BALL_SIZE = 0.05f;      // Diameter of the ball
const float BALL_SPEED = 0.005f;

float leftPaddleY = 0.0f;
float rightPaddleY = 0.0f;

float verticesPaddleLeft[] = {
    -0.95f, PADDLE_HEIGHT, 0.0f,
    -0.85f - PADDLE_WIDTH, PADDLE_HEIGHT, 0.0f,
    -0.85f - PADDLE_WIDTH, -PADDLE_HEIGHT, 0.0f,
    -0.95f, -PADDLE_HEIGHT, 0.0f,
};

float verticesPaddleRight[] = {
    0.85f + PADDLE_WIDTH, PADDLE_HEIGHT, 0.0f,
    0.95f, PADDLE_HEIGHT, 0.0f,
    0.95f, -PADDLE_HEIGHT, 0.0f,
    0.85f + PADDLE_WIDTH, -PADDLE_HEIGHT, 0.0f
};

float ballX = 0.0f;
float ballY = 0.0f;
float ballVelocityX = BALL_SPEED;
float ballVelocityY = -BALL_SPEED;

bool checkPaddleCollision(float leftPaddleY, float rightPaddleY, float paddleHeight) {
    float paddleTop = paddleHeight;
    float paddleBottom = -paddleHeight;

    // Check collision with left paddle
    if (ballX - BALL_SIZE / 2 < -0.85f && ballX + BALL_SIZE / 2 > -0.95f - PADDLE_WIDTH &&
        ballY + BALL_SIZE / 2 > leftPaddleY + paddleBottom && ballY - BALL_SIZE / 2 < leftPaddleY + paddleTop) {
        ballVelocityX = -ballVelocityX;
        return true;
    }

    // Check collision with right paddle
    if (ballX + BALL_SIZE / 2 > 0.85f + PADDLE_WIDTH && ballX - BALL_SIZE / 2 < 0.95f &&
        ballY + BALL_SIZE / 2 > rightPaddleY + paddleBottom && ballY - BALL_SIZE / 2 < rightPaddleY + paddleTop) {
        ballVelocityX = -ballVelocityX;
        return true;
    }

    return false;
}

void updateLeftPaddleVertices() {
    verticesPaddleLeft[1] = leftPaddleY + PADDLE_HEIGHT;
    verticesPaddleLeft[4] = leftPaddleY + PADDLE_HEIGHT;
    verticesPaddleLeft[7] = leftPaddleY - PADDLE_HEIGHT;
    verticesPaddleLeft[10] = leftPaddleY - PADDLE_HEIGHT;
}

// Function to update right paddle vertices
void updateRightPaddleVertices() {
    verticesPaddleRight[1] = rightPaddleY + PADDLE_HEIGHT;
    verticesPaddleRight[4] = rightPaddleY + PADDLE_HEIGHT;
    verticesPaddleRight[7] = rightPaddleY - PADDLE_HEIGHT;
    verticesPaddleRight[10] = rightPaddleY - PADDLE_HEIGHT;
}




void updateBallPosition() {

    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Bounce off the walls
    if (ballX + BALL_SIZE / 2 > 1.0f) {
        ballX = 1.0f - BALL_SIZE / 2;
        ballVelocityX = -ballVelocityX;
    }
    else if (ballX - BALL_SIZE / 2 < -1.0f) {
        ballX = -1.0f + BALL_SIZE / 2;
        ballVelocityX = -ballVelocityX;
    }

    if (ballY + BALL_SIZE / 2 > 1.0f || ballY - BALL_SIZE / 2 < -1.0f) {
        ballVelocityY = -ballVelocityY;
    }

    // Check paddle collisions
    if (checkPaddleCollision(leftPaddleY, rightPaddleY, PADDLE_HEIGHT)) {
        // Adjust the ball position to prevent sticking to the paddle
        ballX += ballVelocityX;
    }
}



string LoadShader(string fileName);



int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else {
        cout << "SDL initialization succeeded!\n";
    }

    // Create an SDL window
    int width = 1280;
    int height = 720;
    unsigned int center = SDL_WINDOWPOS_CENTERED;
    SDL_Window* Window = SDL_CreateWindow("Pong Game", center, center, width, height, SDL_WINDOW_OPENGL);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);

    string vs = LoadShader("simpleVertex.shader");
    const char* vertexShaderSource = vs.c_str();
    string fs = LoadShader("fragment.shader");
    const char* fragmentShaderSource = fs.c_str();

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Glew initialization failed\n";
        return -1;
    }

    // Set up the OpenGL viewport and background color
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load vertex and fragment shaders, create a shader program
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram, 0, "pos");
    glLinkProgram(shaderProgram);


    // Define vertices for paddles and ball


    float verticesBall[] = {
        // Ball
    	-BALL_SIZE /2, -BALL_SIZE /2, 0.0f,
    	BALL_SIZE /2, -BALL_SIZE /2, 0.0f,
    	BALL_SIZE /2, BALL_SIZE, 0.0f,
    	-BALL_SIZE /2, BALL_SIZE, 0.0f
    };

    unsigned int vboPaddle, vaoPaddle, vboBall, vaoBall;

    // Create vertex arrays and buffers for paddles and ball
    glGenBuffers(1, &vboPaddle);
    glGenVertexArrays(1, &vaoPaddle);
    glBindVertexArray(vaoPaddle);
    glBindBuffer(GL_ARRAY_BUFFER, vboPaddle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPaddleLeft), verticesPaddleLeft, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    // Create VBO and VAO for Ball
    glGenBuffers(1, &vboBall);
    glGenVertexArrays(1, &vaoBall);

    // Bind VAO for Ball
    glBindVertexArray(vaoBall);
    glBindBuffer(GL_ARRAY_BUFFER, vboBall);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBall), verticesBall, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    

    bool isRunning = true;
    while (isRunning) {

        // Inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                // Handle key presses
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    std::cout << "Key pressed up";
                    leftPaddleY += 0.01f;
                    break;
                case SDLK_DOWN:
                    std::cout << "Key pressed up";
                    leftPaddleY -= 0.01f;
                    break;
                case SDLK_w:
                    std::cout << "Key pressed w";
                    rightPaddleY += 0.01f;
                    break;
                case SDLK_s:
                    std::cout << "Key pressed s";
                    rightPaddleY -= 0.01f;
                    break;
                case SDLK_ESCAPE:
                    return 0;
                }

            }
        }

        updateLeftPaddleVertices();
        updateRightPaddleVertices();
        updateBallPosition();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the paddles
        glBindVertexArray(vaoPaddle);

        // Update VBO data for left paddle
        glBindBuffer(GL_ARRAY_BUFFER, vboPaddle);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesPaddleLeft), verticesPaddleLeft);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  // Paddle 1


        // Update VBO data for right paddle
        glBindBuffer(GL_ARRAY_BUFFER, vboPaddle);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesPaddleRight), verticesPaddleRight);

        // Draw the right paddle
        glBindVertexArray(vaoPaddle);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(vaoBall);
        glBindBuffer(GL_ARRAY_BUFFER, vboBall);
        float verticesBall[] = {
            // Ball
            ballX - BALL_SIZE / 2, ballY - BALL_SIZE / 2, 0.0f,
            ballX + BALL_SIZE / 2, ballY - BALL_SIZE / 2, 0.0f,
            ballX + BALL_SIZE / 2, ballY + BALL_SIZE / 2, 0.0f,
            ballX - BALL_SIZE / 2, ballY + BALL_SIZE / 2, 0.0f
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesBall), verticesBall);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        SDL_GL_SwapWindow(Window);

    }

    // Quit
    glDeleteVertexArrays(1, &vaoPaddle);
    glDeleteBuffers(1, &vboPaddle);
    glDeleteVertexArrays(1, &vaoBall);
    glDeleteBuffers(1, &vboBall);

    SDL_DestroyWindow(Window);
    SDL_GL_DeleteContext(Context);
    SDL_Quit();

    SDL_Quit();
    return 0;
}

string LoadShader(string fileName) {
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail()) {
        cerr << "Error - failed to open " << fileName << endl;
    }
    string fileText = "";
    string line = "";
    while (getline(myFile, line)) {
        fileText += line + '\n';
    }
    myFile.close();
    return fileText;
}