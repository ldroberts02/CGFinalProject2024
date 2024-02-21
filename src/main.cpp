#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Canis/Canis.hpp"
#include "Canis/Window.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Debug.hpp"
#include "Canis/IOManager.hpp"

int main(int argc, char *argv[])
{
    Canis::Init();

    using namespace glm;

    /// SETUP WINDOW
    Canis::Window window;

    unsigned int flags = 0;

    if (Canis::GetProjectConfig().fullscreen)
        flags |= Canis::WindowFlags::FULLSCREEN;
    
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

    /// Load Image
    Canis::GLTexture texture = Canis::LoadImageGL("assets/textures/BlebhDzIcAALt8a.png");
    /// End of Image Loading

    /// SETUP MODEL
    float vertices[] = {                        // vertices in counter clockwise order
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,         // bottom left
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,         // bottom right
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,         // top right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,         // bottom left
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,         // top right
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,         // top left
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        shader.SetVec3("COLOR", 0.0f, 0.0f, 1.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        shader.SetInt("MEMETEXTURE", 0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        shader.UnUse();

        window.SwapBuffer();
        SDL_Delay(10);
    }

    return 0;
}