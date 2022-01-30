#pragma once
#include "ProjectPopup.h"
#include <EditorAssetLoader.h>

namespace Glory::Editor
{
	class MainEditor
	{
	public:
		MainEditor();
		virtual ~MainEditor();

		void Initialize();
		void Destroy();
		void PaintEditor();

		EditorAssetLoader* GetAssetLoader();

	private:
		void CreateDefaultMainMenuBar();
		void SetDarkThemeColors();

		void Update();

		void RegisterWindows();
		void RegisterPropertyDrawers();
		void RegisterEditors();

	private:
		friend class EditorApplication;
		EditorAssetLoader* m_pAssetLoader;
		ProjectPopup* m_pProjectPopup;
	};
}
