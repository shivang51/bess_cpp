
float sdRoundBox(in vec2 p, in vec2 b, in vec4 r)
{
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x = (p.y > 0.0) ? r.x : r.y;
    vec2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    //	vec2 p = (fragCoord-iResolution.xy)/iResolution.y ;
    //  p += 1.;

    vec2 p = fragCoord / iResolution.xy - 0.5;
    p.x *= iResolution.x / iResolution.y;

    //p -= 0.5;

    vec2 si = vec2(0.8, 0.4);
    vec4 ra = vec4(.3, .1, .3, 0.3);

    float d = sdRoundBox(p, si, ra);

    //  vec3 col = (d>0.0) ? vec3(0.0) : vec3(0.65,0.85,1.0);
    vec3 col = vec3(0.);
    col = mix(col, vec3(1.0), 1.0 - smoothstep(0.0, 0.01, abs(d)));

    fragColor = vec4(col, 1.0);
}
