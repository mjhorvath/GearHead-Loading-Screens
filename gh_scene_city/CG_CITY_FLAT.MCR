/*************************************************************************
		DEFAULT CITY GENERATOR MACRO FILE FOR PERSISTENCE OF VISION 3.x
**************************************************************************

Created by Chris Colefax, 1 February 1999
NOTE: This file is designed for use with City.inc; see City.htm for
		more information

*************************************************************************/

// CHECK OPTIONS AND ASSIGN DEFAULTS
#ifndef (city_seed)	#local city_seed	= 0;	#end
#declare _CT_rand1	= seed(city_seed); // For traffic
#declare _CT_rand2	= seed(city_seed); // For pavement objects
#declare _CT_rand3	= seed(city_seed); // For buildings
#declare _CT_rand4	= seed(city_seed); // For building levels

#ifndef (building_width)		#declare building_width			= 25;			#end
#ifndef (min_building_height)		#declare min_building_height		= building_width * .5;	#end
#ifndef (max_building_height)		#declare max_building_height		= building_width * 2;	#end
#ifndef (building_height_falloff)	#declare building_height_falloff	= 2;			#end
#ifndef (building_height_turb)		#declare building_height_turb		= .5;			#end

#ifndef (pavement_height)		#declare pavement_height		= .15;	#end
#ifndef (traffic_spacing)		#declare traffic_spacing		= 10;	#end
#ifndef (traffic_lanes)			#declare traffic_lanes			= 1;	#end
#ifndef (traffic_width)			#declare traffic_width			= 3;	#end
#declare street_width = traffic_width*2*(traffic_lanes + .5);

#ifndef (city_default_objects)		#declare city_default_objects		= true;	#end
#ifndef (building_types)		#declare building_types			= 0;	#end

#if (city_default_objects) 
	#include "CG_DEFAULT.INC"
	#if (traffic_spacing > 0)
		#include "CG_VEHICLES.INC"
	#end
	#include "CG_FLATS.INC"
	#include "CG_HOTELS.INC"
	#include "CG_OFFICES.INC"
	#include "CG_PARK.INC"
	#include "CG_SQUARE.INC"
#end

// CITY CREATION MACROS
#macro city_base (Corner1, Corner2)
	#declare _CT_extents = (abs(city_corner1.x) + abs(city_corner1.z)) / 2;
	plane
	{
		y, 0
		hollow
		clipped_by {box {<Corner1.x, -.1, Corner1.z>, <Corner2.x, .1, Corner2.z>}}
		texture {street_texture}
	}
#end

#macro city_pavement (Corner1, Corner2)
	box {Corner1, Corner2 + y*pavement_height texture {pavement_texture}}

	#ifdef (pavement_object)
		#local PSize = Corner2 - Corner1;
		#local V = 0;
		#while (V < dimension_size(pavement_object, 1))
			#local P = pavement_object_offset[V] + rand(_CT_rand2)*pavement_object_turb[V];
			#while (P < PSize.x - pavement_object_offset[V])
				object
				{
					pavement_object[V]
					rotate y*90
					translate Corner1 + <P, pavement_height, 0>
				}
				object
				{
					pavement_object[V]
					rotate y*270
					translate Corner2 + <-P, pavement_height, 0>
				}
				#if (pavement_object_spacing[V] <= 0)
					#local P = PSize.x;
				#else
					#local P = P + pavement_object_spacing[V] + rand(_CT_rand2)*pavement_object_turb[V];
				#end
			#end

			#local P = pavement_object_offset[V] + rand(_CT_rand2)*pavement_object_turb[V];
			#while (P < PSize.z - pavement_object_offset[V])
				object
				{
					pavement_object[V]
					translate <Corner2.x, pavement_height, Corner1.z + P>
				}
				object
				{
					pavement_object[V]
					rotate y*180
					translate <Corner1.x, pavement_height, Corner2.z - P>
				}
				#if (pavement_object_spacing[V] <= 0)
					#local P = PSize.z;
				#else
					#local P = P + pavement_object_spacing[V];
				#end
			#end
			#local V = V + 1;
		#end
		#local people_count = 0;
		#local people_total = ceil(10 * rand(_CT_rand2));
		#while (people_count < people_total)
			object
			{
				ped_macro(_CT_rand2)
				translate Corner1 + <+PSize.x * rand(_CT_rand2), pavement_height, +pavement_width * rand(_CT_rand2)>
			}
			object
			{
				ped_macro(_CT_rand2)
				translate Corner1 + <+pavement_width * rand(_CT_rand2), pavement_height, +PSize.z * rand(_CT_rand2)>
			}
			object
			{
				ped_macro(_CT_rand2)
				translate Corner2 + <-PSize.x * rand(_CT_rand2), pavement_height, -pavement_width * rand(_CT_rand2)>
			}
			object
			{
				ped_macro(_CT_rand2)
				translate Corner2 + <-pavement_width * rand(_CT_rand2), pavement_height, -PSize.z * rand(_CT_rand2)>
			}
			#local people_count = people_count + 1;
		#end
	#end
#end

