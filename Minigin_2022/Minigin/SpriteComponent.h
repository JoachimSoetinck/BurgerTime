#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent;


	class SpriteComponent final : public dae::BaseComponent
	{
	public:
		 SpriteComponent(std::shared_ptr<GameObject> object, std::shared_ptr<RenderComponent> render, int amountOfAnimations, const std::string& spriteSheet);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent & other) = delete;
		SpriteComponent(SpriteComponent && other) = delete;
		SpriteComponent& operator=(const SpriteComponent & other) = delete;
		SpriteComponent& operator=(SpriteComponent && other) = delete;

		void Update() override;
		void Render() const override;

		

	private:
		
		RenderComponent* m_pRenderComponent;
		int m_rows;
		float m_interval = 0.4f;
		float m_elapsedSec = 0.0f;
		int m_Index = {0};
		int m_SrRectWidth, m_SrcRectHeight;

		std::string m_file;

		bool m_isActive;
	};
	
}


