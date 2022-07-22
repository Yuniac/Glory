#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <map>

namespace Glory
{
	enum class ModuleType
	{
		MT_Window,
		MT_Graphics,
		MT_Renderer,
		MT_SceneManagement,
		MT_Loader,
		MT_Other,
	};

	class ModuleMetaData
	{
	public:
		ModuleMetaData();
		ModuleMetaData(const std::filesystem::path& path);
		virtual ~ModuleMetaData();

		void Read();

		const std::filesystem::path& Path() const;
		const std::string& Name() const;
		const ModuleType& Type() const;
		const std::string& EditorBackend() const;
		const std::vector<std::string>& EditorExtensions() const;

	private:
		std::filesystem::path m_Path;
		std::string m_Name;
		ModuleType m_Type;
		std::string m_EditorBackend;
		std::vector<std::string> m_EditorExtensions;

		static std::map<std::string, ModuleType> STRINGTOMODULETYPE;
	};
}