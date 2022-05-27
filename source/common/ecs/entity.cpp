#include "entity.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

namespace our {

    // This function returns the transformation matrix from the entity's local space to the world space
    // Remember that you can get the transformation matrix from this entity to its parent from "localTransform"
    // To get the local to world matrix, you need to combine this entities matrix with its parent's matrix and
    // its parent's parent's matrix and so on till you reach the root.
    glm::mat4 Entity::getLocalToWorldMatrix() const {
        //TODO: (Req 7) Write this function
       glm::mat4 localToWorld=this->localTransform.toMat4();
       Entity * ptr= this->parent;
    //    std::cout<<ptr<<std::endl; 
        while(ptr!=nullptr){
            localToWorld=  ptr->localTransform.toMat4()*localToWorld ;
            ptr=ptr->parent;
            // std::cout<<ptr<<std::endl;
        }
        return localToWorld;
    }

    // Deserializes the entity data and components from a json object
    void Entity::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        name = data.value("name", name);
        localTransform.deserialize(data);
        if(data.contains("components")){
            if(const auto& components = data["components"]; components.is_array()){
                for(auto& component: components){
                    deserializeComponent(component, this);
                }
            }
        }
    }

}