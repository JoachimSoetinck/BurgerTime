#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PlatformComponent final : public BaseComponent
	{
	public:
		PlatformComponent(std::shared_ptr<GameObject> object);

		~PlatformComponent() = default;
		PlatformComponent(const PlatformComponent& other) = delete;
		PlatformComponent(PlatformComponent&& other) = delete;
		PlatformComponent& operator=(const PlatformComponent& other) = delete;
		PlatformComponent& operator=(PlatformComponent&& other) = delete;

		void Update() override;
		void Render() const override;

	};
}
