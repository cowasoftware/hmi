#ifndef FLAT_SHADED

	out vec3 vNormal;

	#ifdef USE_TANGENT

		out vec3 vTangent;
		out vec3 vBitangent;

	#endif

#endif