#ifndef GUI_WINDOW_H_GUARD
#define GUI_WINDOW_H_GUARD

#include <iostream>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "utility.h"

const int GLFW_VER_MAJOR = 4;
const int GLFW_VER_MINOR = 6;

const char* GLSL_VER = "#version 130";

namespace Othello::Gui {
    struct Window {
        struct {
            GLFWwindow* window = nullptr;
        } glfw;

        struct {
            ImGuiContext* context = nullptr;
            ImGuiIO* io           = nullptr;
        } imgui;

        Window(const char* TITLE, const int X_POS, const int Y_POS, const int X_SIZE, const int Y_SIZE) {
            {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VER_MAJOR);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VER_MINOR);

                glfw.window = glfwCreateWindow(X_SIZE, Y_SIZE, TITLE, nullptr, nullptr);

                Utility::require(glfw.window);

                glfwSetWindowPos(glfw.window, X_POS, Y_POS);
                glfwMakeContextCurrent(glfw.window);

                Utility::require(gladLoadGL(glfwGetProcAddress));
            }
            {
                IMGUI_CHECKVERSION();

                imgui.context = ImGui::CreateContext();

                ImGui::SetCurrentContext(imgui.context);
                ImGui::StyleColorsDark();

                imgui.io = &ImGui::GetIO();

                ImGui_ImplGlfw_InitForOpenGL(glfw.window, false);
                ImGui_ImplOpenGL3_Init(GLSL_VER);
            }
        }

        ~Window() {
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();
            }
            {
                glfwDestroyWindow(glfw.window);
            }
        }

        inline void startFrame() {
            {
                glfwPollEvents();

                static int sizeX = 0;
                static int sizeY = 0;

                glfwGetFramebufferSize(glfw.window, &sizeX, &sizeY);
                glViewport(0, 0, sizeX, sizeY);
                glClear(GL_COLOR_BUFFER_BIT);
            }
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
            }
        }

        inline void endFrame() {
            {
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
            {
                glfwSwapBuffers(glfw.window);
            }
        }
    };
} // namespace Othello::Gui

#endif