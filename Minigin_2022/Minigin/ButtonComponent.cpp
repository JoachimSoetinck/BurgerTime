#include "MiniginPCH.h"
#include "ButtonComponent.h"

#include "Enums.h"
#include "Scene.h"
#include "SceneManager.h"

dae::ButtonComponent::ButtonComponent(std::shared_ptr<GameObject> object) :m_HoverColor{ 255,0,0 }
{
	m_pGameObject = object.get();
	m_Text = m_pGameObject->GetComponent<TextComponent>();
	m_Text->Update();
	m_Transform = m_pGameObject->GetComponent<TransformComponent>();
	SDL_QueryTexture(m_Text->GetTexture()->GetSDLTexture(), NULL, NULL, &m_width, &m_height);
	m_originalColor = m_Text->GetColor();
}

void dae::ButtonComponent::Render() const
{
}

void dae::ButtonComponent::Update()
{
	int x, y;
	Uint32 buttons{};
	buttons = SDL_GetMouseState(&x, &y);

	if (x >= m_Transform->GetPosition().x && x <= m_Transform->GetPosition().x + m_width &&
		y >= m_Transform->GetPosition().y && y <= m_Transform->GetPosition().y + m_height)
	{
		m_Text->SetColor(m_HoverColor);
	}
	else
	{
		m_Text->SetColor(m_originalColor);
	}






}
