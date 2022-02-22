#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae {

	class TextComponent final: public  BaseComponent
	{
	public:
		TextComponent();
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent & other) = delete;
		TextComponent(TextComponent && other) noexcept = delete;
		TextComponent& operator=(const TextComponent & other) = delete;
		TextComponent& operator=(TextComponent && other) noexcept = delete;

		void Update() override;
		void Render() const override;

		void SetText(const std::string & text);
		void SetFont(std::shared_ptr<Font> font);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color;
		std::shared_ptr<Texture2D> m_TextTexture;

	};
}

