#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
# include <vector>
# include <memory>



namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update() ;
		void Render() const ;

		GameObject();
	    ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			const type_info& type = typeid(T);
			//checking all components 
			for (auto component : m_Components)
			{
				//if there is a component and
				if (typeid(*component) == type)
				{
					return std::static_pointer_cast<T>(component);
				}
			}

			return nullptr;
		}

		void AddChild(std::shared_ptr<GameObject> child);
		void RemoveChild(std::shared_ptr<GameObject> child);

		GameObject* GetParent() const;
		GameObject* GetChild(int i) const
		{
			if(m_Children.size() > 0)return  m_Children[i].get();
			return nullptr;
		}  ;
		void SetParent(GameObject* parent) ;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
		GameObject* m_Parent = nullptr;
		
		
		std::vector<std::shared_ptr<GameObject>> m_Children;
	};
}
