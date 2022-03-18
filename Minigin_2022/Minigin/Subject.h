#pragma once
#include <vector>

#include "Observer.h"
#include "GameObject.h"

namespace dae
{
	class Subject 
	{
		

	public:
		Subject() = default;
		~Subject();
		void AddObserver(Observer * observer);
		void RemoveObserver(Observer * observer);
		void Notify(int eventType, GameObject * object);

	private:
		std::vector<Observer*> m_Observers;
	};
}


