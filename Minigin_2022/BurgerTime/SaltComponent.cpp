#include "MiniginPCH.h"
#include "SaltComponent.h"

#include "PeterPepperComponent.h"

#include "Scene.h"
#include "SceneManager.h"

namespace dae
{
	class EnemyComponent;
}

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

	HandleCollision();
}

void dae::SaltComponent::Render() const
{

}

bool dae::SaltComponent::IsOverlapping(GameObject* object)
{
	const float otherObjectWidth = static_cast<float>(object->GetComponent<RenderComponent>()->GetWidth());
	const auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
	const float otherObjectheight = static_cast<float>(object->GetComponent<RenderComponent>()->GetHeight());

	auto& PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	const float PeterPepperWidth = static_cast<float>(m_pGameObject->GetComponent<RenderComponent>()->GetWidth());
	const float PeterPepperHeight = static_cast<float>(m_pGameObject->GetComponent<RenderComponent>()->GetHeight());


	if ((PeterPepperPos.x >= otherObjectPos.x && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth) &&
		(PeterPepperPos.y + PeterPepperHeight >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight))
	{

		return true;
	}

	return false;
}

void dae::SaltComponent::HandleCollision()
{
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();

	

}
