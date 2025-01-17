#include "ProjectSettings.h"
#include "ListView.h"
#include "EditorUI.h"
#include <imgui.h>
#include <Input.h>
#include <Engine.h>

#include <IconsFontAwesome6.h>

namespace Glory::Editor
{
	const char* Key_InputMaps = "InputMaps";
	const char* Key_InputModes = "InputModes";

	const size_t BUFFER_SIZE = 256;
	char TextBuffer[BUFFER_SIZE] = "\0";

	const char* DeviceIcons[] = {
		ICON_FA_KEYBOARD,
		ICON_FA_COMPUTER_MOUSE,
		ICON_FA_GAMEPAD,
	};

	InputDeviceType CurrentDeviceType = InputDeviceType(-1);
	bool KeysNeedFilter = false;

	char FilterBuffer[200] = "\0";

	bool InputModesGui(YAML::Node& settings)
	{
		bool change = false;

		YAML::Node inputModes = settings[Key_InputModes];

		ListView listView = ListView("Input Modes");

		listView.OnDrawElement = [&](size_t index) {
			YAML::Node inmputMode = inputModes[index];
			YAML::Node nameNode = inmputMode["Name"];
			const std::string name = nameNode.as<std::string>();

			if (EditorUI::Header(name))
			{
				strcpy(TextBuffer, name.c_str());
				if (EditorUI::InputText("Name", TextBuffer, BUFFER_SIZE))
				{
					nameNode = std::string(TextBuffer);
					change = true;
				}

				YAML::Node deviceTypesNode = inmputMode["DeviceTypes"];
				ListView deviceTypesListView{ "Device Types" };

				deviceTypesListView.OnDrawElement = [&](size_t index) {
					YAML::Node deviceTypeNode = deviceTypesNode[index];
					std::string value = deviceTypeNode.as<std::string>();
					InputDeviceType deviceType = InputDeviceType(-1);
					GloryReflect::Enum<InputDeviceType>().FromString(value, deviceType);
					if (EditorUI::InputEnum<InputDeviceType>("", &deviceType))
					{
						GloryReflect::Enum<InputDeviceType>().ToString(deviceType, value);
						deviceTypeNode = value;
						change = true;
					}
				};

				deviceTypesListView.OnAdd = [&]() {
					deviceTypesNode.push_back("");
					change = true;
				};

				deviceTypesListView.OnRemove = [&](int index) {
					deviceTypesNode.remove(index);
					change = true;
				};

				deviceTypesListView.Draw(deviceTypesNode.size());
			}
		};

		listView.OnAdd = [&]() {
			YAML::Node newNode{ YAML::NodeType::Map };
			newNode["Name"] = "New Input Mode";
			newNode["DeviceTypes"] = YAML::Node(YAML::NodeType::Sequence);
			inputModes.push_back(newNode);
			change = true;
		};

		listView.OnRemove = [&](int index) {
			inputModes.remove(index);
			change = true;
		};

		listView.Draw(inputModes.size());

		return change;
	}

	struct InputBindingData
	{
		InputBindingData(InputDeviceType deviceType, std::string label, size_t keyIndex, bool isAxis)
			: DeviceType(deviceType), Label(label), KeyIndex(keyIndex), IsAxis(isAxis) {}

		InputDeviceType DeviceType;
		std::string Label;
		size_t KeyIndex;
		bool IsAxis;
	};
	std::vector<InputBindingData> FilteredBindings;

	void BackButton()
	{
		/* Back button */
		const float availableWidth = ImGui::GetContentRegionAvail().x;
		if (ImGui::Selectable(ICON_FA_ARROW_LEFT, false, ImGuiSelectableFlags_AllowItemOverlap | ImGuiSelectableFlags_DontClosePopups))
		{
			CurrentDeviceType = InputDeviceType(-1);
			KeysNeedFilter = true;
		}

		ImGui::Separator();
	}

