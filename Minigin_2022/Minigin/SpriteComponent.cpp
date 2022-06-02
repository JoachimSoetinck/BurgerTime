#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Timer.h"

dae::SpriteComponent::SpriteComponent(std::shared_ptr<GameObject> object, std::shared_ptr<RenderComponent> render, int rows, const std::string& file)
	:m_rows{ rows },
	m_file{ file }
{
	m_pGameObject = object.get();
	m_pRenderComponent = render.get();

	m_SrRectWidth = render->GetWidth();
	m_SrcRectHeight = render->GetHeight();


}

void dae::SpriteComponent::Update()
{
	if (m_isActive)
	{
		m_elapsedSec += Time::GetDeltaTime();
		

		if (m_elapsedSec >= m_interval)
		{
			++m_Index;
			m_elapsedSec = 0.0f;
			if (m_Index == m_rows)
			{
				m_Index = 0;
			}

			SDL_Rect srcRect;
			srcRect.w = m_SrRectWidth;
			srcRect.h = m_SrcRectHeight;
			srcRect.x = srcRect.w * m_Index;
			srcRect.y = 0;
			m_pRenderComponent->SetTexture(m_file);
			m_pRenderComponent->SetRect(srcRect);

		}
	}
}

void dae::SpriteComponent::Render() const
{
}
