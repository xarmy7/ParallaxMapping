#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include "application.h"
#include "resourceManager.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"
#include "light.h"

#include "maths/vec3.h"
#include "maths/vec2.h"
#include "maths/mat4.h"

void RenderQuad();
void processInput(GLFWwindow* window, bool& mouseCaptured, CameraInputs& input)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double newMouseX = 0.f;
    double newMouseY = 0.f;

    glfwGetCursorPos(window, &newMouseX, &newMouseY);
    float mouseDeltaX = (float)(newMouseX - input.mousePosX);
    float mouseDeltaY = (float)(newMouseY - input.mousePosY);

    input.mousePosX = newMouseX;
    input.mousePosY = newMouseY;

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        if (!mouseCaptured)
        {
            mouseCaptured = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            mouseCaptured = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (mouseCaptured)
    {
        input.deltaX = mouseDeltaX;
        input.deltaY = mouseDeltaY;
        input.moveForward = ImGui::IsKeyDown(GLFW_KEY_W);
        input.moveBackward = ImGui::IsKeyDown(GLFW_KEY_S);
        input.strafeLeft = ImGui::IsKeyDown(GLFW_KEY_A);
        input.strafeRight = ImGui::IsKeyDown(GLFW_KEY_D);
        input.moveUp = ImGui::IsKeyDown(GLFW_KEY_SPACE);
        input.moveDown = ImGui::IsKeyDown(GLFW_KEY_LEFT_CONTROL);
    }
    else
    {
        input.deltaX = 0.f;
        input.deltaY = 0.f;
        input.moveForward = 0.f;
        input.moveBackward = 0.f;
        input.strafeLeft = 0.f;
        input.strafeRight = 0.f;
    }
}

using namespace Core::Maths::Mat4;
using namespace Core::Maths::Vec3;
using namespace Core::Maths::Vec2;
using namespace Core::Maths::Vec4;

int main()
{
    Application app;
    Shader shader;
    Texture texture;
    ResourceManager RM;
    Camera camera(SCR_WIDTH, SCR_HEIGHT);
    CameraInputs input;
    Transform transform;
    Light light;
    mat4x4 view, proj, model, mvp;

    app.InitGLFW();
    app.CreateWindow();

    GLFWwindow* window = app.GetWindow();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -2;
    }

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");


    RM.LoadResources(shader, texture);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glEnable(GL_CULL_FACE);

#pragma region VertexObject
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

#pragma endregion

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    glUseProgram(shader.shaderProgram); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shader.shaderProgram, "diffuseMap"), 0);
    //normal texture
    glUniform1i(glGetUniformLocation(shader.shaderProgram, "normalMap"), 1);
    //depth texture
    glUniform1i(glGetUniformLocation(shader.shaderProgram, "depthMap"), 2);

    //glUniform1i(glGetUniformLocation(shader.shaderProgram, "skybox"), 0);

    while (!glfwWindowShouldClose(window))
    {
        app.newFrame();
        app.showImGuiControl(window, camera, transform, light);

        view = camera.GetViewMatrix();
        proj = camera.GetProjection();
        model = transform.transform();
        mvp = proj * view * model;

        processInput(window, app.mouseCaptured, input);
        camera.Update(ImGui::GetIO().DeltaTime, input);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.UpdateShader(shader, texture.textureObject, VAO, skyboxVAO, mvp, model);

        light.LoadLight(shader.shaderProgram, camera); //Light

        RenderQuad();

        // draw our first triangle

        app.endFrame(window);
    }

    //Clear Buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.shaderProgram);

    glfwTerminate();
    return 0;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void RenderQuad()
{
    if (quadVAO == 0)
    {
        // positions
        float3 pos1{ -1.0f, 1.0f, 0.0f };
        float3 pos2{ -1.0f, -1.0f, 0.0f };
        float3 pos3{ 1.0f, -1.0f, 0.0f };
        float3 pos4{ 1.0f, 1.0f, 0.0f };

        // texture coordinates
        float2 uv1{ 0.0f, 1.0f };
        float2 uv2{ 0.0f, 0.0f };
        float2 uv3{ 1.0f, 0.0f };
        float2 uv4{ 1.0f, 1.0f };
        // normal vector
        float3 nm{ 0.0f, 0.0f, 1.0f };

        // calculate tangent/bitangent vectors of both triangles
        float3 tangent1, bitangent1;
        float3 tangent2, bitangent2;
        // triangle 1
        // ----------
        float3 edge1 = pos2 - pos1;
        float3 edge2 = pos3 - pos1;
        float2 deltaUV1 = uv2 - uv1;
        float2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        //tangent1 = Core::Maths::Fmaths::normal(tangent1);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        //tangent1 = Core::Maths::Fmaths::normal(bitangent1);

        // triangle 2
        // ----------
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;

        f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        //tangent2 = Core::Maths::Fmaths::normal(tangent2);


        bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        //bitangent2 = Core::Maths::Fmaths::normal(bitangent2);


        float quadVertices[] = {
            // positions            // normal         // texcoords  // tangent                          // bitangent
            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
        };
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}