#include "../../core/interactive_event_dispatcher.h"
#include "./fly_control.h"
#include <glm/gtx/quaternion.hpp>

static const Event change_event("change");

FlyControl::FlyControl(InteractiveEventDispatcher& dispatcher, Camera& camera)
	: dispatcher_(dispatcher),
	camera_(camera),
	enabled_(false),
	drag_to_look_(false),
	auto_forward_(false),
	mouse_status_(0.0f),
	up_state_(0.0f),
	down_state_(0.0f),
	left_state_(0.0f),
	right_state_(0.0f),
	forward_state_(0.0f),
	back_state_(0.0f),
	pitch_up_state_(0.0f),
	pitch_down_state_(0.0f),
	yaw_left_state_(0.0f),
	yaw_right_state_(0.0f),
	roll_left_state_(0.0f),
	roll_right_state_(0.0f),
	movement_speed_(0.0f),
	movement_speed_multiplier_(0.0f),
	roll_speed_(0.0f),
	last_quat(0.0f, 0.0f, 0.0f, 0.0f),
	tmp_quat(0.0f, 0.0f, 0.0f, 0.0f),
	last_position(0.0f, 0.0f, 0.0f),
	movement_(0.0f, 0.0f, 0.0f),
	rotation_(0.0f, 0.0f, 0.0f),
	keydown_listener_(nullptr),
	keyup_listener_(nullptr),
	mousedown_listener_(nullptr),
	mousemove_listener_(nullptr),
	mouseup_listener_(nullptr)

{

	movement_speed_ = 1.0f;
	roll_speed_ = 0.005f;

	auto keydown_call = [this](Event const& event)
	{
		if (!this->enabled_)
		{
			return;
		}

		auto e = static_cast<KeyDownEvent const&>(event);
		if (e.HasModifier(KeyModifier::ALT))
		{
			return;
		}
		switch (e.key)
		{
		case Key::SHIFT:
			this->movement_speed_multiplier_ = 0.1f;
			break;
		case Key::W:
			this->forward_state_ = 1.0f;
			break;
		case Key::S:
			this->back_state_ = 1.0f;
			break;
		case Key::A:
			this->left_state_ = 1.0f;
			break;
		case Key::D:
			this->right_state_ = 1.0f;
			break;
		case Key::R:
			this->up_state_ = 1.0f;
			break;
		case Key::F:
			this->down_state_ = 1.0f;
			break;
		case Key::UP:
			this->pitch_up_state_ = 1.0f;
			break;
		case Key::DOWN:
			this->pitch_down_state_ = 1.0f;
			break;
		case Key::LEFT:
			this->yaw_left_state_ = 1.0f;
			break;
		case Key::RIGHT:
			this->yaw_right_state_ = 1.0f;
			break;
		case Key::Q:
			this->roll_left_state_ = 1.0f;
			break;
		case Key::E:
			this->roll_right_state_ = 1.0f;
			break;
		}
		this->UpdateMovement();
		this->UpdateRotation();
	};

	auto keyup_call = [&](Event const& event)
	{
		if (!this->enabled_)
		{
			return;
		}

		auto e = static_cast<KeyUpEvent const&>(event);
		if (e.HasModifier(KeyModifier::ALT))
		{
			return;
		}
		switch (e.key)
		{
		case Key::SHIFT:
			this->movement_speed_multiplier_ = 1.0f;
			break;
		case Key::W:
			this->forward_state_ = 0.0f;
			break;
		case Key::S:
			this->back_state_ = 0.0f;
			break;
		case Key::A:
			this->left_state_ = 0.0f;
			break;
		case Key::D:
			this->right_state_ = 0.0f;
			break;
		case Key::R:
			this->up_state_ = 0.0f;
			break;
		case Key::F:
			this->down_state_ = 0.0f;
			break;
		case Key::UP:
			this->pitch_up_state_ = 0.0f;
			break;
		case Key::DOWN:
			this->pitch_down_state_ = 0.0f;
			break;
		case Key::LEFT:
			this->yaw_left_state_ = 0.0f;
			break;
		case Key::RIGHT:
			this->yaw_right_state_ = 0.0f;
			break;
		case Key::Q:
			this->roll_left_state_ = 0.0f;
			break;
		case Key::E:
			this->roll_right_state_ = 0.0f;
			break;
		}

		this->UpdateMovement();
		this->UpdateRotation();
	};

	auto mousedown_call = [&](Event const& event)
	{
		if (!this->enabled_)
		{
			return;
		}
		auto e = static_cast<MouseDownEvent const&>(event);

		if (this->drag_to_look_)
		{
			this->mouse_status_++;
		}
		else
		{
			switch (e.button)
			{
			case MouseButton::LEFT:
				this->forward_state_ = 1;
				break;
			case MouseButton::RIGHT:
				this->back_state_ = 1;
				break;
			}
			this->UpdateMovement();
		}
	};
	auto mousemove_call = [&](Event const& event)
	{
		if (!this->enabled_)
		{
			return;
		}

		auto e = static_cast<MouseMoveEvent const&>(event);

		if (!this->drag_to_look_ || this->mouse_status_ > 0)
		{
			auto halt_width = e.width != 0 ? e.width / 2.0f : 0.1f;
			auto halt_height = e.height != 0 ? e.height / 2.0f : 0.1f;

			this->yaw_left_state_ = -(e.x - halt_width) / halt_width;
			this->pitch_down_state_ = (e.y - halt_height) / halt_height;
			this->UpdateRotation();
		}
	};

	auto mouseup_call = [&](Event const& event)
	{
		if (!this->enabled_)
		{
			return;
		}

		auto e = static_cast<MouseUpEvent const&>(event);

		if (this->drag_to_look_)
		{
			this->mouse_status_--;
			this->yaw_left_state_ = this->pitch_down_state_ = 0;
		}
		else
		{
			switch (e.button)
			{
			case MouseButton::LEFT:
				this->forward_state_ = 0;
				break;
			case MouseButton::RIGHT:
				this->back_state_ = 0;
				break;
			}
			this->UpdateMovement();
		}

		this->UpdateRotation();
	};

	keydown_listener_.SetCallback(keydown_call);
	keyup_listener_.SetCallback(keyup_call);
	mousedown_listener_.SetCallback(mousedown_call);
	mousemove_listener_.SetCallback(mousemove_call);
	mouseup_listener_.SetCallback(mouseup_call);
	dispatcher_.AddEventListener(InteractiveEventType::KEY_DOWN, keydown_listener_);
	dispatcher_.AddEventListener(InteractiveEventType::KEY_UP, keyup_listener_);
	dispatcher_.AddEventListener(InteractiveEventType::MOUSE_DOWN, mousedown_listener_);
	dispatcher_.AddEventListener(InteractiveEventType::MOUSE_MOVE, mousemove_listener_);
	dispatcher_.AddEventListener(InteractiveEventType::MOUSE_UP, mouseup_listener_);

	UpdateMovement();
	UpdateRotation();
}

