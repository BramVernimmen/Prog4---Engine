#pragma once
#include "UpdateComponent.h"
#include "imgui_plot.h"
#include <vector>

namespace dae
{
	struct Transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 };
	};

	class GameObject3D
	{
	public:
		Transform transform;
		int ID = 1;
	};
	class GameObject3DAlt
	{
	public:
		Transform* transform{ nullptr };
		int ID = 1;
	};

	class TrashTheCache_GameObjComponent : public UpdateComponent
	{
	public:
		TrashTheCache_GameObjComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~TrashTheCache_GameObjComponent();
		TrashTheCache_GameObjComponent(const TrashTheCache_GameObjComponent& other) = delete;
		TrashTheCache_GameObjComponent(TrashTheCache_GameObjComponent&& other) = delete;
		TrashTheCache_GameObjComponent& operator=(const TrashTheCache_GameObjComponent& other) = delete;
		TrashTheCache_GameObjComponent& operator=(TrashTheCache_GameObjComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

	protected:

	private:
		int m_AmountOfSamples{ 100 };

		const float** m_AxisYValues{ nullptr };

		std::vector<float> m_GameObjValues{};
		std::vector<float> m_GameObjAltValues{};

		ImGui::PlotConfig m_PlotConfigGameObj{ };
		ImGui::PlotConfig m_PlotConfigGameObjAlt{ };
		ImGui::PlotConfig m_PlotConfigCombined{ };

		ImU32 m_GraphColors[2] = { ImColor(0,150,200), ImColor(30,200,0) };

		const int m_TestArrayLength{ 1'000'000 };

		void StartTrashingGameObj();
		void StartTrashingGameObjAlt();

		float TrashGameObj(GameObject3D* arr, int arrLength, int stepsize, int sampleSize);
		float TrashGameObjAlt(GameObject3DAlt* arr, int arrLength, int stepsize, int sampleSize);
	};
}


