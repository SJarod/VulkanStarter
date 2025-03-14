#include <cstdio>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "demo_test.hpp"
// NOTES: Placez vos includes ici et modifiez demoList dans le main(), et n'oubliez pas de modifier le Makefile
#include "demo_renderer_basic.hpp"
#include "demo_renderer_onevao.hpp"
#include "demo_renderer_modelvao.hpp"
#include "demo_renderer_multidraw.hpp"

#include "memleaks.hpp"

void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf("OpenGL error: %s\n", message);
}

int main(int argc, char* argv[])
{
    initMemleaksDebug();

    int screenWidth  = 1200;
    int screenHeight = 800;

    if (!glfwInit())
    {
        printf("glfwInit failed\n");
        return -1;
    }

    // Target OpenGL 4.5 API in Compatibility mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "GLFW test", nullptr, nullptr);
    if (window == nullptr)
    {
        printf("glfwCreateWindow failed\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (gladLoaderLoadGL() == 0)
    {
        printf("gladLoaderLoadGL failed\n");
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, NULL);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool showDemoWindow = false;

    Demo* demoList[] =
    {
        new DemoTest(),
        new DemoRendererBasic(),
        new DemoRendererOneVao(),
        new DemoRendererModelVao(),
        new DemoRendererMultiDraw(),
    };

    int demoIndex = 0; // Start index
    int demoCount = IM_ARRAYSIZE(demoList);

    while (glfwWindowShouldClose(window) == false)
    {
        glfwSwapInterval(0);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::Checkbox("Show demo window", &showDemoWindow);
        ImGui::InputInt("Demo index", &demoIndex);
        demoIndex = (demoIndex < 0) ? 0 : (demoIndex >= demoCount) ? demoCount-1 : demoIndex; // clamp

        Demo& currentDemo = *demoList[demoIndex];
        ImGui::Text("Demo name: %s", currentDemo.name());
        ImGui::Separator();

        currentDemo.display();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    for (int i = 0; i < demoCount; ++i)
        delete demoList[i];

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
