#include "Scene.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name) 
{
	m_pRoot = std::make_unique<GameObject>();
}

Scene::~Scene() = default;


void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}

	m_pRoot->Update();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}

	m_pRoot->Render();
}

void dae::Scene::DisplayGui()
{

	for (const auto& object : m_objects)
	{
		object->DisplayGui();
	}

	m_pRoot->DisplayGui();
}

