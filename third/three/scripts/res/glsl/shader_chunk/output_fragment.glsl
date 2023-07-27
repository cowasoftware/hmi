#ifdef OPAQUE
diffuseColor.a = 1.0;
#endif

fragColor = vec4( outgoingLight, diffuseColor.a );