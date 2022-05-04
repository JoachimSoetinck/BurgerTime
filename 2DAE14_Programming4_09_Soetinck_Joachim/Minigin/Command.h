#pragma once
#include <iostream>

#include "GameObject.h"
#include "PeterPepperComponent.h"
#include "RigidBodyComponent.h"
#include "ServiceLocator.h"

class Command
{
public:
	Command() {  }
	virtual ~Command() = default;
	virtual void Execute(std::shared_ptr<dae::GameObject> actor) = 0;


};

class FireCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject> ) override { std::cout << "Fire" << std::endl; };
};

class MoveRight : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{ 
		object->GetComponent<dae::RigidBodyComponent>()->SetDirection(glm::vec2(250.f, 0.f));
	};
};

class StopMoving : public Command
{
public:
	virtual void Execute(std::shared_ptr<dae::GameObject> object) override
	{
		object->GetComponent<dae::RigidBodyComponent>()->SetDirection(glm::vec2(0.f, 0.f));
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

	virtual void Execute(std::shared_ptr<dae::GameObject> ) override { std::cout << "Duck" << std::endl; };
};

class JumpCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject> ) override { std::cout << "Jump" << std::endl; };
};

class FartCommand : public Command
{
public:

	virtual void Execute(std::shared_ptr<dae::GameObject> ) override { std::cout << "Fart" << std::endl; };
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

		pepperComp->GivePoints();
	};
};