FlyControl::~FlyControl()
{
	dispatcher_.RemoveEventLister(InteractiveEventType::KEY_DOWN, keydown_listener_);
	dispatcher_.RemoveEventLister(InteractiveEventType::KEY_UP, keyup_listener_);
	dispatcher_.RemoveEventLister(InteractiveEventType::MOUSE_DOWN, mousedown_listener_);
	dispatcher_.RemoveEventLister(InteractiveEventType::MOUSE_MOVE, mousemove_listener_);
	dispatcher_.RemoveEventLister(InteractiveEventType::MOUSE_UP, mouseup_listener_);
}

void FlyControl::Update(float delta)
{
	float movement_multiplier = delta * movement_speed_;
	float rotate_multiplier = delta * roll_speed_;
	// std::cout << rotate_multiplier << ", " << delta << ", " << roll_speed_ <<std::endl;
	camera_.TranslateX(movement_.x * movement_multiplier);
	camera_.TranslateY(movement_.y * movement_multiplier);
	camera_.TranslateZ(movement_.z * movement_multiplier);
	tmp_quat.x = rotation_.x * rotate_multiplier;
	tmp_quat.y = rotation_.y * rotate_multiplier;
	tmp_quat.z = rotation_.z * rotate_multiplier;
	tmp_quat.w = 1.0f;
	tmp_quat = glm::normalize(tmp_quat);
	camera_.Rotate(tmp_quat);
}

void FlyControl::UpdateMovement()
{
	bool forward = forward_state_ || auto_forward_ && !back_state_ ? true : false;
	movement_.x = -left_state_ + right_state_;
	movement_.y = -down_state_ + up_state_;
	movement_.z = -forward_state_ + back_state_;
}

void FlyControl::UpdateRotation()
{
	rotation_.x = -pitch_down_state_ + pitch_up_state_;
	rotation_.y = -yaw_right_state_ + yaw_left_state_;
	rotation_.z = -roll_right_state_ + roll_left_state_;
}