#pragma once
#include "EntitySystem.h"
#include "Registry.h"

namespace Glory
{
	template<typename T>
	class EntitySystemTemplate : public EntitySystem
	{
	public:
		EntitySystemTemplate(Registry* pRegistry) : EntitySystem(pRegistry, typeid(T)) {}
		virtual ~EntitySystemTemplate() {}

	protected:
		virtual void OnComponentAdded(Registry* pRegistry, EntityID entity, T& pComponent) {}
		virtual void OnComponentRemoved(Registry* pRegistry, EntityID entity, T& pComponent) {}

		virtual void OnUpdate(Registry* pRegistry, EntityID entity, T& pComponent) {}
		virtual void OnDraw(Registry* pRegistry, EntityID entity, T& pComponent) {}

	private:
		virtual void ComponentAdded(Registry* pRegistry, EntityID entity, EntityComponentData* pComponentData)
		{
			OnComponentAdded(pRegistry, entity, pComponentData->GetData<T>());
		}

		virtual void ComponentRemoved(Registry* pRegistry, EntityID entity, EntityComponentData* pComponentData)
		{
			OnComponentRemoved(pRegistry, entity, pComponentData->GetData<T>());
		}

		virtual void Update(Registry* pRegistry, EntityID entity, EntityComponentData* pComponentData) override
		{
			OnUpdate(pRegistry, entity, pComponentData->GetData<T>());
		}

		virtual void Draw(Registry* pRegistry, EntityID entity, EntityComponentData* pComponentData) override
		{
			OnDraw(pRegistry, entity, pComponentData->GetData<T>());
		}
	};
}