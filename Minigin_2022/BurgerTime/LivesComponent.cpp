#include "MiniginPCH.h"
#include "LivesComponent.h"

#include "PeterPepperComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::LivesComponent::LivesComponent(std::shared_ptr<GameObject> object, SDL_Color color, std::shared_ptr<PeterPepperComponent> peter)
{
	m_pGameObject = object.get();

	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	m_color = SDL_Color{ 255, 255, 0 };
	m_pTextComponent = std::make_shared<TextComponent>("Lives", fpsFont, color, object);
	m_pPeter = peter.get();

	SetLives();
}



void dae::LivesComponent::OnNotify(const GameObject& , Event action)
{
	switch (action)
	{
	case Event::Died:
		SetLives();
		break;
	default: ;
	}

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