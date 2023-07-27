#include "./shader_chunk.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
static const char *LIGHTS_LAMBERT_FRAGMENT = "LambertMaterial material;\n"
    "material.diffuseColor = diffuseColor.rgb;";
    
static const char *SPECULARMAP_FRAGMENT = "float specularStrength;\n"
    "#ifdef USE_SPECULARMAP\n"
    "	vec4 texelSpecular = texture2D( specularMap, vUv );\n"
    "	specularStrength = texelSpecular.r;\n"
    "#else\n"
    "	specularStrength = 1.0;\n"
    "#endif";
    
static const char *LIGHTS_PARS_BEGIN = "uniform bool receiveShadow;\n"
    "uniform vec3 ambientLightColor;\n"
    "uniform vec3 lightProbe[ 9 ];\n"
    "vec3 shGetIrradianceAt( in vec3 normal, in vec3 shCoefficients[ 9 ] ) {\n"
    "	float x = normal.x, y = normal.y, z = normal.z;\n"
    "	vec3 result = shCoefficients[ 0 ] * 0.886227;\n"
    "	result += shCoefficients[ 1 ] * 2.0 * 0.511664 * y;\n"
    "	result += shCoefficients[ 2 ] * 2.0 * 0.511664 * z;\n"
    "	result += shCoefficients[ 3 ] * 2.0 * 0.511664 * x;\n"
    "	result += shCoefficients[ 4 ] * 2.0 * 0.429043 * x * y;\n"
    "	result += shCoefficients[ 5 ] * 2.0 * 0.429043 * y * z;\n"
    "	result += shCoefficients[ 6 ] * ( 0.743125 * z * z - 0.247708 );\n"
    "	result += shCoefficients[ 7 ] * 2.0 * 0.429043 * x * z;\n"
    "	result += shCoefficients[ 8 ] * 0.429043 * ( x * x - y * y );\n"
    "	return result;\n"
    "}\n"
    "vec3 getLightProbeIrradiance( const in vec3 lightProbe[ 9 ], const in vec3 normal ) {\n"
    "	vec3 worldNormal = inverseTransformDirection( normal, viewMatrix );\n"
    "	vec3 irradiance = shGetIrradianceAt( worldNormal, lightProbe );\n"
    "	return irradiance;\n"
    "}\n"
    "vec3 getAmbientLightIrradiance( const in vec3 ambientLightColor ) {\n"
    "	vec3 irradiance = ambientLightColor;\n"
    "	return irradiance;\n"
    "}\n"
    "float getDistanceAttenuation( const in float lightDistance, const in float cutoffDistance, const in float decayExponent ) {\n"
    "	#if defined ( PHYSICALLY_CORRECT_LIGHTS )\n"
    "		float distanceFalloff = 1.0 / max( pow( lightDistance, decayExponent ), 0.01 );\n"
    "		if ( cutoffDistance > 0.0 ) {\n"
    "			distanceFalloff *= pow2( saturate( 1.0 - pow4( lightDistance / cutoffDistance ) ) );\n"
    "		}\n"
    "		return distanceFalloff;\n"
    "	#else\n"
    "		if ( cutoffDistance > 0.0 && decayExponent > 0.0 ) {\n"
    "			return pow( saturate( - lightDistance / cutoffDistance + 1.0 ), decayExponent );\n"
    "		}\n"
    "		return 1.0;\n"
    "	#endif\n"
    "}\n"
    "float getSpotAttenuation( const in float coneCosine, const in float penumbraCosine, const in float angleCosine ) {\n"
    "	return smoothstep( coneCosine, penumbraCosine, angleCosine );\n"
    "}\n"
    "#if NUM_DIR_LIGHTS > 0\n"
    "	struct DirectionalLight {\n"
    "		vec3 direction;\n"
    "		vec3 color;\n"
    "	};\n"
    "	uniform DirectionalLight directionalLights[ NUM_DIR_LIGHTS ];\n"
    "	void getDirectionalLightInfo( const in DirectionalLight directionalLight, const in GeometricContext geometry, out IncidentLight light ) {\n"
    "		light.color = directionalLight.color;\n"
    "		light.direction = directionalLight.direction;\n"
    "		light.visible = true;\n"
    "	}\n"
    "#endif\n"
    "#if NUM_POINT_LIGHTS > 0\n"
    "	struct PointLight {\n"
    "		vec3 position;\n"
    "		vec3 color;\n"
    "		float distance;\n"
    "		float decay;\n"
    "	};\n"
    "	uniform PointLight pointLights[ NUM_POINT_LIGHTS ];\n"
    "	void getPointLightInfo( const in PointLight pointLight, const in GeometricContext geometry, out IncidentLight light ) {\n"
    "		vec3 lVector = pointLight.position - geometry.position;\n"
    "		light.direction = normalize( lVector );\n"
    "		float lightDistance = length( lVector );\n"
    "		light.color = pointLight.color;\n"
    "		light.color *= getDistanceAttenuation( lightDistance, pointLight.distance, pointLight.decay );\n"
    "		light.visible = ( light.color != vec3( 0.0 ) );\n"
    "	}\n"
    "#endif\n"
    "#if NUM_SPOT_LIGHTS > 0\n"
    "	struct SpotLight {\n"
    "		vec3 position;\n"
    "		vec3 direction;\n"
    "		vec3 color;\n"
    "		float distance;\n"
    "		float decay;\n"
    "		float coneCos;\n"
    "		float penumbraCos;\n"
    "	};\n"
    "	uniform SpotLight spotLights[ NUM_SPOT_LIGHTS ];\n"
    "	void getSpotLightInfo( const in SpotLight spotLight, const in GeometricContext geometry, out IncidentLight light ) {\n"
    "		vec3 lVector = spotLight.position - geometry.position;\n"
    "		light.direction = normalize( lVector );\n"
    "		float angleCos = dot( light.direction, spotLight.direction );\n"
    "		float spotAttenuation = getSpotAttenuation( spotLight.coneCos, spotLight.penumbraCos, angleCos );\n"
    "		if ( spotAttenuation > 0.0 ) {\n"
    "			float lightDistance = length( lVector );\n"
    "			light.color = spotLight.color * spotAttenuation;\n"
    "			light.color *= getDistanceAttenuation( lightDistance, spotLight.distance, spotLight.decay );\n"
    "			light.visible = ( light.color != vec3( 0.0 ) );\n"
    "		} else {\n"
    "			light.color = vec3( 0.0 );\n"
    "			light.visible = false;\n"
    "		}\n"
    "	}\n"
    "#endif\n"
    "#if NUM_RECT_AREA_LIGHTS > 0\n"
    "	struct RectAreaLight {\n"
    "		vec3 color;\n"
    "		vec3 position;\n"
    "		vec3 halfWidth;\n"
    "		vec3 halfHeight;\n"
    "	};\n"
    "	uniform sampler2D ltc_1; // RGBA Float\n"
    "	uniform sampler2D ltc_2; // RGBA Float\n"
    "	uniform RectAreaLight rectAreaLights[ NUM_RECT_AREA_LIGHTS ];\n"
    "#endif\n"
    "#if NUM_HEMI_LIGHTS > 0\n"
    "	struct HemisphereLight {\n"
    "		vec3 direction;\n"
    "		vec3 skyColor;\n"
    "		vec3 groundColor;\n"
    "	};\n"
    "	uniform HemisphereLight hemisphereLights[ NUM_HEMI_LIGHTS ];\n"
    "	vec3 getHemisphereLightIrradiance( const in HemisphereLight hemiLight, const in vec3 normal ) {\n"
    "		float dotNL = dot( normal, hemiLight.direction );\n"
    "		float hemiDiffuseWeight = 0.5 * dotNL + 0.5;\n"
    "		vec3 irradiance = mix( hemiLight.groundColor, hemiLight.skyColor, hemiDiffuseWeight );\n"
    "		return irradiance;\n"
    "	}\n"
    "#endif";
    
