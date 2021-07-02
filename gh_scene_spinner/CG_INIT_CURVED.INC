/*************************************************************************
		DEFAULT CITY GENERATOR MACRO FILE FOR PERSISTENCE OF VISION 3.x
**************************************************************************

Created by Chris Colefax, 1 February 1999
Modified by Michael Horvath
NOTE: This file is designed for use with City.inc; see City.htm for
		more information

*************************************************************************/

#include "strings.inc"
#include "shapes.inc"
#include "shapesq.inc"
#include "param.inc"		// Meshmerizing Mesh Maker Macros

// CHECK OPTIONS AND ASSIGN DEFAULTS
#ifndef (city_seed)					#declare city_seed				= 0;			#end
#ifndef (building_width)			#declare building_width			= 25;			#end
#ifndef (min_building_height)		#declare min_building_height		= building_width * 1/2;	#end
#ifndef (max_building_height)		#declare max_building_height		= building_width * 2;	#end
#ifndef (building_height_falloff)	#declare building_height_falloff	= 2;		#end
#ifndef (building_height_turb)		#declare building_height_turb	= 1/2;			#end
#ifndef (pavement_height)			#declare pavement_height		= 0.15;			#end
#ifndef (traffic_spacing)			#declare traffic_spacing		= 10;			#end
#ifndef (traffic_lanes)				#declare traffic_lanes			= 1;			#end
#ifndef (traffic_width)				#declare traffic_width			= 3;			#end
#ifndef (building_types)			#declare building_types			= 0;			#end
#ifndef (city_default_objects)		#declare city_default_objects	= false;		#end
#ifndef (park_deco_max)				#declare park_deco_max			= 5;			#end
#ifndef (square_deco_max)			#declare square_deco_max		= 9;			#end
#ifndef (park_deco_number)			#declare park_deco_number		= 5;			#end
#ifndef (square_deco_number)		#declare square_deco_number		= 9;			#end
#ifndef (street_width)				#declare street_width			= 10;			#end
#ifndef (pavement_width)			#declare pavement_width			= 4;			#end
#ifndef (building_width)			#declare building_width			= 25;			#end
#ifndef (city_tileable)				#declare city_tileable			= false;		#end
#ifndef (city_default_objects)		#declare city_default_objects	= false;		#end
#ifndef (city_night)				#declare city_night				= false;		#end
#ifndef (traffic_night)				#declare traffic_night			= false;		#end
#ifndef (windows_lit)				#declare windows_lit			= 0.33;			#end
#ifndef (windows_blend)				#declare windows_blend			= 0.25;			#end
#if (city_night = false)			#declare windows_lit			= false;		#end
#ifndef (city_right_hand_drive)		#declare city_right_hand_drive	= false;		#end

#ifndef (_CT_rand1)	#declare _CT_rand1	= seed(43566);				#end // For traffic
#ifndef (_CT_rand2)	#declare _CT_rand2	= seed(city_seed);			#end // For pavement objects
#ifndef (_CT_rand3)	#declare _CT_rand3	= seed(city_seed);			#end // For buildings
#ifndef (_CT_rand4)	#declare _CT_rand4	= seed(city_seed);			#end // For building levels
#ifndef (_CT_rand5)	#declare _CT_rand5	= seed(city_seed);			#end // For textures/materials

// BUILDING OPTIONS
#declare build_texture		= 1;
#declare build_fit_texture	= 2;
#declare build_profile		= 4;
#declare build_details		= 8;
#declare build_window_levels	= 16;
#declare build_window_profile	= 32;
#declare build_base		= 64;
#declare build_roof		= 128;


// CITY TEXTURES
#switch (TexQual)
	#case (-2)
	#case (-1)
		#declare street_texture		= texture {pigment {lowqual_pig(_CT_rand5)}};
		#declare pavement_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
	#break
	#case (0)
		#declare street_texture		= texture {pigment {gamma_color_adjust(<0.2,0.2,0.2>)}};
		#declare pavement_texture	= texture {pigment {gamma_color_adjust(<0.5,0.5,0.5>)}};
	#break
	#case (1)
	#case (2)
		#declare street_texture = texture
		{
			pigment
			{
				bozo
				color_map
				{
					[0 gamma_color_adjust(<0.2,0.2,0.2>)]
					[1 gamma_color_adjust(<0.4,0.4,0.4>)]
				}
				scale 10
			}
			scale Meters
		}
		#declare pavement_texture = texture
		{
			pigment
			{
				wrinkles
				color_map
				{
					[0 gamma_color_adjust(<0.5,0.5,0.5>)]
					[1 gamma_color_adjust(<0.6,0.6,0.6>)]
				}
				scale 1.5
			}
			scale Meters
		}
	#break
#end
// CITY TEXTURES
// need street lamp texture and potted plant texture too
#switch (TexQual)
	#case (-2)
	#case (-1)
		#declare metal_texture		= texture {pigment {lowqual_pig(_CT_rand5)}};
		#declare lamp_texture		= texture {pigment {lowqual_pig(_CT_rand5)}};
		#declare trash_texture		= texture {pigment {lowqual_pig(_CT_rand5)}};
		#declare plant_texture		= texture {pigment {lowqual_pig(_CT_rand5)}};
	#break
	#case (0)
		#declare metal_texture = texture
		{
			pigment {gamma_color_adjust(<0.4,0.4,0.4>)}
		}
		#declare lamp_texture = texture
		{
			pigment {gamma_color_adjust(<0.4,0.4,0.4>)}
		}
		#declare trash_texture = texture
		{
			pigment {gamma_color_adjust(<0.0,0.0,0.8>)}
		}
		#declare plant_texture = texture
		{
			pigment {gamma_color_adjust(<0.0,0.8,0.0>)}
		}
	#break
	#case (1)
	#case (2)
		#declare metal_texture = texture
		{
			pigment {gamma_color_adjust(<0.4,0.4,0.4>)}
			finish {metallic}
		}
		#declare lamp_texture = texture
		{
			pigment {gamma_color_adjust(<0.4,0.4,0.4>)}
			finish {metallic}
		}
		#declare trash_texture = texture
		{
			pigment {gamma_color_adjust(<0.0,0.0,0.8>)}
			finish {metallic}
		}
		#declare plant_texture = texture
		{
			pigment {gamma_color_adjust(<0.0,0.8,0.0>)}
			finish {metallic}
		}
	#break
#end

// Should measure 2x2 in x-z plane, travelling along the x-axis
// slightly too elevated
#declare street_overlay = texture
{
	pigment
	{
		planar
		pigment_map
		{
			[
				1/2
				gradient y
				pigment_map
				{
					[0.02 checker gamma_color_adjust(<1,1,1>), gamma_color_adjust(<1,1,1,0,1>) scale .1]
					[0.02 gamma_color_adjust(<1,1,1,0,1>)]
				}
				ramp_wave
			]
			[
				1/2
				gradient y
				color_map
				{
					[0.01 gamma_color_adjust(<1,1,1,0,1>)]
					[0.01 gamma_color_adjust(<1,1,1,0,0>)]
					[0.03 gamma_color_adjust(<1,1,1,0,0>)]
					[0.03 gamma_color_adjust(<1,1,1,0,1>)]
				}
				ramp_wave
			]
		}
		rotate x*90
	}
	scale Meters
}

