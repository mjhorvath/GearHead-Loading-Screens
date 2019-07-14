// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"
#include "glass.inc"

global_settings {
  assumed_gamma 1.0
}

// ----------------------------------------

camera {
  location  <0, 2, -4>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
  scale 100
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
  pigment { color rgb <0.7,0.5,0.3,1/2> }
}

// ----------------------------------------


union
{
	cylinder {0, <0,4,0>, 16}
	cylinder {0, <0,12,0>, 8}
	union
	{
		cylinder {<0,0,0>, <128,0,0>, 8 scale y * 1/2}
		cylinder {<128,-4,0>, <128,12,0>, 8}
//		cylinder {<64,-4,0>, <64,4,0>, 8}
		union
		{
			cylinder {<-128,0,0>, <0,0,0>, 8 scale y * 1/2}
			cylinder {<-128,-4,0>, <-128,12,0>, 8}
			cylinder {<-96,-4,0>, <-96,4,0>, 8}
			union
			{
				cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 000}
				cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 120}
				cone {y*4, 2, y*12, 0 translate z*4 rotate x * 15 rotate y * 240}
				translate y * 8
				translate x * -128
			}
			translate y * 8
			rotate +y * 15
			translate x * 128
		}
		translate y * 8
		rotate -y * 15
	}
	pigment {color rgb 1}
	scale 1/2
	rotate -x*90
}
