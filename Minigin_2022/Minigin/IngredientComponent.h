#pragma once
#include "BaseComponent.h"
#include <memory>

#include <glm/detail/type_vec.hpp>


namespace dae
{
	class RenderComponent;
	class TransformComponent;

	class IngredientComponent final : public BaseComponent
	{
	public:
		enum class Type
		{
			TopBun,
			Cheese,
			Lettuce,
			Patty,
			Tomato,
			BottomBun
		};
		IngredientComponent(std::shared_ptr<GameObject> object, Type Ingredient);

		~IngredientComponent() = default;
		IngredientComponent(const IngredientComponent& other) = delete;
		IngredientComponent(IngredientComponent&& other) = delete;
		IngredientComponent& operator=(const IngredientComponent& other) = delete;
		IngredientComponent& operator=(IngredientComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void CheckHitPoints(glm::vec3 positionPP, int height, int width);
		void SetIsFalling(bool isFalling) { m_canFall = isFalling; }

	private:
		std::shared_ptr<RenderComponent> m_pRender{};

		void ChooseTexture(Type ingredient);

		bool m_canFall{ false };
		bool m_canCollide{ true };
		

		bool m_RightCornerHit{false};
		bool m_CenterHit{ false };
		bool m_LeftCornerHit{ false };

		int m_fallSpeed{ 50 };

		std::shared_ptr<TransformComponent> m_pTransform{};

		bool IsOnPlatform(GameObject* o2);
		float m_elapsedSec;
		void DelayCollision();
		void HandleCollision();
		void Fall();
	};
}

