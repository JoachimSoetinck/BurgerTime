#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"


using namespace dae;
dae::BaseComponent::BaseComponent()
{
}

dae::BaseComponent::~BaseComponent()
{

}

GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
