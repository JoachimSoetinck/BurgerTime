#pragma once
#include "Subject.h"
#include "TransformComponent.h"

namespace dae
{
	class RigidBodyComponent : public dae::BaseComponent, public dae::Subject
	{
	public:
		RigidBodyComponent(std::shared_ptr<GameObject> object);
		~RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent& other) = delete;
		RigidBodyComponent(RigidBodyComponent&& other) noexcept = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&& other) noexcept = delete;

		virtual void Update() override;
		void Render() const override;
		void SetDirection(glm::vec2 direction);

	private:
		std::shared_ptr<TransformComponent> m_TransformComponent;


		glm::vec2 m_direction{};
	};

}
