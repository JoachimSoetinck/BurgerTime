#include "MiniginPCH.h"
#include "LadderComponent.h"

dae::LadderComponent::LadderComponent(std::shared_ptr<GameObject> object)
{
	m_pGameObject = object.get();
}

void dae::LadderComponent::Update()
{
}

void dae::LadderComponent::Render() const
{
}
