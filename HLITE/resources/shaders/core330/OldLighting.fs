#version 330

in vec2 fragTexCoord;
uniform sampler2D texture0;
uniform vec2 position; 
uniform vec2 resolution;
uniform float radius;
uniform vec3 lightColor;
uniform int isLightAmbience;
uniform int isVeryBright;

out vec4 finalColor;

void main() {
    vec4 texColor = texture(texture0, fragTexCoord);

    vec2 fragPos = vec2(gl_FragCoord.x, resolution.y - gl_FragCoord.y);

    float dist = distance(fragPos, position);

    float intensity = 1.0 - smoothstep(0.0, radius, dist);

    vec3 lighting = lightColor * intensity;

    // finalColor = vec4(texColor.rgb * intensity, 1.0);

    // More brightness.
    if (isVeryBright == 1) {
        finalColor = vec4(texColor.rgb + lighting, texColor.a);
    } else {
        if (isLightAmbience == 1) {
            vec3 result = texColor.rgb * (0.2 + lighting);
            finalColor = vec4(result, texColor.a);
        } else {
            finalColor = vec4(texColor.rgb * lighting, texColor.a);
        }
    }
}
