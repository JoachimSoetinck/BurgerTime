#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "InputManager.h"
#include "Command.h"
#include "PlayerObserver.h"

dae::PeterPepperComponent::PeterPepperComponent(std::shared_ptr<GameObject> object)
{

	AddObserver(new PlayerObserver());

	m_pGameObject = object.get();

}

dae::PeterPepperComponent::~PeterPepperComponent()
{

}

void dae::PeterPepperComponent::Update()
{
	
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA, 0)) {
		OnDeath();
	}
}

void dae::PeterPepperComponent::Render() const
{

}

int dae::PeterPepperComponent::GetLives() const
{
	return m_nrOfLives;
}

void dae::PeterPepperComponent::OnDeath()
{
	if (m_nrOfLives > 0)
		--m_nrOfLives;

	NotifyAllObservers(*m_pGameObject, Event::Died);
}

