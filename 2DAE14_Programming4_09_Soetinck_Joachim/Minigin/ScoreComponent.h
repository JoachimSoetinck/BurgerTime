#include "BaseComponent.h"
#include "PeterPepperComponent.h"


namespace dae
{
	class TextComponent;

	class ScoreComponent : public BaseComponent, public Observer
	{
	public:
		ScoreComponent(std::shared_ptr<GameObject> object, SDL_Color color);
		~ScoreComponent();

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		void OnNotify(const GameObject& pGameObject, Event event) override;
		void SetTextLocation(glm::vec3 location);
		void Update() override;
		void Render() const override;

		void SetScoreText();
	private:

		std::shared_ptr<TextComponent> m_pTextComponent = nullptr;
		std::shared_ptr<PeterPepperComponent> m_pPeter = nullptr;

	};

}