#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent(const std::string& file)
{
	SetTexture(file);
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
		const auto pos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::RenderComponent::SetTexture(const std::string& file)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(file);
}
