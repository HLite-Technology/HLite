#version 330

#define MAX_LIGHTS 32

#define LIGHT_POINT 0
#define LIGHT_SPOT 1
#define LIGHT_DIRECTIONAL 2
#define LIGHT_AMBIENT 3

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

uniform int lightCount;
uniform vec2 resolution;

struct Light
{
    int type;
    vec2 position;
    vec2 direction;
    vec3 color;
    float radius;
    float intensity;
    float angle;
};

uniform Light lights[MAX_LIGHTS];

out vec4 finalColor;

vec3 CalculatePointLight(Light light, vec2 fragPos, vec3 baseColor)
{
    float dist = distance(fragPos, light.position);

    float attenuation =
        1.0 - smoothstep(0.0, light.radius, dist);

    vec3 result =
        baseColor *
        light.color *
        attenuation *
        light.intensity;

    // if (light.ambience == 1)
    // {
    //     result += baseColor * 0.15;
    // }

    return result;
}

vec3 CalculateSpotLight(Light light, vec2 fragPos, vec3 baseColor)
{
    vec2 dir =
        normalize(fragPos - light.position);

    float theta =
        dot(dir, normalize(light.direction));

    float cone = smoothstep(
        light.angle - 0.02,
        light.angle,
        theta
    );

    float dist =
        distance(fragPos, light.position);

    float attenuation =
        1.0 - smoothstep(0.0,
                         light.radius,
                         dist);

    return
        baseColor *
        light.color *
        attenuation *
        cone *
        light.intensity;
}

vec3 CalculateDirectionalLight(Light light, vec3 baseColor)
{
    return
        baseColor *
        light.color *
        light.intensity;
}

vec3 CalculateAmbientLight(Light light, vec3 baseColor)
{
    return
        baseColor *
        light.color *
        light.intensity;
}

void main()
{
    vec4 texColor =
        texture(texture0, fragTexCoord);

    vec4 baseColor =
        texColor * fragColor;

    vec2 fragPos =
        vec2(gl_FragCoord.x,
             resolution.y - gl_FragCoord.y);

    vec3 result = vec3(0.0);

    for (int i = 0; i < lightCount; i++)
    {
        switch (lights[i].type)
        {
            case LIGHT_POINT:
            {
                result += CalculatePointLight(
                    lights[i],
                    fragPos,
                    baseColor.rgb
                );
            }
            break;

            case LIGHT_SPOT:
            {
                result += CalculateSpotLight(
                    lights[i],
                    fragPos,
                    baseColor.rgb
                );
            }
            break;

            case LIGHT_DIRECTIONAL:
            {
                result += CalculateDirectionalLight(
                    lights[i],
                    baseColor.rgb
                );
            }
            break;

            case LIGHT_AMBIENT:
            {
                result += CalculateAmbientLight(
                    lights[i],
                    baseColor.rgb
                );
            }
            break;
        }
    }

    finalColor =
        vec4(result, baseColor.a);
}