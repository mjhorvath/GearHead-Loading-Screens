


//------------------------------------------------------------------------------Central Axis and Main Struts

#if (!NoStruts)
	union
	{
		// central axis
//		difference
//		{
//			cylinder {+z * (hab_total_length/2 + nose_cone_position + 0), -z * (engine_start + engine_length + 0), central_axis_radius}
//			cylinder {+z * (hab_total_length/2 + nose_cone_position + 1), -z * (engine_start + engine_length + 1), central_axis_radius - metal_thick}
//		}
		// main struts
		#for (i, 0, 5)
			union
			{
				// large struts around remainder of the ship
				difference
				{
					cylinder {-z * (hab_total_length/2 - 0), -z * (engine_start + engine_length + 0), main_strut_radius}
					cylinder {-z * (hab_total_length/2 - 1), -z * (engine_start + engine_length + 1), main_strut_radius - metal_thick}
					bounded_by {box {<-main_strut_radius,-main_strut_radius,-(hab_total_length/2 - 0)>, <+main_strut_radius,+main_strut_radius,-(engine_start + engine_length + 0)>}}
				}
				// long struts around habitats
				difference
				{
					cylinder {+z * (hab_total_length/2 + 0), -z * (hab_total_length/2 + 0), main_strut_radius}
					cylinder {+z * (hab_total_length/2 + 1), -z * (hab_total_length/2 + 1), main_strut_radius - metal_thick}
					bounded_by {box {<+main_strut_radius,+main_strut_radius,+(hab_total_length/2 + 0)>, <-main_strut_radius,-main_strut_radius,-(hab_total_length/2 + 0)>}}
				}
/*
				// short struts between habitats
				difference
				{
					cylinder {+z * (hab_hub_length/2 + 0), -z * (hab_hub_length/2 + 0), main_strut_radius}
					cylinder {+z * (hab_hub_length/2 + 1), -z * (hab_hub_length/2 + 1), main_strut_radius - metal_thick}
					bounded_by {box {<+main_strut_radius,+main_strut_radius,+(hab_hub_length/2 + 0)>, <-main_strut_radius,-main_strut_radius,-(hab_hub_length/2 + 0)>}}
				}
*/
				translate +y * (main_body_radius - main_strut_radius)
				rotate +z * 60 * i
			}
		#end
		// around truss hub
		difference
		{
			cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}
			cylinder {-z * (main_strut_width+1), +z * 1, main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}}
			translate -z * (trusshub_start)
		}
		difference
		{
			cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}
			cylinder {-z * 1, +z * (main_strut_width+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}}
			translate -z * (trusshub_start + trusshub_length)
		}
		// around docking bay
		difference
		{
			cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}
			cylinder {-z * 1, +z * (main_strut_width+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}}
			translate -z * (dock_start)
		}
		difference
		{
			cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}
			cylinder {-z * (main_strut_width+1), +z * 1, main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}}
			translate -z * (dock_start + dock_length)
		}
		#for (i, 0, 5)
			cylinder
			{
				0, +y * main_body_radius - main_strut_radius, main_strut_radius
				rotate +z * 60 * i
				translate -z * (dock_start - main_strut_width/2)
			}
			cylinder
			{
				0, +y * main_body_radius - main_strut_radius, main_strut_radius
				rotate +z * 60 * i
				translate -z * (dock_start + dock_length + main_strut_width/2)
			}
		#end
		// at end of engines
		difference
		{
			cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}
			cylinder {-z * 1, +z * (main_strut_width+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}}
			translate -z * (engine_start + engine_length)
		}
		#for (i, 0, 5)
			cylinder
			{
				0, +y * main_body_radius - main_strut_radius, main_strut_radius
				rotate +z * 60 * i
				translate -z * (engine_start + engine_length - main_strut_width/2)
			}
		#end
		// at reactor
		difference
		{
			cylinder {-z * (main_strut_width/2+0), +z * (main_strut_width/2+0), main_body_radius}
			cylinder {-z * (main_strut_width/2+1), +z * (main_strut_width/2+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * (main_strut_width/2+0), +z * (main_strut_width/2+0), main_body_radius}}
			translate -z * (reactor_start + reactor_length/2)
		}
		// between habitats
		difference
		{
			cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}
			cylinder {-z * 1, +z * (main_strut_width+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}}
			translate -z * (hab_hub_length/2)
		}
		difference
		{
			cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}
			cylinder {-z * (main_strut_width+1), +z * 1, main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}}
			translate +z * (hab_hub_length/2)
		}
	/*
		#for (i, 0, 5)
			cylinder
			{
				0, +y * main_body_radius - main_strut_radius, main_strut_radius
				rotate +z * 60 * i
				translate -z * (hab_hub_length/2 - main_strut_width/2)
			}
			cylinder
			{
				0, +y * main_body_radius - main_strut_radius, main_strut_radius
				rotate +z * 60 * i
				translate +z * (hab_hub_length/2 - main_strut_width/2)
			}
		#end
	*/
		// at ends of habitats
		difference
		{
			cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}
			cylinder {-z * (main_strut_width+1), +z * 1, main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * (main_strut_width+0), +z * 0, main_body_radius}}
			translate -z * (hab_total_length/2)
		}
		difference
		{
			cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}
			cylinder {-z * 1, +z * (main_strut_width+1), main_body_radius - main_strut_radius * 2}
			bounded_by {cylinder {-z * 0, +z * (main_strut_width+0), main_body_radius}}
			translate +z * (hab_total_length/2)
		}
		texture {white_metal_texture}
	}
