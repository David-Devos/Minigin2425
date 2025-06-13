#include "PushableComponent.h"
#include "GridComponent.h"
namespace dae
{
	PushableComponent::PushableComponent(GameObject* gameObject, GridComponent* gridComp, glm::vec2 position)
		: Component(gameObject),
		m_pGridComponent(gridComp),
		m_PushDirection(glm::vec2{ 0.0f, 0.0f }),
		m_Position(position)
	{
		m_Commands = std::map<std::tuple<float, float>, std::unique_ptr<Command>>();
		m_pGridComponent->AddGridlockedGO(m_pGameObject, static_cast<int>(position.x), static_cast<int>(position.y), GridType::Block);
	}
	void PushableComponent::Update(float)
	{
		if (m_PushDirection != glm::vec2{ 0.0f, 0.0f })
		{
			if (!m_pGridComponent->IsFreeSpot(static_cast<int>(m_Position.x + m_PushDirection.x), static_cast<int>(m_Position.y + m_PushDirection.y)))
			{
				m_PushDirection = glm::vec2{ 0.0f, 0.0f };
				return;
			}
			auto it = m_Commands.find(std::make_tuple(m_PushDirection.x, m_PushDirection.y));
			if (it != m_Commands.end())
			{
				it->second->Execute();
			}
		}
	}
	void PushableComponent::Render() const
	{}
	void PushableComponent::BindCommand(const std::tuple<float, float>& direction, std::unique_ptr<Command> command)
	{
		if (m_Commands.find(direction) != m_Commands.end())
		{
			return;
		}
		m_Commands[direction] = std::move(command);
	}
	void PushableComponent::UnbindCommand(const std::tuple<float, float>& direction)
	{
		auto it = m_Commands.find(direction);
		if (it != m_Commands.end())
		{
			m_Commands.erase(it);
		}
	}
	void PushableComponent::GetInteracted(const glm::vec2& direction)
	{
		if (direction == glm::vec2{ 0.0f, 0.0f })
		{
			auto it = m_Commands.find(std::make_tuple(direction.x, direction.y));
			if (it != m_Commands.end())
			{
				it->second->Execute();
			}
		}
		m_PushDirection = direction;
		m_pGridComponent->BufferBlock(m_Position);
	}
	void PushableComponent::HitWall(glm::vec2 newPos)
	{
		m_Position = newPos;
		//m_Position.x = newPos.y; // ik zit zo diep in mn code, ik weet niet waarom dit plots invers is :(
		//m_Position.y = newPos.x; // ik weet enkel en alleen dat het nu werkt
		m_PushDirection = glm::vec2{ 0.0f, 0.0f };
	}
}