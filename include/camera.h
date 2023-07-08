#pragma once

#include <maths/vec3.h>
#include <maths/mat4.h>

#include <IMGUI/imgui.h>

using namespace Core::Maths::Mat4;
using namespace Core::Maths::Vec3;

struct CameraInputs
{
    float deltaX = 0.f;
    float deltaY = 0.f;
    bool moveForward = 0.f;
    bool moveBackward = 0.f;
    bool strafeLeft = 0.f;
    bool strafeRight = 0.f;
    bool moveUp = 0.f;
    bool moveDown = 0.f;

    double mousePosX = 0.f;
    double mousePosY = 0.f;
};

struct Camera
{

public:
    float3 pos = { 0.f, 0.f, 3.f };

    Camera() = default;
    Camera(int width, int height);
    void Update(float deltaTime, const CameraInputs& inputs);
    mat4x4 GetViewMatrix();
    mat4x4 GetProjection();

    void showImGuiControls();

    float yaw = 0.f;
    float pitch = 0.f;
    float posX_light = 0.f;
    float posY_light = 0.f;
    float posZ_light = 0.f;
    float fovY = Core::Maths::Mat4::maths::toRadians(60.f);
    float aspect = 1.f;
    float near = 0.01f;
    float far = 100.f;
};
