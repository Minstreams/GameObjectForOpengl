#version 430  
  
in vec3 Position;  
in vec3 vNormal;
in vec4 Color;
in vec3 ShadowCoord;

uniform sampler2D shadowMap;

uniform int lightNum;
uniform vec3 lightPositions[8];  
uniform vec4 lightColors[8];
uniform float lightItensities[8];
uniform float lightDS[8];

layout( location = 0 ) out vec4 FragColor;  
  
void main() {  
	vec3 Normal = normalize(vNormal);

	vec3 s = normalize(lightPositions[0]);
	vec3 v = normalize(vec3(-Position));  
	vec3 r = reflect( -s, Normal );
		
	float sdn = dot(s, Normal);
	float cosTheta = clamp(sdn * 0.7 + 0.3, 0, 1);
	float bias = 0.002 * tan(acos(cosTheta));
	float visibility = 1.0;
	if(texture2D( shadowMap, ShadowCoord.xy).z < min(ShadowCoord.z,1) - bias){
		visibility = 0.1;
	}

	vec4 dF = max(sdn * 0.5 + 0.5, 0) * lightItensities[0] * lightColors[0] * visibility;
	vec4 sF = pow( max( dot(r,v), 0.0 ), 60 ) * lightItensities[0] * lightColors[0] * visibility;
	

	for(int i = 1; i < lightNum; i++){
		vec3 delta = lightPositions[i] - Position;
		float DS = dot(delta,delta);
		s = normalize(delta);  
		v = normalize(vec3(-Position));  
		r = reflect( -s, Normal );

		float rate = max(1-DS/lightDS[i],0.0);
		dF += max( dot(s, Normal), 0.0 ) * lightItensities[i] * rate * lightColors[i];
		sF += pow( max( dot(r,v), 0.0 ), 60 ) * lightItensities[i] * rate * lightColors[i];
	}

	vec4 ambient = Color * 0.1;
	vec4 diffuse = Color * dF;
	vec4 specular = Color * sF;

    //FragColor = texture2D( shadowMap, ShadowCoord.xy);
	FragColor = (ambient + diffuse + specular);
}  