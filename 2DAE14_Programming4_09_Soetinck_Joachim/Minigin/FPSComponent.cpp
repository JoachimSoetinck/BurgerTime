#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include <memory.h>

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> object)
{
	m_pGameObject = object.get();
	m_Text = m_pGameObject->GetComponent<TextComponent>();
}


void dae::FPSComponent::Update()
{
	m_AccumulatedTime += Time::GetDeltaTime();
	const float fps = 1.0f / Time::GetInstance().GetDeltaTime();
	if (m_AccumulatedTime >= 1.0f)
	{	
		m_text = std::to_string(int(fps)) + "FPS";
		m_Text->SetText(m_text);
		m_AccumulatedTime = 0;
	}

}

void dae::FPSComponent::Render() const
{

}
