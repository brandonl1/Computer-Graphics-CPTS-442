#version 330

//
// This is the fundamental "EADS" (Emissive-Ambient-Diffuse-Specular)
// shader that is a somewhat simplified version of the traditional
// OpenGL shading model.
//

// material properties
uniform vec3 emittance;
uniform vec3 ambientReflectivity;
uniform vec3 maximumDiffuseReflectivity;
uniform vec3 maximumSpecularReflectivity;
uniform float specularExponent;

// camera propert(y|ies)
uniform vec3 towardsCamera;

// light properties
uniform int nLights;
uniform struct Light {
    vec3 irradiance;
    vec3 towards;
} light[10]; // in later GLSLs, this size can vary

uniform mat4 viewMatrix;      // transforms vertices into NDC

uniform mat3 normalMatrix;    // transforms normals into world

// per-vertex inputs
in vec4 vertexPosition;
in vec3 vertexNormal;

smooth out vec4 interpolatedVertexColor;
const float EPSILON = 1.0e-5; // for single precision

void main(void)
{
    //
    // Copy your previous (PA06) solution here.
    //

   vec3 radiance = emittance;


	for(int i = 0; i < nLights; i++){
	vec3 reflectivity = ambientReflectivity;
	vec3 worldNormal =  normalMatrix * vertexNormal;
	vec3 irradiance = light[i].irradiance;
	worldNormal = normalize(worldNormal);
	vec3 towardsLight_ = light[i].towards;
	towardsLight_ = normalize(towardsLight_);
	float nDotL = dot(worldNormal, towardsLight_); // dot
	if(nDotL >= 0.0){
		reflectivity += nDotL * maximumDiffuseReflectivity;
		vec3 h = towardsCamera + towardsLight_;
		h = normalize(h);
		float nDotH = dot(worldNormal, h); //dot
		if(nDotH >= 0.0){
			 float temp = pow(nDotH, specularExponent);
			 reflectivity += maximumSpecularReflectivity * temp;
		}
	}
	radiance +=  irradiance * reflectivity;
    	//radiance = towardsLight_;
	}
//radiance = vec3(nDotL,0,0);
interpolatedVertexColor = vec4(radiance, 1);
#if 0 // debug
    interpolatedVertexColor = vec4(vertexNormal, 1);
#endif

    // the position transform is trivial
    gl_Position = viewMatrix * vertexPosition;
}
