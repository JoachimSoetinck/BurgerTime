#include "MiniginPCH.h"
#include "PeterPepperComponent.h"

#include "InputManager.h"
#include "Command.h"
#include "PlayerObserver.h"
#include "TextComponent.h"

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

void dae::PeterPepperComponent::GivePoints() 
{
	const int earnedPoints = 100;

	m_score += earnedPoints;
	NotifyAllObservers(*m_pGameObject, Event::GivePoints);
}


