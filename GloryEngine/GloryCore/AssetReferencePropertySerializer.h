#pragma once
#include "PropertySerializer.h"
#include "SerializedProperty.h"

namespace Glory
{
    class AssetReferencePropertySerializer : public PropertySerializer
    {
    public:
        AssetReferencePropertySerializer();
        virtual ~AssetReferencePropertySerializer();

    private:
        virtual void Serialize(const SerializedProperty* serializedProperty, YAML::Emitter& out) override;
        virtual void Deserialize(const SerializedProperty* serializedProperty, YAML::Node& object) override;
        virtual void Deserialize(std::any& out, YAML::Node& object) override;
    };
}
