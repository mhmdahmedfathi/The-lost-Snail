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

       
        diffuse = glm::vec3(data.value("diffuse", glm::vec3(1, 1, 1)));
        specular = glm::vec3(data.value("specular", glm::vec3(1, 1, 1)));
        if (lightType != 0)
        {
        attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));
        }

        if (lightType ==2)
        {  
        cone_angles.x = glm::radians((float)data.value("cone_angles.in",10));
        cone_angles.y = glm::radians((float)data.value("cone_angles.out",80));
        }
    }
    
}