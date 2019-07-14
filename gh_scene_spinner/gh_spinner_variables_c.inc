// citygen variables (mostly)
#declare city_rotate		= 30;					// float, degrees
#declare city_night		= false;				// boolean, obsolete?
#declare city_right_hand_drive	= false;				// boolean
#declare city_default_objects	= false;				// boolean
#declare city_use_mesh		= false;				// boolean
#declare city_all_mesh		= false;				// boolean
#declare city_tileable		= "dummy text";					// boolean, turning this off has weird side-effects!!
#declare city_storey_height	= Meters * 3.5;				// float, for reference, people are between 1.0 and 2.0 meters tall
#declare city_ped_density	= 1/64/Meters;				// float, so far this is just used for sidewalks along streets, it should be used everywhere there are pedestrians
#declare city_grass_height	= Meters / 4;				// too thin and it gets clipped by the pavement
#declare city_tree_height	= Meters * 12;				// float
#declare city_hide_buildings	= NoBuildings;				// boolean
#declare city_use_mesh		= 0;					// boolean, replace some basic CSG shapes with meshes? may not work 100% of the time
#declare total_lanes		= (NewTrain ? 2 : 2);			// integer, in both directions, including half lanes for bikes (minimum 2)
#declare nominal_traffic_width	= Meters * (NewTrain ? 8 : 8);		// float
#declare nominal_building_width	= Meters * 64;				// float
#declare traffic_spacing	= Meters * 256;				// float
#declare traffic_width		= nominal_traffic_width/total_lanes;	// float
#declare traffic_lanes		= floor(total_lanes/2);			// integer, in each direction...
#declare pavement_width		= Meters * 4;				// float
#declare building_width		= nominal_building_width - pavement_width * 2;			// float
#declare min_building_height	= city_storey_height * 6;		// float
#declare max_building_height	= city_storey_height * 12;		// float
#declare building_height_turb	= 1;					// float, between 0 and 1
#declare street_height		= 0;					// to do, may conflict with citygen...
#declare street_width		= nominal_traffic_width;		// float
#declare rail_ped_thick		= Meters;				// float, rail pedestal leg
#declare rail_width		= street_width/2;			// float
#declare rail_height		= Meters * 5;				// float
#declare rail_thick		= Meters/2;				// float
#declare rail_plat_thick	= Meters/2;				// float
#declare rail_plat_radius	= street_width;				// float
#declare rail_ramp_width	= Meters * 2;				// float
#declare rail_cars_number	= 3;					// integer, odd values only
#declare rail_cars_height	= Meters * 3;				// float
#declare rail_buffer		= Meters * 22;
#declare big_block_length_x	= nominal_traffic_width * 1 + nominal_building_width * 3;		// float
#declare big_block_length_z	= nominal_traffic_width * 3 + nominal_building_width * 6;		// float
#declare sml_block_length_x	= nominal_traffic_width * 0 + nominal_building_width * 1;		// float
#declare sml_block_length_z	= nominal_traffic_width * 1 + nominal_building_width * 1;		// float
#declare city_sections		= <2,0,1>;				// vector of integers
#declare city_circum		= (big_block_length_x * 3 + sml_block_length_x * 3) * city_sections.x;		// float, the inner circumference of the spinner colony
#declare city_length		= (big_block_length_z * 1 + sml_block_length_z * 0) * city_sections.z;		// float, the length of the city along the long axis
#declare city_radius		= city_circum/2/pi;			// float, the radius of the spinner colony's ground surface
#declare big_block_angle	= big_block_length_x/city_circum * 360;
#declare sml_block_angle	= sml_block_length_x/city_circum * 360;
#declare street_angle		= street_width/city_circum * 360;
#declare streetlamp_number	= 3;					// integer, the number present on each side of a building
#declare trashcan_number	= 2;					// integer, the number present on each side of a building
#declare pottedplant_number	= 5;					// integer, the number present on each side of a building
#declare people_max_height	= Meters * 2;				// float

