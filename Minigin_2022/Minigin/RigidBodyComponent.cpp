#include "MiniginPCH.h"
#include "RigidBodyComponent.h"


#include "Timer.h"

dae::RigidBodyComponent::RigidBodyComponent(std::shared_ptr<GameObject> object)
{
	m_pGameObject = object.get();
	m_TransformComponent =  m_pGameObject->GetComponent<TransformComponent>();
}

void dae::RigidBodyComponent::Update()
{
	if(m_TransformComponent)
	{
		if (abs(m_direction.x) > 0.01f || abs(m_direction.y) > 0.01f)
		{
			m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x + 50 * Time::GetDeltaTime(), m_TransformComponent->GetPosition().y, m_TransformComponent->GetPosition().z);
		}
		
	}
}

void dae::RigidBodyComponent::Render() const
{
}

void dae::RigidBodyComponent::SetDirection(glm::vec2 direction)
{
	m_direction = direction;
}
