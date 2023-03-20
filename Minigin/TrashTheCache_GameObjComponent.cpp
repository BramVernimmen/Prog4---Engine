#include "TrashTheCache_GameObjComponent.h"
#include "imgui.h"
#include <chrono>
#include <algorithm>
#include <numeric>

dae::TrashTheCache_GameObjComponent::TrashTheCache_GameObjComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
}

dae::TrashTheCache_GameObjComponent::~TrashTheCache_GameObjComponent()
{
    if (m_AxisYValues)
        delete[] m_AxisYValues;
}

void dae::TrashTheCache_GameObjComponent::DisplayGui()
{
	ImGui::Begin("Exercise 2"); 
    ImGui::InputInt("# samples", &m_AmountOfSamples, 5);

    if (ImGui::Button("Trash the cache with GameObject3D") && m_AmountOfSamples >= 4) // we need to subtract 2, so this leaves us with at least 2 more values
    {
        StartTrashingGameObj();
    }
    ImGui::Plot("GameObjTrashCachePlot", m_PlotConfigGameObj);

    if (ImGui::Button("Trash the cache with GameObject3DAlt") && m_AmountOfSamples >= 4)
    {
        StartTrashingGameObjAlt();
    }

    ImGui::Plot("GameObjAltTrashCachePlot", m_PlotConfigGameObjAlt);



    
    if (m_PlotConfigCombined.values.ys_list) // if either of the value vectors are empty, this value will be null
    {
        ImGui::Text("Comined:");
        ImGui::Plot("CominedPlot", m_PlotConfigCombined);
    }

	ImGui::End();
}

void dae::TrashTheCache_GameObjComponent::StartTrashingGameObj()
{
    GameObject3D* gameObjArr = new GameObject3D[m_TestArrayLength];

    m_GameObjValues.clear();

    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 1, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 2, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 4, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 8, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 16, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 32, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 64, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 128, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 256, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 512, m_AmountOfSamples));
    m_GameObjValues.push_back(TrashGameObj(gameObjArr, m_TestArrayLength, 1024, m_AmountOfSamples));

    float maxValue = *std::max_element(m_GameObjValues.begin(), m_GameObjValues.end());

    // prep the plots
    m_PlotConfigGameObj.values.color = ImColor(30, 200, 0);
    m_PlotConfigGameObj.values.ys = m_GameObjValues.data();
    m_PlotConfigGameObj.values.count = static_cast<int>(m_GameObjValues.size());
    m_PlotConfigGameObj.scale.max = maxValue;
    m_PlotConfigGameObj.grid_y.show = true;
    m_PlotConfigGameObj.grid_y.size = maxValue / 10.0f;
    m_PlotConfigGameObj.frame_size = ImVec2(120, 70);
    m_PlotConfigGameObj.line_thickness = 2.f;

    if (!m_GameObjValues.empty() && !m_GameObjAltValues.empty()) // check if both have values, only then we want to make our combined config
    {
        ImU32 colors[2] = { ImColor(0,150,200), ImColor(30,200,0) };

        if (m_AxisYValues)
            delete[] m_AxisYValues;

        m_AxisYValues = new const float* [] {m_GameObjAltValues.data(), m_GameObjValues.data()};

        float otherMaxValue = *std::max_element(m_GameObjAltValues.begin(), m_GameObjAltValues.end());

        maxValue = (maxValue > otherMaxValue) ? maxValue : otherMaxValue;

        m_PlotConfigCombined.values.colors = m_GraphColors;
        m_PlotConfigCombined.values.ys_list = m_AxisYValues;
        m_PlotConfigCombined.values.ys_count = 2;
        m_PlotConfigCombined.values.count = static_cast<int>(m_GameObjValues.size());
        m_PlotConfigCombined.scale.max = maxValue;
        m_PlotConfigCombined.grid_y.show = true;
        m_PlotConfigCombined.grid_y.size = maxValue / 10.0f;
        m_PlotConfigCombined.frame_size = ImVec2(120, 70);
        m_PlotConfigCombined.line_thickness = 2.f;
    }


    // DELETE
    delete[] gameObjArr;
}

