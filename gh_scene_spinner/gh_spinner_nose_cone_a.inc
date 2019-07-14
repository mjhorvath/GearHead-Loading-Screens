#local z_position = habitat_length/2 + outer_shell_radius1;
#local shield_scale = outer_shell_radius1 * 3;
#local ring_distance = Meters * 256;
#local ring_amount = 8;
#local main_cone = difference
{
	object
	{
		Piriform
		sturm
		rotate +y * 90
		translate +z * 1
		scale <shield_scale,shield_scale,outer_shell_radius1 * 20>
	}
	object
	{
		Piriform
		sturm
		rotate +y * 90
		translate +z * 1
		scale <shield_scale,shield_scale,outer_shell_radius1 * 20>
		scale 0.99
	}
}
difference
{
	union
	{
		// glass portion
		intersection
		{
			object {main_cone scale 0.99}
			plane {+z, ring_distance * ring_amount}
		}
		// longitudinal arcs
		union
		{
			#local count_max = 4;
			#local count_itr = 0;
			#while (count_itr < count_max)
				#local turn_angle = count_itr * 45;
				intersection
				{
					object {main_cone}
					plane {+z, ring_distance * ring_amount}
					plane {+x, Meters * 8}
					plane {-x, Meters * 8}
					rotate +z * turn_angle
				}
				#local count_itr = count_itr + 1;
			#end
			texture {white_metal_texture}
		}
		// latitudinal rings
		union
		{
			#local ring_max = ring_amount;
			#local ring_cnt = 0;
			#while (ring_cnt < ring_max)
				intersection
				{
					object {main_cone}
					plane {+z, Meters * 8    translate +z * ring_distance * (ring_cnt + 1/2)}
					plane {-z, Meters * 8    translate +z * ring_distance * (ring_cnt + 1/2)}
				}
				#local ring_cnt = ring_cnt + 1;
			#end
			texture {white_metal_texture}
		}
		rotate +y * 180
		translate +z * z_position
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
//	texture {pigment {color rgbt 1}}
	texture {dome_texture}
}
// tip
intersection
{
	object {main_cone}
	plane {+z, Meters * 16}
	rotate +y * 180
	translate +z * z_position
	texture {white_metal_texture}
}
// comms trusses
#declare truss_sides = 6;
#declare truss_sections = 1;
#declare truss_radius = Meters*16;
#declare truss_thickness = Meters/2;
#declare truss_point1 = -z*Meters*16;
#declare truss_point2 = 0;
#local comm_truss = object
{
	#include "truss.inc"
	texture {white_metal_texture}
}
#local comm_dish = union
{
	difference
	{
		object {Paraboloid_Z}
		object {Paraboloid_Z	scale 0.999}
		plane {-z,-0.05}
		rotate y * 180
		scale		dock_radius1/4
	}
	cylinder {<0,0,0>, <0,0,-Meters*8>, Meters/2}
	scale 2
	translate -z*Meters*16
}
#local comm_dome = difference
{
	sphere {-z*Meters*16, Meters*16}
	plane {-z,0}
}
#local comm_anten = union
{
	cylinder {<0,0,0>, <0,0,-city_length/16>, Meters}
	cylinder {<0,0,0>, <0,0,-city_length/4>, Meters/2}
	cylinder {<0,-Meters*32,0>, <0,-Meters*32,-city_length/32>, Meters}
	cylinder {<0,-Meters*32,0>, <0,-Meters*32,-city_length/8>, Meters/2}
	object {blinky_sphere    translate <0,0,-city_length/4-blinky_radius>}
	sphere {blinky_sphere    translate <0,-Meters*32,-city_length/8-blinky_radius>}
}
union
{
	object
	{
		comm_dome
		translate	-y * Meters * 64
		rotate		+z * 300
	}
	object
	{
		comm_truss
		translate	-y * Meters * 64
		rotate		+z * 300
	}
	object
	{
		comm_dish
		translate	-y * Meters * 64
		rotate		+z * 120
	}
	object
	{
		comm_truss
		translate	-y * Meters * 64
		rotate		+z * 120
	}
	object
	{
		comm_anten
	}
	rotate		+y * 180
	translate 	+z * z_position
	texture {white_metal_texture}
}

