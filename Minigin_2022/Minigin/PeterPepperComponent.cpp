#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "InputManager.h"
#include "Command.h"
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
		m_direction = { -50,0 };
		break;
	}
	case PlayerState::MovingRight:
	{
		m_direction = { 50,0 };
		break;
	}
	case PlayerState::Climbing:
	{
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
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
	auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();

	auto characterPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int characterWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int characterHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();

	if ((characterPos.x >= otherObjectPos.x && characterPos.x + characterWidth <= otherObjectPos.x + otherObjectWidth) &&
		(characterPos.y + characterHeight >= otherObjectPos.y && characterPos.y + characterHeight <= otherObjectPos.y + 10))
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

		else if (m_isOnGround == false)
		{
			m_TransformComponent->SetPosition(m_TransformComponent->GetPosition().x, m_TransformComponent->GetPosition().y + 9.81f * Time::GetDeltaTime(), m_TransformComponent->GetPosition().z);
		}
	}

}

void dae::PeterPepperComponent::HandleCollision()
{
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();


	for (const auto& o2 : objects)
	{
		if (o2.get()->GetComponent<PlatformComponent>() != nullptr)
		{
			if (IsOnGround(o2.get()))
			{
				SetOnGround(true);
			}
		}
	}
}

void dae::PeterPepperComponent::GivePoints()
{
	const int earnedPoints = 100;

	m_score += earnedPoints;
	NotifyAllObservers(*m_pGameObject, Event::GivePoints);
}


