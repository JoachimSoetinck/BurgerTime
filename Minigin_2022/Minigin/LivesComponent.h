#pragma once
#include "BaseComponent.h"
#include "PeterPepperComponent.h"


namespace dae
{
	class TextComponent;

	class LivesComponent : public BaseComponent, public Observer
	{
	public:
		LivesComponent(std::shared_ptr<GameObject> object, SDL_Color color);
		~LivesComponent();

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) noexcept = delete;

		void OnNotify(const GameObject& pGameObject, Event event) override;


		void Update() override;
		void Render() const override;
		void SetLives();

	private:

		std::shared_ptr<TextComponent> m_pTextComponent = nullptr;
		std::shared_ptr<PeterPepperComponent> m_pPeter = nullptr;
		SDL_Color m_color = SDL_Color{ 255,255,0 };

	};

}