static const char *BEGINNORMAL_VERTEX = "vec3 objectNormal = vec3( normal );\n"
    "#ifdef USE_TANGENT\n"
    "	vec3 objectTangent = vec3( tangent.xyz );\n"
    "#endif";
    
static const char *LIGHTS_PHONG_FRAGMENT = "BlinnPhongMaterial material;\n"
    "material.diffuseColor = diffuseColor.rgb;\n"
    "material.specularColor = specular;\n"
    "material.specularShininess = shininess;\n"
    "material.specularStrength = specularStrength;";
    
static const char *OUTPUT_FRAGMENT = "#ifdef OPAQUE\n"
    "diffuseColor.a = 1.0;\n"
    "#endif\n"
    "fragColor = vec4( outgoingLight, diffuseColor.a );";
    
static const char *BSDFS = "vec3 BRDF_Lambert( const in vec3 diffuseColor ) {\n"
    "	return RECIPROCAL_PI * diffuseColor;\n"
    "} // validated\n"
    "vec3 F_Schlick( const in vec3 f0, const in float f90, const in float dotVH ) {\n"
    "	float fresnel = exp2( ( - 5.55473 * dotVH - 6.98316 ) * dotVH );\n"
    "	return f0 * ( 1.0 - fresnel ) + ( f90 * fresnel );\n"
    "} // validated\n"
    "float F_Schlick( const in float f0, const in float f90, const in float dotVH ) {\n"
    "	float fresnel = exp2( ( - 5.55473 * dotVH - 6.98316 ) * dotVH );\n"
    "	return f0 * ( 1.0 - fresnel ) + ( f90 * fresnel );\n"
    "} // validated\n"
    "vec3 Schlick_to_F0( const in vec3 f, const in float f90, const in float dotVH ) {\n"
    "    float x = clamp( 1.0 - dotVH, 0.0, 1.0 );\n"
    "    float x2 = x * x;\n"
    "    float x5 = clamp( x * x2 * x2, 0.0, 0.9999 );\n"
    "    return ( f - vec3( f90 ) * x5 ) / ( 1.0 - x5 );\n"
    "}\n"
    "float V_GGX_SmithCorrelated( const in float alpha, const in float dotNL, const in float dotNV ) {\n"
    "	float a2 = pow2( alpha );\n"
    "	float gv = dotNL * sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNV ) );\n"
    "	float gl = dotNV * sqrt( a2 + ( 1.0 - a2 ) * pow2( dotNL ) );\n"
    "	return 0.5 / max( gv + gl, EPSILON );\n"
    "}\n"
    "float D_GGX( const in float alpha, const in float dotNH ) {\n"
    "	float a2 = pow2( alpha );\n"
    "	float denom = pow2( dotNH ) * ( a2 - 1.0 ) + 1.0; // avoid alpha = 0 with dotNH = 1\n"
    "	return RECIPROCAL_PI * a2 / pow2( denom );\n"
    "}\n"
    "vec3 BRDF_GGX( const in vec3 lightDir, const in vec3 viewDir, const in vec3 normal, const in vec3 f0, const in float f90, const in float roughness ) {\n"
    "	float alpha = pow2( roughness ); // UE4's roughness\n"
    "	vec3 halfDir = normalize( lightDir + viewDir );\n"
    "	float dotNL = saturate( dot( normal, lightDir ) );\n"
    "	float dotNV = saturate( dot( normal, viewDir ) );\n"
    "	float dotNH = saturate( dot( normal, halfDir ) );\n"
    "	float dotVH = saturate( dot( viewDir, halfDir ) );\n"
    "	vec3 F = F_Schlick( f0, f90, dotVH );\n"
    "	float V = V_GGX_SmithCorrelated( alpha, dotNL, dotNV );\n"
    "	float D = D_GGX( alpha, dotNH );\n"
    "	return F * ( V * D );\n"
    "}\n"
    "#ifdef USE_IRIDESCENCE\n"
    "	vec3 BRDF_GGX_Iridescence( const in vec3 lightDir, const in vec3 viewDir, const in vec3 normal, const in vec3 f0, const in float f90, const in float iridescence, const in vec3 iridescenceFresnel, const in float roughness ) {\n"
    "		float alpha = pow2( roughness ); // UE4's roughness\n"
    "		vec3 halfDir = normalize( lightDir + viewDir );\n"
    "		float dotNL = saturate( dot( normal, lightDir ) );\n"
    "		float dotNV = saturate( dot( normal, viewDir ) );\n"
    "		float dotNH = saturate( dot( normal, halfDir ) );\n"
    "		float dotVH = saturate( dot( viewDir, halfDir ) );\n"
    "		vec3 F = mix( F_Schlick( f0, f90, dotVH ), iridescenceFresnel, iridescence );\n"
    "		float V = V_GGX_SmithCorrelated( alpha, dotNL, dotNV );\n"
    "		float D = D_GGX( alpha, dotNH );\n"
    "		return F * ( V * D );\n"
    "	}\n"
    "#endif\n"
    "vec2 LTC_Uv( const in vec3 N, const in vec3 V, const in float roughness ) {\n"
    "	const float LUT_SIZE = 64.0;\n"
    "	const float LUT_SCALE = ( LUT_SIZE - 1.0 ) / LUT_SIZE;\n"
    "	const float LUT_BIAS = 0.5 / LUT_SIZE;\n"
    "	float dotNV = saturate( dot( N, V ) );\n"
    "	vec2 uv = vec2( roughness, sqrt( 1.0 - dotNV ) );\n"
    "	uv = uv * LUT_SCALE + LUT_BIAS;\n"
    "	return uv;\n"
    "}\n"
    "float LTC_ClippedSphereFormFactor( const in vec3 f ) {\n"
    "	float l = length( f );\n"
    "	return max( ( l * l + f.z ) / ( l + 1.0 ), 0.0 );\n"
    "}\n"
    "vec3 LTC_EdgeVectorFormFactor( const in vec3 v1, const in vec3 v2 ) {\n"
    "	float x = dot( v1, v2 );\n"
    "	float y = abs( x );\n"
    "	float a = 0.8543985 + ( 0.4965155 + 0.0145206 * y ) * y;\n"
    "	float b = 3.4175940 + ( 4.1616724 + y ) * y;\n"
    "	float v = a / b;\n"
    "	float theta_sintheta = ( x > 0.0 ) ? v : 0.5 * inversesqrt( max( 1.0 - x * x, 1e-7 ) ) - v;\n"
    "	return cross( v1, v2 ) * theta_sintheta;\n"
    "}\n"
    "vec3 LTC_Evaluate( const in vec3 N, const in vec3 V, const in vec3 P, const in mat3 mInv, const in vec3 rectCoords[ 4 ] ) {\n"
    "	vec3 v1 = rectCoords[ 1 ] - rectCoords[ 0 ];\n"
    "	vec3 v2 = rectCoords[ 3 ] - rectCoords[ 0 ];\n"
    "	vec3 lightNormal = cross( v1, v2 );\n"
    "	if( dot( lightNormal, P - rectCoords[ 0 ] ) < 0.0 ) return vec3( 0.0 );\n"
    "	vec3 T1, T2;\n"
    "	T1 = normalize( V - N * dot( V, N ) );\n"
    "	T2 = - cross( N, T1 ); // negated from paper; possibly due to a different handedness of world coordinate system\n"
    "	mat3 mat = mInv * transposeMat3( mat3( T1, T2, N ) );\n"
    "	vec3 coords[ 4 ];\n"
    "	coords[ 0 ] = mat * ( rectCoords[ 0 ] - P );\n"
    "	coords[ 1 ] = mat * ( rectCoords[ 1 ] - P );\n"
    "	coords[ 2 ] = mat * ( rectCoords[ 2 ] - P );\n"
    "	coords[ 3 ] = mat * ( rectCoords[ 3 ] - P );\n"
    "	coords[ 0 ] = normalize( coords[ 0 ] );\n"
    "	coords[ 1 ] = normalize( coords[ 1 ] );\n"
    "	coords[ 2 ] = normalize( coords[ 2 ] );\n"
    "	coords[ 3 ] = normalize( coords[ 3 ] );\n"
    "	vec3 vectorFormFactor = vec3( 0.0 );\n"
    "	vectorFormFactor += LTC_EdgeVectorFormFactor( coords[ 0 ], coords[ 1 ] );\n"
    "	vectorFormFactor += LTC_EdgeVectorFormFactor( coords[ 1 ], coords[ 2 ] );\n"
    "	vectorFormFactor += LTC_EdgeVectorFormFactor( coords[ 2 ], coords[ 3 ] );\n"
    "	vectorFormFactor += LTC_EdgeVectorFormFactor( coords[ 3 ], coords[ 0 ] );\n"
    "	float result = LTC_ClippedSphereFormFactor( vectorFormFactor );\n"
    "/*\n"
    "	float len = length( vectorFormFactor );\n"
    "	float z = vectorFormFactor.z / len;\n"
    "	const float LUT_SIZE = 64.0;\n"
    "	const float LUT_SCALE = ( LUT_SIZE - 1.0 ) / LUT_SIZE;\n"
    "	const float LUT_BIAS = 0.5 / LUT_SIZE;\n"
    "	vec2 uv = vec2( z * 0.5 + 0.5, len );\n"
    "	uv = uv * LUT_SCALE + LUT_BIAS;\n"
    "	float scale = texture2D( ltc_2, uv ).w;\n"
    "	float result = len * scale;\n"
    "*/\n"
    "	return vec3( result );\n"
    "}\n"
    "float G_BlinnPhong_Implicit( /* const in float dotNL, const in float dotNV */ ) {\n"
    "	return 0.25;\n"
    "}\n"
    "float D_BlinnPhong( const in float shininess, const in float dotNH ) {\n"
    "	return RECIPROCAL_PI * ( shininess * 0.5 + 1.0 ) * pow( dotNH, shininess );\n"
    "}\n"
    "vec3 BRDF_BlinnPhong( const in vec3 lightDir, const in vec3 viewDir, const in vec3 normal, const in vec3 specularColor, const in float shininess ) {\n"
    "	vec3 halfDir = normalize( lightDir + viewDir );\n"
    "	float dotNH = saturate( dot( normal, halfDir ) );\n"
    "	float dotVH = saturate( dot( viewDir, halfDir ) );\n"
    "	vec3 F = F_Schlick( specularColor, 1.0, dotVH );\n"
    "	float G = G_BlinnPhong_Implicit( /* dotNL, dotNV */ );\n"
    "	float D = D_BlinnPhong( shininess, dotNH );\n"
    "	return F * ( G * D );\n"
    "} // validated\n"
    "#if defined( USE_SHEEN )\n"
    "float D_Charlie( float roughness, float dotNH ) {\n"
    "	float alpha = pow2( roughness );\n"
    "	float invAlpha = 1.0 / alpha;\n"
    "	float cos2h = dotNH * dotNH;\n"
    "	float sin2h = max( 1.0 - cos2h, 0.0078125 ); // 2^(-14/2), so sin2h^2 > 0 in fp16\n"
    "	return ( 2.0 + invAlpha ) * pow( sin2h, invAlpha * 0.5 ) / ( 2.0 * PI );\n"
    "}\n"
    "float V_Neubelt( float dotNV, float dotNL ) {\n"
    "	return saturate( 1.0 / ( 4.0 * ( dotNL + dotNV - dotNL * dotNV ) ) );\n"
    "}\n"
    "vec3 BRDF_Sheen( const in vec3 lightDir, const in vec3 viewDir, const in vec3 normal, vec3 sheenColor, const in float sheenRoughness ) {\n"
    "	vec3 halfDir = normalize( lightDir + viewDir );\n"
    "	float dotNL = saturate( dot( normal, lightDir ) );\n"
    "	float dotNV = saturate( dot( normal, viewDir ) );\n"
    "	float dotNH = saturate( dot( normal, halfDir ) );\n"
    "	float D = D_Charlie( sheenRoughness, dotNH );\n"
    "	float V = V_Neubelt( dotNV, dotNL );\n"
    "	return sheenColor * ( D * V );\n"
    "}\n"
    "#endif";
    
