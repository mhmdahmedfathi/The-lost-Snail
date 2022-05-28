#include "camera.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace our
{
    // Reads camera parameters from the given json object
    void LightComponent::LightComponent(LightType myType ,glm::vec3 myDiffuse,glm::vec3 mySpecular,glm::vec4 myColor)
    {
        lightType =myType; // The type of the light
        diffuse= myDiffuse;
        specular=mySpecular;
        color=myColor;
    }

    void setAngles( glm:: vec2 myAngles)
    {
         if(lightType == LightType::SPOT){
                cone_angles=myAngles;
            }
    }

    void computeAttenuation()
    {
        if(light.type != LightType::DIRECTIONAL)
        {
            //??????
            float d = glm::distance(light.position, fs_in.world);
         // attenuation gya mneen??
            attenuation /= glm::dot( attenuation, vec3(d*d, d, 1));
             if(lightType == LightType::SPOT)
         {
             //-direction_to_light, light.direction???
                float angle = glm::acos( glm::dot(-direction_to_light, light.direction));
                attenuation *= smoothstep(cone_angles.y, cone_angles.x, angle);
         }
        }

    }

     

}