#end


//------------------------------------------------------------------------------Reactor & Liquid/Gas Storage

#if (!NoReactor)
	union
	{
		// nested spherical storage tanks
		difference
		{
			union
			{
				#local ring_max = 5;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					#local segment_radius = reactor_radius/5;
					difference
					{
						sphere {0,reactor_radius-segment_radius*ring_cnt+Meters}
						sphere {0,reactor_radius-segment_radius*ring_cnt-Meters}
						bounded_by {sphere {0,reactor_radius-segment_radius*ring_cnt+Meters}}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
				#local ring_max = 40;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					#local segment_radius = reactor_radius/50;
					difference
					{
						sphere {0,reactor_radius-segment_radius*ring_cnt+Meters/4}
						sphere {0,reactor_radius-segment_radius*ring_cnt-Meters/4}
						bounded_by {sphere {0,reactor_radius-segment_radius*ring_cnt+Meters/4}}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
			}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			bounded_by {sphere {0,reactor_radius*5/5		scale <0.99,0.99,1>}}
			texture {white_metal_texture}
		}
		// liquid/gas ball
		difference
		{
			sphere {0,reactor_radius*5/5		scale <0.99,0.99,1>}
			sphere {0,reactor_radius*1/5		scale <0.99,0.99,1>}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			bounded_by {sphere {0,reactor_radius*5/5		scale <0.99,0.99,1>}}
			material {water_material}
		}
		// reactor
		#local trumpet_radius = Meters * 16;
		#local trumpet_length = reactor_radius-trumpet_radius-ring_gap;
		#local reactor_Fx2 = function(u,v) {v}
		#local reactor_Fy2 = function(u,v) {trumpet_radius/pow(v+1,0.7)*cos(u)}
		#local reactor_Fz2 = function(u,v) {trumpet_radius/pow(v+1,0.7)*sin(u)}
		object
		{
			Parametric(reactor_Fx2,reactor_Fy2,reactor_Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate -y * 90
			translate -z*(+Meters*2-trumpet_radius)
		}
		object
		{
			Parametric(reactor_Fx2,reactor_Fy2,reactor_Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate +y * 90
			translate -z*(-Meters*2+trumpet_radius)
		}
		#local ball_radius = trumpet_radius;
		sphere
		{
			0, ball_radius*5/4
		}
//		torus
//		{
//			ball_radius*3, ball_radius*3/4
//			rotate x * 90
//		}
		// spherical trusses around reactor
		difference
		{
			#declare N = 2;
			#declare Half = 0;
			#declare Method = 1;
			#declare Disc = 0;
			#declare R_Ten = 0.01 / N;
			#declare R_Hen = 0.01 / N;
			#declare Thickness = big_truss_thick;
			verbose_include("sphere.inc", 0)
			union
			{
				object {Ten}
				object {Hen}
				scale reactor_radius * 1.01
			}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			bounded_by {sphere {0, (reactor_radius + big_truss_thick) * 1.01}}
		}
		texture {white_metal_texture}
		translate -z * (reactor_start + reactor_length/2)
	}
#end


//------------------------------------------------------------------------------Engines

#if (!NoEngines)
	// parabolic exhaust cone
	#local z_position = pow(nozzle_radius,2)/nozzle_radius * 4;
	#local exhaust_scale = nozzle_radius * 3/2;
	verbose_include("gh_rocket_chess_exhaust.inc", 0)
	union
	{
		// spherical fuel tanks
		union
		{
			#for (i, 0, 5)
				sphere
				{
					-x * engine_sphere_distance, engine_sphere_radius
					rotate +z * i * 60
				}
			#end
			texture {white_metal_texture}
		}
		intersection
		{
			difference
			{
				object
				{
					Paraboloid_Z
					scale nozzle_radius
					translate -z * Meters
				}
				object
				{
					Paraboloid_Z
					scale nozzle_radius
					translate +z * Meters
				}
				rotate y * 180
			}
			plane {-z, z_position}
			// incorrect
//			bounded_by {cylinder {0, -z * z_position, nozzle_radius}}
			texture {engine_nozzle_texture}
			translate -z * (engine_sphere_radius)
		}
		object
		{
			Exhaust_Object
			rotate <0,90,0>
			scale exhaust_scale
			translate -z * (engine_sphere_radius + Meters * 128)
		}
/*
		// engine connector hub
		difference
		{
			cylinder
			{
				+z * engine_sphere_radius, -z * engine_sphere_radius, engine_hub_radius
			}
		//	#if (!ShowWhole)
		//		object {cutaway_object1}
		//	#end
			texture {white_metal_texture}
		}
		// large arms connecting each fuel pod to the axle
	//	#local truss_rotate = 45;
		#local truss_sides = 4;
		#local truss_sections = 4;
		#local truss_thickness = big_truss_thick;
		#local truss_radius = big_truss_radius - big_truss_thick;
		#local truss_point1 = -x * (engine_hub_radius);
		#local truss_point2 = -x * (engine_sphere_distance - engine_sphere_radius);
		union
		{
			#local truss_arms_max = 6;
			#local truss_arms_cnt = 0;
			#while (truss_arms_cnt < truss_arms_max)
				union
				{
					object {#include "truss.inc"}
					cylinder {truss_point1, truss_point2, Meters * 4}
					rotate +z * 360/truss_arms_max * truss_arms_cnt
				}
				#local truss_arms_cnt = truss_arms_cnt + 1;
			#end
			texture {white_metal_texture}
		}
*/
		translate -z * (engine_start + engine_length/2)
	}
	// big tanks
	union
	{
		#for (i, 0, 5)
			object
			{
				fuel_tank(engine_fuel_length, engine_fuel_radius)
				translate -x * (engine_fuel_radius * 2)
				rotate +z * (60 * i)
			}
			object
			{
				fuel_tank(engine_fuel_length, engine_fuel_radius)
				translate -x * (main_body_radius - engine_fuel_radius - main_strut_radius * 2)
				rotate +z * (60 * i + 30)
			}
		#end
		texture {white_metal_texture}
		translate -z * (dock_start + dock_length/2)
	}
#end


//------------------------------------------------------------------------------Tanks, Blinky Lights & Thrusters

#if (!NoGreebles)
/*
	// tanks
	#local tank_radius = Meters * 16;
	#local tank_length = Meters * 128;
	#local tank_object = object
	{
		fuel_tank(tank_length,tank_radius)
		translate -y*(main_body_radius+tank_radius)
	}
	union
	{
		object {tank_object		rotate -z * 030}
		#if (ShowWhole)
			object {tank_object	rotate -z * 090}
			object {tank_object	rotate -z * 150}
			object {tank_object	rotate -z * 210}
			object {tank_object	rotate -z * 270}
		#end
		object {tank_object		rotate -z * 330}
		texture {white_metal_texture}
	}
*/
	#local blinky_group_1 = union
	{
		// habitat blinkies
		object {blinky_sphere(blinky_radius)	translate <0,-(outer_shell_radius1+blinky_radius),-(hab_section_length/2+hab_section_offset)>}
		object {blinky_sphere(blinky_radius)	translate <0,-(outer_shell_radius1+blinky_radius),+(hab_section_length/2+hab_section_offset)>}
		object {blinky_sphere(blinky_radius)	translate <0,-(outer_shell_radius1+blinky_radius),-(hab_section_length/2-hab_section_offset)>}
		object {blinky_sphere(blinky_radius)	translate <0,-(outer_shell_radius1+blinky_radius),+(hab_section_length/2-hab_section_offset)>}
		// docking bay blinkies
		object {blinky_sphere(blinky_radius)	translate <0,-(dock_radius1+blinky_radius),-(dock_start+dock_length)>}
		object {blinky_sphere(blinky_radius)	translate <0,-(dock_radius1+blinky_radius),-(dock_start)>}
		// engine blinkies
		object {blinky_sphere(blinky_radius)	translate <0,-(dock_radius1+blinky_radius),-(engine_start+engine_length)>}
	}
	union
	{
		object {blinky_group_1	rotate +z * 270}
		object {blinky_group_1	rotate +z * 330}
		object {blinky_group_1	rotate +z * 030}
		object {blinky_group_1	rotate +z * 090}
		#if (ShowWhole)
			object {blinky_group_1	rotate +z * 150}
			object {blinky_group_1	rotate +z * 210}
		#end
	}
	// nose cone blinkies
	union
	{
		#for (i, 3, nose_cone_length, 1)
			#local y_new = nose_cone_radius/4 * i * 2 + nose_wire_radius_thick + blinky_radius;
			#local z_new = nose_cone_radius/4 * pow(i, 2);
			#declare blinky_group_3 = union
			{
				object {blinky_sphere(blinky_radius)	translate <0,-y_new,+z_new>}
			}
			object {blinky_group_3	rotate +z * 270}
			object {blinky_group_3	rotate +z * 330}
			object {blinky_group_3	rotate +z * 030}
			object {blinky_group_3	rotate +z * 090}
			#if (ShowWhole)
				object {blinky_group_3	rotate +z * 150}
				object {blinky_group_3	rotate +z * 210}
			#end
		#end
		rotate +y * 180
		translate +z * (hab_total_length/2 + nose_cone_position)
	}
	// thrusters
	#local thruster_nozzle = union
	{
		cone {<0, 0, 0>, 0, <0, 0, -2>, 1 open hollow}
		cylinder {<0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow}
		scale 1/2
	}
	#local thruster_aggregate = union
	{
		sphere {0,1}
	//	object {thruster_nozzle	rotate <000, 000, 0> translate < 0, 0,-3>}
	//	object {thruster_nozzle	rotate <000, 180, 0> translate < 0, 0,+3>}
		object {thruster_nozzle	rotate <000, 090, 0> translate <-1, 0, 0>}
		object {thruster_nozzle	rotate <000, 270, 0> translate <+1, 0, 0>}
		object {thruster_nozzle	rotate <270, 000, 0> translate < 0,-1, 0>}
		object {fuel_tank(4,1)}
		scale thruster_tank_radius
	}
	#local thruster_group = union
	{
		object {thruster_aggregate	translate <0,-1*(main_body_radius+thruster_tank_radius),-1*(engine_start+engine_length/2)>}
		object {thruster_aggregate	translate <0,-1*(main_body_radius+thruster_tank_radius),-1*(reactor_start+reactor_length/2)>}
		object {thruster_aggregate	translate <0,-1*(main_body_radius+thruster_tank_radius),-1*(hab_section_offset)>}
		object {thruster_aggregate	translate <0,-1*(main_body_radius+thruster_tank_radius),+1*(hab_section_offset)>}
		texture {white_metal_texture}
	}
	union
	{
		object {thruster_group	rotate +z * 300}
		object {thruster_group	rotate +z * 360}
		object {thruster_group	rotate +z * 060}
		#if (ShowWhole)
			object {thruster_group	rotate +z * 120}
			object {thruster_group	rotate +z * 180}
			object {thruster_group	rotate +z * 240}
		#end
	}
#end


//------------------------------------------------------------------------------Neighboring Craft

#if (!NoOuterShips)
/*
	// http://skotan.deviantart.com/art/Aquila-Mk-I-spacecraft-185944452
	union
	{
		verbose_include("Aquila-Mk_I.pov", 0)
		scale		32
		translate	+x * outer_shell_radius1
		translate	-z * dock_start
	}
*/
	// http://povrayinclude.wytraven.com/links.html
	union
	{
		verbose_include("SPACESHP.POV", 0)
		scale		2
		rotate		+x * 090
		translate	-y * 0
		translate	+x * (outer_shell_radius1 + Meters * 128)
		translate	-z * (city_length/2 + reactor_length)
	}

	// http://news.povray.org/povray.binaries.scene-files/thread/%3C4dfdbaad%40news.povray.org%3E/
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		scale 1/2
		translate -z*dock_start*5/4
		translate +x*city_radius*5/4
	}
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		scale 1/2
		translate -z*dock_start*5/4
		translate +x*city_radius*5/4
		translate -x*Meters*32
		translate +z*Meters*32
	}
#end