void dae::TrashTheCache_GameObjComponent::StartTrashingGameObjAlt()
{
    GameObject3DAlt* gameObjAltArr = new GameObject3DAlt[m_TestArrayLength];

    m_GameObjAltValues.clear();

    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 1, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 2, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 4, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 8, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 16, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 32, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 64, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 128, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 256, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 512, m_AmountOfSamples));
    m_GameObjAltValues.push_back(TrashGameObjAlt(gameObjAltArr, m_TestArrayLength, 1024, m_AmountOfSamples));

    float maxValue = *std::max_element(m_GameObjAltValues.begin(), m_GameObjAltValues.end());

    // prep the plots
    m_PlotConfigGameObjAlt.values.color = ImColor(0, 150, 200);
    m_PlotConfigGameObjAlt.values.ys = m_GameObjAltValues.data();
    m_PlotConfigGameObjAlt.values.count = static_cast<int>(m_GameObjAltValues.size());
    m_PlotConfigGameObjAlt.scale.max = maxValue;
    m_PlotConfigGameObjAlt.grid_y.show = true;
    m_PlotConfigGameObjAlt.grid_y.size = maxValue / 10.0f;
    m_PlotConfigGameObjAlt.frame_size = ImVec2(120, 70);
    m_PlotConfigGameObjAlt.line_thickness = 2.f;

    if (!m_GameObjValues.empty() && !m_GameObjAltValues.empty()) // check if both have values, only then we want to make our combined config
    {
        ImU32 colors[2] = { ImColor(0,150,200), ImColor(30,200,0) };

        if (m_AxisYValues)
            delete[] m_AxisYValues;

        m_AxisYValues = new const float* [] {m_GameObjAltValues.data(), m_GameObjValues.data()};

        float otherMaxValue = *std::max_element(m_GameObjValues.begin(), m_GameObjValues.end());

        maxValue = (maxValue > otherMaxValue) ? maxValue : otherMaxValue;

        m_PlotConfigCombined.values.colors = m_GraphColors;
        m_PlotConfigCombined.values.ys_list = m_AxisYValues;
        m_PlotConfigCombined.values.ys_count = 2;
        m_PlotConfigCombined.values.count = static_cast<int>(m_GameObjAltValues.size());
        m_PlotConfigCombined.scale.max = maxValue;
        m_PlotConfigCombined.grid_y.show = true;
        m_PlotConfigCombined.grid_y.size = maxValue / 10.0f;
        m_PlotConfigCombined.frame_size = ImVec2(120, 70);
        m_PlotConfigCombined.line_thickness = 2.f;
    }

    // DELETE
    delete[] gameObjAltArr;
}

float dae::TrashTheCache_GameObjComponent::TrashGameObj(GameObject3D* arr, int arrLength, int stepsize, int sampleSize)
{
    std::vector<long long> elapsedTimes{};

    for (int currentSample{ 0 }; currentSample < sampleSize; ++currentSample)
    {

        const auto start = std::chrono::high_resolution_clock::now();

        for (int i{ 0 }; i < arrLength; i += stepsize)
        {
            arr[i].ID *= 2;
        }

        const auto end = std::chrono::high_resolution_clock::now();


        const long long total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        elapsedTimes.push_back(total);
    }

    // remove min and max from times
    elapsedTimes.erase(std::min_element(elapsedTimes.begin(), elapsedTimes.end()));
    elapsedTimes.erase(std::max_element(elapsedTimes.begin(), elapsedTimes.end()));
    // take avg and print
    const float avgTime{ std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0f) / elapsedTimes.size() / 1000.0f }; // in microseconds
    return avgTime;
}

float dae::TrashTheCache_GameObjComponent::TrashGameObjAlt(GameObject3DAlt* arr, int arrLength, int stepsize, int sampleSize)
{
    std::vector<long long> elapsedTimes{};

    for (int currentSample{ 0 }; currentSample < sampleSize; ++currentSample)
    {

        const auto start = std::chrono::high_resolution_clock::now();

        for (int i{ 0 }; i < arrLength; i += stepsize)
        {
            arr[i].ID *= 2;
        }

        const auto end = std::chrono::high_resolution_clock::now();


        const long long total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        elapsedTimes.push_back(total);
    }

    // remove min and max from times
    elapsedTimes.erase(std::min_element(elapsedTimes.begin(), elapsedTimes.end()));
    elapsedTimes.erase(std::max_element(elapsedTimes.begin(), elapsedTimes.end()));
    // take avg and print
    const float avgTime{ std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0f) / elapsedTimes.size() / 1000.0f}; // in microseconds

    return avgTime;
}
