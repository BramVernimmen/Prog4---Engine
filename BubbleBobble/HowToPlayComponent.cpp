#include "HowToPlayComponent.h"
#include "imgui.h"

dae::HowToPlayComponent::HowToPlayComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::HowToPlayComponent::DisplayGui()
{
	if (m_IsOpen)
	{
		ImGui::Begin("How To Play?", &m_IsOpen);

		ImGui::Text("Player1:");
		ImGui::Spacing();
		ImGui::Text("Keyboard movement:");
		ImGui::Text("Move left and right with 'a' and 'd'");
		ImGui::Text("Jump with 'w'");
		ImGui::Spacing();
		ImGui::Text("Controller movement:");
		ImGui::Text("Move left and right with 'dpad-left' and 'dpad-right'");
		ImGui::Text("Jump with 'dpad-up'");
		ImGui::Dummy(ImVec2(0.0f, 25.0f));
		ImGui::Text("Player2:");
		ImGui::Spacing();
		ImGui::Text("Keyboard movement:");
		ImGui::Text("Move left and right with 'arrow-left' and 'arrow-right'");
		ImGui::Text("Jump with 'arrow-up'");
		ImGui::Spacing();
		ImGui::Text("Controller movement:");
		ImGui::Text("Move left and right with 'dpad-left' and 'dpad-right'");
		ImGui::Text("Jump with 'dpad-up'");
		ImGui::Dummy(ImVec2(0.0f, 25.0f));
		ImGui::Text("Go to previous scene using F3");
		ImGui::Text("Go to next scene using F4");


		ImGui::End();
	}
	

}

