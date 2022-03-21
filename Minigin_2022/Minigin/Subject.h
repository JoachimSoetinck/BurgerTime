#pragma once
#include <vector>

#include "Enums.h"
#include "Observer.h"
#include "GameObject.h"

namespace dae
{
	class Subject
	{


	public:
		Subject() = default;
		~Subject();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(Event eventType, GameObject& object);

		template <class T>
		T* GetObserver()
		{
			const type_info& ti = typeid(T);
			for (Observer* obs : m_pObservers)
			{
				if (obs && typeid(*obs) == ti)
					return static_cast<T*>(obs);
			}
			return nullptr;
		}

		
		void NotifyAllObservers(const GameObject& entity, Event event);


	private:
		std::vector<Observer*> m_pObservers;
	};
}