// scene variables (mostly)
#declare ring_gap		= Meters * 2;				// float
#declare metal_thick		= Meters * 2;				// float
#declare ext_glass_thick	= Meters;				// float
#declare int_glass_thick	= Meters / 100;				// float
#declare inner_rock_thick	= Meters * 4;				// float
#declare outer_rock_thick	= Meters * 16;				// float
#declare central_axis_radius	= Meters * 6;				// float
#declare hab_hub_length		= Meters * 64;				// float
#declare hab_section_length	= city_length + metal_thick * 2;	// float
#declare hab_section_offset	= hab_section_length/2 + hab_hub_length/2;	// float
#declare hab_total_length	= hab_section_length * 2 + hab_hub_length;	// float
#declare hab_cap_nudge_angle	= street_angle - 30;				// float
#declare inner_shell_radius1	= city_radius + inner_rock_thick + metal_thick;	// float
#declare inner_shell_radius2	= city_radius + inner_rock_thick;	// float
#declare inner_shell_radius3	= city_radius;				// float
#declare inner_shell_bulge	= inner_shell_radius3/8;		// float
#declare outer_shell_radius1	= inner_shell_radius1 + ring_gap + outer_rock_thick + metal_thick * 2;		// float
#declare outer_shell_radius2	= outer_shell_radius1 - metal_thick;		// float
#declare outer_shell_radius3	= outer_shell_radius2 - outer_rock_thick;	// float
#declare outer_shell_radius4	= outer_shell_radius3 - metal_thick;		// float
//#declare main_body_radius	= Meters * 224;				// float
#declare main_strut_radius	= Meters * 4;				// float
#declare main_strut_width	= Meters * 8;				// float
#declare main_body_radius	= outer_shell_radius1 + main_strut_radius * 2;	// float
#declare trusshub_start		= hab_total_length/2 + Meters * 64;	// float
#declare trusshub_length	= Meters * 128;				// float
#declare nose_cone_radius	= outer_shell_radius1 * 4/3;		// float
#declare nose_cone_position	= nose_cone_radius + Meters * 64;	// float
#declare nose_cone_length	= 4.6;					// float, t-value
#declare nose_wire_radius_thick	= Meters/1;				// float
#declare nose_wire_radius_thin	= Meters/4;				// float
#declare nose_para_multi	= 10;					// float
#declare window_radius		= outer_shell_radius1 * 2/9;		// float
//#declare reactor_start	= trusshub_start + trusshub_length;	// float
#declare reactor_start		= trusshub_start;			// float
#declare reactor_radius		= Meters * 192;				// float
#declare reactor_length		= reactor_radius * 2;			// float
#declare dock_length		= Meters * 256;				// float
#declare dock_start		= reactor_start + reactor_length;	// float
#declare dock_radius1		= main_body_radius;			// float
#declare dock_radius2		= dock_radius1 * 1/2;			// float
#declare dock_depth		= Meters * 48;				// float
#declare dock_thick		= Meters * 4;				// float
#declare engine_sphere_radius	= dock_radius2/3;			// float
#declare engine_sphere_distance	= engine_sphere_radius * 2;		// float
#declare engine_start		= dock_start + dock_length;		// float
#declare engine_length		= engine_sphere_radius * 2;		// float
#declare engine_hub_radius	= Meters * 32;				// float
#declare engine_fuel_radius	= engine_sphere_radius;			// float
#declare engine_fuel_length	= dock_length - engine_fuel_radius * 2;	// float
#declare nozzle_length		= 0;					// float
#declare nozzle_radius		= Meters * 32;				// float
#declare total_length		= nose_cone_position + engine_start + engine_length + nozzle_length;		// float
#declare agridome_radius	= Meters * 32;				// float
#declare agridome_ringrad	= main_body_radius * 2;			// float
#declare agridome_ringgap	= Meters * 128;
#declare panel_gap		= Meters * 8;				// float
#declare panel_width		= Meters * 64;				// float
#declare panel_length		= panel_width * 2;			// float
#declare panel_thick		= Meters/2;				// float
#declare panel_mortar		= Meters;				// float
#declare panel_number		= 4;					// integer
#declare panel_rotate		= 90;					// float, degrees
#declare sml_truss_radius	= Meters * 2;				// float
#declare sml_truss_sides	= 3;					// integer, 3 or more
#declare sml_truss_thick	= Meters/4;				// float
#declare sml_truss_section_size	= Meters * 64;				// float
#declare med_truss_thick	= Meters * 1;				// float
#declare med_truss_radius	= Meters * 8;				// float
#declare big_truss_thick	= Meters * 1;				// float
#declare big_truss_radius	= Meters * 16;				// float
#declare blinky_radius		= Meters * 2;				// float
#declare Lightsys_Scene_Scale	= Meters * 100;				// float, 1 = 1cm?
#declare Lightsys_Brightness	= 2;					// float
#declare lamp_lumens		= 1;					// float
#declare lamp_temperature	= Daylight(5500);			// float
#declare lamp_color		= Light_Color(lamp_temperature, lamp_lumens);			// color vector
#declare lamp_number		= 8;					// integer, size of the area light
#declare lamp_radius1		= Meters * 2;				// float
#declare lamp_radius2		= central_axis_radius + lamp_radius1 * 1;		// float
#declare lamp_radius3		= central_axis_radius + lamp_radius1 * 2;		// float
#declare lamp_frequency		= pi/lamp_radius1/4;			// float
#declare lamp_length		= city_length + inner_shell_bulge * 2;	// float
#declare sun_lumens		= 1;					// float
#declare sun_temp		= Daylight(6100);			// float
#declare sun_color		= Light_Color(sun_temp, sun_lumens);	// color vector
#declare sun_distance		= Meters * 816040000000/1000;		// float, distance of Jupiter from the sun
#declare sun_radius		= Meters * 696342000/1000;		// float, equatorial radius of the sun
#declare sun_location		= vaxis_rotate(-z * sun_distance,y,45);	// vector
#declare planet_distance	= Meters * 200000000/1000;		// float, distance of Jupiter from the space craft
#declare planet_radius		= Meters * 71492000/1000;		// float, equatorial radius of Jupiter
#declare planet_location	= +z * planet_distance;			// vector
#declare antenna_length		= Meters * 256;				// float
#declare antenna_offset		= Meters * 32;				// float
#declare thruster_tank_radius	= Meters * 12;

