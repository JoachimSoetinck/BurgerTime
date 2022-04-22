#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

#include "ResourceManager.h"

dae::ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> object, SDL_Color color)
{
	m_pGameObject = object.get();



	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	m_pTextComponent = std::make_shared<TextComponent>("Lives", fpsFont, color, object);
	m_pPeter = object->GetComponent<PeterPepperComponent>();

	SetScoreText();

}

dae::ScoreComponent::~ScoreComponent()
{

}


void dae::ScoreComponent::OnNotify(const GameObject& , Event action)
{
	switch (action)
	{
	case Event::Died:
		SetScoreText();
		break;
	}
	
}

void dae::ScoreComponent::SetTextLocation(glm::vec3 location)
{
	m_pTextComponent->SetLocation(location);
}

void dae::ScoreComponent::Update()
{
	m_pTextComponent->Update();
}

void dae::ScoreComponent::Render() const
{
	m_pTextComponent->Render();
}

void dae::ScoreComponent::SetScoreText()
{
	if (m_pTextComponent != nullptr)
	{
		const int score = m_pPeter->GetScore();
		// text
		std::stringstream ssText;
		ssText << "Score: " << score;
		m_pTextComponent->SetText(ssText.str());

	}
}
