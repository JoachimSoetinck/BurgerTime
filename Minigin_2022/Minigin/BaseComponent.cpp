#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"


using namespace dae;
dae::BaseComponent::BaseComponent()
{
}

dae::BaseComponent::~BaseComponent()
{
	delete m_pGameObject;
	m_pGameObject = nullptr;
}



GameObject * dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
