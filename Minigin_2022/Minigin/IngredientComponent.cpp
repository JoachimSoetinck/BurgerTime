#include "MiniginPCH.h"
#include "IngredientComponent.h"
#include "RenderComponent.h"

dae::IngredientComponent::IngredientComponent(std::shared_ptr<GameObject> object, Type ingredient)
{
	m_pGameObject = object.get();

	m_pRender = m_pGameObject->GetComponent<RenderComponent>();
	if (m_pRender)
		ChooseTexture(ingredient);
}

void dae::IngredientComponent::Update()
{
}

void dae::IngredientComponent::Render() const
{
}

void dae::IngredientComponent::ChooseTexture(Type ingredient)
{
	switch (ingredient)
	{
	case Type::BottomBun:
		m_pRender->SetTexture("BottomBun.png");
		break;
	case Type::Cheese:
		m_pRender->SetTexture("Cheese.png");
		break;
	
	case Type::Lettuce:
		m_pRender->SetTexture("Lettuce.png");
		break;

	case Type::Patty:
		//m_pRender->SetTexture("Patty.png");
		break;

	case Type::Tomato:
		m_pRender->SetTexture("Tomato.png");
		break;

	case Type::TopBun:
		m_pRender->SetTexture("TopBun.png");
		break;
	}
}
