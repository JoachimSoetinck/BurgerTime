#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto component : m_Components)
	{
		component->Update();
	}

	for (auto child : m_Children)
	{
		child->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto component : m_Components)
	{
		component->Render();
	}

	for (auto child : m_Children)
	{
		child->Render();
	}
}


void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_Components.push_back(component);
	component->SetGameObject(this);
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Children.push_back(child);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	
}
