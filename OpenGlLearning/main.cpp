#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

#include <iostream>

#include "Renderer.h"

#include "Texture.h"

#include "raymath.h"

#include "mineclone/Game.h"

int main(void)
{
    GLFWwindow* window;
  
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1440, 900, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //std::cout << (glfwSetKeyCallback(window, keyCallback)
    //    ? "[Input Function Set Successfully]\n" : "Input Function Failed!\n");

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error!";
    }

    std::cout << glGetString(GL_VERSION);


    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    //glEnable(GL_DEPTH_TEXTURE_MODE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_STENCIL_TEST);
    glEnable(GL_CULL_FACE);
    //glDepthFunc(GL_LESS);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    Game* game = new Game();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        renderer.Clear();
    
        ImGui_ImplGlfwGL3_NewFrame();

        if (game)
        {
            game->SetWindowPointer(window);
            game->OnUpdate(0.0f);
            game->OnRender();
            ImGui::Begin("Test");

            game->OnImGuiRender();

            ImGui::End();
        }
 
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    delete game;
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}