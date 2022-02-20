#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
{
}

dae::TransformComponent::TransformComponent(const glm::vec3& pos):
    m_Position{pos}
{
}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
    return m_Position;
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
