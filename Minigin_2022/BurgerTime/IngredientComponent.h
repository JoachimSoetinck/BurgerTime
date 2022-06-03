#pragma once
#include "BaseComponent.h"
#include <memory>

#include <glm/detail/type_vec.hpp>

#include "PeterPepperComponent.h"


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
		Type GetType()const { return m_Type; }
		void SetType(Type type) { m_Type = type; }
		bool IsOnTray() const { return m_isOnTray; }

		void CheckHitPoints(glm::vec3 positionPP, int height, int width, std::shared_ptr<PeterPepperComponent> pepper);
		void SetIsFalling(bool isFalling) { m_canFall = isFalling; }
		void ChooseTexture(Type ingredient);

	private:
		std::shared_ptr<RenderComponent> m_pRender{};

		bool m_canFall{ false };
		bool m_canCollide{ true };
		bool m_canSwap{ true };
		Type m_Type;
		float m_swapTimer{ 2.0f };


		bool m_RightCornerHit{ false };
		bool m_CenterHit{ false };
		bool m_LeftCornerHit{ false };
		bool m_hassFallen{ false };

		int m_fallSpeed{ 50 };

		std::shared_ptr<TransformComponent> m_pTransform{};

		bool IsOnPlatform(GameObject* o2);

		float m_elapsedSec;
		bool m_isOnTray{ false };
		std::shared_ptr<PeterPepperComponent> m_pepper{};
		std::shared_ptr<IngredientComponent> m_previousIngredient{};

		void HandleCollision();
		void Fall();
	};
}

