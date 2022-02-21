#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

namespace dae {
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(BaseComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void Render() const override;

	private:
		std::shared_ptr<TextComponent> m_Text;
		std::shared_ptr<TransformComponent> m_Transform;

		float m_AccumulatedTime = 0;
		std::string m_text;
	};
}