// legacy code
#declare Tiles			= 1;					// integer, the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height		= 128;					// float, still used? changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;					// float, the default width of a tile.
//#declare lamp_number		= floor(lamp_length/lamp_radius1/2);			// integer, legacy code
#declare lamp_num		= 360;						// integer, legacy code
#declare lamp_frq		= 24;						// integer, legacy code
//#declare lamp_mod		= floor(lamp_num/lamp_frq) - 1;				// integer, legacy code
#declare lamp_mod		= 29;				// integer, legacy code
#declare lamp_lit_num		= floor(lamp_num/lamp_mod);					// integer, legacy code
#declare lamp_ang		= 360/floor(lamp_num/lamp_frq);				// float, legacy code
#declare lamp_lumens_adjust	= lamp_lumens/lamp_frq;				// float, legacy code
#declare lamp_color_adjust	= Light_Color(lamp_temperature, lamp_lumens_adjust);			// color vector, legacy code


//------------------------------------------------------------------------------Macros

/*
// obsolete?
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
*/

#macro gamma_color_adjust(in_color)
	color srgbft in_color + <0,0,0,0,0>
#end
#macro vstr_def(in_vector)
	concat("<", vstr(3,in_vector,",",0,-1), ">")
#end
#macro vfloor_def(in_vector)
	<floor(in_vector.x),floor(in_vector.y),floor(in_vector.z)>
#end
#macro vceil_def(in_vector)
	<ceil(in_vector.x),ceil(in_vector.y),ceil(in_vector.z)>
#end
#macro vmod_def(in_vector,in_quot)
	<mod(in_vector.x,in_quot),mod(in_vector.y,in_quot),mod(in_vector.z,in_quot)>
#end
#macro vgreat_def(in_vector_1,in_vector_2)
	((in_vector_1.x>in_vector_2.x)&(in_vector_1.y>in_vector_2.y)&(in_vector_1.z>in_vector_2.z))
#end
#macro str_def(in_value)
	str(in_value,0,-1)
#end
#macro verbose_include(in_file, in_bool)
	#if (in_bool)
		#debug concat("\n======Already included \"", in_file, "\", skipping.\n")
	#else
		#debug concat("\n>>>>>>Starting to include \"", in_file, "\".\n")
		#include in_file
		#debug concat("\n<<<<<<Finished including \"", in_file, "\".\n")
	#end
#end
#macro verbose_parse_string(in_string)
	#debug concat("\nParsing \"", in_string, "\"\n")
	Parse_String(in_string)
#end
#macro lowqual_pig(in_seed)
	gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed),0,0>)
#end
#macro debug_detail(in_string)
	#if (debug_progress)
		#debug in_string
	#end
#end