#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"


using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

void dae::Scene::DeleteObjects()
{
	m_Objects.clear();
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}

}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}



