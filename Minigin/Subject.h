#pragma once
#include <vector>
#include "Observer.h"
namespace dae
{
	struct BaseEvent;
	class Subject
	{
	public:
		virtual ~Subject() = default;
		virtual void AddObserver(Observer* observer) ;
		virtual void RemoveObserver(Observer* observer) ;
	protected:
		virtual void Notify(const BaseEvent& event, GameObject* gameObject) ;
	private:
		std::vector<Observer*> m_Observers;
	};
}
