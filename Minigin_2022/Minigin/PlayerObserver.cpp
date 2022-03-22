#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "PeterPepperComponent.h"
#include "TextComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"

void dae::PlayerObserver::OnNotify(const GameObject& entity, Event event)
{


	std::shared_ptr<PeterPepperComponent> pepperComp = entity.GetComponent<PeterPepperComponent>();
	std::shared_ptr<LivesComponent>  livesComp = entity.GetComponent<LivesComponent>();
	std::shared_ptr<ScoreComponent>  scoreComp = entity.GetComponent<ScoreComponent>();


	switch (event) {
	case Event::Died:
	{

		if (livesComp != nullptr)
		{
			livesComp->SetLives();
			std::cout << "Pepper Has lost 1 live\n";
		}

		if (pepperComp->GetLives() <= 0)
		{
			std::cout << "Pepper Has no lives\n";
		}
		break;
	}

	case Event::GivePoints:
	{
		if (scoreComp != nullptr)
		{
			scoreComp->SetScoreText();
			std::cout << "Pepper Has Earned 100 Points\n";
		}

		if (pepperComp->GetScore() >= 500)
		{
			std::cout << "Pepper Has Earned 500 Points\n";
		}
		break;
	}
	default:
		break;
	}
}


