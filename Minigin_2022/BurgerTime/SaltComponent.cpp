#include "MiniginPCH.h"
#include "SaltComponent.h"

#include "PeterPepperComponent.h"
#include "EnemyComponent.h"
#include "IngredientComponent.h"
#include "LadderComponent.h"
#include "PlatformComponent.h"

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

	m_peterPepper = pp;

}

void dae::SaltComponent::Update()
{
	if (m_peterPepper != nullptr && m_RenderComponent != nullptr)
	{
		if (m_peterPepper->IsThrowing())
		{
			m_RenderComponent->SetVisibility(true);
			m_isActive = true;
		}

		else
		{
			m_RenderComponent->SetVisibility(false);
			m_isActive = false;
		}

	}

	HandleCollision();
}

void dae::SaltComponent::Render() const
{

}

dae::PeterPepperComponent* dae::SaltComponent::GetPeterPepper() const
{
	return m_peterPepper.get();
}

bool dae::SaltComponent::IsOverlapping(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
	auto& otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = object->GetComponent<RenderComponent>()->GetHeight();

	auto PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int PeterPepperWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int PeterPepperHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();
	int offset = 15;

	if ((PeterPepperPos.x >= otherObjectPos.x - offset && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth + offset) &&
		(PeterPepperPos.y + PeterPepperHeight >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight + 3))
	{
		return true;
	}

	return false;
}

void dae::SaltComponent::HandleCollision()
{



}
