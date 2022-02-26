#pragma once
#include "BaseComponent.h"

namespace dae {
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		TransformComponent(const glm::vec3& pos);
		virtual ~TransformComponent() override = default;

		virtual void Update() override;
		virtual void Render() const override;

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& newPos);

	private:
		glm::vec3 m_Position;
	};

}


