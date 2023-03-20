#include "TrashTheCache_IntegerComponent.h"
#include "imgui.h"
#include <iostream>
#include <chrono>
#include <numeric>

dae::TrashTheCache_IntegerComponent::TrashTheCache_IntegerComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::TrashTheCache_IntegerComponent::DisplayGui()
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_AmountOfSamples, 5);

	if (ImGui::Button("Trash the cache") && m_AmountOfSamples >= 4) // we need to subtract 2, so this leaves us with at least 2 more values
	{
		ExecuteFunction();
	}

	ImGui::Plot("plot", m_PlotConfig);

	ImGui::End();
}

void dae::TrashTheCache_IntegerComponent::ExecuteFunction()
{
	 //all steps are: 1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f -> will be a size of 11

	// clear the old data
	m_PlotYValues.clear();

	// allocate the integers
	const int arrLength{ static_cast<int>(std::powf(2, 26)) };
	int* arr = new int[arrLength];

	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 1, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 1, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 2, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 4, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 8, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 16, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 32, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 64, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 128, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 256, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 512, m_AmountOfSamples));
	m_PlotYValues.push_back(TrashIntegers(arr, arrLength, 1024, m_AmountOfSamples));

	float maxValue = *std::max_element(m_PlotYValues.begin(), m_PlotYValues.end());

	// prep the plots
	m_PlotConfig.values.color = ImColor(255, 120, 0);
	m_PlotConfig.values.ys = m_PlotYValues.data();
	m_PlotConfig.values.count = static_cast<int>(m_PlotYValues.size());
	m_PlotConfig.scale.max = maxValue;
	m_PlotConfig.grid_y.show = true;
	m_PlotConfig.grid_y.size = maxValue / 10.0f;
	// tooltip doesn't show the last value, so turning it off
	//m_PlotConfig.tooltip.show = true;
	//m_PlotConfig.tooltip.format = "x=%.2f, y=%.2f";
	m_PlotConfig.frame_size = ImVec2(120, 70);
	m_PlotConfig.line_thickness = 2.f;


	// DONT FORGET TO DELETE
	delete[] arr;
}

float dae::TrashTheCache_IntegerComponent::TrashIntegers(int* arr, int arrLength, int stepsize, int sampleSize)
{
	std::vector<long long> elapsedTimes{};

	for (int currentSample{ 0 }; currentSample < sampleSize; ++currentSample)
	{

		const auto start = std::chrono::high_resolution_clock::now();

		for (int i{ 0 }; i < arrLength; i += stepsize)
		{
			arr[i] *= 2;
		}

		const auto end = std::chrono::high_resolution_clock::now();


		const long long total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		elapsedTimes.push_back(total);
	}

	// remove min and max from times
	elapsedTimes.erase(std::min_element(elapsedTimes.begin(), elapsedTimes.end()));
	elapsedTimes.erase(std::max_element(elapsedTimes.begin(), elapsedTimes.end()));
	// take avg and print
	float avgTime{ std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0f) / elapsedTimes.size() / 1000.0f}; // in milliseconds

	return avgTime;
}
