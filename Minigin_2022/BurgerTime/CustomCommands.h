#pragma once
#include "Command.h"
#include "PeterPepperComponent.h"
#include <memory>

class FireCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject>) override { std::cout << "Fire" << std::endl; };
};

class MoveRight : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::MovingRight);
	};
};

class MoveLeft : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::MovingLeft);
	};
};

class MoveDown : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		if (object->GetComponent<dae::PeterPepperComponent>()->IsOnLadder())
			object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::ClimbingDown);
		else
		{

			object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::Idle);

		}



	};
};

class MoveUp : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		if (object->GetComponent<dae::PeterPepperComponent>()->IsOnLadder())
			object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::ClimbingUp);
		else
		{
			object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::Idle);
		}
	};
};

class Attack : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{

		object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::ThrowingSaltRight);

	};
};

class StopMoving : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		object->GetComponent<dae::PeterPepperComponent>()->SetState(dae::PeterPepperComponent::PlayerState::Idle);
	};
};

class PlaySound : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		dae::ServiceLocator::GetSoundSystem().RegisterSound("../Data/Sound/burgertime_dies.wav");
	};
};


class DuckCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject>) override { std::cout << "Duck" << std::endl; };
};

class JumpCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject>) override { std::cout << "Jump" << std::endl; };
};

class FartCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject>) override { std::cout << "Fart" << std::endl; };
};

class LoseLive : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> actor) override {

		std::shared_ptr<dae::PeterPepperComponent> pepperComp = actor->GetComponent<dae::PeterPepperComponent>();


		pepperComp->LoseLive();


	};
};

class GivePointsCommand : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> actor) override {

		std::shared_ptr<dae::PeterPepperComponent> pepperComp = actor->GetComponent<dae::PeterPepperComponent>();

		pepperComp->GivePoints(50);
	};
};

