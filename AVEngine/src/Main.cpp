#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

int main(int argc, char** argv) {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", nullptr, nullptr);
    if (window == nullptr) {
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    printf("%s\n", glGetString(GL_VERSION));

    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray vertexArray;
        VertexBuffer vertexBuffer(vertices, 4 * 5 * sizeof(float));
        VertexBufferLayout vertexBufferLayout;
        vertexBufferLayout.Push<float>(3);
        vertexBufferLayout.Push<float>(2);
        vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

        IndexBuffer indexBuffer(indices, 6);

        Shader shader("assets/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("assets/textures/texture.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        vertexArray.Unbind();
        vertexBuffer.Unbind();
        indexBuffer.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        while (!glfwWindowShouldClose(window)) {
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.4f, 0.8f, 1.0f);
            shader.SetUniform1i("u_Texture", 0);

            renderer.Draw(vertexArray, indexBuffer, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}