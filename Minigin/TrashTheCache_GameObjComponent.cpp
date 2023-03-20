#include "TrashTheCache_GameObjComponent.h"
#include "imgui.h"

dae::TrashTheCache_GameObjComponent::TrashTheCache_GameObjComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::TrashTheCache_GameObjComponent::DisplayGui()
{
	ImGui::Begin("Exercise 2");
	ImGui::Text("Add Exercise 2 here");
	ImGui::End();
}
