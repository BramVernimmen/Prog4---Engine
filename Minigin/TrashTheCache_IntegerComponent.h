#pragma once
#include "UpdateComponent.h"
#include "imgui_plot.h"
#include <vector>

namespace dae
{

	class TrashTheCache_IntegerComponent : public UpdateComponent
	{
	public:
		TrashTheCache_IntegerComponent(GameObject* pOwner);
		virtual ~TrashTheCache_IntegerComponent() = default;
		TrashTheCache_IntegerComponent(const TrashTheCache_IntegerComponent& other) = delete;
		TrashTheCache_IntegerComponent(TrashTheCache_IntegerComponent&& other) = delete;
		TrashTheCache_IntegerComponent& operator=(const TrashTheCache_IntegerComponent& other) = delete;
		TrashTheCache_IntegerComponent& operator=(TrashTheCache_IntegerComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

	protected:

	private:
		int m_AmountOfSamples{ 10 };

		std::vector<float> m_PlotYValues{ };

		ImGui::PlotConfig m_PlotConfig{ }; // keep this, no need to remake it every frame

		void StartTrashing();
		float TrashIntegers(int* arr, int arrLength, int stepsize, int sampleSize);
	};

}