static const char *COMMON = "#define PI 3.141592653589793\n"
    "#define PI2 6.283185307179586\n"
    "#define PI_HALF 1.5707963267948966\n"
    "#define RECIPROCAL_PI 0.3183098861837907\n"
    "#define RECIPROCAL_PI2 0.15915494309189535\n"
    "#define EPSILON 1e-6\n"
    "#ifndef saturate\n"
    "#define saturate( a ) clamp( a, 0.0, 1.0 )\n"
    "#endif\n"
    "#define whiteComplement( a ) ( 1.0 - saturate( a ) )\n"
    "float pow2( const in float x ) { return x*x; }\n"
    "vec3 pow2( const in vec3 x ) { return x*x; }\n"
    "float pow3( const in float x ) { return x*x*x; }\n"
    "float pow4( const in float x ) { float x2 = x*x; return x2*x2; }\n"
    "float max3( const in vec3 v ) { return max( max( v.x, v.y ), v.z ); }\n"
    "float average( const in vec3 v ) { return dot( v, vec3( 0.3333333 ) ); }\n"
    "highp float rand( const in vec2 uv ) {\n"
    "	const highp float a = 12.9898, b = 78.233, c = 43758.5453;\n"
    "	highp float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );\n"
    "	return fract( sin( sn ) * c );\n"
    "}\n"
    "#ifdef HIGH_PRECISION\n"
    "	float precisionSafeLength( vec3 v ) { return length( v ); }\n"
    "#else\n"
    "	float precisionSafeLength( vec3 v ) {\n"
    "		float maxComponent = max3( abs( v ) );\n"
    "		return length( v / maxComponent ) * maxComponent;\n"
    "	}\n"
    "#endif\n"
    "struct IncidentLight {\n"
    "	vec3 color;\n"
    "	vec3 direction;\n"
    "	bool visible;\n"
    "};\n"
    "struct ReflectedLight {\n"
    "	vec3 directDiffuse;\n"
    "	vec3 directSpecular;\n"
    "	vec3 indirectDiffuse;\n"
    "	vec3 indirectSpecular;\n"
    "};\n"
    "struct GeometricContext {\n"
    "	vec3 position;\n"
    "	vec3 normal;\n"
    "	vec3 viewDir;\n"
    "#ifdef USE_CLEARCOAT\n"
    "	vec3 clearcoatNormal;\n"
    "#endif\n"
    "};\n"
    "vec3 transformDirection( in vec3 dir, in mat4 matrix ) {\n"
    "	return normalize( ( matrix * vec4( dir, 0.0 ) ).xyz );\n"
    "}\n"
    "vec3 inverseTransformDirection( in vec3 dir, in mat4 matrix ) {\n"
    "	return normalize( ( vec4( dir, 0.0 ) * matrix ).xyz );\n"
    "}\n"
    "mat3 transposeMat3( const in mat3 m ) {\n"
    "	mat3 tmp;\n"
    "	tmp[ 0 ] = vec3( m[ 0 ].x, m[ 1 ].x, m[ 2 ].x );\n"
    "	tmp[ 1 ] = vec3( m[ 0 ].y, m[ 1 ].y, m[ 2 ].y );\n"
    "	tmp[ 2 ] = vec3( m[ 0 ].z, m[ 1 ].z, m[ 2 ].z );\n"
    "	return tmp;\n"
    "}\n"
    "float luminance( const in vec3 rgb ) {\n"
    "	const vec3 weights = vec3( 0.2126729, 0.7151522, 0.0721750 );\n"
    "	return dot( weights, rgb );\n"
    "}\n"
    "bool isPerspectiveMatrix( mat4 m ) {\n"
    "	return m[ 2 ][ 3 ] == - 1.0;\n"
    "}\n"
    "vec2 equirectUv( in vec3 dir ) {\n"
    "	float u = atan( dir.z, dir.x ) * RECIPROCAL_PI2 + 0.5;\n"
    "	float v = asin( clamp( dir.y, - 1.0, 1.0 ) ) * RECIPROCAL_PI + 0.5;\n"
    "	return vec2( u, v );\n"
    "}";
    
