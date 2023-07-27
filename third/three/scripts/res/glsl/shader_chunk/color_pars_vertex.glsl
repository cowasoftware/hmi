#if defined( USE_COLOR_ALPHA )

	out vec4 vColor;

#elif defined( USE_COLOR ) || defined( USE_INSTANCING_COLOR )

	out vec3 vColor;

#endif