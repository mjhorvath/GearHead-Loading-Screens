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
  location  <0.0, 0.5, -4.0>
  direction 1.5*z
  right     x*image_width/image_height
  look_at   <0.0, 0.0,  0.0>
  scale 20
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

// ----------------------------------------

#macro gamma_color_adjust(in_color)
	#if (version < 3.7)
		#local out_gamma = 2.2;
	#else
		#local out_gamma = 1;
	#end
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

#declare Fx = function(u,v) {v}
#declare Fy = function(u,v) {6/pow(v+1,0.7)*cos(u)}
#declare Fz = function(u,v) {6/pow(v+1,0.7)*sin(u)}

#include "param.inc"

object
{
	Parametric(Fx,Fy,Fz,<0,0>,<2*pi,17>,30,30,"")
	rotate y * 45
	texture
	{
		pigment {gamma_color_adjust(<1,1,1>)}
//		finish {reflection 1}
	}
}


/*
	union
	{
		#include "param.inc"
		#declare Fx = function(u,v) {v}
		#declare Fy = function(u,v) {city_units*16/pow(v+1,0.7)*cos(u)}
		#declare Fz = function(u,v) {city_units*16/pow(v+1,0.7)*sin(u)}
		object
		{
			Parametric(Fx,Fy,Fz,<0,0>,<2*pi,ring_length/2>,30,30,"")
			rotate -y * 90
			translate -z*(city_length/2+ring_gap*2+city_units*2+ring_length/2)
		}
		object
		{
			Parametric(Fx,Fy,Fz,<0,0>,<2*pi,ring_length/2>,30,30,"")
			rotate +y * 90
			translate -z*(city_length/2+ring_gap*2+city_units*2+ring_length/2)
		}
		texture
		{
			pigment {gamma_color_adjust(<1,1,1>)}
	//		finish {reflection 1}
		}
	}
*/