static const char *NORMAL_VERTEX = "#ifndef FLAT_SHADED // normal is computed with derivatives when FLAT_SHADED\n"
    "	vNormal = normalize( transformedNormal );\n"
    "	#ifdef USE_TANGENT\n"
    "		vTangent = normalize( transformedTangent );\n"
    "		vBitangent = normalize( cross( vNormal, vTangent ) * tangent.w );\n"
    "	#endif\n"
    "#endif";
    
static const char *DEFAULT_FRAGMENT = "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0,0.0,0.0, 1.0);\n"
    "}";
    
static const char *COLOR_FRAGMENT = "#if defined( USE_COLOR_ALPHA )\n"
    "	diffuseColor *= vColor;\n"
    "#elif defined( USE_COLOR )\n"
    "	diffuseColor.rgb *= vColor;\n"
    "#endif";
    
static const char *DEFAULT_VERTEX = "void main()\n"
    "{\n"
    "  gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);\n"
    "}";
    
static const char *PROJECT_VERTEX = "vec4 mvPosition = vec4( transformed, 1.0 );\n"
    "#ifdef USE_INSTANCING\n"
    "	mvPosition = instanceMatrix * mvPosition;\n"
    "#endif\n"
    "mvPosition = modelViewMatrix * mvPosition;\n"
    "gl_Position = projectionMatrix * mvPosition;";
    
