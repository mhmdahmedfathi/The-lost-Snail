#include "Collision.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        effect = data.value("effect", effect);
        obstucaseType = data.value("obstucaseType", obstucaseType);
    }
}