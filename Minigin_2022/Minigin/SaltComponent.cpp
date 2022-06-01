#include "MiniginPCH.h"
#include "SaltComponent.h"

#include "PeterPepperComponent.h"

dae::SaltComponent::SaltComponent(std::shared_ptr<GameObject> object, std::shared_ptr<PeterPepperComponent> pp)
{
	m_pGameObject = object.get();

	m_RenderComponent = m_pGameObject->GetComponent<RenderComponent>();
	m_TransformComponent = m_pGameObject->GetComponent<TransformComponent>();

	m_Parent = m_pGameObject->GetParent()->GetParent();

	 m_peterPepper =pp;
	
}

void dae::SaltComponent::Update()
{
	if(m_peterPepper != nullptr && m_RenderComponent != nullptr)
	{
		if (m_peterPepper->IsThrowing())
			m_RenderComponent->SetVisibility(true);
		else
			m_RenderComponent->SetVisibility(false);
	}
}

void dae::SaltComponent::Render() const
{

}
