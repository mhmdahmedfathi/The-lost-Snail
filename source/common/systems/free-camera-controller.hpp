#pragma once
#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/Snail.hpp"
#include "../components/free-camera-controller.hpp"
#include "iostream"
#include "../application.hpp"

#include "../components/Collision.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class FreeCameraControllerSystem
    {
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world, float deltaTime)
        {
            // First of all, we search for an entity containing both a CameraComponent and a FreeCameraControllerComponent
            // As soon as we find one, we break
            CameraComponent *camera = nullptr;
            SnailComponent *Snail = nullptr;
            FreeCameraControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<FreeCameraControllerComponent>();
                if (camera && controller)
                    break;
            }
            for (auto entity : world->getEntities())
            {
                Snail = entity->getComponent<SnailComponent>();
                if (Snail)
                    break;
            }

            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!(Snail))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *entity = Snail->getOwner();
            // If the left mouse button is pressed, we lock and hide the mouse. This common in First Person Games.
            if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked)
            {
                app->getMouse().lockMouse(app->getWindow());
                mouse_locked = true;
                // If the left mouse button is released, we unlock and unhide the mouse.
            }
            else if (!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked)
            {
                app->getMouse().unlockMouse(app->getWindow());
                mouse_locked = false;
            }

            // We get a reference to the entity's position and rotation
            glm::vec3 &position = entity->localTransform.position;
            glm::vec3 &rotation = entity->localTransform.rotation;

            Entity *Collision_entity = nullptr;
            CollisionComponent *Collision = nullptr;

            for (auto entity : world->getEntities())
            {
                Collision = entity->getComponent<CollisionComponent>();
                if (!(Collision))
                    continue;
                Collision_entity = Collision->getOwner();

                glm::vec3 &objPosition = Collision_entity->localTransform.position;

                bool collisionX = false;

                if (Collision->getobstucaseType() == "danger")
                {
                    collisionX = position.x + 1.5 >= objPosition.x &&
                                 objPosition.x + 1.5 >= position.x;
                }
                else
                {
                    collisionX = position.x + 1 >= objPosition.x &&
                                 objPosition.x + 1 >= position.x;
                }
                // collision z-axis?
                bool collisionY = position.z + 1.0 >= objPosition.z &&
                                  objPosition.z + 1.0 >= position.z;
                // collision only if on both axes
                if (collisionX && collisionY)
                {
                    std::cout << " X " << position.x << " => " << objPosition.x << std::endl;
                    std::cout << " Z " << position.z << " => " << objPosition.z << std::endl;
                    std::cout << " type " << Collision->getobstucaseType() << std::endl;
                    objPosition.y = 100;
                    if (Collision->getobstucaseType() != "danger")
                        app->score += 0.1;
                    break;
                }
            }

            // If the left mouse button is pressed, we get the change in the mouse location
            // and use it to update the camera rotation
            if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1))
            {
                glm::vec2 delta = app->getMouse().getMouseDelta();
                rotation.x -= delta.y * controller->rotationSensitivity; // The y-axis controls the pitch
                rotation.y -= delta.x * controller->rotationSensitivity; // The x-axis controls the yaw
            }

            // We prevent the pitch from exceeding a certain angle from the XZ plane to prevent gimbal locks
            if (rotation.x < -glm::half_pi<float>() * 0.99f)
                rotation.x = -glm::half_pi<float>() * 0.99f;
            if (rotation.x > glm::half_pi<float>() * 0.99f)
                rotation.x = glm::half_pi<float>() * 0.99f;
            // This is not necessary, but whenever the rotation goes outside the 0 to 2*PI range, we wrap it back inside.
            // This could prevent floating point error if the player rotates in single direction for an extremely long time.
            rotation.y = glm::wrapAngle(rotation.y);

            // We update the camera fov based on the mouse wheel scrolling amount
            float fov = camera->fovY + app->getMouse().getScrollOffset().y * controller->fovSensitivity;
            fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f); // We keep the fov in the range 0.01*PI to 0.99*PI
            camera->fovY = fov;

            // We get the camera model matrix (relative to its parent) to compute the front, up and right directions
            glm::mat4 matrix = entity->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;
            // If the LEFT SHIFT key is pressed, we multiply the position sensitivity by the speed up factor
            // if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= controller->speedupFactor;
            // current_sensitivity *= controller->speedupFactor;
            // make it move forward all the time
            position += front * (deltaTime * current_sensitivity.z);
            // We change the camera position based on the keys WASD/QE
            if (position.x < 2.35222)
            {

                // A & D moves the player left or right
                if (app->getKeyboard().isPressed(GLFW_KEY_D))
                    position -= right * (deltaTime * current_sensitivity.x);
                if (app->getKeyboard().isPressed(GLFW_KEY_RIGHT))
                    position -= right * (deltaTime * current_sensitivity.x);
            }
            if (position.x > -2.35222)
            {
                if (app->getKeyboard().isPressed(GLFW_KEY_A))
                    position += right * (deltaTime * current_sensitivity.x);
                if (app->getKeyboard().isPressed(GLFW_KEY_LEFT))
                    position += right * (deltaTime * current_sensitivity.x);
            }
        }

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit()
        {
            if (mouse_locked)
            {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }
    };

}
