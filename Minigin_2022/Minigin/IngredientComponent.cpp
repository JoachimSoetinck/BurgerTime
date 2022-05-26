#include "MiniginPCH.h"
#include "IngredientComponent.h"

#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Time.h"

dae::IngredientComponent::IngredientComponent(std::shared_ptr<GameObject> object, Type ingredient)
{
	m_pGameObject = object.get();

	m_pRender = m_pGameObject->GetComponent<RenderComponent>();
	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	if (m_pRender)
		ChooseTexture(ingredient);
}

void dae::IngredientComponent::Update()
{

	if (m_pTransform)
	{
		HandleCollision();


		if (m_LeftCornerHit && m_CenterHit )
			Fall();
	}

}

void dae::IngredientComponent::Render() const
{
}

void dae::IngredientComponent::CheckHitPoints(glm::vec3 positionPP, int height, int width)
{
	if (m_pTransform->GetPosition().x > positionPP.x &&
		m_pTransform->GetPosition().x <  positionPP.x + width &&
		m_pTransform->GetPosition().y > positionPP.y &&
		m_pTransform->GetPosition().y < positionPP.y + height)
	{
		m_LeftCornerHit = true;
	}
	if (m_pTransform->GetPosition().x + m_pRender->GetWidth() / 2 > positionPP.x &&
		m_pTransform->GetPosition().x + m_pRender->GetWidth() / 2 < positionPP.x + width &&
		m_pTransform->GetPosition().y > positionPP.y &&
		m_pTransform->GetPosition().y < positionPP.y + height)
	{
		m_CenterHit = true;
	}

	if (m_pTransform->GetPosition().x + m_pRender->GetWidth() < positionPP.x &&
		m_pTransform->GetPosition().x + m_pRender->GetWidth() > positionPP.x + width &&
		m_pTransform->GetPosition().y > positionPP.y &&
		m_pTransform->GetPosition().y < positionPP.y + height)
	{
		std::cout << "Right Corner Hit\n";
		m_RightCornerHit = true;
	}


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
		m_pRender->SetTexture("Patty.png");
		break;

	case Type::Tomato:
		m_pRender->SetTexture("Tomato.png");
		break;

	case Type::TopBun:
		m_pRender->SetTexture("TopBun.png");
		break;
	}
}

bool dae::IngredientComponent::IsOnPlatform(GameObject* o2)
{
	const int otherObjectWidth = o2->GetComponent<RenderComponent>()->GetWidth();
	auto& otherObjectPos = o2->GetComponent<TransformComponent>()->GetPosition();
	const auto otherObjectheight = o2->GetComponent<RenderComponent>()->GetHeight() / 2;

	auto& ingredientPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	const int ingredientWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	const int ingredientHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();



	if ((ingredientPos.y > otherObjectPos.y &&
		ingredientPos.y + ingredientHeight <= otherObjectPos.y + otherObjectheight) &&
		(ingredientPos.x >= otherObjectPos.x &&
			ingredientPos.x + ingredientWidth <= otherObjectPos.x + otherObjectWidth))
	{
		return true;
	}

	else return false;
}

void dae::IngredientComponent::DelayCollision()
{
	m_canCollide = false;
}

void dae::IngredientComponent::HandleCollision()
{
	auto objects = SceneManager::GetInstance().GetScene(0)->GetObjects();



	for (const auto& object : objects)
	{
		if (object.get()->GetComponent<IngredientComponent>() != nullptr)
		{
			if (IsOnPlatform(object.get()))
			{

				object->GetComponent<IngredientComponent>()->SetIsFalling(false);
				object->GetComponent<IngredientComponent>()->DelayCollision();

				object->GetComponent<TransformComponent>()->SetPosition(m_pTransform->GetPosition());

				m_canFall = true;

			}
		}


	}

}

void dae::IngredientComponent::Fall()
{
	m_pTransform->SetPosition(m_pTransform->GetPosition().x,
		m_pTransform->GetPosition().y + m_fallSpeed * Time::GetDeltaTime(),
		m_pTransform->GetPosition().z);

}
