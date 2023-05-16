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
		ImGui::Text("Gain Score: Press 'u'");
		ImGui::Text("Do Damage: Press 'j'");
		ImGui::Dummy(ImVec2(0.0f, 25.0f));
		ImGui::Text("Move left and right with 'a' and 'd'");
		ImGui::Text("Jump with 'w'");
		ImGui::Dummy(ImVec2(0.0f, 25.0f));
		//ImGui::Text("Player2:");
		//ImGui::Spacing();
		//ImGui::Text("Gain Score: Press 'i'");
		//ImGui::Text("Do Damage: Press 'k'");
		//ImGui::Dummy(ImVec2(0.0f, 25.0f));
		//ImGui::Text("Please note; doing damage will give the same player extra points.");
		//ImGui::Text("When they die they get some more points.");
		ImGui::Text("There are 2 sounds in the game: Pickup and Jump");
		ImGui::Text("Both will be loaded on startup");
		ImGui::Text("Pickup will be played at startup, cannot be played again");
		ImGui::Text("Jump can be played when jumping");


		ImGui::End();
	}
	

}

