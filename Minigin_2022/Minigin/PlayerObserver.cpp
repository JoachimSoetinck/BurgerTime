#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"

void dae::PlayerObserver::OnNotify(const GameObject& entity, Event event)
{
	switch (event) {
	case Event::Died:
	{

		std::shared_ptr<PeterPepperComponent> pepperComp = entity.GetComponent<PeterPepperComponent>();
		std::shared_ptr<TextComponent>  textComp = entity.GetComponent<TextComponent>();

		const int lives = pepperComp->GetLives();

		if (textComp != nullptr)
		{
			std::stringstream ssText;
			ssText << "Lives: " << lives;
			textComp->SetText(ssText.str());
		}

		if (pepperComp->GetLives() <= 0)
		{
			std::cout << "Pepper Has no lives\n";
			
		}
		break;
	}

	default:
		break;
	}
}

int dae::PlayerObserver::GetLives() const
{
	return 0;
}