// CITY CREATION MACROS
#macro city_base(Corner1, Corner2)
	debug_detail(concat("CG......Calling city_base().\n"))
	#local PSize = Corner2 - Corner1;
	object
	{
		#if	(city_is_flat)
			pos_object(box {Corner1 - y * city_base_thick, Corner2}, <0,0,0>)
		#elseif (city_all_mesh)
			pos_object(cyl_box_mesh(Corner1 - y * city_base_thick, Corner2, prim_base_sections), <0,0,0>)
		#else
			pos_object(cyl_box_csg(Corner1 - y * city_base_thick, Corner2), <0,0,0>)
		#end
		texture {street_texture}
		// bounding may not help here
//		bounded_by {cyl_box_bound()}
	}
#end

#macro city_pedestrians(Corner1, Corner2, block_ped_density)
	#local PSize = Corner2 - Corner1;
	#local PArea = PSize.x * PSize.z;
	#local PCent = (Corner1 + Corner2)/2 * <1,0,1>;
	#local pedestrian_count = 0;
	#local pedestrian_total = floor(PArea * city_ped_density * block_ped_density);		// why are there two different densities?
	#while (pedestrian_count < pedestrian_total)
		#local pedestrian_posit = <rand(_CT_rand2)*PSize.x-PSize.x/2,0,rand(_CT_rand2)*PSize.z-PSize.z/2> + PCent;
		object {pos_object(ped_macro(_CT_rand2), pedestrian_posit)}
		#local pedestrian_count = pedestrian_count + 1;
	#end
#end

#macro city_decorations(InObject, Point1, Point2, bSkip1, bSkip2, nNumber)
	#local LLength = vlength(Point2 - Point1);
	#local LVector = vnormalize(Point2 - Point1);
	#local LDistance = LLength/nNumber;
	#local nCount = bSkip1;
	#while (nCount <= nNumber - bSkip2)
		#local LPosition = Point1 + nCount * LVector * LDistance;
		object {pos_object(InObject, LPosition)}
		#local nCount = nCount + 1;
	#end
#end

#macro city_pavement(Corner1, Corner2)
	debug_detail(concat("CG.........Calling city_pavement().\n"))
	#local PSize = Corner2 - Corner1;
	object
	{
		#if	(city_is_flat)
			pos_object(box {Corner1, Corner2 + y * pavement_height}, <0,0,0>)
		#elseif (city_all_mesh)
			pos_object(cyl_box_mesh(Corner1, Corner2 + y * pavement_height, prim_base_sections), <0,0,0>)
		#else
			pos_object(cyl_box_csg(Corner1, Corner2 + y * pavement_height), <0,0,0>)
		#end
		texture {pavement_texture}
		// bounding may not help here
//		bounded_by {cyl_box_bound(Corner1, Corner2 + y * pavement_height)}
	}
/*
	// obsolete road stuff
	#ifdef (pavement_object)
		#local V = 0;
		#while (V < dimension_size(pavement_object, 1))
			#local p_offset = Meters * pavement_object_offset[V];
			#local p_turb	= Meters * pavement_object_turb[V];
			#local p_space	= Meters * pavement_object_spacing[V];
			#local p_object	= object
			{
				verbose_parse_string(concat(pavement_object[V],"(_CT_rand2)"))
				translate -x * Meters/2
			}
			#local P = p_offset + rand(_CT_rand2) * p_turb;
			#while (P < PSize.x - p_offset)
				#local obj1 = object {p_object rotate y * 090}
				#local obj2 = object {p_object rotate y * 270}

				object {pos_object(obj1, Corner1 + <+P, pavement_height, 0>)}
				object {pos_object(obj2, Corner2 + <-P, pavement_height, 0>)}

				#if (p_space <= 0)
					#local P = PSize.x;
				#else
					#local P = P + p_space + rand(_CT_rand2) * p_turb;
				#end
			#end

			#local P = p_offset + rand(_CT_rand2) * p_turb;
			#while (P < PSize.z - p_offset)
				#local obj1 = object {p_object rotate y * 000}
				#local obj2 = object {p_object rotate y * 180}

				object {pos_object(obj1, <Corner2.x, pavement_height, Corner1.z + P>)}
				object {pos_object(obj2, <Corner1.x, pavement_height, Corner2.z - P>)}

				#if (p_space <= 0)
					#local P = PSize.z;
				#else
					#local P = P + p_space + rand(_CT_rand2) * p_turb;
				#end
			#end
			#local V = V + 1;
		#end
	#end
*/
#end

// no longer used
#macro city_onstreet_traffic(From, To, Direction)
	debug_detail(concat("CG......Calling city_onstreet_traffic().\n"))
	#local V = dimension_size(city_vehicle_macros, 1);
	#local I = (Direction ? block_size.z : block_size.x) + street_width;
	#local L = -traffic_lanes;
	#while (L <= traffic_lanes)
		#local VD = (L < 0 ? -1 : 1);
		#local V2 = (Direction ? From.x : From.z) + traffic_width *VD * (abs(L)-.5);
		#local V1 = (Direction ? From.z : From.x) + street_width + rand(_CT_rand1)*traffic_spacing;
		#while (V1 < (Direction ? To.z : To.x) - ((Direction ? city_tileable_z : city_tileable_x) ? 0 : street_width))
			#local VT = int(V*rand(_CT_rand1));
			#local obj1_translate = (Direction ? <V2, 0, V1> : <V1, 0, V2>);
			#local obj1_parse = verbose_parse_string(concat(city_vehicle_macros[VT],"(",str(Direction,0,-1),",",str(VD,0,-1),")"));
			#local obj1_object = object
			{
				obj1_parse
				rotate +y*90*VD
				rotate -y*90*Direction
			}

			object {pos_object(obj1_object, obj1_translate)}

			#local V1 = V1 + city_vehicle_spacing[VT] + (1 + 2*rand(_CT_rand1))*traffic_spacing;
			#if (mod(V1 - (Direction ? From.z : From.x), I) < street_width)
				#local V1 = V1 + street_width;
			#end
		#end
		#local L = L + (L = -1 ? 2 : 1);
	#end
#end

