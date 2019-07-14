// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#include "colors.inc"
#include "math.inc"
#include "shapes.inc"
#include "shapesq.inc"

#declare city_radius = 10;
#declare city_circum = pi * city_radius * 2;
#declare city_use_mesh = 1;
#include "CG_PRIMITIVES.INC"


// ----------------------------------------

global_settings
{
	assumed_gamma 1.0
}
default {finish {ambient 0 diffuse 1}}
background {color rgb 1/2}


// ----------------------------------------

#local temp_camera_1 = camera
{
  orthographic
  location  z*-12
  direction  z
  up    y
  right    x*image_width/image_height
  scale    32
}

#local temp_light_1 = light_source
{
  0
  color rgb 1
  translate <-30, 30, -30>
}

#local temp_light_2 = light_source
{
  0
  color rgb 1
  translate <-30, 30, +30>
}


// ----------------------------------------

union
{
  object {temp_light_1}
  object {temp_light_2}
//  camera {temp_camera_1}  // doesn't work!!!
}

//object {temp_camera_1}  // doesn't work!!!
camera {temp_camera_1}  // works!!!


// ----------------------------------------

sphere
{
	0,1
	pigment {color rgb x}
}