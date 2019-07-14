//---------------------------------------------------------------------------
//---------------------------- objects in scene ----------------------------
//---------------------------------------------------------------------------

#local dock_width = 8;
#local dock_length = 64;
#local dock_height = 1;
#local pylon_radius = 1/2;
#local pylon_height = 4;
#declare loading_dock = union
{
	box
	{
		<-dock_width/2,0,-pylon_radius>,
		<+dock_width/2,-dock_height,+pylon_radius+dock_length>
	}
	cylinder {<-dock_width/2+pylon_radius,0,dock_length*0/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*0/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*0/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*0/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*1/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*1/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*1/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*1/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*2/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*2/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*2/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*2/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*3/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*3/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*3/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*3/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*4/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*4/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*4/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*4/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*5/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*5/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*5/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*5/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*6/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*6/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*6/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*6/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*7/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*7/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*7/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*7/8>,pylon_radius}

	cylinder {<-dock_width/2+pylon_radius,0,dock_length*8/8>,<-dock_width/2+pylon_radius,-pylon_height,dock_length*8/8>,pylon_radius}
	cylinder {<+dock_width/2-pylon_radius,0,dock_length*8/8>,<+dock_width/2-pylon_radius,-pylon_height,dock_length*8/8>,pylon_radius}

	pigment {color rgb 1/2}
	scale 4
}

#ifndef (Included)
// PoVRay 3.7 Scene File " ... .pov"
// author:  ...
// date:    ...
//--------------------------------------------------------------------------
#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 
//--------------------------------------------------------------------------
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"
#include "stones.inc"
#include "woods.inc"
#include "shapes.inc"
#include "shapes2.inc"
#include "functions.inc"
#include "math.inc"
#include "transforms.inc"
//--------------------------------------------------------------------------
// camera ------------------------------------------------------------------
#declare Camera_0 = camera {perspective angle 75               // front view
                            location  <0.0 , 1.0 ,-3.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
#declare Camera_1 = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <2.0 , 2.5 ,-3.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>
				scale 20}
#declare Camera_2 = camera {/*ultra_wide_angle*/ angle 90  //right side view
                            location  <3.0 , 1.0 , 0.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
#declare Camera_3 = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <0.0 , 3.0 ,-0.001>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
camera{Camera_1}
// sun ----------------------------------------------------------------------
light_source{< 3000,3000,-3000> color White}
// sky ----------------------------------------------------------------------
sky_sphere { pigment { gradient <0,1,0>
                       color_map { [0.00 rgb <0.6,0.7,1.0>]
                                   [0.35 rgb <0.1,0.0,0.8>]
                                   [0.65 rgb <0.1,0.0,0.8>]
                                   [1.00 rgb <0.6,0.7,1.0>] 
                                 } 
                       scale 2         
                     } // end of pigment
           } //end of skysphere

object {loading_dock}
#end