static const char *COLOR_VERTEX = "#if defined( USE_COLOR_ALPHA )\n"
    "	vColor = vec4( 1.0 );\n"
    "#elif defined( USE_COLOR ) || defined( USE_INSTANCING_COLOR )\n"
    "	vColor = vec3( 1.0 );\n"
    "#endif\n"
    "#ifdef USE_COLOR\n"
    "	vColor *= color;\n"
    "#endif\n"
    "#ifdef USE_INSTANCING_COLOR\n"
    "	vColor.xyz *= instanceColor.xyz;\n"
    "#endif";
    
static const char *BEGIN_VERTEX = "vec3 transformed = vec3(position);";
    
static const char *TEST = "";
static const char *SPECULARMAP_PARS_FRAGMENT = "#ifdef USE_SPECULARMAP\n"
    "	uniform sampler2D specularMap;\n"
    "#endif";
    
static const char *LIGHTS_FRAGMENT_BEGIN = "GeometricContext geometry;\n"
    "geometry.position = - vViewPosition;\n"
    "geometry.normal = normal;\n"
    "geometry.viewDir = ( isOrthographic ) ? vec3( 0, 0, 1 ) : normalize( vViewPosition );\n"
    "#ifdef USE_CLEARCOAT\n"
    "	geometry.clearcoatNormal = clearcoatNormal;\n"
    "#endif\n"
    "#ifdef USE_IRIDESCENCE\n"
    "	float dotNVi = saturate( dot( normal, geometry.viewDir ) );\n"
    "	if ( material.iridescenceThickness == 0.0 ) {\n"
    "		material.iridescence = 0.0;\n"
    "	} else {\n"
    "		material.iridescence = saturate( material.iridescence );\n"
    "	}\n"
    "	if ( material.iridescence > 0.0 ) {\n"
    "		material.iridescenceFresnel = evalIridescence( 1.0, material.iridescenceIOR, dotNVi, material.iridescenceThickness, material.specularColor );\n"
    "		material.iridescenceF0 = Schlick_to_F0( material.iridescenceFresnel, 1.0, dotNVi );\n"
    "	}\n"
    "#endif\n"
    "IncidentLight directLight;\n"
    "#if ( NUM_POINT_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "	PointLight pointLight;\n"
    "	#if defined( USE_SHADOWMAP ) && NUM_POINT_LIGHT_SHADOWS > 0\n"
    "	PointLightShadow pointLightShadow;\n"
    "	#endif\n"
    "	#pragma unroll_loop_start\n"
    "	for ( int i = 0; i < NUM_POINT_LIGHTS; i ++ ) {\n"
    "		pointLight = pointLights[ i ];\n"
    "		getPointLightInfo( pointLight, geometry, directLight );\n"
    "		// #if defined( USE_SHADOWMAP ) && ( UNROLLED_LOOP_INDEX < NUM_POINT_LIGHT_SHADOWS )\n"
    "		// pointLightShadow = pointLightShadows[ i ];\n"
    "		// directLight.color *= all( bvec2( directLight.visible, receiveShadow ) ) ? getPointShadow( pointShadowMap[ i ], pointLightShadow.shadowMapSize, pointLightShadow.shadowBias, pointLightShadow.shadowRadius, vPointShadowCoord[ i ], pointLightShadow.shadowCameraNear, pointLightShadow.shadowCameraFar ) : 1.0;\n"
    "		// #endif\n"
    "		RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "	}\n"
    "	#pragma unroll_loop_end\n"
    "#endif\n"
    "#if ( NUM_SPOT_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "	SpotLight spotLight;\n"
    "	#if defined( USE_SHADOWMAP ) && NUM_SPOT_LIGHT_SHADOWS > 0\n"
    "	SpotLightShadow spotLightShadow;\n"
    "	#endif\n"
    "	#pragma unroll_loop_start\n"
    "	for ( int i = 0; i < NUM_SPOT_LIGHTS; i ++ ) {\n"
    "		spotLight = spotLights[ i ];\n"
    "		getSpotLightInfo( spotLight, geometry, directLight );\n"
    "		// #if defined( USE_SHADOWMAP ) && ( UNROLLED_LOOP_INDEX < NUM_SPOT_LIGHT_SHADOWS )\n"
    "		// spotLightShadow = spotLightShadows[ i ];\n"
    "		// directLight.color *= all( bvec2( directLight.visible, receiveShadow ) ) ? getShadow( spotShadowMap[ i ], spotLightShadow.shadowMapSize, spotLightShadow.shadowBias, spotLightShadow.shadowRadius, vSpotShadowCoord[ i ] ) : 1.0;\n"
    "		// #endif\n"
    "		RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "	}\n"
    "	#pragma unroll_loop_end\n"
    "#endif\n"
    "#if ( NUM_DIR_LIGHTS > 0 ) && defined( RE_Direct )\n"
    "	DirectionalLight directionalLight;\n"
    "	#if defined( USE_SHADOWMAP ) && NUM_DIR_LIGHT_SHADOWS > 0\n"
    "	DirectionalLightShadow directionalLightShadow;\n"
    "	#endif\n"
    "	#pragma unroll_loop_start\n"
    "	for ( int i = 0; i < NUM_DIR_LIGHTS; i ++ ) {\n"
    "		directionalLight = directionalLights[ i ];\n"
    "		getDirectionalLightInfo( directionalLight, geometry, directLight );\n"
    "		// #if defined( USE_SHADOWMAP ) && ( UNROLLED_LOOP_INDEX < NUM_DIR_LIGHT_SHADOWS )\n"
    "		// directionalLightShadow = directionalLightShadows[ i ];\n"
    "		// directLight.color *= all( bvec2( directLight.visible, receiveShadow ) ) ? getShadow( directionalShadowMap[ i ], directionalLightShadow.shadowMapSize, directionalLightShadow.shadowBias, directionalLightShadow.shadowRadius, vDirectionalShadowCoord[ i ] ) : 1.0;\n"
    "		// #endif\n"
    "		RE_Direct( directLight, geometry, material, reflectedLight );\n"
    "	}\n"
    "	#pragma unroll_loop_end\n"
    "#endif\n"
    "#if ( NUM_RECT_AREA_LIGHTS > 0 ) && defined( RE_Direct_RectArea )\n"
    "	RectAreaLight rectAreaLight;\n"
    "	#pragma unroll_loop_start\n"
    "	for ( int i = 0; i < NUM_RECT_AREA_LIGHTS; i ++ ) {\n"
    "		rectAreaLight = rectAreaLights[ i ];\n"
    "		RE_Direct_RectArea( rectAreaLight, geometry, material, reflectedLight );\n"
    "	}\n"
    "	#pragma unroll_loop_end\n"
    "#endif\n"
    "#if defined( RE_IndirectDiffuse )\n"
    "	vec3 iblIrradiance = vec3( 0.0 );\n"
    "	vec3 irradiance = getAmbientLightIrradiance( ambientLightColor );\n"
    "	irradiance += getLightProbeIrradiance( lightProbe, geometry.normal );\n"
    "	#if ( NUM_HEMI_LIGHTS > 0 )\n"
    "		#pragma unroll_loop_start\n"
    "		for ( int i = 0; i < NUM_HEMI_LIGHTS; i ++ ) {\n"
    "			irradiance += getHemisphereLightIrradiance( hemisphereLights[ i ], geometry.normal );\n"
    "		}\n"
    "		#pragma unroll_loop_end\n"
    "	#endif\n"
    "#endif\n"
    "#if defined( RE_IndirectSpecular )\n"
    "	vec3 radiance = vec3( 0.0 );\n"
    "	vec3 clearcoatRadiance = vec3( 0.0 );\n"
    "#endif";
    
