#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "PeterPepperComponent.h"
#include "PlayerObserver.h"
#include "TextComponent.h"

dae::LivesComponent::LivesComponent(std::shared_ptr<GameObject> object)
{
	m_pGameObject = object.get();

	m_pTextComponent = object->GetComponent<TextComponent>();
	m_pPeter = object->GetComponent<PeterPepperComponent>();



}

dae::LivesComponent::~LivesComponent()
{
	m_pPlayerObserver = nullptr;
	m_pTextComponent = nullptr;
}

void dae::LivesComponent::Update()
{
	if (m_pTextComponent != nullptr)
	{
		const int lives = m_pPeter->GetLives();


		// text
		std::stringstream ssText;
		ssText << "Lives: " << lives;
		m_pTextComponent->SetText(ssText.str());



	}
}

void dae::LivesComponent::Render() const
{
}
