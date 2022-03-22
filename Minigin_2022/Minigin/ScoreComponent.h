#include "BaseComponent.h"
#include "PeterPepperComponent.h"
#include "PlayerObserver.h"

namespace dae
{
	class TextComponent;

	class ScoreComponent : public BaseComponent
	{
	public:
		ScoreComponent(std::shared_ptr<GameObject> object);
		~ScoreComponent();

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		void SetTextLocation(glm::vec3 location);
		void Update() override;
		void Render() const override;

		void SetScoreText();
	private:

		std::shared_ptr<TextComponent> m_pTextComponent = nullptr;
		std::shared_ptr<PeterPepperComponent> m_pPeter = nullptr;

	};

}