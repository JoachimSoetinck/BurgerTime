#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include <memory.h>

dae::RenderComponent::RenderComponent(const std::string& file, std::shared_ptr<GameObject> object, bool isVisible): m_isVisible{isVisible}
{
	m_pGameObject = object.get();

	m_TransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	SetTexture(file);
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if(m_isVisible)
	{
		const glm::vec3 pos = m_TransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
		
}

void dae::RenderComponent::SetTexture(const std::string& file)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(file);

	//setting Width and height
	if (m_Texture != nullptr)
	{
		Uint32 format;
		int access;

		SDL_QueryTexture(m_Texture.get()->GetSDLTexture(), &format, &access, &m_Width, &m_Height);
	}
	
}

int dae::RenderComponent::GetWidth() const
{
	return m_Width;
}

int dae::RenderComponent::GetHeight() const
{
	return m_Height;
}