#macro city_rail_traffic(From, To, Direction)
	debug_detail(concat("CG......Calling city_rail_traffic().\n"))
	#local V = dimension_size(city_vehicle_macros, 1);
	#local cars_max_per_lane = 1;
	#local buffer_me = rail_buffer * 3/2;
	#if (Direction = 0)
		// once each lane
		#local I = block_size.x + street_width;
		#local L = -traffic_lanes;
		#while (L <= traffic_lanes)
			#local VD = (L < 0 ? -1 : 1);
			#local V2 = From.z + traffic_width * VD * (abs(L)-0.5);
			#for (cars_count, 0, cars_max_per_lane - 1)
				#local V1 = From.x + buffer_me + rand(_CT_rand1) * (To.x - From.x - buffer_me * 2);
				#local VT = int(V*rand(_CT_rand1));

				#local obj1_translate = <V1, rail_height*2, V2>;
				#local obj1_parse = verbose_parse_string(concat(city_vehicle_macros[VT],"(",str(Direction,0,-1),",",str(VD,0,-1),")"));
				#local obj1_object = object
				{
					obj1_parse
					rotate +y*90*VD
					rotate -y*90*Direction
				}
				object {pos_object(obj1_object, obj1_translate)}
			#end

			#local L = L + (L = -1 ? 2 : 1);
		#end
	#else
		// there is only one lane in this direction
		#local VD = 1;
		#local V2 = From.x;
		#local V1 = From.z + buffer_me + rand(_CT_rand1) * (To.z - From.z - buffer_me * 2);
		#for (cars_count, 0, cars_max_per_lane - 1)
			#local VT = int(V*rand(_CT_rand1));
			#local obj1_translate = <V2, rail_height*1, V1>;
			#local obj1_parse = verbose_parse_string(concat(city_vehicle_macros[VT],"(",str(Direction,0,-1),",",str(VD,0,-1),")"));
			#local obj1_object = object
			{
				obj1_parse
				rotate +y*90*VD
				rotate -y*90*Direction
			}

			object {pos_object(obj1_object, obj1_translate)}
		#end
	#end
#end

// no longer used
#macro city_onstreet_track(From, To, Direction)
	debug_detail(concat("CG......Calling city_onstreet_track().\n"))
	#ifdef (street_overlay)
		#if (!Direction)
			#local v1 = From	+ <0,+0.001,-street_width/2>;
			#local v2 = To		+ <0,+0.002,+street_width/2>;
		#else
			#local v1 = From	+ <-street_width/2,+0.001,0>;
			#local v2 = To		+ <+street_width/2,+0.002,0>;
		#end
		object
		{
			#if	(city_is_flat)
				box {v1, v2}
			#elseif (city_all_mesh)
				cyl_box_mesh(v1, v2, prim_base_sections)
			#else
				cyl_box_csg (v1, v2)
			#end
			// bounding may not help here
//			bounded_by {cyl_box_bound(v1, v2)}
			texture
			{
				street_overlay
				scale		traffic_width
				rotate		-y * 90 * Direction
				translate	From
			}

//			texture {pigment {rgb 1}}
		}
	#end
#end

#macro city_rail_track(From, To, Direction)
	debug_detail(concat("CG......Calling city_rail_track().\n"))
	#ifdef (street_overlay)
		#if (!Direction)
			#local height_mod = rail_height*2;
			#local width_mod = rail_width/1;
			#local ped_rotate = 0;
			// track
			#local b1 = From	+ <0,height_mod-rail_thick,-width_mod/2>;
			#local b2 = To		+ <0,height_mod,           +width_mod/2>;
		#else
			#local height_mod = rail_height*1;
			#local width_mod = rail_width/1;	// divide by 2 to get skinny track
			#local ped_rotate = 270;
			// track
			#local b1 = From	+ <-width_mod/2,height_mod-rail_thick,0>;
			#local b2 = To		+ <+width_mod/2,height_mod,           0>;
		#end
		union
		{
			// the pedestals holding up the rail, they need to align with the walkways between buildings
			#if (!Direction)
				#local supp_adjust = x * pavement_width;
				#local supp_count = buildings_per_block.x;
				#local supp_diff = To - From - supp_adjust * 2;
				#for (i, 1, supp_count - 1)
					#local supp_ratio = i/supp_count;
					#local supp_step = supp_diff * supp_ratio;
					#local supp_loc = From + supp_step + supp_adjust;
					city_rail_pedestal(supp_loc, Direction)
				#end
			#else
				#local supp_adjust = z * pavement_width;
				#local supp_count = buildings_per_block.z;
				#local supp_diff = To - From - supp_adjust * 2;
				#for (i, 1, supp_count - 1)
					#local supp_ratio = i/supp_count;
					#local supp_step = supp_diff * supp_ratio;
					#local supp_loc = From + supp_step + supp_adjust;
					city_rail_pedestal(supp_loc, Direction)
				#end
			#end
			// the rail itself
			difference
			{
				pos_object(cyl_box(b1, b2), <0,0,0>)
			}
			city_rail_texture()
		}
	#end
#end

#macro city_rail_pedestal(From, Direction)
	// the pedestals holding up the rail
	debug_detail(concat("CG......city_rail_pedestal().\n"))
	#ifdef (street_overlay)
		#if (!Direction)
			#local height_mod = rail_height*2;
			// pedestal support
			#local c1 = From + <-(street_width/4),pavement_height,-(street_width/2)>;
			#local c2 = From + <+(street_width/4),height_mod,+(street_width/2)>;
			// pedestal cutout
			#local d1 = From + <-street_width/2,-rail_ped_thick,-(-rail_ped_thick+street_width/2)>;
			#local d2 = From + <+street_width/2,+(-rail_ped_thick+height_mod),+(-rail_ped_thick+street_width/2)>;
			// pedestal
			difference
			{
//				pos_object(cyl_pyr(c1, c2), <0,0,0>)		// weird clipping issues when city curvature is high
				pos_object(cyl_box(c1, c2), <0,0,0>)
				pos_object(cyl_box(d1, d2), <0,0,0>)
				bounded_by {pos_object(cyl_box_bound(c1, c2), <0,0,0>)}
				city_rail_texture()
			}
		#else
			#local height_mod = rail_height*1;
			// pedestal support
			#local c1 = From + <-(street_width/2),pavement_height,-(street_width/4)>;
			#local c2 = From + <+(street_width/2),height_mod,+(street_width/4)>;
			// pedestal cutout
			#local d1 = From + <-(-rail_ped_thick+street_width/2),-rail_ped_thick,-street_width/2>;
			#local d2 = From + <+(-rail_ped_thick+street_width/2),+(-rail_ped_thick+height_mod),+street_width/2>;
			// pedestal
			difference
			{
//				pos_object(cyl_pyr(c1, c2), <0,0,0>)		// weird clipping issues when city curvature is high
				pos_object(cyl_box(c1, c2), <0,0,0>)
				pos_object(cyl_box(d1, d2), <0,0,0>)
				bounded_by {pos_object(cyl_box_bound(c1, c2), <0,0,0>)}
				city_rail_texture()
			}
		#end
	#end
#end

