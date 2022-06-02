#pragma once
#include "BaseComponent.h"
#include "Enums.h"
#include "TextComponent.h"
#include "SDL_events.h"

namespace dae
{
;
	class ButtonComponent final: public BaseComponent
	{
	public:
		ButtonComponent(std::shared_ptr<GameObject> object);
		~ButtonComponent() = default;
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;
		void Render() const override;
		void Update() override;

	private:
		std::shared_ptr<TextComponent> m_Text;
		std::shared_ptr<TransformComponent> m_Transform;
		int m_width;
		int m_height;

		

		SDL_Color m_originalColor{};
		SDL_Color m_HoverColor{};
		 
	};
}