	bool KeyPopup(std::string& value)
	{
		bool keyChosen = false;

		if (ImGui::BeginPopup("BindingPicker"))
		{
			ImGui::TextUnformatted(ICON_FA_MAGNIFYING_GLASS);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
			if (ImGui::InputText("##search", FilterBuffer, 200))
				KeysNeedFilter = true;

			const ImVec2 availablePopupRegion = ImGui::GetContentRegionAvail();

			const std::string_view search = FilterBuffer;

			if (KeysNeedFilter)
			{
				FilteredBindings.clear();
				if (CurrentDeviceType == InputDeviceType(-1) || CurrentDeviceType == InputDeviceType::Keyboard)
				{
					auto keyEnum = GloryReflect::Enum<KeyboardKey>();
					for (size_t i = 0; i < keyEnum.NumValues(); i++)
					{
						std::string keyString;
						keyEnum.ToString(KeyboardKey(i), keyString);
						if (keyString.find(search) == std::string::npos) continue;
						FilteredBindings.push_back({ InputDeviceType::Keyboard, keyString, i, false });
					}
				}

				if (CurrentDeviceType == InputDeviceType(-1) || CurrentDeviceType == InputDeviceType::Mouse)
				{
					auto keyEnum = GloryReflect::Enum<MouseButton>();
					for (size_t i = 0; i < keyEnum.NumValues(); i++)
					{
						std::string buttonString;
						keyEnum.ToString(MouseButton(i), buttonString);
						if (buttonString.find(search) == std::string::npos) continue;
						FilteredBindings.push_back({ InputDeviceType::Mouse, buttonString, i, false });
					}

					auto axisEnum = GloryReflect::Enum<MouseAxis>();
					for (size_t i = 0; i < axisEnum.NumValues(); i++)
					{
						std::string axisString;
						axisEnum.ToString(MouseAxis(i), axisString);
						if (axisString.find(search) == std::string::npos) continue;
						FilteredBindings.push_back({ InputDeviceType::Mouse, axisString, i, true });
					}
				}

				if (CurrentDeviceType == InputDeviceType(-1) || CurrentDeviceType == InputDeviceType::Gamepad)
				{

				}

				KeysNeedFilter = false;
			}

			if (CurrentDeviceType != InputDeviceType(-1))
			{
				BackButton();
			}

			if (CurrentDeviceType == InputDeviceType(-1) && search.empty())
			{
				auto deviceTypeEnum = GloryReflect::Enum<InputDeviceType>();
				for (size_t i = 0; i < deviceTypeEnum.NumValues(); i++)
				{
					InputDeviceType deviceType = InputDeviceType(i);
					std::string deviceTypeString;
					deviceTypeEnum.ToString(deviceType, deviceTypeString);
					const float availableWidth = ImGui::GetContentRegionAvail().x;
					const ImVec2 cursorPos = ImGui::GetCursorPos();
					if (ImGui::Selectable(DeviceIcons[i], false, ImGuiSelectableFlags_AllowItemOverlap | ImGuiSelectableFlags_DontClosePopups))
					{
						CurrentDeviceType = deviceType;
						KeysNeedFilter = true;
					}

					ImGui::SameLine();
					ImGui::SetCursorPosX(cursorPos.x + 30.0f);
					ImGui::TextUnformatted(deviceTypeString.c_str());

					ImGui::SameLine();
					ImGui::SetCursorPos({ cursorPos.x + availableWidth - ImGui::CalcTextSize(ICON_FA_ARROW_RIGHT).x, cursorPos.y });
					ImGui::TextUnformatted(ICON_FA_ARROW_RIGHT);
				}
			}
			else
			{
				if (ImGui::BeginChild("Filtered Bindings"))
				{
					InputDeviceType previousDeviceType;
					for (size_t i = 0; i < FilteredBindings.size(); i++)
					{
						const InputBindingData& bindingData = FilteredBindings[i];
						const float availableWidth = ImGui::GetContentRegionAvail().x;
						const ImVec2 cursorPos = ImGui::GetCursorPos();

						ImGui::PushID(i);
						/* Icon */
						std::string bindingString;
						GloryReflect::Enum<InputDeviceType>().ToString(bindingData.DeviceType, bindingString);
						std::filesystem::path bindingPath{ bindingString };
						bindingPath = bindingPath.append(bindingData.IsAxis ? "Axis" : "Key").append(bindingData.Label);
						if (ImGui::Selectable(bindingData.IsAxis ? ICON_FA_ARROW_RIGHT_ARROW_LEFT : ICON_FA_CIRCLE_DOWN, bindingPath.string() == value, ImGuiSelectableFlags_AllowItemOverlap))
						{
							value = bindingPath.string();
							keyChosen = true;
						}

						/* Key name */
						ImGui::SameLine();
						ImGui::SetCursorPosX(cursorPos.x + 30.0f);
						ImGui::TextUnformatted(bindingData.Label.c_str());
						ImGui::PopID();
					}
				}
				ImGui::EndChild();
			}

			if (keyChosen)
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		return keyChosen;
	}

	bool KeyDrowdown(std::string_view label, std::string& value)
	{
		ImGui::PushID(label.data());

		bool openPopup = false;
		float start, width;
		EditorUI::EmptyDropdown(EditorUI::MakeCleanName(label), value, [&]
		{
			KeysNeedFilter = true;
			CurrentDeviceType = InputDeviceType(-1);
			openPopup = true;
		}, start, width);

		const float scrollHeight = ImGui::GetScrollY();

		if (openPopup)
			ImGui::OpenPopup("BindingPicker");
		openPopup = false;

		const ImVec2 cursor = ImGui::GetCursorPos();
		const ImVec2 windowPos = ImGui::GetWindowPos();
		Window* pWindow = Game::GetGame().GetEngine()->GetWindowModule()->GetMainWindow();
		int mainWindowWidth, mainWindowHeight;
		pWindow->GetDrawableSize(&mainWindowWidth, &mainWindowHeight);
		ImGui::SetNextWindowPos({ windowPos.x + start, windowPos.y + cursor.y - 2.5f - scrollHeight });
		ImGui::SetNextWindowSize({ width, mainWindowHeight - windowPos.y - cursor.y - 10.0f + scrollHeight });
		bool change = KeyPopup(value);
		ImGui::PopID();
		return change;
	}

	bool InputMapsGui(YAML::Node& settings)
	{
		bool change = false;

		std::vector<std::string> inputModeNamesTemp;
		std::vector<std::string_view> inputModeNames;
		YAML::Node inputModes = settings[Key_InputModes];
		for (size_t i = 0; i < inputModes.size(); i++)
		{
			const std::string name = inputModes[i]["Name"].as<std::string>();
			inputModeNamesTemp.push_back(name.c_str());
			inputModeNames.push_back(inputModeNamesTemp[i].c_str());
		}

		YAML::Node inputMaps = settings[Key_InputMaps];

		ListView listView = ListView("Input Maps");

		listView.OnDrawElement = [&](size_t index) {
			YAML::Node inmputMode = inputMaps[index];
			YAML::Node nameNode = inmputMode["Name"];
			const std::string name = nameNode.as<std::string>();

			if (EditorUI::Header(name))
			{
				strcpy(TextBuffer, name.c_str());
				if (EditorUI::InputText("Name", TextBuffer, BUFFER_SIZE))
				{
					nameNode = std::string(TextBuffer);
					change = true;
				}

				YAML::Node actionsNode = inmputMode["Actions"];
				ListView actionsListView{ "Actions" };

				actionsListView.OnDrawElement = [&](size_t index) {
					YAML::Node actionNode = actionsNode[index];

					YAML::Node actionNameNode = actionNode["Name"];
					const std::string actionName = actionNameNode.as<std::string>();

					if (EditorUI::Header(actionName))
					{
						strcpy(TextBuffer, actionName.c_str());
						if (EditorUI::InputText("Name", TextBuffer, BUFFER_SIZE))
						{
							actionNameNode = std::string(TextBuffer);
							change = true;
						}

						YAML::Node actionMappingNode = actionNode["ActionMapping"];
						std::string actionMappingString = actionMappingNode.as<std::string>();
						YAML::Node axisBlendingNode = actionNode["AxisBlending"];
						std::string axisBlendingString = axisBlendingNode.as<std::string>();
						YAML::Node axisBlendingSpeedNode = actionNode["AxisBlendingSpeed"];

						InputMappingType actionMapping = InputMappingType::Bool;
						GloryReflect::Enum<InputMappingType>().FromString(actionMappingString, actionMapping);
						if (EditorUI::InputEnum<InputMappingType>("Mapping Type", &actionMapping))
						{
							GloryReflect::Enum<InputMappingType>().ToString(actionMapping, actionMappingString);
							actionMappingNode = actionMappingString;
							change = true;
						}

						if (actionMapping == InputMappingType::Float)
						{
							AxisBlending axisBlending = AxisBlending::Jump;
							GloryReflect::Enum<AxisBlending>().FromString(axisBlendingString, axisBlending);
							if (EditorUI::InputEnum<AxisBlending>("Axis Blending", &axisBlending))
							{
								GloryReflect::Enum<AxisBlending>().ToString(axisBlending, axisBlendingString);
								axisBlendingNode = axisBlendingString;
								change = true;
							}

							float blendingSpeed = axisBlendingSpeedNode.as<float>();
							if (EditorUI::InputFloat("Axis Blending Speed", &blendingSpeed, 0.0f))
							{
								axisBlendingSpeedNode = blendingSpeed;
								change = true;
							}
						}

						YAML::Node bindingsNode = actionNode["Bindings"];

						ListView bindingsListView{ "Bindings" };

						bindingsListView.OnDrawElement = [&](size_t index) {
							YAML::Node bindingNode = bindingsNode[index];
							YAML::Node BindingNameNode = bindingNode["Name"];
							const std::string bindingName = BindingNameNode.as<std::string>();

							if (EditorUI::Header(bindingName))
							{
								YAML::Node stateNode = bindingNode["State"];
								YAML::Node multiplierNode = bindingNode["Multiplier"];
								YAML::Node inputModeNode = bindingNode["InputMode"];
								YAML::Node bindingKeyNode = bindingNode["Binding"];
								YAML::Node mapDeltaToValueNode = bindingNode["MapDeltaToValue"];
								std::string stateString = stateNode.as<std::string>();
								std::string bindingString = bindingKeyNode.as<std::string>();

								KeyBinding binding{ bindingString };

								strcpy(TextBuffer, bindingName.c_str());
								if (EditorUI::InputText("Name", TextBuffer, BUFFER_SIZE))
								{
									BindingNameNode = std::string(TextBuffer);
									change = true;
								}

								if (actionMapping == InputMappingType::Bool && binding.m_DeviceType != InputDeviceType(-1) && !binding.m_IsAxis)
								{
									InputState state = InputState::KeyDown;
									GloryReflect::Enum<InputState>().FromString(stateString, state);
									if (EditorUI::InputEnum<InputState>("Key State", &state, { size_t(InputState::Axis) }))
									{
										GloryReflect::Enum<InputState>().ToString(state, stateString);
										stateNode = stateString;
										change = true;
									}
								}

								if (actionMapping == InputMappingType::Float)
								{
									bool mapToDelta = mapDeltaToValueNode.as<bool>();

									if (EditorUI::CheckBox("Map Delta to Value", &mapToDelta))
									{
										mapDeltaToValueNode = mapToDelta;
										change = true;
									}

									float multiplier = multiplierNode.as<float>();
									if (EditorUI::InputFloat("Multiplier", &multiplier))
									{
										multiplierNode = multiplier;
										change = true;
									}
								}

								std::string inputMode = inputModeNode.as<std::string>();
								size_t inputModeIndex = 0;
								for (size_t i = 0; i < inputModeNames.size(); i++)
								{
									if (inputMode == inputModeNames[i])
									{
										inputModeIndex = i;
										break;
									}
								}
								if (inputMode.empty() && inputModeNames.size() > 0)
								{
									inputMode = inputModeNames[inputModeIndex];
									inputModeNode = inputMode;
								}

								if (EditorUI::InputDropdown("Input Mode", inputModeNames, &inputModeIndex, inputMode))
								{
									inputMode = inputModeNames[inputModeIndex];
									inputModeNode = inputMode;
									change = true;
								}

								if (KeyDrowdown("Binding", bindingString))
								{
									bindingKeyNode = bindingString;
									change = true;
								}
							}
						};

						bindingsListView.OnAdd = [&]() {
							YAML::Node newNode{ YAML::NodeType::Map };
							newNode["Name"] = "New Binding";
							newNode["State"] = "KeyDown";
							newNode["MapDeltaToValue"] = false;
							newNode["Multiplier"] = 1.0f;
							newNode["InputMode"] = "";
							newNode["Binding"] = "";
							bindingsNode.push_back(newNode);
							change = true;
						};

						bindingsListView.OnRemove = [&](int index) {
							bindingsNode.remove(index);
							change = true;
						};

						bindingsListView.Draw(bindingsNode.size());
					}
				};

				actionsListView.OnAdd = [&]() {
					YAML::Node newNode{ YAML::NodeType::Map };
					newNode["Name"] = "New Action";
					newNode["ActionMapping"] = "Bool";
					newNode["AxisBlending"] = "Jump";
					newNode["AxisBlendingSpeed"] = 5.0f;
					newNode["Bindings"] = YAML::Node(YAML::NodeType::Sequence);
					actionsNode.push_back(newNode);
					change = true;
				};

				actionsListView.OnRemove = [&](int index) {
					inputMaps.remove(index);
					change = true;
				};

				actionsListView.Draw(actionsNode.size());
			}
		};

		listView.OnAdd = [&]() {
			YAML::Node newNode{ YAML::NodeType::Map };
			newNode["Name"] = "New Input Map";
			newNode["Actions"] = YAML::Node(YAML::NodeType::Sequence);
			inputMaps.push_back(newNode);
			change = true;
		};

		listView.OnRemove = [&](int index) {
			inputMaps.remove(index);
			change = true;
		};

		listView.Draw(inputMaps.size());

		return change;
	}

	bool InputSettings::OnGui()
	{
		bool change = false;
		ImGui::BeginChild("Input Settings");
		change |= InputModesGui(m_SettingsNode);
		change |= InputMapsGui(m_SettingsNode);
		ImGui::EndChild();
		return change;
	}

	void InputSettings::OnSettingsLoaded()
	{
		if (!m_SettingsNode.IsDefined() || !m_SettingsNode.IsMap())
		{
			m_SettingsNode = YAML::Node(YAML::NodeType::Map);
		}

		SETTINGS_DEFAULT_KEY(inputModes, Key_InputModes, Sequence);
		SETTINGS_DEFAULT_KEY(kayMaps, Key_InputMaps, Sequence);
	}

	void InputSettings::OnStartPlay_Impl()
	{
		Game::GetGame().GetEngine()->GetInputModule()->ReadInputData(m_SettingsNode);
		Game::GetGame().GetEngine()->GetInputModule()->InputBlocked() = false;
	}

	void InputSettings::OnStopPlay_Impl()
	{
		Game::GetGame().GetEngine()->GetInputModule()->InputBlocked() = true;
		Game::GetGame().GetEngine()->GetInputModule()->ClearInputData();
	}
}