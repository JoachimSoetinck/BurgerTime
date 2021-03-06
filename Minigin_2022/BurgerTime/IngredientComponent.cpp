#include "MiniginPCH.h"
#include "IngredientComponent.h"

#include "PlatformComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Timer.h"
#include "TrayComponent.h"

dae::IngredientComponent::IngredientComponent(std::shared_ptr<GameObject> object, Type ingredient) : m_Type(ingredient)
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

		if (m_isOnTray == false)
			Fall();

	}

}

void dae::IngredientComponent::Render() const
{
}

void dae::IngredientComponent::CheckHitPoints(glm::vec3 positionPP, int height, int width, std::shared_ptr<PeterPepperComponent> pepper)
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

	float width2 = 105;
	if (m_pTransform->GetPosition().x + width2 > positionPP.x &&
		m_pTransform->GetPosition().x + width2 < positionPP.x + width2 &&
		m_pTransform->GetPosition().y > positionPP.y &&
		m_pTransform->GetPosition().y < positionPP.y + height)
	{
		m_RightCornerHit = true;
	}

	if ((m_LeftCornerHit && m_CenterHit && m_RightCornerHit) && m_hassFallen == false)
	{
		pepper->GivePoints(50);
		m_pepper = pepper;
		m_hassFallen = true;
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

bool dae::IngredientComponent::IsOnPlatform(GameObject* object)
{
	int otherObjectWidth = object->GetComponent<RenderComponent>()->GetWidth();
	auto otherObjectPos = object->GetComponent<TransformComponent>()->GetPosition();
	auto otherObjectheight = object->GetComponent<RenderComponent>()->GetHeight();

	auto PeterPepperPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	int PeterPepperWidth = m_pGameObject->GetComponent<RenderComponent>()->GetWidth();
	int PeterPepperHeight = m_pGameObject->GetComponent<RenderComponent>()->GetHeight();

	int offset = 15;

	if ((PeterPepperPos.x >= otherObjectPos.x - offset && PeterPepperPos.x + PeterPepperWidth <= otherObjectPos.x + otherObjectWidth) &&
		(PeterPepperPos.y + PeterPepperHeight + 10 >= otherObjectPos.y && PeterPepperPos.y + PeterPepperHeight <= otherObjectPos.y + otherObjectheight))
	{
		return true;
	}

	return false;
}


void dae::IngredientComponent::HandleCollision()
{
	auto nr = SceneManager::GetInstance().GetActiveSceneNr();
	auto objects = SceneManager::GetInstance().GetScene(nr)->GetObjects();

	for (const auto& object : objects)
	{
		if (object.get()->GetComponent<IngredientComponent>() != nullptr)
		{
			if (IsOnPlatform(object.get()) && object.get() != m_pGameObject)
			{
				if (object->GetComponent<IngredientComponent>()->IsOnTray())
				{
					m_isOnTray = true;
					m_canFall = false;
				}

				if (m_isOnTray == false)
				{
					if(m_canSwap)
					{
						const auto prevType = m_Type;
						const auto objType = object->GetComponent<IngredientComponent>()->GetType();
						m_Type = objType;
						object->GetComponent<IngredientComponent>()->SetType(prevType);
						object->GetComponent<IngredientComponent>()->ChooseTexture(prevType);
						ChooseTexture(objType);

						if (object->GetComponent<IngredientComponent>() != m_previousIngredient)
							if (m_pepper)
								m_pepper->GivePoints(50);

						m_previousIngredient = object->GetComponent<IngredientComponent>();


					}
					



				}



			}
		}

		if (object.get()->GetComponent<TrayComponent>() != nullptr)
		{
			if (IsOnPlatform(object.get()) && object.get())
			{
				m_isOnTray = true;
				m_canFall = false;
			}
		}

	}

}

void dae::IngredientComponent::Fall()
{
	if ((m_LeftCornerHit && m_CenterHit && m_RightCornerHit))
	{
		m_pTransform->SetPosition(static_cast<float>(m_pTransform->GetPosition().x),
			m_pTransform->GetPosition().y + m_fallSpeed * Time::GetDeltaTime(),
			0.0f);

		m_canFall = true;
	}



}
