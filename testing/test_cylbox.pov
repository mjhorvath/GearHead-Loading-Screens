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

global_settings
{
	assumed_gamma 1.0
}
default {finish {ambient 0 diffuse 1}}

// ----------------------------------------

camera
{
	orthographic
	location	z*-12
	direction	z
	up		y
	right		x*image_width/image_height
	scale		16
//	rotate		x * 30
//	rotate		y * 30
	translate	y * -8
}

sky_sphere
{
	pigment
	{
		gradient y
		color_map
		{
			[0.0 rgb <0.6,0.7,1.0>]
			[0.7 rgb <0.0,0.1,0.8>]
		}
	}
}

light_source
{
	<0, 0, 0>            // light's position (translated below)
	color rgb <1, 1, 1>/1  // light's color
	translate <-30, 30, -30>
}

light_source
{
	<0, 0, 0>            // light's position (translated below)
	color rgb <1, 1, 1>/1  // light's color
	translate <-30, 30, +30>
}

// ----------------------------------------

#declare city_radius = 10;
#declare city_circum = pi * city_radius * 2;
#declare city_use_mesh = 1;
#include "CG_PRIMITIVES.INC"

// bounding boxes are rotated and smaller
#macro cyl_pyr_mesh_fit(in1_pos, in2_pos, segments_total)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	#local half_angle	= (in2_zangle - in1_zangle)/2;
	#local step_angle	= (in2_zangle - in1_zangle)/segments_total;
	#local aaa = vrotate(<0,-in1_height,in1_pos.z>, z * -half_angle);
	#local baa = vrotate(<0,-in1_height,in1_pos.z>, z * +half_angle);
	#local aba = vrotate(<0,-in2_height,in1_pos.z>, z * -half_angle);
	#local bba = vrotate(<0,-in2_height,in1_pos.z>, z * +half_angle);
	#local aab = vrotate(<0,-in1_height,in2_pos.z>, z * -half_angle);
	#local bab = vrotate(<0,-in1_height,in2_pos.z>, z * +half_angle);
	#local abb = vrotate(<0,-in2_height,in2_pos.z>, z * -half_angle);
	#local bbb = vrotate(<0,-in2_height,in2_pos.z>, z * +half_angle);
	#local min_x = min(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local min_y = min(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local min_z = min(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local max_x = max(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local max_y = max(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local max_z = max(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local min_y = min(min_y,-city_radius);
	#if (half_angle >= 90)
		#local min_x = min(min_x,-city_radius);
		#local max_x = max(max_x,+city_radius);
		#if (half_angle >= 180)
			#local max_y = max(max_y,+city_radius);
		#end
	#end
	#local out_mesh = mesh
	{
		#local segments_count	= 0;
		#while (segments_count <= segments_total)
			#local aaa_new = <0,-in1_height,in1_pos.z>;
			#local aba_new = <0,-in2_height,tand(half_angle)*+in2_pos.y + in1_pos.z>;
			#local aab_new = <0,-in1_height,in2_pos.z>;
			#local abb_new = <0,-in2_height,tand(half_angle)*-in2_pos.y + in2_pos.z>;
			#local aaa_new = vrotate(aaa_new, z * (step_angle * segments_count - half_angle));
			#local aba_new = vrotate(aba_new, z * (step_angle * segments_count - half_angle));
			#local aab_new = vrotate(aab_new, z * (step_angle * segments_count - half_angle));
			#local abb_new = vrotate(abb_new, z * (step_angle * segments_count - half_angle));
			#if (segments_count = 0)
				triangle {aba_new,aab_new,abb_new}
				triangle {aab_new,aba_new,aaa_new}
			#else
				triangle {aba_new,aaa_old,aba_old}
				triangle {aaa_old,aba_new,aaa_new}
				triangle {abb_old,aab_new,abb_new}
				triangle {aab_new,abb_old,aab_old}
				triangle {abb_new,aba_old,abb_old}
				triangle {aba_old,abb_new,aba_new}
				triangle {aaa_new,aab_old,aaa_old}
				triangle {aab_old,aaa_new,aab_new}
				#if (segments_count = segments_total)
					triangle {abb_new,aaa_new,aba_new}
					triangle {aaa_new,abb_new,aab_new}
				#end
			#end
			#local aaa_old = aaa_new;
			#local aba_old = aba_new;
			#local aab_old = aab_new;
			#local abb_old = abb_new;
			#local segments_count = segments_count + 1;
		#end
		inside_vector y
		bounded_by {box {<min_x,min_y,min_z>,<max_x,max_y,max_z>}}
	}
	union
	{
		box
		{
			<min_x,min_y,min_z>,<max_x,max_y,max_z>
			pigment {color rgbt <0,0,1,3/4>}
		}
		union
		{
			sphere {aaa,0.1}
			sphere {baa,0.1}
			sphere {aba,0.1}
			sphere {bba,0.1}
			sphere {aab,0.1}
			sphere {bab,0.1}
			sphere {abb,0.1}
			sphere {bbb,0.1}
			pigment {color rgb y}
		}
		object
		{
			out_mesh
		}
			rotate z * (half_angle + in1_zangle)
	}
#end

#declare test_mesh	=  cyl_pyr_mesh_fit(<2,0,0>*-1,<2,2,2>*+1, 12)
//#declare test_bound	= cyl_box_bound_fit(<2,0,0>*-1,<4,2,2>*+1)
object {test_mesh	pigment {color rgb x}	translate +z*0}
//object {test_bound	pigment {color rgb z}	translate +z*2}

cylinder
{
	0,z*2,city_radius
	translate z * 4
	pigment {color rgb 1}
}

intersection
{
	object
	{
		sph_mesh(-2, 2, 24)
//		cyl_mesh(-2, -5, 2, 24)
	//	con_mesh(-2, 0, -5, 2, 24)
	}
	plane {-x+y,0}
	pigment {color rgb y}
	translate -z*2
}

intersection
{
	cylinder
	{
		0,z*+40,1/4
		pigment {color rgb y}
	}
	plane {-x+y,0}
	pigment {color rgb y}
	translate -z*2
}