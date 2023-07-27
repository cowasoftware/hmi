#pragma once

#include <string>
#include <functional>
#include <vector>
#include <list>
#include <map>

class Event;
class EventListener;
class EventDispatcher;

class Event
{
	friend class EventDispatcher;

public:
	Event();
	explicit Event(std::string const& type);
	virtual ~Event();

public:
	std::string const& GetType() const { return type_; }
	EventDispatcher* GetDispatcher() const { return target_; }

private:
	std::string type_;
	mutable EventDispatcher* target_;
};

class EventListener
{
public:
	EventListener();
	EventListener(std::function<void(Event const&)> callback);
	virtual ~EventListener();

public:
	void SetCallback(std::function<void(Event const&)> callback) { callback_ = std::move(callback); }
	std::function<void(Event const&)>& GetCallback() { return callback_; }

public:
	virtual void Handle(Event const& event);

private:
	std::function<void(Event const&)> callback_;
};

class EventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();

public:
	void AddEventListener(std::string const& type, EventListener& listener);
	bool HasEventListener(std::string const& type, EventListener& listener);
	void RemoveEventLister(std::string const& type, EventListener& listener);
	void DispatchEvent(Event const& event);

private:
	std::map<std::string, std::vector<EventListener*>> listeners_;
};