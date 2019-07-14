// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"

global_settings {
  assumed_gamma 1.0
}

// ----------------------------------------

camera {
  location  <0.0, 0.5, -4.0>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
}

sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.6,0.7,1.0>]
      [0.7 rgb <0.0,0.1,0.8>]
    }
  }
}

light_source {
  <0, 0, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <-30, 30, -30>
}

// ----------------------------------------

plane {
  y, -1
  pigment { color rgbt <0.7,0.5,0.3,1/2> }
}

				#include "param.inc"
				#local Fx = function(u,v) {u*cos(v)}
				#local Fy = function(u,v) {u*sin(v)}
				#local Fz = function(u,v) {v}
				#local platform_ramp = object
				{
					Parametric(Fx,Fy,Fz,<0,0>,<1,2*pi>,30,30,"")
					scale 10
				}

