#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include <memory.h>

dae::RenderComponent::RenderComponent(const std::string& file, std::shared_ptr<GameObject> object)
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
		const glm::vec3 pos = m_TransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::RenderComponent::SetTexture(const std::string& file)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(file);
}
