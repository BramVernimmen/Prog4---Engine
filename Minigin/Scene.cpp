#include "Scene.h"
#include "EngineEvents.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

void dae::Scene::IsSetAsActive()
{
	NotifyObservers(SceneLoaded(), this);
}

Scene::Scene(const std::string& name)
	: m_name(name) 
{
	m_pRoot = std::make_unique<GameObject>();
}



Scene::~Scene() = default;


void Scene::Update()
{
	m_pRoot->Update();
}

void Scene::Render() const
{
	m_pRoot->Render();
}

void dae::Scene::DisplayGui()
{
	m_pRoot->DisplayGui();
}

void dae::Scene::CheckForRemoval()
{
	RemoveMarkedObjects(m_pRoot.get());
}

void dae::Scene::RemoveMarkedObjects(GameObject* parent)
{
	auto allChildren{ parent->GetChildren() };
	for (auto it{ allChildren.end() }; it != allChildren.begin(); )
	{
		--it;
		GameObject* currObject{ (*it) };
		if (currObject->IsMarkedForDelete())
		{
			auto tempObjectForDelete{ std::make_unique<GameObject>() };
			currObject->SetParent(tempObjectForDelete.get());
			// setting the parent to the temp object, will make the lifespawn of the object last as long as this scope
			// meaning it will get destroyed right after
			// using the SetParent also removes the object from the vectors keeping track of it
		}
		else
		{
			// we need to check all their children -> this should be recursive
			RemoveMarkedObjects(currObject);
		}
	}
}