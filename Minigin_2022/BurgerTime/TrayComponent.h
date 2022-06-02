#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
	class TrayComponent: public BaseComponent
	{
	public:
		TrayComponent(std::shared_ptr<GameObject> object) { m_pGameObject = object.get(); }
		~TrayComponent() = default;
		TrayComponent(const TrayComponent& other) = delete;
		TrayComponent(TrayComponent&& other) noexcept = delete;
		TrayComponent& operator=(const TrayComponent& other) = delete;
		TrayComponent& operator=(TrayComponent&& other) noexcept = delete;
		void Update() override;
		void Render() const override;

	};
}


