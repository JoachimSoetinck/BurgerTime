
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
	m_IsDead = true;
	m_pRenderComponent->SetVisibility(false);
	m_pGameObject->GetComponent<TransformComponent>()->SetPosition(static_cast<float>(m_spawnPoint.x), static_cast<float>(m_spawnPoint.y), 0);
}

void dae::EnemyComponent::Respawn()
{
}

void dae::EnemyComponent::HandleCollision()
{
	const auto nr = SceneManager::GetInstance().GetActiveSceneNr();

	const auto objects = SceneManager::GetInstance().GetScene(nr)->GetObjects();


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
				OnDeath();
				auto pepper = object->GetComponent<SaltComponent>()->GetPeterPepper();
				pepper->GivePoints(100);
				break;
			}
		}

		if (object->GetComponent<PeterPepperComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()))
			{
				OnDeath();
				break;
			}
		}


		if (object->GetComponent<IngredientComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()) && object->GetComponent<IngredientComponent>()->IsFalling()== true)
			{
				OnDeath();
				object->GetComponent<IngredientComponent>()->GetDropper()->GivePoints(500);
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

	auto& enemyPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	const float enemyWidth = static_cast<float>(m_pGameObject->GetComponent<RenderComponent>()->GetWidth());
	const float enemyHeight = static_cast<float>(m_pGameObject->GetComponent<RenderComponent>()->GetHeight());


	if ((enemyPos.x >= otherObjectPos.x && enemyPos.x + enemyWidth <= otherObjectPos.x + otherObjectWidth) &&
		(enemyPos.y + enemyHeight >= otherObjectPos.y && enemyPos.y + enemyHeight <= otherObjectPos.y + otherObjectheight))
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

	m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x + m_direction.x * Time::GetDeltaTime(), (m_TransformComponent->GetPosition().y + m_direction.y * Time::GetDeltaTime()), 0.0f);



}

