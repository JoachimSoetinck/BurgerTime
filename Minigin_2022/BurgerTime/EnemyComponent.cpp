
#include "EnemyComponent.h"

#include "BarrierComponent.h"
#include "LadderComponent.h"
#include "PlatformComponent.h"
#include "PeterPepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"
#include "BurgerTimePCH.h"
#include <iostream>

#include "IngredientComponent.h"
#include "SaltComponent.h"


dae::EnemyComponent::EnemyComponent(std::shared_ptr<GameObject> gameObject, const glm::ivec2 spawn) :
	m_spawnPoint{ spawn }
	
{
	m_pGameObject = gameObject.get();

	m_pRenderComponent = gameObject->GetComponent<RenderComponent>();
	m_TransformComponent = gameObject->GetComponent<TransformComponent>();

	m_pGameObject->GetComponent<TransformComponent>()->SetPosition(static_cast<float>(spawn.x), static_cast<float>(spawn.y), 0);


}

void dae::EnemyComponent::Update()
{
	HandleCollision();
	DoMovement();

	if (m_IsDead)
	{
		m_elapsedSec += Time::GetDeltaTime();

		if (m_elapsedSec >= m_respawnTimer)
		{
			m_pRenderComponent->SetVisibility(true);
		}
	}
}

void dae::EnemyComponent::Render() const
{
}

void dae::EnemyComponent::OnDeath()
{
}

void dae::EnemyComponent::Respawn()
{
}

void dae::EnemyComponent::HandleCollision()
{
	auto nr = SceneManager::GetInstance().GetActiveSceneNr();

	auto objects = SceneManager::GetInstance().GetScene(nr)->GetObjects();


	int random{ rand() };

	for (auto object : objects)
	{
		if (object->GetComponent<PlatformComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()))
			{
				
				break;
			}
		}


		if (object->GetComponent<SaltComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()) && object->GetComponent<SaltComponent>()->GetVisibility())
			{
				m_IsDead = true;
				m_pRenderComponent->SetVisibility(false);
				m_pGameObject->GetComponent<TransformComponent>()->SetPosition(m_spawnPoint.x, m_spawnPoint.y, 0);
				auto pepper = object->GetComponent<SaltComponent>()->GetPeterPepper();
				pepper->GivePoints(100);
				break;
			}
		}

		if (object->GetComponent<PeterPepperComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()))
			{
				std::cout << "Hit";
				break;
			}
		}

		

	}




}


bool dae::EnemyComponent::IsOverlapping(GameObject* object)
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



void dae::EnemyComponent::DoMovement()
{
	if (m_TransformComponent)
	{
		switch (m_state)
		{

		case EnemyState::MovingLeft:
		{
			m_direction = { -m_Speed,0 };
			break;
		}
		case EnemyState::MovingRight:
		{
			m_direction = { m_Speed,0 };
			break;
		}
		case EnemyState::Climbing:
		{
			m_direction = { 0,m_Speed };
			break;
		}

		case EnemyState::Dying:
		{
			m_direction = { 0,0 };
			break;
		}

		case EnemyState::ClimbingUP:
		{
			m_direction = { 0,-m_Speed };
			break;
		}
		}

	}

	m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x + m_direction.x * Time::GetDeltaTime(), m_TransformComponent->GetPosition().y + m_direction.y * Time::GetDeltaTime(), m_TransformComponent->GetPosition().z);



}

