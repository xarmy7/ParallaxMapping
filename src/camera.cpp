#include "camera.h"

using namespace Core;

Camera::Camera(int width, int height)
{
    aspect = (float)width / (float)height;
    // width and height are useful to compute projection matrix with the right aspect ratio
}

void Camera::Update(float deltaTime, const CameraInputs& input)
{
    const float MOUSE_SENSITIVITY = 0.002f;
    const float SPEED = 1.f;

    yaw += input.deltaX * MOUSE_SENSITIVITY;
    pitch += input.deltaY * MOUSE_SENSITIVITY;

    float forwardMovement = 0.f;
    if (input.moveForward)
        forwardMovement += SPEED * deltaTime;
    if (input.moveBackward)
        forwardMovement -= SPEED * deltaTime;

    float strafeMovement = 0.f;
    if (input.strafeLeft)
        strafeMovement -= SPEED * deltaTime;
    if (input.strafeRight)
        strafeMovement += SPEED * deltaTime;

    float verticalMovement = 0.f;
    if (input.moveUp)
        verticalMovement += SPEED * deltaTime;
    if (input.moveDown)
        verticalMovement -= SPEED * deltaTime;

    pos.x += maths::sin(yaw) * forwardMovement;
    pos.z -= maths::cos(yaw) * forwardMovement;

    pos.x += maths::cos(yaw) * strafeMovement;
    pos.z += maths::sin(yaw) * strafeMovement;

    pos.y += verticalMovement;
}

Core::Maths::Mat4::mat4x4 Camera::GetViewMatrix()
{
    return mat4::rotateX(pitch) * mat4::rotateY(yaw) * mat4::translate(-pos);
}

Core::Maths::Mat4::mat4x4 Camera::GetProjection()
{
    return mat4::perspective(fovY, aspect, near, far);
}

void Camera::showImGuiControls()
{
    ImGui::SliderFloat3("pos", pos.e, -10, 10);
    ImGui::SliderFloat("yaw", &yaw, 0, 7);
    ImGui::SliderFloat("pitch", &pitch, 0, 7);
}