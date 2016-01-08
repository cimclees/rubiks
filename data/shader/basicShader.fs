#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main() {
  vec2 flipped_texcoord = vec2(texCoord0.x, 1.0 - texCoord0.y);
  gl_FragColor = texture2D(diffuse, flipped_texcoord) 
    * clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0);
}
