#pragma once

namespace dae {
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;

		GameObject* GetGameObject() const;

	private:
		friend class GameObject;
		//every component needs an Object to attach to
		GameObject* m_pGameObject{};
	};

}



