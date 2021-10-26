#include "EditorApplication.h"
#include <imgui.h>
//#include "EditorWindow.h"

namespace Glory::Editor
{
	EditorApplication* EditorApplication::m_pEditorInstance = nullptr;

	EditorApplication::EditorApplication() : m_pMainEditor(nullptr), m_pPlatform(nullptr)
	{
	}

	EditorApplication::~EditorApplication()
	{
		delete m_pMainEditor;
		m_pMainEditor = nullptr;

		delete m_pPlatform;
		m_pPlatform = nullptr;
	}

	void EditorApplication::Destroy()
	{
		m_pMainEditor->Destroy();
		m_pPlatform->Destroy();
	}

	void EditorApplication::Run()
	{
		while (true)
		{
			if (m_pPlatform->PollEvents()) break;
			m_pPlatform->BeginRender();
			m_pPlatform->WaitIdle();
			RenderEditor();
			m_pPlatform->EndRender();
			m_pPlatform->WaitIdle();
		}
	}

	EditorPlatform* EditorApplication::GetEditorPlatform()
	{
		return m_pPlatform;
	}

	EditorApplication* EditorApplication::GetInstance()
	{
		return m_pEditorInstance;
	}

	void EditorApplication::RenderEditor()
	{
		//ImGui::Begin("Test");
		//
		//ImGui::End();

		m_pMainEditor->Paint();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
		ImGui::ShowDemoWindow();
	}
}
