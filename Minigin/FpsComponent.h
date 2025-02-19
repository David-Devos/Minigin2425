#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "ResourceManager.h"

namespace dae
{
	class FpsComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override ;

		FpsComponent(TextComponent* textComponent, GameObject* gameObject);
		FpsComponent() = default;
		virtual ~FpsComponent();
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

	private:
		TextComponent* m_pTextComponent;
		float m_Fps;
	};

}


