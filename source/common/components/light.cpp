#include "light.hpp"
#include "../deserialize-utils.hpp"
#include "./component-deserializer.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

namespace our
{
    // Deserializes the light data from a json object
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        lightTypeStr = data.value("typeOfLight", "DIRECTIONAL");

        if (lightTypeStr == "DIRECTIONAL")
            lightType = 0;

        else if (lightTypeStr == "POINT")
            lightType = 1;

        else if (lightTypeStr == "SPOT")
            lightType =2;

       
        diffuse = glm::vec3(data.value("diffuse", glm::vec3(1, 0.9, 0.7)));
        specular = glm::vec3(data.value("specular", glm::vec3(1, 0.9, 0.7)));
        attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));
        // cone_angles = glm::vec2(data.value("cone_angles", glm::vec2(glm::radians(90.0f), glm::radians(120.0f))));
        cone_angles.x = glm::radians((float)data.value("cone_angles.inner",90));
        cone_angles.y = glm::radians((float)data.value("cone_angles.outer",120));
        // I didn't assign default values (second parameter of data.value)
        // diffuse = data.value("diffuse",diffuse);
        // specular = data.value("specular",specular);
        // color = data.value("color", color);
        // // initPosition = data.value("position", initPosition);
        // // initDirection = data.value("direction", initDirection);

        // if (lightType != 0)
        // {
        //     attenuation = data.value("attenuation",attenuation);
        // }

        // if (lightType ==2)
        // {
        //   //  glm::vec2 angles =
        //   cone_angles =  data.value("cone_angles",cone_angles);
        //   //glm::radians(angles[0]), glm::radians(angles[1]);
        // }
    }
    void LightComponent::calculatePosition(glm::mat4 localToWorld)
    {
        position = glm::vec3(localToWorld * glm::vec4(initPosition, 1));
    }
    void LightComponent::calculateDirection(glm::mat4 localToWorld)
    {
        direction = glm::vec3(localToWorld * glm::vec4(initDirection, 0));
    }
}