// TWEAKED!!!
#macro city_traffic (From, To, Direction)
	#local V = dimension_size(city_vehicle, 1);
	#if (Direction = 0)
		#local I = BlockSize.x;
	#else
		#local I = BlockSize.z;
	#end
	#local I = I + street_width;
	#local L = -traffic_lanes;
	#while (L <= traffic_lanes)
		#local VD = (L < 0 ? -1 : 1);
		#local V2 = (Direction ? From.x : From.z) + traffic_width*VD*(abs(L)-.5);
		#local V1 = (Direction ? From.z : From.x) + street_width + rand(_CT_rand1)*traffic_spacing;
		#while (V1 < (Direction ? To.z : To.x) - (city_tileable ? 0 : street_width))
			#local VT = int(V*rand(_CT_rand1));
			object
			{
				city_vehicle[VT]
				rotate +y*90*VD
				rotate -y*90*Direction
				#if (!Direction)
					translate <V1, 0, V2>
				#else
					translate <V2, 0, V1>
				#end
			}
			#local V1 = V1 + city_vehicle_spacing[VT] + (1 + 2*rand(_CT_rand1))*traffic_spacing;
			#if (mod(V1 - (Direction ? From.z : From.x), I) < street_width)
				#local V1 = V1 + street_width;
			#end
		#end
		#local L = L + (L = -1 ? 2 : 1);
	#end
#end

// TWEAKED!!!
#macro city_street (From, To, Direction)
	#ifdef (street_overlay)
		box
		{
			#if (!Direction)
				From	- <0,0.01,street_width/2>,
				To	+ <0,0.02,street_width/2>
			#else
				From	- <street_width/2,0.01,0>,
				To	+ <street_width/2,0.02,0>
			#end
			texture
			{
				street_overlay
				scale traffic_width
				rotate -y*90*Direction
				translate From
			}
		}
	#end
	#if (traffic_spacing > 0 & defined(city_vehicle))
		city_traffic(From, To, Direction)
	#end
#end

#macro city_building (Corner1, Corner2, Direction)
	#if (building_types > 0 & defined(building_size))
		#local BCentre = (Corner1 + Corner2)/2;
		#local BHeight = pow(1.2 - (vlength(BCentre) / _CT_extents), building_height_falloff);
		#local BHeight = BHeight + (rand(_CT_rand3) - .5)*building_height_turb;
		#local BHeight = min_building_height + BHeight*(max_building_height - min_building_height);
		#if (BHeight > 0)
			city_assemble_building (int(building_types*rand(_CT_rand3)), (Corner2-Corner1) + y*BHeight, -y*90*Direction, BCentre + y*pavement_height)
		#end
	#end
#end

#macro city_option (Option)
	(mod(building_options[Type], Option*2) >= Option ? true : false)
#end
#macro city_assemble_building (Type, Size, Rotate, Translate)
	#local Levels = ceil((Size.y / Size.x) / (building_size[Type].y / building_size[Type].x));
	#local LHeight = y*building_size[Type];
	#local Scale = Size/building_size[Type]; #local Scale = <Scale.x, (Scale.x+Scale.z)/2, Scale.z>;
	#local CLevel = 0;

	union
	{
		#if (city_option(build_profile))
			object {building_profile[Type] scale <1, Levels, 1>}
		#end
		#if (city_option(build_base))
			object {building_base[Type]} #local CLevel = 1;
		#end
		#if (city_option(build_details))
			#while (CLevel < Levels)
				object
				{
					building_details[Type]
					translate LHeight*CLevel
				}
				#local CLevel = CLevel + 1;
			#end
		#end

		#if (city_option(build_window_profile))
			object
			{
				building_windows[Type]
				scale <1, Levels, 1>
				texture
				{
					building_window_texture[Type]
					translate <int(rand(_CT_rand4)*100)-50, int(rand(_CT_rand4)*100), int(rand(_CT_rand4)*100)-50>*building_window_size[Type]
				}
			}
		#end
		#if (city_option(build_window_levels))
			#local CLevel = 0;
			#while (CLevel < Levels)
				object
				{
					building_windows[Type]
					texture
					{
						building_window_texture[Type]
						translate <int(rand(_CT_rand4)*100)-50, int(rand(_CT_rand4)*100), int(rand(_CT_rand4)*100)-50>*building_window_size[Type]
					}
					translate LHeight*CLevel
				}
				#local CLevel = CLevel + 1;
			#end
		#end

		#if (city_option(build_roof))
			object
			{
				building_roof[Type]
				translate LHeight*Levels
			}
		#else
			sphere
			{
				0, 0
				pigment {rgb 0}
			}
		#end

		#if (city_option(build_fit_texture))
			texture {building_texture[Type]}
		#end
		rotate Rotate
		scale Scale
		translate Translate
		#if (city_option(build_texture))
			texture {building_texture[Type] scale Scale}
		#end
	}
#end

#macro ped_macro(in_seed)
	#local col1 = gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed)>);
	#local col2 = gamma_color_adjust(<rand(in_seed),rand(in_seed),rand(in_seed)>);
	#local col3 = gamma_color_adjust(<128,080,048>/255+rand(in_seed)*128/255);
	union
	{
		sphere
		{
			y/2, 1/2
			pigment {col1}
			scale <1/4,4/3,1/4>
		}
		difference
		{
			sphere {y/2, 1/2}
			plane {y, 1/2}
			pigment {col2}
			scale <1/3,4/3,1/3>
		}
		sphere
		{
			y, 1/12
			pigment {col3}
			scale <4/3,4/3,4/3>
		}
		scale <rand(in_seed) * 1/3 + 2/3,rand(in_seed) * 1/3 + 2/3,rand(in_seed) * 1/3 + 2/3>
	}
#end
