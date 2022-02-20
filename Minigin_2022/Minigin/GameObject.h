#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& type = typeid(T);
			//checking all components 
			for (auto component : m_Components)
			{
				//if there is a component and
				if (typeid(*component) == type)
				{
					return std::dynamic_pointer_cast<T>(component);
				}
			}

			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;



		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	};
}