static const char *DEFAULTNORMAL_VERTEX = "vec3 transformedNormal = objectNormal;\n"
    "#ifdef USE_INSTANCING\n"
    "	mat3 m = mat3( instanceMatrix );\n"
    "	transformedNormal /= vec3( dot( m[ 0 ], m[ 0 ] ), dot( m[ 1 ], m[ 1 ] ), dot( m[ 2 ], m[ 2 ] ) );\n"
    "	transformedNormal = m * transformedNormal;\n"
    "#endif\n"
    "transformedNormal = normalMatrix * transformedNormal;\n"
    "#ifdef FLIP_SIDED\n"
    "	transformedNormal = - transformedNormal;\n"
    "#endif\n"
    "#ifdef USE_TANGENT\n"
    "	vec3 transformedTangent = ( modelViewMatrix * vec4( objectTangent, 0.0 ) ).xyz;\n"
    "	#ifdef FLIP_SIDED\n"
    "		transformedTangent = - transformedTangent;\n"
    "	#endif\n"
    "#endif";
    
static const char *LIGHTS_LAMBERT_PARS_FRAGMENT = "in vec3 vViewPosition;\n"
    "struct LambertMaterial {\n"
    "	vec3 diffuseColor;\n"
    "	float specularStrength;\n"
    "};\n"
    "void RE_Direct_Lambert( const in IncidentLight directLight, const in GeometricContext geometry, const in LambertMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "	float dotNL = saturate( dot( geometry.normal, directLight.direction ) );\n"
    "	vec3 irradiance = dotNL * directLight.color;\n"
    "	reflectedLight.directDiffuse += irradiance * BRDF_Lambert( material.diffuseColor );\n"
    "}\n"
    "void RE_IndirectDiffuse_Lambert( const in vec3 irradiance, const in GeometricContext geometry, const in LambertMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "	reflectedLight.indirectDiffuse += irradiance * BRDF_Lambert( material.diffuseColor );\n"
    "}\n"
    "#define RE_Direct				RE_Direct_Lambert\n"
    "#define RE_IndirectDiffuse		RE_IndirectDiffuse_Lambert\n"
    "#define Material_LightProbeLOD( material )	(0)";
    
