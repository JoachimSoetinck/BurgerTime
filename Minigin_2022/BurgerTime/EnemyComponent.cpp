
#include "EnemyComponent.h"

#include "BarrierComponent.h"
#include "LadderComponent.h"
#include "PlatformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"
#include "BurgerTimePCH.h"
#include <iostream>


dae::EnemyComponent::EnemyComponent(std::shared_ptr<GameObject> gameObject, const glm::ivec2 spawn) :
	m_spawnPoint{ spawn }
{
	m_pGameObject = gameObject.get();

	m_pRenderComponent = gameObject->GetComponent<RenderComponent>();
	m_TransformComponent = gameObject->GetComponent<TransformComponent>();

	m_pGameObject->GetComponent<TransformComponent>()->SetPosition(static_cast<float>(spawn.x), static_cast<float>(spawn.y), 0);

	srand(time(NULL));
}

void dae::EnemyComponent::Update()
{
	HandleCollision();
	DoMovement();
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
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();


	int random{rand() };



	for (auto object : objects)
	{
		if (object->GetComponent<PlatformComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()))
			{

				break;
			}
		}

		if (object->GetComponent<LadderComponent>() != nullptr)
		{
			if (IsOverlapping(object.get()) && (random == 1 || m_state == EnemyState::MovingRight))
			{
				//m_state = EnemyState::Climbing;
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
		}

	}

	m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x + m_direction.x * Time::GetDeltaTime(), m_TransformComponent->GetPosition().y + m_direction.y * Time::GetDeltaTime(), m_TransformComponent->GetPosition().z);



}

