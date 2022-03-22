#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "PeterPepperComponent.h"
#include "PlayerObserver.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::LivesComponent::LivesComponent(std::shared_ptr<GameObject> object)
{
	m_pGameObject = object.get();

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	
	m_pTextComponent = std::make_shared<TextComponent>("Lives", fpsFont, SDL_Color{ 255, 255, 0 }, object);
	m_pPeter = object->GetComponent<PeterPepperComponent>();


	SetLives();
}

dae::LivesComponent::~LivesComponent()
{
	
	m_pTextComponent = nullptr;
}

void dae::LivesComponent::Update()
{
	if (m_pTextComponent != nullptr)
	{

		
		m_pTextComponent->Update();

	}

	
}

void dae::LivesComponent::Render() const
{
	m_pTextComponent->Render();
}

void dae::LivesComponent::SetLives()
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
