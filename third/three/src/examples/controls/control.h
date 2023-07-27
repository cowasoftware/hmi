#pragma once

#include "../../core/event_dispatcher.h"

class Control : public EventDispatcher
{
public:
	Control() = default;
	virtual ~Control() = default;

public:
	virtual void Update(float delta) {};
};