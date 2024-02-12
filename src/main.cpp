#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"

int main(int argc, char *argv[])
{
    /// SETUP WINDOW
    Canis::Window window;

    unsigned int flags = 0;

    if (Canis::GetProjectConfig().fullscreen)
        flags |= Canis::FULLSCREEN;
    
    window.Create("Hello Triangle",
        Canis::GetProjectConfig().width,
        Canis::GetProjectConfig().heigth,
        flags);
    /// END OF WINDOW SETUP

    /// SETUP SHADER
    Canis::Shader shader;
    shader.Compile("assets/shaders/hello_shader.vs", "assets/shaders/hello_shader.fs");
    shader.AddAttribute("aPosition");
    shader.Link();
    /// END OF SHADER

    /// SETUP MODEL
    float vertices[] = {        // vertices in counter clockwise order
        -0.5f, -0.5f, 0.0f,     // bottom left
        0.5f, -0.5f, 0.0f,      // bottom right
        0.0f, 0.5f, 0.0f        // top center
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /// END OF MODEL

    bool running = true;

    while(running)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        shader.UnUse();

        window.SwapBuffer();
        SDL_Delay(10);
    }

    return 0;
}