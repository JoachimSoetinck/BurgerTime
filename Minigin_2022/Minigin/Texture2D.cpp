#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::Texture2D::SetRect(const SDL_Rect& newRect)
{
	m_rect = newRect;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
	
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);
	m_rect.w = m_Width;
	m_rect.h = m_Height;
}
