#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
	class RenderComponent;

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


	private:
		std::shared_ptr<RenderComponent> m_pRender{};

		void ChooseTexture(Type ingredient);
	};
}

