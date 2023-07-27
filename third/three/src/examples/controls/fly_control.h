#pragma once

#include "../../core/event_dispatcher.h"
#include "../../cameras/camera.h"
#include "./control.h"

namespace three
{
	class Camera;
}

using namespace three;

class FlyControl : public Control
{
public:
	FlyControl(InteractiveEventDispatcher& dispatcher, Camera& camera);
	virtual ~FlyControl();

public:
	void Enable(bool enabled) { enabled_ = enabled; };
	void SetDragToLook(bool enabled) { drag_to_look_ = enabled; }
	void SetRollSpeed(float speed) { roll_speed_ = speed; };
	void SetMovementSpeed(float speed) { movement_speed_ = speed; };

public:
	void Update(float delta) override;

private:
	void UpdateMovement();
	void UpdateRotation();

private:
	bool enabled_;
	bool auto_forward_;
	bool drag_to_look_;
	float mouse_status_;
	float up_state_;
	float down_state_;
	float left_state_;
	float right_state_;
	float forward_state_;
	float back_state_;
	float pitch_up_state_;
	float pitch_down_state_;
	float yaw_left_state_;
	float yaw_right_state_;
	float roll_left_state_;
	float roll_right_state_;
	float movement_speed_;
	float movement_speed_multiplier_;
	float roll_speed_;

	quat last_quat;
	quat tmp_quat;
	vec3 last_position;
	vec3 movement_;
	vec3 rotation_;
	Camera& camera_;
	InteractiveEventDispatcher& dispatcher_;
	EventListener keydown_listener_;
	EventListener keyup_listener_;
	EventListener mousedown_listener_;
	EventListener mousemove_listener_;
	EventListener mouseup_listener_;
};
