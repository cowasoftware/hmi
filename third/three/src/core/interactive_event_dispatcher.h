#pragma once

#include "./event_dispatcher.h"

enum class InteractiveEventType
{
	INVALID = 0,
	MOUSE_DOWN,
	MOUSE_MOVE,
	MOUSE_UP,
	KEY_DOWN,
	KEY_UP,
	WHEEL,
};

enum class MouseButton
{
	NONE = 0,
	LEFT = 1 << 0,
	MIDDLE = 1 << 1,
	RIGHT = 1 << 2,
};

enum class Key
{
	NONE = 0,
	LEFT,
	RIGHT,
	DOWN,
	UP,
	SHIFT,
	CTRL,
	ALT,
	PLUS,
	MINUS,
	NUM0 = 48,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	A = 97,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

};

enum class KeyModifier
{
	NONE = 0,
	CTRL = 1 << 0,
	SHIFT = 1 << 1,
	ALT = 1 << 2,
};

class InteractiveEvent : public Event
{
protected:
	InteractiveEvent(std::string const& type);

public:
	bool HasModifier(KeyModifier modifier) const { return (modifiers & ((uint32_t)modifier)) != 0; }

public:
	int width;
	int height;
	uint32_t modifiers;
};

class MouseDownEvent : public InteractiveEvent
{
public:
	MouseDownEvent();

public:
	int x;
	int y;
	MouseButton button;
};

class MouseMoveEvent : public InteractiveEvent
{
public:
	MouseMoveEvent();

public:
	int x;
	int y;
	MouseButton button;
};

class MouseUpEvent : public InteractiveEvent
{
public:
	MouseUpEvent();

public:
	int x;
	int y;
	MouseButton button;
};

class KeyUpEvent : public InteractiveEvent
{
public:
	KeyUpEvent();

public:
	Key key;
};

class KeyDownEvent : public InteractiveEvent
{
public:
	KeyDownEvent();

public:
	Key key;
};

class WheelEvent : public InteractiveEvent
{
public:
	WheelEvent();

public:
	int x;
	int y;
	float angle;
};

class InteractiveEventDispatcher final : public EventDispatcher
{
public:
	void AddEventListener(InteractiveEventType type, EventListener& listener);
	bool HasEventListener(InteractiveEventType type, EventListener& listener);
	void RemoveEventLister(InteractiveEventType type, EventListener& listener);
};
