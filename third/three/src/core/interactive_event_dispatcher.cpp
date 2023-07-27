#include <iostream>

#include "./interactive_event_dispatcher.h"

static const std::string INVALID_TYPE = "";
static const std::string MOUSE_UP_TYPE = "mouseup";
static const std::string MOUSE_DOWN_TYPE = "mousedown";
static const std::string MOUSE_MOVE_TYPE = "mousemove";
static const std::string KEY_UP_TYPE = "keyup";
static const std::string KEY_DOWN_TYPE = "keydown";
static const std::string WHEEL_TYPE = "wheel";

static std::string const& convert(InteractiveEventType type)
{
	switch (type)
	{
	case InteractiveEventType::MOUSE_DOWN:
		return MOUSE_DOWN_TYPE;
	case InteractiveEventType::MOUSE_MOVE:
		return MOUSE_MOVE_TYPE;
	case InteractiveEventType::MOUSE_UP:
		return MOUSE_UP_TYPE;
	case InteractiveEventType::KEY_DOWN:
		return KEY_DOWN_TYPE;
	case InteractiveEventType::KEY_UP:
		return KEY_UP_TYPE;
	case InteractiveEventType::WHEEL:
		return WHEEL_TYPE;
	default:
		std::cerr << "unsupport interactive event: " << (uint32_t)type << std::endl;
		return INVALID_TYPE;
	}
}

InteractiveEvent::InteractiveEvent(std::string const& type) : Event(type),
width(0),
height(0),
modifiers(0)
{
}

MouseDownEvent::MouseDownEvent() : InteractiveEvent(MOUSE_DOWN_TYPE),
x(0),
y(0),
button(MouseButton::NONE)
{
}

MouseMoveEvent::MouseMoveEvent() : InteractiveEvent(MOUSE_MOVE_TYPE),
x(0),
y(0),
button(MouseButton::NONE)
{
}

MouseUpEvent::MouseUpEvent() : InteractiveEvent(MOUSE_UP_TYPE),
x(0),
y(0),
button(MouseButton::NONE)
{
}

KeyDownEvent::KeyDownEvent() : InteractiveEvent(KEY_DOWN_TYPE),
key(Key::NONE)
{
}

KeyUpEvent::KeyUpEvent() : InteractiveEvent(KEY_UP_TYPE),
key(Key::NONE)
{
}

WheelEvent::WheelEvent() : InteractiveEvent(WHEEL_TYPE),
x(0),
y(0),
angle(0.0f)
{
}

void InteractiveEventDispatcher::AddEventListener(InteractiveEventType type, EventListener& listener)
{
	EventDispatcher::AddEventListener(convert(type), listener);
}

bool InteractiveEventDispatcher::HasEventListener(InteractiveEventType type, EventListener& listener)
{
	return EventDispatcher::HasEventListener(convert(type), listener);
}

void InteractiveEventDispatcher::RemoveEventLister(InteractiveEventType type, EventListener& listener)
{
	EventDispatcher::RemoveEventLister(convert(type), listener);
}