static const char *NORMAL_PARS_FRAGMENT = "#ifndef FLAT_SHADED\n"
    "	in vec3 vNormal;\n"
    "	#ifdef USE_TANGENT\n"
    "		in vec3 vTangent;\n"
    "		in vec3 vBitangent;\n"
    "	#endif\n"
    "#endif";
    
static const char *COLOR_PARS_VERTEX = "#if defined( USE_COLOR_ALPHA )\n"
    "	out vec4 vColor;\n"
    "#elif defined( USE_COLOR ) || defined( USE_INSTANCING_COLOR )\n"
    "	out vec3 vColor;\n"
    "#endif";
    
static const char *LIGHTS_PHONG_PARS_FRAGMENT = "in vec3 vViewPosition;\n"
    "struct BlinnPhongMaterial {\n"
    "	vec3 diffuseColor;\n"
    "	vec3 specularColor;\n"
    "	float specularShininess;\n"
    "	float specularStrength;\n"
    "};\n"
    "void RE_Direct_BlinnPhong( const in IncidentLight directLight, const in GeometricContext geometry, const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "	float dotNL = saturate( dot( geometry.normal, directLight.direction ) );\n"
    "	vec3 irradiance = dotNL * directLight.color;\n"
    "	\n"
    "	reflectedLight.directDiffuse += irradiance * BRDF_Lambert( material.diffuseColor );\n"
    "	reflectedLight.directSpecular = irradiance * BRDF_BlinnPhong( directLight.direction, geometry.viewDir, geometry.normal, material.specularColor, material.specularShininess ) * material.specularStrength;\n"
    "}\n"
    "void RE_IndirectDiffuse_BlinnPhong( const in vec3 irradiance, const in GeometricContext geometry, const in BlinnPhongMaterial material, inout ReflectedLight reflectedLight ) {\n"
    "	reflectedLight.indirectDiffuse += irradiance * BRDF_Lambert( material.diffuseColor );\n"
    "}\n"
    "#define RE_Direct				RE_Direct_BlinnPhong\n"
    "#define RE_IndirectDiffuse		RE_IndirectDiffuse_BlinnPhong\n"
    "#define Material_LightProbeLOD( material )	(0)";
    
