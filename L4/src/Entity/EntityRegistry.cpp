#include "EntityRegistry.h"

Entity EntityRegistry::createEntity()
{
    entt::entity entity = m_registry.create();
    return Entity(&m_registry, entity);
}

void EntityRegistry::destroyEntity(Entity& entity)
{
    m_registry.destroy(entity.getNativeEntity());
}

entt::registry& EntityRegistry::getRegistry()
{
    return m_registry;
}
