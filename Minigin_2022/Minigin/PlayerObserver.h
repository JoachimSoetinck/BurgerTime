#pragma once
#include "Enums.h"
#include "Observer.h"

namespace dae
{
	class GameObject;

	class PlayerObserver : public dae::Observer
	{
	public:
		void OnNotify(const dae::GameObject& entity, Event event) override;

		int GetLives() const ;
	};
}




