#pragma once
#include <glm.hpp>
#include <map>
#include "Component.h"
#include "Command.h"
namespace dae
{
	class GridComponent;
	class PushableComponent : public Component
	{
	public:
		PushableComponent(GameObject* gameObject, GridComponent* gridComp, glm::vec2 position);
		void Update(float) override;
		void Render() const override;
		void BindCommand(const std::tuple<float, float>&, std::unique_ptr<Command> command);
		void UnbindCommand(const std::tuple<float, float>&);
		void GetInteracted(const glm::vec2& direction);
		void HitWall(glm::vec2 newPos);
	private:
		std::map<std::tuple<float, float>, std::unique_ptr<Command>> m_Commands;
		GridComponent* m_pGridComponent = nullptr;
		glm::vec2 m_PushDirection = { 0.0f, 0.0f };
		glm::vec2 m_Position = { 0.0f, 0.0f };

	};
}

