#include "colors.inc"
#include "math.inc"
#local scene_scale = 1000;

global_settings
{
	assumed_gamma 1.0
}
default {finish {ambient 0 diffuse 1}}


// ----------------------------------------

camera
{
	orthographic
	location	z*-1
	direction	z
	up		y
	right		x*image_width/image_height
	scale		2 * scene_scale
	rotate		x * 30
	rotate		y * 30
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
	0
	color rgb 1
	translate <-3,+3,-3> * scene_scale
}

light_source
{
	0
	color rgb 1
	translate <-3,+3,+3> * scene_scale
}


// ----------------------------------------

#macro sph_macro(in_pt, in_rd, use_mesh)
	#if (use_mesh)
		sph_mesh(in_pt, in_rd, 24)
	#else
		sphere {in_pt, in_rd}
	#end
#end
#macro sph_mesh(in_pt, in_rd, segments_total)
	#local mesh_object = mesh
	{
		#local theta_total = segments_total;
		#local phi_total = floor(segments_total/2);
		#local theta_count = 0;
		#while (theta_count <= theta_total)
			#local theta_angle_new = radians(360 * theta_count/theta_total);
			#local phi_count = 0;
			#while (phi_count <= phi_total)
				#local phi_angle_new = radians(180 * phi_count/phi_total);
				#if ((theta_count > 0) & (phi_count > 0))
					#local p1 = in_rd*<cos(theta_angle_new)*sin(phi_angle_new),cos(phi_angle_new),sin(theta_angle_new)*sin(phi_angle_new)>;
					#local p2 = in_rd*<cos(theta_angle_old)*sin(phi_angle_new),cos(phi_angle_new),sin(theta_angle_old)*sin(phi_angle_new)>;
					#local p3 = in_rd*<cos(theta_angle_new)*sin(phi_angle_old),cos(phi_angle_old),sin(theta_angle_new)*sin(phi_angle_old)>;
					#local p4 = in_rd*<cos(theta_angle_old)*sin(phi_angle_old),cos(phi_angle_old),sin(theta_angle_old)*sin(phi_angle_old)>;
					triangle {p1,p2,p3}
					triangle {p4,p3,p2}
				#end
				#local phi_angle_old = phi_angle_new;
				#local phi_count = phi_count + 1;
			#end
			#local theta_angle_old = theta_angle_new;
			#local theta_count = theta_count + 1;
		#end
		inside_vector y
	}
	object
	{
		mesh_object
		translate	in_pt
		bounded_by {sphere {in_pt, in_rd}}
	}
#end


// ----------------------------------------

union
{
	#local temp_seed = seed(0239454196);
	#local sphere_total = scene_scale;
	#local sphere_count = 0;
	#while (sphere_count < sphere_total)
		#local sphere_pos = <rand(temp_seed)*scene_scale-scene_scale/2,rand(temp_seed)*scene_scale-scene_scale/2,rand(temp_seed)*scene_scale-scene_scale/2>;
		object {sph_macro(sphere_pos, scene_scale/100, 0)}
//		object {sph_macro(sphere_pos, scene_scale/100, 1)}
		#local sphere_count = sphere_count + 1;
	#end
	pigment {color rgb x}
}
