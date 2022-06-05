#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "GameObject.h"

dae::TransformComponent::TransformComponent()
{

}

dae::TransformComponent::TransformComponent(const glm::vec3& pos) :
	m_Position{ pos },
	m_WorldPos{  }
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::Render() const
{
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

const glm::vec3& dae::TransformComponent::GetWorldPosition() const
{
	
	return  m_WorldPos;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = static_cast<float>(x);
	m_Position.y = static_cast<float>(y);
	m_Position.z = static_cast<float>(z);
}

void dae::TransformComponent::SetPosition(const glm::vec3& newPos)
{
	m_Position = newPos;

}
