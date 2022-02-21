#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

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

		void AddChild(std::shared_ptr<GameObject> child);
		void RemoveChild(std::shared_ptr<GameObject> child);

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		
		std::vector<std::shared_ptr<GameObject>> m_Children;
	};
}
