#ifndef FLAT_SHADED

	in vec3 vNormal;

	#ifdef USE_TANGENT

		in vec3 vTangent;
		in vec3 vBitangent;

	#endif

#endif