#include <algorithm>
#include <iostream>

#include "./event_dispatcher.h"

Event::Event()
	: target_(nullptr)
{
}

Event::Event(std::string const& type)
	: type_(type),
	target_(nullptr)
{
}

Event::~Event()
{
}

EventListener::EventListener()
{
}

EventListener::EventListener(std::function<void(Event const&)> callback)
	: callback_(std::move(callback))
{
}

EventListener::~EventListener()
{
}

void EventListener::Handle(Event const& event)
{
	if (callback_)
	{
		callback_(event);
	}
}

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::AddEventListener(std::string const& type, EventListener& listener)
{
	if (type.empty())
	{
		return;
	}

	auto iter = listeners_.find(type);

	if (iter == listeners_.end())
	{
		listeners_[type] = std::vector<EventListener*>{ &listener };
	}
	else if (std::find(iter->second.begin(), iter->second.end(), &listener) == iter->second.end())
	{
		iter->second.push_back(&listener);
	}
}

bool EventDispatcher::HasEventListener(std::string const& type, EventListener& listener)
{
	if (type.empty())
	{
		return false;
	}

	auto iter = listeners_.find(type);

	if (iter == listeners_.end())
	{
		return false;
	}
	else if (std::find(iter->second.begin(), iter->second.end(), &listener) == iter->second.end())
	{
		return false;
	}

	return true;
}

void EventDispatcher::RemoveEventLister(std::string const& type, EventListener& listener)
{
	if (type.empty())
	{
		return;
	}

	auto iter = listeners_.find(type);

	if (iter != listeners_.end())
	{
		iter->second.erase(std::find(iter->second.begin(), iter->second.end(), &listener));
	}
}

void EventDispatcher::DispatchEvent(Event const& event)
{
	if (event.GetType().empty())
	{
		return;
	}

	auto iter = listeners_.find(event.GetType());

	if (iter != listeners_.end())
	{
		event.target_ = this;

		for (auto listener : iter->second)
		{
			listener->Handle(event);
		}

		event.target_ = nullptr;
	}
}