#macro city_station_track(From)
	debug_detail(concat ("CG......city_station_track().\n"))
	#ifdef (street_overlay)
		// spiral ramp issues:
		// 1. does not take the curvature/gravity of the station perimeter into account
		// 2. has no thickness
		#local Fx = function(u,v) {u*cos(v)}
		#local Fy = function(u,v) {u*sin(v)}
		#local Fz = function(u,v) {v}
		// spiral ramp #1
		#local platform_ramp_1 = object
		{
			Parametric(Fx,Fy,Fz,<0,0>,<1,pi>,12,12,"")
			rotate +x * 90
			rotate -y * 90
			scale y/pi
			translate y
			scale <rail_plat_radius,rail_height*2,rail_plat_radius>
		}
		// spiral ramp #2
		#local platform_ramp_2 = object
		{
			platform_ramp_1
			rotate y * 180
		}
		// core removed from outside the spiral ramp
		#local platform_core_out = cone
		{
			0, rail_plat_radius, y*city_radius, 0
			inverse
		}
		// core removed from inside the spiral ramp
		#local platform_core_inn = cone
		{
			0, rail_plat_radius - rail_ramp_width, y*city_radius, 0
		}
		#local platform_plat_out = cone
		{
			0, rail_plat_radius, y*city_radius, 0
		}
		#local platform_ped_out = cone
		{
			0, rail_plat_radius * 2, y*city_radius, 0
		}
		#local platform_ped_inn = cone
		{
			0, rail_plat_radius - rail_ramp_width, y*city_radius, 0
		}
		#local platform_plat_ped = difference
		{
			object {platform_ped_out}
			object {platform_ped_inn}
			plane {+x, 0 rotate -y * 45}
			plane {-x, 0}
		}
		// the platforms people stand on
		#local height_mod = rail_height*2;
		#local platform_plat_1 = intersection
		{
			difference
			{
				object {platform_plat_out}
				// gaps for people to walk up the ramp. ugly
//				object {platform_plat_ped    rotate +y * ped_rotate}
//				object {platform_plat_ped    rotate +y * (ped_rotate + 180)}
				bounded_by {platform_plat_out}
			}
			difference
			{
				cylinder {-z*10000,+z*10000,city_radius - height_mod + rail_plat_thick}
				cylinder {-z*10001,+z*10001,city_radius - height_mod}
				bounded_by {cylinder {-z*10000,+z*10000,city_radius - height_mod + rail_plat_thick}}
				translate +y * city_radius
			}
			bounded_by {platform_plat_out}
		}
		#local height_mod = rail_height*1;
		#local platform_plat_2 = intersection
		{
			difference
			{
				object {platform_plat_out}
				// gaps for people to walk up the ramp. ugly
//				object {platform_plat_ped    rotate +y * ped_rotate}
//				object {platform_plat_ped    rotate +y * (ped_rotate + 180)}
				bounded_by {platform_plat_out}
			}
			difference
			{
				cylinder {-z*10000,+z*10000,city_radius - height_mod + rail_plat_thick}
				cylinder {-z*10001,+z*10001,city_radius - height_mod}
				bounded_by {cylinder {-z*10000,+z*10000,city_radius - height_mod + rail_plat_thick}}
				translate +y * city_radius
			}
			bounded_by {platform_plat_out}
		}
		union
		{
			// station platform ramps
			difference
			{
				union
				{
					pos_object(platform_ramp_1, From)
					pos_object(platform_ramp_2, From)
				}
				pos_object(platform_core_inn, From)
				pos_object(platform_core_out, From)
			}
			// station platform surfaces
			pos_object(platform_plat_1, From)
			pos_object(platform_plat_2, From)
			city_rail_texture()
		}
	#end
#end


#macro city_rail_pavement(From, To, Direction)
	debug_detail(concat("CG......Calling city_rail_pavement().\n"))
	#ifdef (street_overlay)
		#if (!Direction)
			// floor
			#local a1 = From	- <0,0,street_width/2>;
			#local a2 = To		+ <0,pavement_height,street_width/2>;
		#else
			// floor
			#local a1 = From	- <street_width/2,0,0>;
			#local a2 = To		+ <street_width/2,pavement_height,0>;
		#end
		object
		{
			pos_object(cyl_box(a1, a2), <0,0,0>)
			texture {pavement_texture}
		}
		#local ped_density = 1;
		city_pedestrians(From - (Direction ? x : z) * street_width/2, To + (Direction ? x : z) * street_width/2, ped_density)
	#end
#end

#macro city_station_pavement(From)
	debug_detail(concat("CG......Calling city_station_pavement().\n"))
	#ifdef (street_overlay)
		// floor
		#local a1 = From	- <street_width/2,0,street_width/2>;
		#local a2 = From	+ <street_width/2,pavement_height,street_width/2>;
		object
		{
			pos_object(cyl_box(a1, a2), <0,0,0>)
			texture {pavement_texture}
		}
		#local ped_density = 1;
		city_pedestrians(From - <street_width/2,0,street_width/2>, From + <street_width/2,pavement_height,street_width/2>, ped_density)
	#end
#end


#macro city_building(Corner1, Corner2, Direction)
	debug_detail(concat("CG.........Calling city_building(", vstr_def(Corner1), ", ", vstr_def(Corner2), ", ", str_def(Direction), ")\n"))
	#if (building_types > 0 & defined(building_macros))
		#local BCentre	= (Corner1 + Corner2)/2;
		#local BHeight	= pow(1.2 - (vlength(BCentre) / _CT_extents), building_height_falloff);
		#local BHeight	= BHeight + (rand(_CT_rand3) - 1/2) * building_height_turb;
		#local BHeight	= min_building_height + BHeight * (max_building_height - min_building_height);
		#if (BHeight > 0)
			// get a random building
			#local rand_val		= rand(_CT_rand3);
			#local chance_total	= 0;
			#local building_count	= 0;
			#while (building_count < building_types)
				#local chance_total	= chance_total + building_chance[building_count];
				#local building_count	= building_count + 1;
			#end
			#if (chance_total = 0)
				#local chance_total = 1;
			#end
			#local chance_ratio	= 0;
			#local building_count	= 0;
			#while (building_count < building_types)
				#local chance_ratio	= chance_ratio + building_chance[building_count]/chance_total;
/*
#debug "\n"
#debug concat("chance_total = ",Str(chance_total),"\n")
#debug concat("chance_ratio = ",Str(chance_ratio),"\n")
#debug concat("rand_val = ",Str(rand_val),"\n")
*/
				#if (rand_val < chance_ratio)
					city_assemble_building
					(
						building_count,
						(Corner2 - Corner1) + y * BHeight,
						Direction,
						BCentre + y * pavement_height
					)
					#local building_count	= building_types;
				#else
					#local building_count	= building_count + 1;
				#end
			#end
		#end
	#end
#end

#macro city_assemble_building(Type, Size, Direction, Translate)
	debug_detail(concat("CG............Calling city_assemble_building().\n"))
	union
	{
		verbose_parse_string
		(
			concat
			(
				building_macros[Type],
				"(<",
				vstr(3,Size,",",0,-1),
				">,",
				str(Direction,0,-1),
				",<",
				vstr(3,Translate,",",0,-1),
				">)"
			)
		)
	}
#end


/*******************************************************************************/

// upload these macros to the Object Collection
// need a horizontal cylinder/tube as well using a torus for one of the directions
#include "transforms.inc"
#include "shapes.inc"
#declare prim_radial_sections	= 24;
#declare prim_cylarc_sections	= 8;
#declare prim_base_sections	= floor(city_radius/4);		// the number/size of the city blocks also needs to be taken into account


//------------------------------------------------------------------------------positioning

#macro pos_object(in_object, in_position)
	#local in_zangle	= in_position.x/city_circum * 360;
	#local in_height	= city_radius - in_position.y;
	object
	{
		in_object
		translate	z * in_position.z
		translate	y * -in_height
		rotate		z * in_zangle
	}
