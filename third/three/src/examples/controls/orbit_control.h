#pragma once

#include "./control.h"
#include "../../math/vector.h"
#include "../../math/matrix.h"

class OrbitControl : public Control
{
public:
	OrbitControl();
	virtual ~OrbitControl();

public:
	void Update(float delta) override;

private:
	bool enabled_;

	vec3 target_;

	float min_distance;
	float max_distance; // How far you can zoom in and out ( OrthographicCamera only )

	float min_zoom;
	float max_zoom; // How far you can orbit vertically, upper and lower limits.

	// Range is 0 to Math.PI radians.
	float min_polar_angle;
	float max_polar_angle;

	// How far you can orbit horizontally, upper and lower limits.
	// If set, the interval [ min, max ] must be a sub-interval of [ - 2 PI, 2 PI ], with ( max - min < 2 PI )
	float min_azimuth_angle;
	float max_azimuth_angle;

	// Set to true to enable damping (inertia)
	// If damping is enabled, you must call controls.update() in your animation loop
	bool enable_damping;
	float damping_factor; // This option actually enables dollying in and out; left as "zoom" for backwards compatibility.

	// Set to false to disable zooming
	float enable_zoom;
	float zoom_speed;

	// Set to false to disable rotating
	bool enable_rotate;
	float rotate_speed;

	// Set to false to disable panning
	bool enablePan;
	float pan_speed;
	bool screen_space_panning; // if false, pan orthogonal to world-space direction camera.up

	float key_pan_speed; // pixels moved per arrow key push

	// Set to true to automatically rotate around the target
	// If auto-rotate is enabled, you must call controls.update() in your animation loop
	bool auto_rotate;
	float auto_rotate_speed; // 30 seconds per orbit when fps is 60
	// The four arrow keys

	// this.keys = {
	// 	LEFT : 'ArrowLeft',
	// 	UP : 'ArrowUp',
	// 	RIGHT : 'ArrowRight',
	// 	BOTTOM : 'ArrowDown'
	// }; // Mouse buttons

	// this.mouseButtons = {
	// 	LEFT : THREE.MOUSE.ROTATE,
	// 	MIDDLE : THREE.MOUSE.DOLLY,
	// 	RIGHT : THREE.MOUSE.PAN
	// }; // Touch fingers

	// this.touches = {
	// 	ONE : THREE.TOUCH.ROTATE,
	// 	TWO : THREE.TOUCH.DOLLY_PAN
	// }; // for reset

	vec3 target0;
	vec3 position0;
	float zoom0; // the target DOM element for key events
};