#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include <memory.h>

dae::FPSComponent::FPSComponent()
{
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
	
}

void dae::FPSComponent::Update()
{
	m_AccumulatedTime += Time::GetDeltaTime();
	if (m_AccumulatedTime > 0.5f)
	{
		const float fps = 1 / Time::GetDeltaTime();
		m_text = std::to_string(int(fps)) + "FPS";
		m_pGameObject->GetComponent<TextComponent>()->SetText(m_text);
		m_AccumulatedTime = 0;
	}
		
}

void dae::FPSComponent::Render() const
{
	
}
