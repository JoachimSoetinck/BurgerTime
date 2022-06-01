#include "BarrierComponent.h"

#include "EnemyComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

#include "Timer.h"

dae::BarrierComponent::BarrierComponent(std::shared_ptr<GameObject> object, bool leftside)
	: m_leftSide{ leftside }
{
	m_pGameObject = object.get();

}

void dae::BarrierComponent::Render() const
{
}

void dae::BarrierComponent::Update()
{
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();

	if (m_canHit)
	{
		for (auto object : objects)
		{
			if (object->GetComponent<EnemyComponent>() != nullptr)
			{
				if (IsOverlapping(object.get()) && m_leftSide)
				{
					object->GetComponent<EnemyComponent>()->SetState(EnemyComponent::EnemyState::MovingRight);
					m_canHit = false;
					break;
				}
				else if (IsOverlapping(object.get()))
				{
					object->GetComponent<EnemyComponent>()->SetState(EnemyComponent::EnemyState::MovingLeft);
					m_canHit = false;
					break;
				}
			}
		}
	}

	if(m_canHit == false)
	{
		m_elapsedSec += Time::GetDeltaTime();

		if(m_elapsedSec >= m_delay)
		{
			m_canHit = true;
		}
		
	}
}

bool dae::BarrierComponent::IsOverlapping(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
	auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
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