#end
#macro pos_point(in_position)
	#local in_zangle	= in_position.x/city_circum * 360;
	#local in_height	= city_radius - in_position.y;
	vrotate(<0,-in_height,in_position.z>,<0,0,in_zangle>)
#end


//------------------------------------------------------------------------------cyl_box

#macro cyl_box(in1_pos, in2_pos)
	#if	(city_is_flat)
		box {in1_pos, in2_pos}
	#elseif (city_use_mesh)
		cyl_box_mesh(in1_pos, in2_pos, prim_cylarc_sections)
	#else
		cyl_box_csg(in1_pos, in2_pos)
	#end
#end
#macro cyl_box_mesh(in1_pos, in2_pos, in_segments)
	#if (bound_fit)
		// bounding boxes are rotated and closer fit but not parallel to coordinate axes
//		cyl_box_mesh_fit(in1_pos, in2_pos, in_segments)
	#else
		// bounding boxes are parallel to coordinate axes but larger and less fit
//		cyl_box_mesh_block(in1_pos, in2_pos, in_segments)
	#end
#end
#macro cyl_box_csg(in1_pos, in2_pos)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	difference
	{
		cylinder {<0,0,in1_pos.z-0>, <0,0,in2_pos.z+0>, in1_height}
		cylinder {<0,0,in1_pos.z-1>, <0,0,in2_pos.z+1>, in2_height}
		plane {+x, 0 rotate z * in1_zangle}
		plane {-x, 0 rotate z * in2_zangle}
		translate +y * city_radius
		bounded_by {cyl_box_bound(in1_pos, in2_pos)}
	}
#end
// bounding boxes are rotated and closer fit but not parallel to coordinate axes
#macro cyl_box_mesh_fit(in1_pos, in2_pos, segments_total)
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
			#local aaa_new = vrotate(<0,-in1_height,in1_pos.z>, z * (step_angle * segments_count - half_angle));
			#local aba_new = vrotate(<0,-in2_height,in1_pos.z>, z * (step_angle * segments_count - half_angle));
			#local aab_new = vrotate(<0,-in1_height,in2_pos.z>, z * (step_angle * segments_count - half_angle));
			#local abb_new = vrotate(<0,-in2_height,in2_pos.z>, z * (step_angle * segments_count - half_angle));
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
		// do meshes need to be bounded?
//		bounded_by {box {<min_x,min_y,min_z>,<max_x,max_y,max_z>}}
	}
	object
	{
		out_mesh
		rotate z * (half_angle + in1_zangle)
		translate +y * city_radius
	}
#end
// bounding boxes are parallel to coordinate axes but larger and less fit
#macro cyl_box_mesh_block(in1_pos, in2_pos, segments_total)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	#local step_angle	= (in2_zangle - in1_zangle)/segments_total;
	#local aaa = vrotate(<0,-in1_height,in1_pos.z>, z * in1_zangle);
	#local baa = vrotate(<0,-in1_height,in1_pos.z>, z * in2_zangle);
	#local aba = vrotate(<0,-in2_height,in1_pos.z>, z * in1_zangle);
	#local bba = vrotate(<0,-in2_height,in1_pos.z>, z * in2_zangle);
	#local aab = vrotate(<0,-in1_height,in2_pos.z>, z * in1_zangle);
	#local bab = vrotate(<0,-in1_height,in2_pos.z>, z * in2_zangle);
	#local abb = vrotate(<0,-in2_height,in2_pos.z>, z * in1_zangle);
	#local bbb = vrotate(<0,-in2_height,in2_pos.z>, z * in2_zangle);
	#local min_x = min(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local min_y = min(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local min_z = min(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local max_x = max(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local max_y = max(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local max_z = max(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local farray = array[4] {0,0,0,0}
	#local f1 = floor(in1_zangle/90);
	#local f2 = floor(in2_zangle/90);
	#local fdiff = f2 - f1;
//	#debug concat("\nf1=",str(f1,0,0),"\n\n")
//	#debug concat("\nf2=",str(f2,0,0),"\n\n")
//	#debug concat("\nfdiff=",str(fdiff,0,0),"\n\n")
	#if (fdiff > 0)
		#local fcount = 1;
		#while (fcount <= fdiff)
			#local findex = mod(100 + f1 + fcount - 1,4);
//			#debug concat("\nfindex=",str(findex,0,0),"\n\n")
			#local farray[findex] = 1;
			#local fcount = fcount + 1;
		#end
	#end
	#if (farray[0] = 1)	#local max_x = +city_radius;	#end
	#if (farray[1] = 1)	#local max_y = +city_radius;	#end
	#if (farray[2] = 1)	#local min_x = -city_radius;	#end
	#if (farray[3] = 1)	#local min_y = -city_radius;	#end
	mesh
	{
		#local segments_count	= 0;
		#while (segments_count <= segments_total)
			#local aaa_new = vrotate(<0,-in1_height,in1_pos.z>, z * (step_angle * segments_count + in1_zangle));
			#local aba_new = vrotate(<0,-in2_height,in1_pos.z>, z * (step_angle * segments_count + in1_zangle));
			#local aab_new = vrotate(<0,-in1_height,in2_pos.z>, z * (step_angle * segments_count + in1_zangle));
			#local abb_new = vrotate(<0,-in2_height,in2_pos.z>, z * (step_angle * segments_count + in1_zangle));
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
		// do meshes need to be bounded?
//		bounded_by {box {<min_x,min_y,min_z>,<max_x,max_y,max_z>}}
		translate +y * city_radius
	}
#end


//------------------------------------------------------------------------------cyl_box_bound

#macro cyl_box_bound(in1_pos, in2_pos)
	#if (bound_fit)
		// bounding boxes are rotated and closer fit but not parallel to coordinate axes
		cyl_box_bound_fit(in1_pos, in2_pos)
	#else
		// bounding boxes are parallel to coordinate axes but larger and less fit
		cyl_box_bound_block(in1_pos, in2_pos)
	#end
#end
// bounding boxes are rotated and closer fit but not parallel to coordinate axes
#macro cyl_box_bound_fit(in1_pos, in2_pos)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	#local half_angle	= (in2_zangle - in1_zangle)/2;
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
	#local min_y = min(min_y,-city_radius,-in1_height);
	#if (half_angle >= 90)
		#local min_x = min(min_x,-city_radius);
		#local max_x = max(max_x,+city_radius);
		#if (half_angle >= 180)
			#local max_y = max(max_y,+city_radius);
		#end
	#end
	box
	{
		<min_x,min_y,min_z>,<max_x,max_y,max_z>
		rotate z * (half_angle + in1_zangle)
		translate +y * city_radius
	}
