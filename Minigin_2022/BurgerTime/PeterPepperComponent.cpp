#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "InputManager.h"
#include "CustomCommands.h"
#include "IngredientComponent.h"
#include "LadderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

#include "TextComponent.h"
#include "Timer.h"
#include "PlatformComponent.h"

dae::PeterPepperComponent::PeterPepperComponent(std::shared_ptr<GameObject> object)
{

	//AddObserver(new PlayerObserver());

	m_pGameObject = object.get();

	m_TransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();


	InputManager::GetInstance().AddCommand(ControllerButton::ButtonRight, new MoveRight(), object, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonRight, new StopMoving(), object, 0, ButtonPressType::IsUp);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonLeft, new MoveLeft(), object, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonLeft, new StopMoving(), object, 0, ButtonPressType::IsUp);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonDown, new MoveDown(), object, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonDown, new StopMoving(), object, 0, ButtonPressType::IsUp);

	InputManager::GetInstance().AddCommand(ControllerButton::ButtonUp, new MoveUp(), object, 0, ButtonPressType::IsDown);
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonUp, new StopMoving(), object, 0, ButtonPressType::IsUp);


	InputManager::GetInstance().AddCommand(ControllerButton::ButtonA, new Attack(), object, 0, ButtonPressType::IsUp);


}

dae::PeterPepperComponent::~PeterPepperComponent()
{

}

void dae::PeterPepperComponent::Update()
{
	if(!m_isThrowing)
	{
		HandleMovement();
		HandleCollision();
	}

	if(m_isThrowing)
	{
		m_elapsedSec += Time::GetDeltaTime();

		if (m_elapsedSec >= m_throwDuration)
		{
			m_state = PlayerState::Idle;
			m_isThrowing = false;
			m_elapsedSec = 0.0f;
			std::cout << "idle";
		}
			
	}
	
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
		m_direction.x = -50;
		break;
	}
	case PlayerState::MovingRight:
	{
		m_direction.x = 50;
		break;
	}
	case PlayerState::ClimbingUp:
	{
		m_direction.y = -50;
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
		m_direction = { 0,0 };
		m_isThrowing = true;
		break;
	}
	case PlayerState::ThrowingSaltRight:
	{
		m_direction = { 0,0 };
		m_isThrowing = true;
		break;
	}
	}
}

bool dae::PeterPepperComponent::IsOnGround(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
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

bool dae::PeterPepperComponent::IsOverlapping(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
	auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = object->GetComponent<RenderComponent>()->GetHeight();

	auto PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int PeterPepperWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int PeterPepperHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();
	int offset = 15;

	if ((PeterPepperPos.x >= otherObjectPos.x - offset && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth) &&
		(PeterPepperPos.y + PeterPepperHeight + 10 >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight))
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

		if (m_isOnGround == false && m_isOnLadder == false)
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

		if (o2.get()->GetComponent<IngredientComponent>() != nullptr)
		{
			if (IsOverlapping(o2.get()))
			{
				o2.get()->GetComponent<IngredientComponent>()->CheckHitPoints(m_TransformComponent->GetPosition(), m_pGameObject->GetComponent<RenderComponent>()->GetHeight(), m_pGameObject->GetComponent<RenderComponent>()->GetWidth());

			}
		}
	}

	m_isOnGround = isOnGround;
	m_isOnLadder = isOnLadder;

}

bool dae::PeterPepperComponent::IsOnLadder(GameObject* obj)
{
	int otherObjectWidth = obj->GetComponent<RenderComponent>()->GetWidth();
	auto otherObjectPos = obj->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = obj->GetComponent<RenderComponent>()->GetHeight();

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


void dae::PeterPepperComponent::GivePoints(int nrOfPoints)
{


	m_score += nrOfPoints;
	NotifyAllObservers(*m_pGameObject, Event::GivePoints);
}

