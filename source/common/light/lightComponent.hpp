#pragma once

#include "../ecs/component.hpp"

#include <glm/mat4x4.hpp>

namespace our {
    // An enum that defines the type of the light source
    enum class LightType {
        DIRECTIONAL,
        SPOT,
        POINT
    };
    class LightComponent : public Component {
    public:
        LightType lightType; // The type of the light
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec4 color;
        glm::vec3 attenuation; // x*d^2 + y*d + z
        glm::vec2 cone_angles; // x: inner_angle, y: outer_angle
        
        // constructor
        void LightComponent(myType myDiffuse,mySpecular,myColor,myAttenuation,myAngles);
        // compute Angles if spot light
        void computeAngles();
        // compute attenuation if spot or point light
        void computeAttenuation();

        // should be calculated from the entity component
        // void calculatePosition ();
        // void calculateDirection();
    };

}