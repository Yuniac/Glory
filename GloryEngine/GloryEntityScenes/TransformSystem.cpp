#include "TransformSystem.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Glory
{
    TransformSystem::TransformSystem(Registry* pRegistry) : EntitySystemTemplate(pRegistry)
    {
    }

    TransformSystem::~TransformSystem()
    {
    }

    void Glory::TransformSystem::OnUpdate(Registry* pRegistry, EntityID entity, Transform& pComponent)
    {
        glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), pComponent.Scale);
        glm::mat4 rotation = glm::mat4_cast(pComponent.Rotation);
        //glm::mat4 rotation = glm::eulerAngleXYX(90.0f, 90.0f, 0.0f);
        glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), pComponent.Position);
        pComponent.MatTransform = translation * rotation * scale;
    }
}
