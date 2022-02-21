#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include "TransformComponent.h"
#include "GameObject.h"

using namespace dae;
dae::TextComponent::TextComponent() : m_Text("")
, m_Font(nullptr)
, m_NeedsUpdate(true)
, m_Color{ 255,255,255 }
{
}
dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font):
	m_Text{text},
	m_Font{font},
	m_Color{ 255,255,255 },
	m_NeedsUpdate{true}
{

}

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color):
	m_Text{ text },
	m_Font{ font },
	m_Color{ color },
	m_NeedsUpdate{true}
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		//getting the Transform component out of the gameobjects
		const auto pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> font)
{
	m_Font = font;
}
