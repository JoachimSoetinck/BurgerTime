#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "InputManager.h"
#include "Command.h"
#include "LadderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

#include "TextComponent.h"
#include "Time.h"
#include "PlatformComponent.h"

dae::PeterPepperComponent::PeterPepperComponent(std::shared_ptr<GameObject> object)
{

	//AddObserver(new PlayerObserver());

	m_pGameObject = object.get();

	m_TransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();



}

dae::PeterPepperComponent::~PeterPepperComponent()
{

}

void dae::PeterPepperComponent::Update()
{
	HandleMovement();
	HandleCollision();
}

void dae::PeterPepperComponent::Render() const
{

}

int dae::PeterPepperComponent::GetLives() const
{
	return m_nrOfLives;
}

int dae::PeterPepperComponent::GetScore() const
{
	return m_score;
}

void dae::PeterPepperComponent::LoseLive()
{
	if (m_nrOfLives > 0)
		--m_nrOfLives;

	NotifyAllObservers(*m_pGameObject, Event::Died);
}

void dae::PeterPepperComponent::SetState(PlayerState state)
{
	m_state = state;

	switch (state)
	{
	case PlayerState::Idle:
	{
		m_direction = { 0,0 };
		break;
	}
	case PlayerState::MovingLeft:
	{
		m_direction.x = -50 ;
		break;
	}
	case PlayerState::MovingRight:
	{
		m_direction.x =  50;
		break;
	}
	case PlayerState::ClimbingUp:
	{
		m_direction.y =  -50 ;
		break;
	}
	case PlayerState::ClimbingDown:
	{
		m_direction.y = 50;
		break;
	}
	case PlayerState::Dying:
	{
		break;
	}
	case PlayerState::ThrowingSaltLeft:
	{
		break;
	}
	case PlayerState::ThrowingSaltRight:
	{
		break;
	}
	}
}

bool dae::PeterPepperComponent::IsOnGround(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth() ;
	auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = object->GetComponent<RenderComponent>()->GetHeight();

	auto PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int PeterPepperWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int PeterPepperHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();
	int offset = 15;

	if ((PeterPepperPos.x >= otherObjectPos.x - offset && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth + offset) &&
		(PeterPepperPos.y + PeterPepperHeight >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight))
	{
		return true;
	}

	return false;
}

void dae::PeterPepperComponent::SetOnGround(bool isOnGround)
{
	m_isOnGround = isOnGround;
}

void dae::PeterPepperComponent::HandleMovement()
{
	if (m_TransformComponent)
	{
		if (abs(m_direction.x) > 0.01f || abs(m_direction.y) > 0.01f)
		{
			m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x + m_direction.x * Time::GetDeltaTime(), m_TransformComponent->GetPosition().y + m_direction.y * Time::GetDeltaTime(), m_TransformComponent->GetPosition().z);
		}

		if (m_isOnGround == false && m_isOnLadder == false )
		{
			m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x, m_TransformComponent->GetPosition().y + 9.81f * Time::GetDeltaTime(), m_TransformComponent->GetPosition().z);
		}
		
	}

}

void dae::PeterPepperComponent::HandleCollision()
{
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();

	bool isOnGround = false;
	bool isOnLadder = false;

	for (const auto& o2 : objects)
	{
		if (o2.get()->GetComponent<PlatformComponent>() != nullptr)
		{
			if (IsOnGround(o2.get()))
			{
				isOnGround = true;
				m_direction.y = 0;
			}
		}

		if (o2.get()->GetComponent<LadderComponent>() != nullptr)
		{
			if (IsOnLadder(o2.get()))
			{
				isOnLadder = true;
			}
		}
	}

	m_isOnGround = isOnGround;
	m_isOnLadder = isOnLadder;

}

bool dae::PeterPepperComponent::IsOnLadder(GameObject* obj)
{
	int otherObjectWidth = obj->GetComponent<RenderComponent>()->GetWidth() ;
	auto otherObjectPos = obj->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = obj->GetComponent<RenderComponent>()->GetHeight();

	auto PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int PeterPepperWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int PeterPepperHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();
	int offset = 15;

	if ((PeterPepperPos.x >= otherObjectPos.x - offset && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth + offset ) &&
		(PeterPepperPos.y + PeterPepperHeight >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight +3 ))
	{
		return true;
	}

	return false;
}


void dae::PeterPepperComponent::GivePoints()
{
	const int earnedPoints = 100;

	m_score += earnedPoints;
	NotifyAllObservers(*m_pGameObject, Event::GivePoints);
}


