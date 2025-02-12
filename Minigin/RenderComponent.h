#pragma once
#include "Component.h"

namespace dae
{
	class RenderComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void Render(Texture2D* texture) const;
		void Render() const;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D>* texture);


		RenderComponent(std::shared_ptr< GameObject> gameObject);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};

}
