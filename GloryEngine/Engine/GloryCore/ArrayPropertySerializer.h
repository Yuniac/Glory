#pragma once
#include "PropertySerializer.h"

namespace Glory
{
    class ArrayPropertySerializer : public PropertySerializer
    {
    public:
        ArrayPropertySerializer();
        virtual ~ArrayPropertySerializer();

    private:
        virtual void Serialize(const SerializedProperty* serializedProperty, YAML::Emitter& out) override;
        virtual void Deserialize(const SerializedProperty* serializedProperty, YAML::Node& object) override;
        virtual void Serialize(const GloryReflect::FieldData* pFieldData, void* data, YAML::Emitter& out) override;
        virtual void Deserialize(std::any& out, YAML::Node& object) override;
        virtual void Deserialize(const GloryReflect::FieldData* pFieldData, void* data, YAML::Node& object) override;
    };
}
