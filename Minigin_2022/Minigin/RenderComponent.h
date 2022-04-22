#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "GameObject.h"
#include <memory.h>

#include "TransformComponent.h"


namespace dae
{
	
	class RenderComponent final : public BaseComponent
	{
	public:
		//Render Needs file to load
		RenderComponent(const std::string& file,  std::shared_ptr<GameObject> object);


		
	   virtual ~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& file);

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<TransformComponent> m_TransformComponent;

	};
}


