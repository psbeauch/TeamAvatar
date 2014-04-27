uniform vec3 dColor;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform vec3 uLPos;
uniform vec3 cameraPos;
uniform float uOutline;
uniform sampler2D uTexUnit;
uniform float sky;

varying vec4 fNormal;
varying vec3 fColor;
varying vec4 fPos;
varying vec2 vTexCoord;

void main() {
   vec4 color;
   float numShades = 3.0;
   vec4 texColor1 = texture2D(uTexUnit, vTexCoord);
   
   if(uOutline > 0.5) {
      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
   }
   else {
      //calculate light vector
      vec4 L = normalize(vec4(uLPos, 1.0) - fPos);
      float intensity = dot(L, normalize(fNormal));
      float q_intensity = ceil(intensity * numShades)/numShades;
	  if(q_intensity < 0.1) {
            q_intensity = 1.0;
      }

      gl_FragColor = vec4(dColor * q_intensity, 1.0);
	  //gl_FragColor = vec4(0.7, 0.7, 0.7, 1.0);
	  
	  if(sky == 1.0){
		gl_FragColor = texColor1;
	  }
   }
}
