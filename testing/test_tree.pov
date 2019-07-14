// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#declare TexQual = 1;
#include "colors.inc"

global_settings {
  assumed_gamma 1.0
}
default {finish {ambient 0 diffuse 1}}

// ----------------------------------------

camera {
  location  <0.0, 1, -2.0>
  up        y/2
  right     x/2*image_width/image_height
  look_at   <0.0, 0.0,  1.0>
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
  pigment { color rgb <0.7,0.5,0.3> }
}

#include "gh_tomtree_tree_mesh.inc"
object {TREE translate -x*1/2}

#include "gh_deciduous_tree.inc"
object {TREE translate +x*1/2}