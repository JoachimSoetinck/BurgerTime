#pragma once
#include <iostream>

#include "GameObject.h"


#include "ServiceLocator.h"

class Command
{
public:
	Command() {  }
	virtual ~Command() = default;
	virtual void Execute(std::shared_ptr<dae::GameObject> actor) = 0;


};



