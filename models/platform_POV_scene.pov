//==================================================
//POV-Ray Main scene file
//==================================================
//This file has been created by PoseRay v3.12.2.456
//3D model to POV-Ray/Moray Converter.
//Author: FlyerX
//Email: flyerx_2000@yahoo.com
//Web: http://mysite.verizon.net/sfg0000/
//==================================================
//Files needed to run the POV-Ray scene:
//platform_POV_main.ini (initialization file - open this to render)
//platform_POV_scene.pov (scene setup of cameras, lights and geometry)
//platform_POV_geom.inc (geometry mesh)
//platform_POV_mat.inc (materials)
//Plat00.jpg
//Plat01.jpg
// 
//==================================================
//Model Statistics:
//Number of triangular faces..... 42402
//Number of vertices............. 26561
//Number of normals.............. 57113
//Number of UV coordinates....... 26225
//Number of lines................ 0
//Number of materials............ 5
//Number of groups/meshes........ 24
//Number of subdivision faces.... 0
//UV boundaries........ from u,v=(-3.993489,-2.983851)
//                        to u,v=(3.375087,0.9991546)
//Bounding Box....... from x,y,z=(-202.5934,0.04158981,-108.5112)
//                      to x,y,z=(204.9744,209.5526,107.7019)
//                 size dx,dy,dz=(407.5679,209.511,216.2132)
//                  center x,y,z=(1.190483,104.7971,-0.4046593)
//                       diagonal 506.7095
//Surface area................... 607319
//             Smallest face area 0.0004283285
//              Largest face area 43869.69
//Memory allocated for geometry.. 5 MBytes
// 
//==================================================
//IMPORTANT:
//This file was designed to run with the following command line options: 
// +W320 +H239 +FN +AM1 +A -UA
//if you are not using an INI file copy and paste the text above to the command line box before rendering
 
#include "platform_POV_geom.inc" //Geometry
 
global_settings {
  //This setting is for alpha transparency to work properly.
  //Increase by a small amount if transparent areas appear dark.
   max_trace_level 15
 
}
 
//CAMERA PoseRayCAMERA
camera {
        orthographic
        up	y*500
        right	x*500
        location	-z*1000
        direction	+z*1000
        rotate <30,0,0> //roll
        rotate <0,0,0> //pitch
        rotate <0,45,0> //yaw
        translate 0
        }
 
//PoseRay default Light attached to the camera
light_source {
              <-9.32617187920926E-8,2.18301177028479E-5,1013.41865927124> //light position
              color rgb <1,1,1>*1.6
              parallel
              point_at <-9.326172E-8,2.183012E-5,0>
              rotate <0,0,2.947006> //roll
              rotate <-2.883382,0,0> //elevation
              rotate <0,79.44086,0> //rotation
             }
 
//Background
background { color rgb<1,1,1>  }
 
//Assembled object that is contained in platform_POV_geom.inc
object{
      platform_
      }

union
{
	sphere		{0,    0.01 pigment{color rgb <0,0,0,>}}
	cylinder	{0, x, 0.01 pigment{color rgb <1,0,0,>}}
	cylinder	{0, y, 0.01 pigment{color rgb <0,1,0,>}}
	cylinder	{0, z, 0.01 pigment{color rgb <0,0,1,>}}
	finish {ambient 1}
	scale		110
	translate	<0,160,0,>
	no_shadow
	no_reflection
}
//==================================================
