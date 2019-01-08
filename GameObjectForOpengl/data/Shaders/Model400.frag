#version 430  
  
in vec3 Position;  
in vec2 TextCoord;
in vec3 vNormal;
in vec3 Tangent;
in vec3 ShadowCoord;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D shadowMap;

uniform int lightNum;
uniform vec3 lightPositions[8];  
uniform vec4 lightColors[8];
uniform float lightItensities[8];
uniform float lightDS[8];

layout( location = 0 ) out vec4 FragColor;  
  
void main() {  
	vec4 texd = texture2D(texture_diffuse0, TextCoord);
	vec4 texs = texture2D(texture_specular0, TextCoord);
	vec4 texn = texture2D(texture_normal0, TextCoord);
	
	vec3 n = normalize(vec3(texn) * 4 - vec3(3,3,3));

	vec3 normal = normalize(vNormal);
	vec3 tangent = normalize(Tangent);
	vec3 Binormal = normalize(cross(tangent,normal));

	mat3 tMat = mat3(tangent,Binormal,normal);
	vec3 Normal = normalize(tMat * n);

	vec3 s = normalize(lightPositions[0]);
	vec3 v = normalize(vec3(-Position));  
	vec3 r = reflect( -s, Normal );
		
	float bias = 0.002;
	float visibility = 1.0;
	if(texture2D( shadowMap, ShadowCoord.xy).z < min(ShadowCoord.z,1) - bias){
		visibility = 0.1;
	}

	vec4 dF = max( dot(s, Normal) * 0.7 + 0.3, 0.0 ) * lightItensities[0] * lightColors[0] * visibility;
	vec4 sF = pow( max( dot(r,v), 0.0 ), 60 ) * lightItensities[0] * lightColors[0] * visibility;
	
	for(int i = 1; i < lightNum; i++){
		vec3 delta = lightPositions[i] - Position;
		float DS = dot(delta,delta);
		s = normalize(delta);  
		v = normalize(vec3(-Position));  
		r = reflect( -s, Normal );

		float rate = max(1-DS/lightDS[i],0.0);
		dF += max( dot(s, Normal), 0.0 ) * lightItensities[i] * rate * lightColors[i];
		sF += pow( max( dot(r,v), 0.0 ), 80 ) * lightItensities[i] * rate * lightColors[i];
	}

	vec4 ambient = texd * 0.1;
	vec4 diffuse = texd * dF *0.7;
	vec4 specular = texs * sF;
	
	FragColor = (ambient + diffuse + specular);
    //FragColor = vec4(TextCoord,0,1);
}  