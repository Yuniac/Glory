#pragma once
#include <BaseEditorExtension.h>
#include <Glory.h>
#include <vector>
#include <imgui_internal.h>
#include <GloryContext.h>

extern "C" GLORY_API Glory::Editor::BaseEditorExtension* LoadExtension();
extern "C" GLORY_API void SetContext(Glory::GloryContext * pContext, ImGuiContext* pImGUIContext);

namespace Glory::Editor
{
    class EntityScenesEditorExtension : public BaseEditorExtension
    {
    public:
        EntityScenesEditorExtension();
        virtual ~EntityScenesEditorExtension();

    private:
        virtual void RegisterEditors() override;
    };
}
