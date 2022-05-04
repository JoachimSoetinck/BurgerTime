#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "GameObject.h"

dae::TransformComponent::TransformComponent()
{

}

dae::TransformComponent::TransformComponent(const glm::vec3& pos) :
	m_Position{ pos }
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

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	
	return  m_WorldPos;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& newPos)
{
	m_Position = newPos;

}
