#pragma once

#include "RigidBodyComponent.h"
#include "Subject.h"
#include "RenderComponent.h"

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
			Climbing,
			Dying
		};

		PeterPepperComponent(std::shared_ptr<GameObject> object) ;
		virtual ~PeterPepperComponent() override;
		
		PeterPepperComponent(const PeterPepperComponent& other) = delete;
		PeterPepperComponent(PeterPepperComponent&& other) noexcept = delete;
		PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
		PeterPepperComponent& operator=(PeterPepperComponent&& other) noexcept = delete;

		 
		void Update() override;
		void Render() const override;

		int GetLives()const;
		int GetScore()const;

		void GivePoints();

		void LoseLive();
		void SetState(PlayerState state);

		
		bool IsOnGround(GameObject* object);
		void SetOnGround(bool isOnGround);

	private:
		int m_nrOfLives{ 3 };
		int m_score{ 0 };
		bool m_isOnGround {false};
		PlayerState m_state = PlayerState::Idle;

		std::shared_ptr<RigidBodyComponent> m_pRigidBody{};
		std::shared_ptr<TransformComponent> m_TransformComponent{};
		std::shared_ptr<RenderComponent> m_pRenderComponent{};

		

		void HandleMovement();
		void HandleCollision();
		glm::vec2 m_direction{ 0,0 };

	};
}