#end
// bounding boxes are parallel to coordinate axes but larger and less closely fit
#macro cyl_box_bound_block(in1_pos, in2_pos)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	#local aaa = vrotate(<0,-in1_height,in1_pos.z>, z * in1_zangle);
	#local baa = vrotate(<0,-in1_height,in1_pos.z>, z * in2_zangle);
	#local aba = vrotate(<0,-in2_height,in1_pos.z>, z * in1_zangle);
	#local bba = vrotate(<0,-in2_height,in1_pos.z>, z * in2_zangle);
	#local aab = vrotate(<0,-in1_height,in2_pos.z>, z * in1_zangle);
	#local bab = vrotate(<0,-in1_height,in2_pos.z>, z * in2_zangle);
	#local abb = vrotate(<0,-in2_height,in2_pos.z>, z * in1_zangle);
	#local bbb = vrotate(<0,-in2_height,in2_pos.z>, z * in2_zangle);
	#local min_x = min(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local min_y = min(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local min_z = min(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local max_x = max(aaa.x,baa.x,aba.x,bba.x,aab.x,bab.x,abb.x,bbb.x);
	#local max_y = max(aaa.y,baa.y,aba.y,bba.y,aab.y,bab.y,abb.y,bbb.y);
	#local max_z = max(aaa.z,baa.z,aba.z,bba.z,aab.z,bab.z,abb.z,bbb.z);
	#local farray = array[4] {0,0,0,0}
	#local f1 = floor(in1_zangle/90);
	#local f2 = floor(in2_zangle/90);
	#local fdiff = f2 - f1;
//	#debug concat("\nf1=",str(f1,0,0),"\n\n")
//	#debug concat("\nf2=",str(f2,0,0),"\n\n")
//	#debug concat("\nfdiff=",str(fdiff,0,0),"\n\n")
	#if (fdiff > 0)
		#local fcount = 1;
		#while (fcount <= fdiff)
			#local findex = mod(100 + f1 + fcount - 1,4);
//			#debug concat("\nfindex=",str(findex,0,0),"\n\n")
			#local farray[findex] = 1;
			#local fcount = fcount + 1;
		#end
	#end
	#if (farray[0] = 1)	#local max_x = +city_radius;	#end
	#if (farray[1] = 1)	#local max_y = +city_radius;	#end
	#if (farray[2] = 1)	#local min_x = -city_radius;	#end
	#if (farray[3] = 1)	#local min_y = -city_radius;	#end
	box
	{
		<min_x,min_y,min_z>,<max_x,max_y,max_z>
		translate +y * city_radius
	}
#end


//-----------------------------------------------------------------------------cyl_pyr
// needs a flat option

#macro cyl_pyr(in1_pos, in2_pos)
	#if (city_use_mesh)
		cyl_pyr_mesh(in1_pos, in2_pos, prim_cylarc_sections)
	#else
		cyl_pyr_csg(in1_pos, in2_pos)
	#end
#end
#macro cyl_pyr_csg(in1_pos, in2_pos)
	#local in1_height	= city_radius - in1_pos.y;
	#local in2_height	= city_radius - in2_pos.y;
	#local in1_zangle	= in1_pos.x/city_circum * 360;
	#local in2_zangle	= in2_pos.x/city_circum * 360;
	#local diff_angle	= abs(in2_zangle - in1_zangle)/2;
	difference
	{
		cylinder {<0,0,in1_pos.z-0>, <0,0,in2_pos.z+0>, in1_height}
		cylinder {<0,0,in1_pos.z-1>, <0,0,in2_pos.z+1>, in2_height}
		plane {+x, 0 rotate z * in1_zangle}
		plane {-x, 0 rotate z * in2_zangle}
		plane {+z, 0 rotate x * +diff_angle translate y * -city_radius translate z * in1_pos.z}
		plane {-z, 0 rotate x * -diff_angle translate y * -city_radius translate z * in2_pos.z}
//		bounded_by {}
		translate +y * city_radius
	}
#end
#macro cyl_pyr_mesh(in1_pos, in2_pos, in_segments)
	// bounding boxes are rotated and closer fit but not parallel to coordinate axes
	cyl_pyr_mesh_fit(in1_pos, in2_pos, in_segments)
	// bounding boxes are parallel to coordinate axes but larger and less fit
//	cyl_box_mesh_block(in1_pos, in2_pos, prim_cylarc_sections)
#end
// bounding boxes are rotated and closer fit
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
		// do meshes need to be bounded?
//		bounded_by {box {<min_x,min_y,min_z>,<max_x,max_y,max_z>}}
	}
	object
	{
		out_mesh
		rotate z * (half_angle + in1_zangle)
		translate +y * city_radius
	}
#end


//------------------------------------------------------------------------------cyl_tiltA

#macro cyl_tiltA(in_radius, in_height, tweak)
//	#if (city_is_flat)
//		cyl_tiltA_mesh(in_radius, in_height, tweak, 24)		// why is this commented out?
//	#elseif (city_use_mesh)
//		cyl_tiltA_mesh(in_radius, in_height, tweak, 24)		// why is this commented out?
//	#else
		cyl_tiltA_csg(in_radius, in_height, tweak)
//	#end
#end

#macro cyl_tiltA_mesh(in_radius, in_height, tweak, segments_total)
	// should be able to determine the proper "tweak" value algorithmically
	#if (tweak)
		#local diff_teak = 2;
	#else
		#local diff_teak = 0;
	#end
	mesh
	{
		#local theta_total = segments_total;
		#local theta_count = 0;
		#while (theta_count <= theta_total)
			#local theta_angle_new = radians(360 * theta_count/theta_total);
			#if (theta_count > 0)
				#local p1 = pos_point(<in_radius*cos(theta_angle_new),+in_height+diff_teak,in_radius*sin(theta_angle_new)>);
				#local p2 = pos_point(<in_radius*cos(theta_angle_old),+in_height+diff_teak,in_radius*sin(theta_angle_old)>);
				#local p3 = pos_point(<in_radius*cos(theta_angle_new),          -diff_teak,in_radius*sin(theta_angle_new)>);
				#local p4 = pos_point(<in_radius*cos(theta_angle_old),          -diff_teak,in_radius*sin(theta_angle_old)>);
				#local p5 = pos_point(<0,+diff_teak+in_height,0>);
				#local p6 = pos_point(<0,-diff_teak,0>);
				triangle {p1,p2,p3}
				triangle {p4,p3,p2}
				triangle {p1,p2,p5}
				triangle {p3,p4,p6}
			#end
			#local theta_angle_old = theta_angle_new;
			#local theta_count = theta_count + 1;
		#end
		inside_vector y
		translate +y * city_radius
	}
#end
#macro cyl_tiltA_csg(in_radius, in_height, tweak)
	// should be able to determine the proper "tweak" value algorithmically
	#if (tweak)
		#local diff_teak = 2;
	#else
		#local diff_teak = 0;
	#end
	#local in_zangle	= in_radius/city_circum * 360;
	#local out1_radius	= sind(in_zangle) * (city_radius + diff_teak)
	#local out2_radius	= sind(in_zangle) * (city_radius - diff_teak - in_height);
	object
	{
		Supercone(<0,-diff_teak,0>, out1_radius, out1_radius, <0,in_height+diff_teak,0>, out2_radius, out1_radius)
		translate +y * city_radius
	}
#end


//------------------------------------------------------------------------------cyl_tiltB

#macro cyl_tiltB(in_radius, in_height, tweak, Scale)
	#if (city_is_flat)
		cyl_tiltB_mesh(in_radius, in_height, tweak, Scale)
	#elseif (city_use_mesh)
		cyl_tiltB_mesh(in_radius, in_height, tweak, Scale)
	#else
		cyl_tiltB_csg(in_radius, in_height, tweak, Scale)
	#end
