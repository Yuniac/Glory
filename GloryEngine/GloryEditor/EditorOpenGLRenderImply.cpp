#include "EditorOpenGLRenderImpl.h"
#include <Game.h>
#include <GL/glew.h>

namespace Glory::Editor
{
	EditorOpenGLRenderImpl::EditorOpenGLRenderImpl() {}

	EditorOpenGLRenderImpl::~EditorOpenGLRenderImpl() {}

	void EditorOpenGLRenderImpl::Setup()
	{
		m_pEditorPlatform->GetWindowImpl()->SetupForOpenGL();
	}

	void EditorOpenGLRenderImpl::SetupBackend()
	{
		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void EditorOpenGLRenderImpl::UploadImGUIFonts()
	{
		
	}

	void EditorOpenGLRenderImpl::Shutdown()
	{
		
	}

	void EditorOpenGLRenderImpl::Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void EditorOpenGLRenderImpl::BeforeRender()
	{
		
	}

	void EditorOpenGLRenderImpl::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void EditorOpenGLRenderImpl::Clear(const ImVec4& clearColor)
	{
		int display_w, display_h;
		m_pEditorPlatform->GetWindowImpl()->GetMainWindow()->GetDrawableSize(&display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void EditorOpenGLRenderImpl::FrameRender(ImDrawData* pDrawData)
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void EditorOpenGLRenderImpl::FramePresent()
	{
		m_pEditorPlatform->GetWindowImpl()->GetMainWindow()->GLSwapWindow();
	}
}
