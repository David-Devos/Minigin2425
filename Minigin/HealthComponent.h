#pragma once
#include "Component.h"
class HealthComponent : public dae::Component
{
public:
	HealthComponent(dae::GameObject* gameObject, int health);
	virtual ~HealthComponent() = default;
	//virtual void Update(float deltaTime) override;
	//virtual void Render() const override;
	void TakeDamage(int damage);
	int GetHealth() const;
private:
	int m_Health;
};

