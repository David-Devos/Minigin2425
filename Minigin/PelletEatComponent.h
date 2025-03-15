#pragma once
#include "Component.h"
#include "Subject.h"
#include "TextComponent.h"
namespace dae
{

	class PelletEatComponent : public Subject, public Component
	{
	public:
		PelletEatComponent(dae::GameObject* gameObject, int health, TextComponent* textComp);
		virtual ~PelletEatComponent() = default;
		virtual void Update(float deltaTime) override;
		virtual void Render() const override;
		void EatPellet(int damage);
		int GetScore() const;
	private:
		TextComponent* m_pTextComponent = {};
		int m_Score;
	};
}


