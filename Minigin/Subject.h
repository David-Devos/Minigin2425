#pragma once
#include <vector>
#include "Observer.h"
#include "Event.h"
namespace dae
{
	class Subject
	{
	public:
		virtual ~Subject() = default;
		virtual void AddObserver(Observer* observer) ;
		virtual void RemoveObserver(Observer* observer) ;
	protected:
		virtual void Notify(const Event& event, GameObject* gameObject) ;
	private:
		std::vector<Observer*> m_Observers;
	};
}
