#pragma once
#include "BaseComponent.h"
#include <memory>




namespace  dae
{
	class RenderComponent;
	class BarrierComponent: public BaseComponent
	{
	public:
		BarrierComponent(std::shared_ptr<GameObject> object, bool leftSide);
		void Render() const override;
		void Update() override;
		bool IsLeftSide()const  {return m_leftSide; } 
		


	private:
		
		bool m_leftSide{true};

		float m_delay {1.0f};
		float m_elapsedSec{ 0 };
		bool m_canHit{true};

		std::shared_ptr<RenderComponent> m_RenderComponent{};
		bool IsOverlapping(GameObject* object);
	};



}


