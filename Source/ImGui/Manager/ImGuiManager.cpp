#include "ImGuiManager.h"

#include "../Library/imgui.h"

ImGuiManager::ImGuiManager() 
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
}

ImGuiManager::~ImGuiManager() 
{
	ImGui::DestroyContext();
}
