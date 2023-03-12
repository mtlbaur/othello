#include <iostream>
#include <chrono>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "utility.h"
#include "gui_window.h"
#include "gui_board.h"
#include "gui_game_end.h"
#include "gui_cfg.h"

const std::string PATH_SYSTEM = "./data/";
const std::string EXT_DEFAULT = ".cfg";

const double SCREEN_SIZE_X = 1920.0;
const double SCREEN_SIZE_Y = 1080.0;

static double windowSizeX = SCREEN_SIZE_X * 0.75;
static double windowSizeY = SCREEN_SIZE_Y * 0.75;

void glfwKeyCallback(GLFWwindow*, int, int, int, int);
void glfwWindowSizeCallback(GLFWwindow*, int, int);

void execute(Othello::Gui::Window& window);
inline void displayGui();

int main() {
    glfwSetErrorCallback([](int error, const char* desc) {
        std::cerr << "GLFW error: " << error << ": " << desc << '\n';
        abort();
    });

    Othello::Utility::require(glfwInit());

    {
        cfg.load(PATH_SYSTEM, "system", EXT_DEFAULT);

        Othello::Gui::Window window("Othello",
                                    (SCREEN_SIZE_X / 2.0) - (windowSizeX / 2.0),
                                    (SCREEN_SIZE_Y / 2.0) - (windowSizeY / 2.0),
                                    windowSizeX,
                                    windowSizeY);

        { // GLFW WINDOW CALLBACKS
            GLFWwindow* glfwWindow = window.glfw.window;

            glfwSetKeyCallback(glfwWindow, glfwKeyCallback);
            glfwSetWindowSizeCallback(glfwWindow, glfwWindowSizeCallback);

            // forward all other events directly to available ImGui implementation callbacks
            glfwSetWindowFocusCallback(glfwWindow, ImGui_ImplGlfw_WindowFocusCallback);
            glfwSetCursorEnterCallback(glfwWindow, ImGui_ImplGlfw_CursorEnterCallback);
            glfwSetCursorPosCallback(glfwWindow, ImGui_ImplGlfw_CursorPosCallback);
            glfwSetMouseButtonCallback(glfwWindow, ImGui_ImplGlfw_MouseButtonCallback);
            glfwSetScrollCallback(glfwWindow, ImGui_ImplGlfw_ScrollCallback);
            glfwSetCharCallback(glfwWindow, ImGui_ImplGlfw_CharCallback);
        }

        execute(window);

        cfg.save(PATH_SYSTEM, "system", EXT_DEFAULT);
    }

    glfwTerminate();
}

void execute(Othello::Gui::Window& window) {
    std::chrono::steady_clock::time_point updateTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window.glfw.window)) {
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> deltaTime           = currentTime - updateTime; // seconds
        double targetSecondsPerFrame                      = 1.0 / cfg.targetFPS;

        if (deltaTime.count() >= targetSecondsPerFrame) {
            updateTime = currentTime;

            window.startFrame();

            displayGui();

            window.endFrame();
        }
    }
}

inline void displayGui() {
    static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_NoNav |
                                                 ImGuiWindowFlags_NoDecoration |
                                                 ImGuiWindowFlags_NoInputs |
                                                 ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetNextWindowPos({0.0f, 0.0f});
    ImGui::SetNextWindowSize({float(windowSizeX), float(windowSizeY)});

    if (ImGui::Begin("MAIN_WINDOW", nullptr, WINDOW_FLAGS)) {
        Othello::Gui::Board::display();
        cfg.window->display();
        Othello::Gui::GameEnd::display();
    }

    ImGui::End();
}

void glfwKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_F:
                if (glfwGetWindowAttrib(glfwWindow, GLFW_MAXIMIZED)) glfwRestoreWindow(glfwWindow);
                else glfwMaximizeWindow(glfwWindow);
                break;
            case GLFW_KEY_ESCAPE:
                cfg.enabled.cfgWindow ^= true;
                break;
        }
    }
}

void glfwWindowSizeCallback(GLFWwindow* glfwWindow, int x, int y) {
    windowSizeX = x;
    windowSizeY = y;
}