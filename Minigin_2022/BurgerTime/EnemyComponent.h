#pragma once
#include <glm/vec2.hpp>
#include <memory>
#include "BaseComponent.h"
#include "RenderComponent.h"


namespace  dae
{
	class EnemyComponent final: public BaseComponent
	{
	public:
		enum class EnemyState
		{
			MovingLeft,
			MovingRight,
			Dying,
			Climbing,
			ClimbingUP
		};

		EnemyComponent(std::shared_ptr<GameObject> gameObject, const glm::ivec2 spawn);
		~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) noexcept = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;


		void Update() override;
		void Render() const override;

		void OnDeath();
		void Respawn();
		void SetState(EnemyState state) { m_state = state; }
		

	private:
		bool m_IsDead{false};
		float m_elapsedSec{ 0 };
		float m_respawnTimer{ 10 };

		std::shared_ptr<dae::GameObject> m_Target;

		bool m_isOnLadder{false};
		int m_Speed{ 40 };
		glm::vec2 m_direction{ 0,0 };
		glm::ivec2 m_spawnPoint{};


		
		void HandleCollision();

		std::shared_ptr<RenderComponent> m_pRenderComponent{};
		std::shared_ptr<TransformComponent> m_TransformComponent{};

		bool IsOverlapping(GameObject* obj);
	
		void DoMovement();

		EnemyState m_state{EnemyState::MovingRight};

	};
}


