#pragma once
#include "BaseComponent.h"
#include "PeterPepperComponent.h"
#include "PlayerObserver.h"

namespace dae
{
	class DieObserver;
	class TextComponent;

	class LivesComponent : public BaseComponent
	{
	public:
		LivesComponent( std::shared_ptr<GameObject> object);
		~LivesComponent();

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) noexcept = delete;


		void Update() override;
		void Render() const override;
		

	private:

		std::shared_ptr<TextComponent> m_pTextComponent = nullptr;
		std::shared_ptr<PeterPepperComponent> m_pPeter = nullptr;
		PlayerObserver* m_pPlayerObserver = nullptr;

	};

}

