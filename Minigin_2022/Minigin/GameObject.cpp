#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::GameObject::GameObject() : m_Parent(this)
{
	
	const auto transformComponent = std::make_shared<TransformComponent>();
	m_Components.push_back(transformComponent);
}

dae::GameObject::~GameObject()
{
	
}

void dae::GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Update();
	}

	for (auto& child : m_Children)
	{
		child->Update();

		child->GetComponent<TransformComponent>()->SetPosition(GetComponent<TransformComponent>()->GetPosition() + child->GetComponent<TransformComponent>()->GetWorldPosition());
		
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

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Children.push_back(child);
	child->SetParent(this);

	child->GetComponent<TransformComponent>()->SetPosition(this->GetComponent<TransformComponent>()->GetPosition() + child->GetComponent<TransformComponent>()->GetWorldPosition());
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{

}

dae::GameObject* dae::GameObject::GetParent() const
{
	
	return  m_Parent;

	
}

void dae::GameObject::SetParent(GameObject* parent) 
{

	m_Parent = parent;

}
