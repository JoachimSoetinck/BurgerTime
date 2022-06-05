#pragma once


#include "Subject.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"

namespace dae
{
	class Scene;

	class PeterPepperComponent : public BaseComponent, public Subject
	{

	public:

		enum class PlayerState
		{
			MovingRight,
			ThrowingSaltRight,
			Idle,
			MovingLeft,
			ThrowingSaltLeft,
			ClimbingUp,
			ClimbingDown,
			Dying
		};

		PeterPepperComponent(std::shared_ptr<GameObject> object, glm::ivec2 startPos,int index = 0) ;
		virtual ~PeterPepperComponent() override;
		
		PeterPepperComponent(const PeterPepperComponent& other) = delete;
		PeterPepperComponent(PeterPepperComponent&& other) noexcept = delete;
		PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
		PeterPepperComponent& operator=(PeterPepperComponent&& other) noexcept = delete;

		 
		void Update() override;
		void Render() const override;

		int GetLives()const;
		int GetScore()const;
		bool IsOnLadder() const { return m_isOnLadder; }

		void GivePoints(int nrOfPoints);

		void LoseLive();
		void SetState(PlayerState state);
		bool IsThrowing() { return m_isThrowing; };

		
		

	private:
		int m_nrOfLives{ 3 };
		int m_score{ 0 };
		bool m_isOnGround {false};
		bool m_isOnLadder{false};
		bool m_isThrowing{ false };
		bool m_isDamaged{ false };
		float m_speed{ 50 };
		PlayerState m_state = PlayerState::Idle;

		int playerIndex{0}; 
		std::shared_ptr<TransformComponent> m_TransformComponent{};
		std::shared_ptr<RenderComponent> m_pRenderComponent{};
		std::shared_ptr<SpriteComponent> m_pSprite{};
		
		float m_throwDuration{ 1.0f};
		float m_DeathTimer{ 3.0f};
		float m_elapsedSec{};

		glm::ivec2 m_startPos{};

		void HandleMovement();
		bool IsOverlapping2(GameObject* get);
		bool IsOnGround(GameObject* object);
		bool IsOverlapping(GameObject* object);
		void SetOnGround(bool isOnGround);
		void HandleCollision();
		glm::vec2 m_direction{ 0,0 };

	};
}


