#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto object : m_Components)
	{
		object->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto object : m_Components)
	{
		object->Render();
	}


}


void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_Components.push_back(component);
	component->m_pGameObject = this;
}
