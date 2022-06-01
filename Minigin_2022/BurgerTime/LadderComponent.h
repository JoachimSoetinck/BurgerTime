#pragma once
#include "BaseComponent.h"
namespace dae
{
	class LadderComponent final : public BaseComponent
	{
	public:
		LadderComponent(std::shared_ptr<GameObject> object);

		~LadderComponent() = default;
		LadderComponent(const LadderComponent& other) = delete;
		LadderComponent(LadderComponent&& other) = delete;
		LadderComponent& operator=(const LadderComponent& other) = delete;
		LadderComponent& operator=(LadderComponent&& other) = delete;

		void Update() override;
		void Render() const override;

	};
}