#end
#macro cyl_tiltB_csg(in_radius, in_height, tweak, in_corner)
	#if (tweak)
		#local diff_tweak = 4;
	#else
		#local diff_tweak = 0;
	#end
	#local in1_zangle	= in_radius/city_circum * 360;
	#local in2_zangle	= in_corner/sind(45)/city_circum * 360;
	#local out1_radius	= sind(in1_zangle) * (city_radius + diff_tweak);
	#local out2_radius	= sind(in1_zangle) * (city_radius - diff_tweak - in_height);
	#local out1_intsec	= cosd(in1_zangle) * (city_radius + diff_tweak);
	#local out2_intsec	= cosd(in1_zangle) * (city_radius - diff_tweak - in_height);
	#local corner_angle	= 90-atan2d(tand(90-in2_zangle) * sind(90-in2_zangle),1);
	#local corner_apex	= vrotate(<0,1,0>, <corner_angle,0,0>);
	union
	{
		#local corner_count = 0;
		#while (corner_count < 4)
			cone
			{
				<0,-out1_intsec,0>, out1_radius, <0,-out2_intsec,0>, out2_radius
//				Supercone(<0,-out1_intsec,0>, out1_radius*2/3, out1_radius, <0,-out2_intsec,0>, out2_radius*2/3, out2_radius)
				rotate z * corner_angle
				rotate y * (45 + corner_count * 90)
			}
			#local corner_count = corner_count + 1;
		#end
		translate +y * city_radius
	}
#end
#macro cyl_tiltB_mesh(in_radius, in_height, tweak, in_corner)
	#if (tweak)
		#local diff_tweak = 4;
	#else
		#local diff_tweak = 0;
	#end
	#local in1_zangle	= in_radius/city_circum * 360;
	#local in2_zangle	= in_corner/sind(45)/city_circum * 360;
	#local out1_radius	= sind(in1_zangle) * (city_radius + diff_tweak);
	#local out2_radius	= sind(in1_zangle) * (city_radius - diff_tweak - in_height);
	#local out1_intsec	= cosd(in1_zangle) * (city_radius + diff_tweak);
	#local out2_intsec	= cosd(in1_zangle) * (city_radius - diff_tweak - in_height);
	#local corner_angle	= 90-atan2d(tand(90-in2_zangle) * sind(90-in2_zangle),1);
	#local corner_apex	= vrotate(<0,1,0>, <corner_angle,0,0>);
	union
	{
		#local corner_count = 0;
		#while (corner_count < 4)
			object
			{
				con_mesh(<0,-out1_intsec,0>, out1_radius, <0,-out2_intsec,0>, out2_radius, 36)
				rotate z * corner_angle
				rotate y * (45 + corner_count * 90)
			}
			#local corner_count = corner_count + 1;
		#end
		translate +y * city_radius
	}
#end


//------------------------------------------------------------------------------sph

#macro sph_macro(in_pt, in_rd)
	#if (city_use_mesh)
		sph_mesh(in_pt, in_rd, prim_radial_sections)
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
		// do meshes need to be bounded?
//		bounded_by {sphere {in_pt, in_rd}}
	}
#end


//------------------------------------------------------------------------------cyl

#macro cyl_macro(in_pt1, in_pt2, in_rd)
	#if (city_use_mesh)
		cyl_mesh(in_pt1, in_pt2, in_rd, prim_radial_sections)
	#else
		cylinder {in_pt1, in_pt2, in_rd}
	#end
#end
#macro cyl_mesh(in_pt1, in_pt2, in_rd, segments_total)
	#local vec_diff = in_pt2 - in_pt1;
	#local vec_long = vlength(vec_diff);
	#local mesh_object = mesh
	{
		#local theta_total = segments_total;
		#local theta_count = 0;
		#while (theta_count <= theta_total)
			#local theta_angle_new = radians(360 * theta_count/theta_total);
			#if (theta_count > 0)
				#local p1 = <in_rd*cos(theta_angle_new),vec_long,in_rd*sin(theta_angle_new)>;
				#local p2 = <in_rd*cos(theta_angle_old),vec_long,in_rd*sin(theta_angle_old)>;
				#local p3 = <in_rd*cos(theta_angle_new),       0,in_rd*sin(theta_angle_new)>;
				#local p4 = <in_rd*cos(theta_angle_old),       0,in_rd*sin(theta_angle_old)>;
				#local p5 = y*vec_long;
				#local p6 = 0;
				triangle {p1,p2,p3}
				triangle {p4,p3,p2}
				triangle {p1,p2,p5}
				triangle {p3,p4,p6}
			#end
			#local theta_angle_old = theta_angle_new;
			#local theta_count = theta_count + 1;
		#end
		inside_vector y
	}
	object
	{
		mesh_object
		Point_At_Trans(vec_diff)
		translate	in_pt1
		// do meshes need to be bounded?
//		bounded_by {cylinder {in_pt1, in_pt2, in_rd}}
	}
#end


//------------------------------------------------------------------------------con

#macro con_macro(in_pt1, in_rd1, in_pt2, in_rd2)
	#if (city_use_mesh)
		con_mesh(in_pt1, in_rd1, in_pt2, in_rd2, prim_radial_sections)
	#else
		cone {in_pt1, in_rd1, in_pt2, in_rd2}
	#end
#end
// not optimized for when either of the radii equal zero
#macro con_mesh(in_pt1, in_rd1, in_pt2, in_rd2, segments_total)
	#local vec_diff = in_pt2 - in_pt1;
	#local vec_long = vlength(vec_diff);
	#local mesh_object = mesh
	{
		#local theta_total = segments_total;
		#local theta_count = 0;
		#while (theta_count <= theta_total)
			#local theta_angle_new = radians(360 * theta_count/theta_total);
			#if (theta_count > 0)
				#local p1 = <in_rd2*cos(theta_angle_new),vec_long,in_rd2*sin(theta_angle_new)>;
				#local p2 = <in_rd2*cos(theta_angle_old),vec_long,in_rd2*sin(theta_angle_old)>;
				#local p3 = <in_rd1*cos(theta_angle_new),       0,in_rd1*sin(theta_angle_new)>;
				#local p4 = <in_rd1*cos(theta_angle_old),       0,in_rd1*sin(theta_angle_old)>;
				#local p5 = y*vec_long;
				#local p6 = 0;
				triangle {p1,p2,p3}
				triangle {p4,p3,p2}
				triangle {p1,p2,p5}
				triangle {p3,p4,p6}
			#end
			#local theta_angle_old = theta_angle_new;
			#local theta_count = theta_count + 1;
		#end
		inside_vector y
	}
	object
	{
		mesh_object
		Point_At_Trans(vec_diff)
		translate	in_pt1
		// do meshes need to be bounded?
//		bounded_by {cone {in_pt1, in_rd1, in_pt2, in_rd2}}
	}
#end


//------------------------------------------------------------------------------cyl_grad

#macro cyl_grad(in1_pos, in2_pos, in_radius)
	#if (city_use_mesh)
		cyl_grad_mesh(in1_pos, in2_pos, in_radius, prim_radial_sections)
	#else
		cyl_grad_csg(in1_pos, in2_pos, in_radius)
	#end
