#pragma once
#include "BaseComponent.h"

#include "RenderComponent.h"

namespace dae
{
	class PeterPepperComponent;
	class SaltComponent: public BaseComponent
	{
	public:
		SaltComponent(std::shared_ptr<GameObject> object, std::shared_ptr<PeterPepperComponent> pp);
		~SaltComponent() = default;
		SaltComponent(const SaltComponent& other) = delete;
		SaltComponent(SaltComponent&& other) noexcept = delete;
		SaltComponent& operator=(const SaltComponent& other) = delete;
		SaltComponent& operator=(SaltComponent&& other) noexcept = delete;

		void Update() override;

		void Render() const override;

		PeterPepperComponent* GetPeterPepper() const;

		bool GetVisibility() const { return m_isActive; }
		
	private:
		
		std::shared_ptr<RenderComponent> m_RenderComponent{};
		std::shared_ptr<TransformComponent> m_TransformComponent{};
		std::shared_ptr<PeterPepperComponent> m_peterPepper{};
		GameObject* m_Parent{};

		bool m_isActive{false};

		bool IsOverlapping(GameObject* object);

		void HandleCollision();
	};
}


