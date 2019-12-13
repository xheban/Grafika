#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform vec3 CameraPos;
uniform vec3 LightDirection2;
uniform vec3 LightColor2;
uniform float specularPower;

//material properties
uniform vec3 ambientProp;
uniform vec3 diffuseProp;
uniform vec3 specularProp;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

in vec3 FragPos;

// The final color
out vec4 FragmentColor;

void main() {
  // Compute diffuse lighting
  float diffuse = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.0f);

vec3 viewDir = normalize(CameraPos - FragPos);
    vec3 reflectDir = reflect(normalize(-LightDirection), vec3(normal.x, normal.y, normal.z));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularPower);
    vec3 specular = specularProp * spec;
    vec3 light = (ambientProp+diffuse+specular) * LightColor;
    vec3 diffuse2 = max(dot(normal, vec4(normalize(LightDirection2), 1.0f)), 0.0f)*diffuseProp;
    vec3 viewDir2 = normalize(CameraPos - FragPos);
    vec3 reflectDir2 = reflect(normalize(-LightDirection2), vec3(normal.x, normal.y, normal.z));
    float spec2 = pow(max(dot(viewDir2, reflectDir2), 0.0), specularPower);
    vec3 specular2 = specularProp * spec2 ;
    vec3 light2 = (ambientProp+diffuse2+specular2) * LightColor2;

  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
   FragmentColor.r = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset).r * (light.r+light2.r) ;
   FragmentColor.g = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset).g * (light.g+light2.g);
   FragmentColor.b = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset).b * (light.b+light2.b);
   FragmentColor.a = Transparency;
}
