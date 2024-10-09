#pragma once

enum CamaraMovement {
    FORWARD, BACKWARD, LEFT, RIGHT
};

const float YAW         = -90.0;
const float PITCH       = 0;
const float SPEED       = 2.5;
const float SENSITIVITY = 0.1;
const float ZOOM        = 45.0;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(
        glm::vec3 position = glm::vec3(0), glm::vec3 up = glm::vec3(0, 1.0, 0),
        float yaw = YAW, float pitch = PITCH
    ) :
        Front(glm::vec3(0, 0, -1.0)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        this->Position = position;
        this->WorldUp = up;
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }

    Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch
    ) :
        Front(glm::vec3(0, 0, -1.0)), MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        this->Position = glm::vec3(posX, posY, posZ);
        this->WorldUp = glm::vec3(upX, upY, upZ);
        this->Yaw = yaw;
        this->Pitch = pitch;
        this->updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(
            this->Position,
            this->Position + this->Front,
            this->Up
        );
    }

    void ProcessKeyboard(CamaraMovement direction, float deltaTime)
    {
        float velocity = this->MovementSpeed * deltaTime;

        if (direction == FORWARD)
            this->Position += velocity * this->Front;

        if (direction == BACKWARD)
            this->Position -= velocity * this->Front;

        if (direction == LEFT)
            this->Position -= this->Right * velocity;

        if (direction == RIGHT)
            this->Position += this->Right * velocity;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constainPitch = true)
    {
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        this->Yaw += xoffset;
        this->Pitch += yoffset;

        if (constainPitch) {
            if (this->Pitch > 89.0f) this->Pitch = 89.0f;
            if (this->Pitch < -89.0f) this->Pitch = -89.0f;
        }

        this->updateCameraVectors();
    }

    void ProcessMouseScroll(double yoffset)
    {
        this->Zoom -= (float)yoffset;
        if (this->Zoom < 1.0) this->Zoom = 1.0;
        if (this->Zoom > 45.0) this->Zoom = 45.0;
    }

private:
    void updateCameraVectors()
    {
        glm::vec3 front;

        front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
        front.y = sin(glm::radians(this->Pitch));
        front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

        this->Front = glm::normalize(front);
        this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
        this->Up = glm::normalize(glm::cross(this->Right, this->Front));
    }
};