#end
#macro cyl_grad_mesh(in1_pos, in2_pos, in_radius, segments_total)
	#local in_zangle	= in_radius/city_circum * 360;
	#local out1_radius	= sind(in_zangle) * (city_radius - in1_pos.y);
	#local out2_radius	= sind(in_zangle) * (city_radius - in2_pos.y);
	object {con_mesh(in1_pos, out1_radius, in2_pos, out2_radius, segments_total)}
#end
#macro cyl_grad_csg(in1_pos, in2_pos, in_radius)
	#local in_zangle	= in_radius/city_circum * 360;
	#local out1_radius	= sind(in_zangle) * (city_radius - in1_pos.y);
	#local out2_radius	= sind(in_zangle) * (city_radius - in2_pos.y);
	cone {in1_pos, out1_radius, in2_pos, out2_radius}
#end


//------------------------------------------------------------------------------Re-used stuff

#macro street_lamp_macro(in_seed)
	union
	{
		intersection
		{
			object {sph_macro(y*3.25, 0.20)}
			plane {-y, -3.25}
		}
		object {con_macro(y*0, 0.10, y*3, 0.05)}
		object
		{
			con_macro(y*3, 0.10, y*3.25, 0.20)
			texture
			{
				pigment {gamma_color_adjust(<1.0, 0.9, 0.7>)}
				finish {emission 1.3}
			}
		}
		texture {lamp_texture}
		scale Meters
	}
#end
#macro potted_plant_macro(in_seed)
	#local unknown_texture = texture
	{
		#switch (TexQual)
			#case (-1)
				pigment {lowqual_pig(in_seed)}
			#break
			#case (0)
			#case (1)
			#case (2)
				pigment {gamma_color_adjust(<0.2,0.2,0.2>)}
			#break
		#end
	}
	union
	{
		object
		{
			TREE
			scale		<1,2,1> * rand(in_seed) + <1,2,1>
			translate	y * 1/8
			rotate		y * rand(in_seed) * 360
		}
		difference
		{
			object {sph_macro(y*1, 8/8)}
			object {sph_macro(y*1, 7/8)}
			plane {-y,-1}
//			bounded_by {sph_macro(y*1, 8/8)}
		}
		intersection
		{
			object {sph_macro(y*1, 7/8)}
			plane {y, 7/8}
			texture {unknown_texture}
//			bounded_by {sph_macro(y*1, 7/8)}
		}
		object {cyl_macro(0, y/2, 1/8)	translate <-1,0,-1>/2}
		object {cyl_macro(0, y/2, 1/8)	translate <-1,0,+1>/2}
		object {cyl_macro(0, y/2, 1/8)	translate <+1,0,+1>/2}
		object {cyl_macro(0, y/2, 1/8)	translate <+1,0,-1>/2}
		rotate +y * rand(in_seed) * 360
		texture {metal_texture}
		scale Meters * 1/2
	}
#end
#macro trash_can_macro(in_seed)
	union
	{
		difference
		{
			cone {y/2, 12/16, y*5/2, 16/16}
			cone {y/1, 11/16, y*6/2, 15/16}
			bounded_by {cone {y/2, 12/16, y*5/2, 16/16}}
		}
		cylinder {0, y*5/2, 1/8	translate <-1,0,0>}
		cylinder {0, y*5/2, 1/8	translate <+1,0,0>}
		cylinder {0, y*5/2, 1/8	translate <0,0,+1>}
		cylinder {0, y*5/2, 1/8	translate <0,0,-1>}
		scale 2/5
		rotate +y * rand(in_seed) * 360
		texture {trash_texture}
		scale Meters * 1
	}
#end
#macro ped_macro(in_seed)
	// need to create hair too
	#local col1 = gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed)>);
	#local col2 = gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed)>);
//	#local col3 = gamma_color_adjust(<128,080,048>/255+rand(in_seed)*128/255);
	#local col3 = gamma_color_adjust(<044,018,018>/255+rand(in_seed)*<192,192,170>/255);
	union
	{
		sphere
		{
			y/2, 1/2
			pigment {col1}
			scale <1/4,1,1/4>
		}
		difference
		{
			sphere {y/2, 1/2}
			plane {y, 1/2}
			pigment {col2}
			scale <1/3,1,1/3>
		}
		sphere
		{
			y, 1/12
			pigment {col3}
			scale <4/3,1,4/3>
		}
		scale <rand(in_seed) * 1/2 + 1/2,rand(in_seed) * 1/2 + 1/2,rand(in_seed) * 1/2 + 1/2>
		scale people_max_height
	}
#end
#macro tree_macro(in_seed)
	object
	{
		TREE
		scale city_tree_height * (rand(in_seed) * 2/3 + 1/3)
		rotate y * rand(in_seed) * 360
		scale Meters
	}
#end

/*******************************************************************************/

//#version 3.7		// can't set the version here
verbose_include("gh_deciduous_tree.inc", defined(TREE))

// For creating lit/unlit window textures
// no longer used, but need to re-implement
#macro window_texture(UnlitTexture, LitTexture, WindowSize)
	#local WScale = WindowSize + <(WindowSize.x = 0 ? 1 : 0), (WindowSize.y = 0 ? 1 : 0), (WindowSize.z = 0 ? 1 : 0)>;
	#local WV = windows_lit*(1+windows_blend);
	bozo
	texture_map
	{
		[WV - windows_blend	LitTexture	scale 1/(100*WScale)]
		[WV			UnlitTexture	scale 1/(100*WScale)]
	}
	scale 100
	#if (WindowSize.x) warp {repeat x offset -x * 100} #end
	#if (WindowSize.y) warp {repeat y offset -y * 100} #end
	#if (WindowSize.z) warp {repeat z offset -z * 100} #end
	scale WScale * 1.001
#end

#macro set_window_texture(UnlitTexture, LitTexture, WindowSize)
	#declare building_window_texture[building_types] = texture
	{
		window_texture(UnlitTexture, LitTexture, WindowSize)
	}
	#declare building_window_size[building_types] = WindowSize;
#end

// For creating spotlights without media or light sources: Colour should include filter and/or transmit
// ugly but fast
// can't use cone macro because it doesn't support the "open" keyword!!!
#macro spotlight_cone(Point1, Radius1, Point2, Radius2, Colour, Falloff)
	#local D = Point2 - Point1;
	cone
	{
		Point1, Radius1, Point2, Radius2
		open
		hollow
		no_shadow
		pigment
		{
			gradient D
			color_map
			{
				[0 Colour]
				[1 Colour transmit 1]
			}
			poly_wave Falloff
			scale vlength(D)
			translate Point1
		}
		finish {ambient 1 diffuse 0}
	}
#end

#macro init_building_types()
	// INITIALIZE BUILDING OBJECT ARRAYS
	#local max_building_types = 100;
	#declare building_macros		= array[max_building_types];
	#declare building_ident			= array[max_building_types];
	#declare building_chance		= array[max_building_types];
	#declare building_unique		= array[max_building_types];
	#declare building_types			= 0;
#end