static const char *COLOR_PARS_FRAGMENT = "#if defined( USE_COLOR_ALPHA )\n"
    "	in vec4 vColor;\n"
    "#elif defined( USE_COLOR )\n"
    "	in vec3 vColor;\n"
    "#endif";
    
static const char *NORMAL_FRAGMENT_BEGIN = "float faceDirection = gl_FrontFacing ? 1.0 : - 1.0;\n"
    "#ifdef FLAT_SHADED\n"
    "	vec3 fdx = vec3( dFdx( vViewPosition.x ), dFdx( vViewPosition.y ), dFdx( vViewPosition.z ) );\n"
    "	vec3 fdy = vec3( dFdy( vViewPosition.x ), dFdy( vViewPosition.y ), dFdy( vViewPosition.z ) );\n"
    "	vec3 normal = normalize( cross( fdx, fdy ) );\n"
    "#else\n"
    "	vec3 normal = normalize( vNormal );\n"
    "	#ifdef DOUBLE_SIDED\n"
    "		normal = normal * faceDirection;\n"
    "	#endif\n"
    "	#ifdef USE_TANGENT\n"
    "		vec3 tangent = normalize( vTangent );\n"
    "		vec3 bitangent = normalize( vBitangent );\n"
    "		#ifdef DOUBLE_SIDED\n"
    "			tangent = tangent * faceDirection;\n"
    "			bitangent = bitangent * faceDirection;\n"
    "		#endif\n"
    "		#if defined( TANGENTSPACE_NORMALMAP ) || defined( USE_CLEARCOAT_NORMALMAP )\n"
    "			mat3 vTBN = mat3( tangent, bitangent, normal );\n"
    "		#endif\n"
    "	#endif\n"
    "#endif\n"
    "vec3 geometryNormal = normal;";
    
static const char *LIGHTS_FRAGMENT_END = "#if defined( RE_IndirectDiffuse )\n"
    "	RE_IndirectDiffuse( irradiance, geometry, material, reflectedLight );\n"
    "#endif\n"
    "#if defined( RE_IndirectSpecular )\n"
    "	RE_IndirectSpecular( radiance, iblIrradiance, clearcoatRadiance, geometry, material, reflectedLight );\n"
    "#endif";
    
static const char *NORMAL_PARS_VERTEX = "#ifndef FLAT_SHADED\n"
    "	out vec3 vNormal;\n"
    "	#ifdef USE_TANGENT\n"
    "		out vec3 vTangent;\n"
    "		out vec3 vBitangent;\n"
    "	#endif\n"
    "#endif";
    
static const char *WORLDPOS_VERTEX = "#if defined( USE_ENVMAP ) || defined( DISTANCE ) || defined ( USE_SHADOWMAP ) || defined ( USE_TRANSMISSION )\n"
    "	vec4 worldPosition = vec4( transformed, 1.0 );\n"
    "	#ifdef USE_INSTANCING\n"
    "		worldPosition = instanceMatrix * worldPosition;\n"
    "	#endif\n"
    "	worldPosition = modelMatrix * worldPosition;\n"
    "#endif";
    
static const std::map<std::string,const char*> shader_chunk_map = {
	{ "lights_lambert_fragment",LIGHTS_LAMBERT_FRAGMENT },
	{ "specularmap_fragment",SPECULARMAP_FRAGMENT },
	{ "lights_pars_begin",LIGHTS_PARS_BEGIN },
	{ "beginnormal_vertex",BEGINNORMAL_VERTEX },
	{ "lights_phong_fragment",LIGHTS_PHONG_FRAGMENT },
	{ "output_fragment",OUTPUT_FRAGMENT },
	{ "bsdfs",BSDFS },
	{ "common",COMMON },
	{ "normal_vertex",NORMAL_VERTEX },
	{ "default_fragment",DEFAULT_FRAGMENT },
	{ "color_fragment",COLOR_FRAGMENT },
	{ "default_vertex",DEFAULT_VERTEX },
	{ "project_vertex",PROJECT_VERTEX },
	{ "color_vertex",COLOR_VERTEX },
	{ "begin_vertex",BEGIN_VERTEX },
	{ "test",TEST },
	{ "specularmap_pars_fragment",SPECULARMAP_PARS_FRAGMENT },
	{ "lights_fragment_begin",LIGHTS_FRAGMENT_BEGIN },
	{ "defaultnormal_vertex",DEFAULTNORMAL_VERTEX },
	{ "lights_lambert_pars_fragment",LIGHTS_LAMBERT_PARS_FRAGMENT },
	{ "normal_pars_fragment",NORMAL_PARS_FRAGMENT },
	{ "color_pars_vertex",COLOR_PARS_VERTEX },
	{ "lights_phong_pars_fragment",LIGHTS_PHONG_PARS_FRAGMENT },
	{ "color_pars_fragment",COLOR_PARS_FRAGMENT },
	{ "normal_fragment_begin",NORMAL_FRAGMENT_BEGIN },
	{ "lights_fragment_end",LIGHTS_FRAGMENT_END },
	{ "normal_pars_vertex",NORMAL_PARS_VERTEX },
	{ "worldpos_vertex",WORLDPOS_VERTEX }
};


std::string ShaderChunk::Get(std::string const& name)
{
	auto iter = shader_chunk_map.find(name);
	
	if(iter == shader_chunk_map.end())
	{
		std::stringstream ss;
        ss << __FILE__ << ":" << __LINE__ << " - ERROR - " << "not eixst shader chunk: " << name << std::endl;
		return "";
	}

	return iter->second;
}