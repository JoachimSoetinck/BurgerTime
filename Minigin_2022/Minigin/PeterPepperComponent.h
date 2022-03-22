#pragma once

#include "Subject.h"

namespace dae
{
	class PeterPepperComponent : public BaseComponent, Subject
	{

	public:
		PeterPepperComponent(std::shared_ptr<GameObject> object);
		virtual ~PeterPepperComponent() override;
		PeterPepperComponent(const PeterPepperComponent& other) = delete;
		PeterPepperComponent(PeterPepperComponent&& other) noexcept = delete;
		PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
		PeterPepperComponent& operator=(PeterPepperComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;

		int GetLives()const;
		int GetScore()const;

		void GivePoints();

		void LoseLive();
		

	private:
		int m_nrOfLives{ 3 };
		int m_score{ 0 };


	};
}


