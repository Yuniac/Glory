#pragma once
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
		void Paint();

	private:
		void CreateDefaultMainMenuBar();
		void SetDarkThemeColors();

	private:
		EditorAssetLoader* m_pAssetLoader;
	};
}
