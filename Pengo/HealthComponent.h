#pragma once
#include "Component.h"
#include "Subject.h"
#include "TextComponent.h"
namespace dae
{

	class HealthComponent : public Subject, public Component
	{
	public:
		HealthComponent(dae::GameObject* gameObject, int health, TextComponent* textComp);
		virtual ~HealthComponent() = default;
		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
		void TakeDamage(int damage);
		int GetHealth() const;
	private:
		TextComponent* m_pTextComponent = {};
		int m_Health;
	};
}

