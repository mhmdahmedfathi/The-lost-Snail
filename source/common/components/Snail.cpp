#include "Snail.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void SnailComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
    }
}