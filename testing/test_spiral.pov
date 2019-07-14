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
  location  <0, 0, -1>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
  rotate x * 15
  rotate y * 45
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
  y, 0
  pigment { color rgbt <0.7,0.5,0.3,1/2> }
}

// ----------------------------------------

#declare dome_radius		= 32;
#declare Seed			= seed(8829464);
#declare Included		= 1;				// tells any included files that they are being included.
#macro gamma_color_adjust(in_color)
	#local out_gamma = 2.2;
	#local in_color = in_color + <0,0,0,0,0>;
	color rgbft
	<
		pow(in_color.red, out_gamma),
		pow(in_color.green, out_gamma),
		pow(in_color.blue, out_gamma),
		in_color.filter,
		in_color.transmit
	>
#end

union {
#local Side=10;
#local Max_Height=20;
#local Step=0.1;
#local Current=0;
#local Turn=60; /* Degrees of rotation per vertical unit */
#while (Current < Max_Height)
#local AA=<Side * (Max_Height - Current)/Max_Height, Current, Side *
(Max_Height - Current)/Max_Height>;
#local BB=<Side * (Max_Height - Current)/Max_Height, Current+Step, Side
* (Max_Height - Current)/Max_Height>;
box { AA*<-1,1,1>,BB rotate Turn*Current*y }
#local Current=Current+Step;
#end
}
