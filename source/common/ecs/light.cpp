#include "light.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <iostream>


namespace our
{ 
    // Deserializes the light data from a json object
    void LightComponent::deserialize (const nlohmann::json& data)
    {
        if(!data.is_object()) return;
        
        lightTypeStr = data.value("type", "DIRECTIONAL");

        if ( lightTypeStr = "DIRECTIONAL")
            lightType =LightType::DIRECTIONAL;

        else if ( lightTypeStr = "SPOT")
            lightType =LightType::SPOT;

        else if ( lightTypeStr = "POINT")
            lightType =LightType::POINT;
       
        // I didn't assign default values (second parameter of data.value)
        diffuse = data.value("diffuse");
        specular = data.value("specular");
        color = data.value("color", color);
        
        if ( lightType != LightType::DIRECTIONAL)
        {
         attenuation= data.value("attenuation");
        }

        if ( lightType == LightType::SPOT)
        {
         glm::vec2 angles = data.value("cone_angles");
         cone_angles=glm::radians(angles[0]f), glm::radians(angles[1]f)
        }
    }
}