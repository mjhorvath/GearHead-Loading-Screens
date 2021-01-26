// citygen variables (mostly)
#declare city_rotate			= 30;						// float, degrees
#declare city_night				= false;					// boolean, obsolete?
#declare city_right_hand_drive	= false;					// boolean
#declare city_default_objects	= false;					// boolean
#declare city_use_mesh			= false;					// boolean
#declare city_all_mesh			= false;					// boolean
#declare city_tileable			= true;						// boolean
#declare city_storey_height		= Meters * 4;				// for reference, people are roughly Meters * 2 units tall
#declare city_ped_density		= 1/64/Meters;				// is this being used?? it should be!
#declare city_grass_height		= Meters / 4;				// too thin and it gets clipped by the pavement
#declare city_tree_height		= Meters * 12;				// float
#declare city_car_scale			= Meters * 2;				// float
#declare city_hide_buildings	= NoBuildings;				// boolean
#declare total_lanes			= (NewTrain ? 2 : 3);		// in both directions, including half lanes for bikes (minimum 2)
#declare nominal_traffic_width	= Meters * (NewTrain ? 12 : 16);			// float
#declare nominal_building_width	= Meters * 64;				// float
#declare traffic_spacing		= Meters * 128;				// float
#declare traffic_width			= nominal_traffic_width/total_lanes;		// float
#declare traffic_lanes			= floor(total_lanes/2);		// integer, in each direction...
#declare pavement_width			= Meters * 4;				// float
#declare building_gap			= pavement_width * 2;		// float
#declare building_width			= nominal_building_width - pavement_width * 2;			// float
#declare min_building_height	= city_storey_height * 6;	// float
#declare max_building_height	= city_storey_height * 12;	// float
#declare building_height_turb	= 1;
#declare street_height			= 0;						// to do, may conflict with citygen...
#declare street_width			= nominal_traffic_width;	// float
#declare rail_ped_thick			= Meters;					// float, rail pedestal leg
#declare rail_width				= street_width/2;			// float
#declare rail_height			= Meters * 6;				// float
#declare rail_thick				= Meters/2;					// float
#declare rail_plat_thick		= Meters/2;					// float
#declare rail_plat_radius		= street_width;				// float
#declare rail_ramp_width		= Meters * 2;				// float
#declare rail_cars_number		= 1;						// integer, odd values only
#declare big_block_length		= nominal_traffic_width + nominal_building_width * 4;		// float
#declare sml_block_length		= nominal_traffic_width + nominal_building_width * 1;		// float
#declare city_sections			= <2,0,1>;
#declare city_circum			= (big_block_length * 2 + sml_block_length * 1) * city_sections.x;		// float, the circumference of the spinner colony
#declare city_length			= (big_block_length * 4 + sml_block_length * 3) * city_sections.z;		// float, the length of the city along the long axis
#declare city_radius			= city_circum/2/pi;			// float, the innermost radius of the spinner colony

// scene variables (mostly)
#declare ring_gap				= Meters * 8;				// float
#declare metal_thick			= Meters * 4;				// float
#declare inner_rock_thick		= Meters * 16;				// float
#declare outer_rock_thick		= Meters * 16;				// float
#declare trusshub_length		= Meters * 128;				// float
#declare habitat_length			= city_length + ring_gap * 2 + metal_thick * 8;		// float
#declare inner_shell_radius1	= city_radius + inner_rock_thick + metal_thick;		// float
#declare inner_shell_radius2	= inner_shell_radius1 - metal_thick;				// float
#declare inner_shell_radius3	= inner_shell_radius2 - inner_rock_thick;			// float
#declare outer_shell_radius1	= inner_shell_radius1 + ring_gap + outer_rock_thick + metal_thick * 2;		// float
#declare outer_shell_radius2	= outer_shell_radius1 - metal_thick;		// float
#declare outer_shell_radius3	= outer_shell_radius2 - outer_rock_thick;		// float
#declare outer_shell_radius4	= outer_shell_radius3 - metal_thick;		// float
#declare window_radius			= outer_shell_radius1 * 2/9;		// float
#declare reactor_radius			= outer_shell_radius1;		// float
#declare dock_length			= Meters * 256;				// float
#declare dock_start				= habitat_length/2 + trusshub_length + reactor_radius * 2;		// float
#declare dock_radius_outer			= outer_shell_radius1;		// float
#declare dock_radius_inner			= outer_shell_radius1 * 1/4;		// float
#declare dock_depth				= Meters * 48;				// float
#declare dock_thick				= Meters * 4;			// float
#declare total_length			= habitat_length + trusshub_length + reactor_radius * 2 + dock_length;		// float
#declare agridome_radius		= Meters * 32;				// float
#declare agridome_ringrad		= outer_shell_radius1 * 2;		// float
#declare agridome_ringgap		= Meters * 128;
#declare panel_gap				= Meters * 8;				// float
#declare panel_width			= Meters * 64;				// float
#declare panel_length			= panel_width * 2;			// float
#declare panel_thick			= Meters/2;					// float
#declare panel_mortar			= Meters;					// float
#declare panel_number			= 4;						// integer
#declare panel_rotate			= 90;						// float, degrees
#declare sml_truss_radius		= Meters * 2;				// float
#declare sml_truss_sides		= 3;						// integer, 3 or more
#declare sml_truss_thick		= Meters/4;					// float
#declare sml_truss_section_size	= Meters * 64;				// float
#declare big_truss_thick		= Meters * 2;
#declare big_truss_radius		= Meters * 16;
#declare blinky_radius			= Meters * 2;				// float
#declare lamp_radius			= Meters * 4;				// float
#declare lamp_length			= city_length;				// float
#switch (TexQual)
	#case (-1)
		#declare lamp_number = 1;			// integer
	#break
	#case (0)
		#declare lamp_number = 16;			// integer
	#break
	#case (1)
		#declare lamp_number = 32;			// integer
	#break
	#case (2)
		#declare lamp_number = 64;			// integer
	#break
#end

#declare Lightsys_Scene_Scale	= Meters * 100;				// float, 1 = 1cm?
#declare Lightsys_Brightness	= 2;						// float
#declare light_lumens			= 1;						// float
#declare light_temp				= Daylight(6100);			// float
#declare light_color			= Light_Color(light_temp, light_lumens);		// color vector
#declare lamp_lumens			= 1;						// float
#declare lamp_temp				= Daylight(5500);			// float
#declare lamp_color				= Light_Color(lamp_temp, lamp_lumens);			// color vector
#declare planet_distance		= 385000000/10000;			// float, meters
#declare planet_radius			=   6371000/10000;			// float, meters
#declare sun_distance			= 149600000/10000;			// float, kilometers
#declare sun_radius				=    695500/10000;			// float, kilometers


//------------------------------------------------------------------------------Macros

/*
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
	pigment {gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed)>)}
#end
#macro lowqual_tex(in_seed)
	texture {lowqual_pig(in_seed)}
#end
#macro lowqual_mat(in_seed)
	material {texture {lowqual_pig(in_seed)}}
#end
