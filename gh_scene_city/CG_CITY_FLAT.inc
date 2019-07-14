/*************************************************************************
		  CITY GENERATOR INCLUDE FILE FOR PERSISTENCE OF VISION 3.x
**************************************************************************

Created by Chris Colefax, 1 February 1999

See City.htm for more information.

*************************************************************************/

// CHECK VERSION
#if (version < 3.1)
	#warning "The City Generator Include File requires POV-Ray 3.1 or later!\n\n"
#else
	#local _CT_version = version;
	#version 3.1;

	// INCLUDE CITY MACROS/OBJECTS
	#ifndef (debug_progress)
		#local debug_progress = false;
	#end
	#if (debug_progress)
		#debug "CITY GENERATOR INCLUDE FILE:\n"
	#end
	#ifdef (city_macro_file)
		#include city_macro_file
		#if (debug_progress)
			#debug concat ("  Including \"", city_macro_file, "\"...\n")
		#end
	#else
		#ifndef (city_base)
			#include "CG_CITY_FLAT.MCR"
			#if (debug_progress)
				#debug concat ("  Including \"CG_City_FLAT.mcr\"...\n")
			#end
		#end
	#end

	// CHECK OPTIONS AND ASSIGN DEFAULTS
	#macro _CT_get_dimensions(V1, V2)
		#local Vec = <1, 1, 1> * V1;
		#declare V2 = <max(1, Vec.x), 0, max(max(1, Vec.y), Vec.z)>;
	#end

	#local BlockCount = <2, 0, 2>;
	#ifdef (city_block_count)
		_CT_get_dimensions (city_block_count, BlockCount)
	#end

	#local BPB = <3, 0, 2>;
	#ifdef (buildings_per_block)
		_CT_get_dimensions (buildings_per_block, BPB)
	#end

	#ifndef (street_width)
		#local street_width = 10;
	#end
	#ifndef (pavement_width)
		#local pavement_width = 4;
	#end
	#ifndef (building_width)
		#local building_width = 25;
	#end
	#ifndef (building_gap)
		#local building_gap = 2;
	#end
	#ifndef (city_tileable)
		#local city_tileable = false;
	#end

	// CREATE UNION OF CITY BLOCKS
	#macro VStr(V, C1, C2)
		concat("<", str(V.x, C1, C2), ",", str(V.y, C1, C2), ",", str(V.z, C1, C2), ">")
	#end

	#local BlockSize = building_width * BPB + building_gap * (BPB - <1, 0, 1>) + pavement_width * <2, 0, 2>;
	#declare city_corner1 = (BlockCount * BlockSize + (BlockCount + <1, 0, 1>) * street_width) * <-.5, 0, -.5>;
	#declare city_corner2 = -city_corner1;																					 
	#if (city_tileable)
		#declare city_corner2 = city_corner2 - street_width * <1, 0, 1>;
	#end

	union
	{
		#if (debug_progress)
			#debug concat ("  Creating city base from ", VStr(city_corner1, 0, 2), " to ", VStr(city_corner2, 0, 2), "...\n")
		#end
		city_base (city_corner1, city_corner2)
/*
		// CREATE CITY STREETS
		#ifdef (city_street)
			#if (debug_progress)
				#debug concat ("  Creating city streets...\n")
			#end
			#local BlockZ = 0;
			#while (BlockZ < BlockCount.z + (city_tileable ? 0 : 1))
				#local StreetStart = city_corner1 + z*(BlockZ*(BlockSize+street_width) + street_width/2);
				city_street (StreetStart, StreetStart + x*(city_corner2-city_corner1), 0)
				#local BlockZ = BlockZ + 1;
			#end

			#local BlockX = 0;
			#while (BlockX < BlockCount.x + (city_tileable ? 0 : 1))
				#local StreetStart = city_corner1 + x*(BlockX*(BlockSize+street_width) + street_width/2);
				city_street (StreetStart, StreetStart + z*(city_corner2-city_corner1), 1)
				#local BlockX = BlockX + 1;
			#end
		#end
*/
		// CREATE CITY STREETS
		#ifdef (city_street)
			#if (debug_progress)
				#debug concat ("  Creating city streets...\n")
			#end
			#local BlockZ = 0;
			#while (BlockZ < BlockCount.z + (city_tileable ? 0 : 1))
				#local BlockX = 0;
				#while (BlockX < BlockCount.x + (city_tileable ? 0 : 1))
					// PASS 1
					#local StreetStart = city_corner1
					+ z*(BlockZ*(BlockSize+street_width) + street_width * 1/2)
					+ x*(BlockX*(BlockSize+street_width) + street_width * 2/2);
					#local StreetStop = StreetStart
					+ x*(BlockSize);
					city_street (StreetStart, StreetStop, 0)

					// PASS 2
					#local StreetStart = city_corner1
					+ z*(BlockZ*(BlockSize+street_width) + street_width * 2/2)
					+ x*(BlockX*(BlockSize+street_width) + street_width * 1/2);
					#local StreetStop = StreetStart
					+ z*(BlockSize);
					city_street (StreetStart, StreetStop, 1)

					#local BlockX = BlockX + 1;
				#end
				#local BlockZ = BlockZ + 1;
			#end
		#end

		// CREATE CITY BLOCKS
		#local BlockX = 0;
		#while (BlockX < BlockCount.x)
			#local BlockZ = 0;
			#while (BlockZ < BlockCount.z)
				#local BlockCorner1 = city_corner1 + <BlockX, 0, BlockZ> * (BlockSize + street_width);
				#local BlockCorner2 = BlockCorner1 + BlockSize + street_width * <1, 0, 1>;

				// CREATE PAVEMENT FOR CURRENT BLOCK
				#if (debug_progress)
					#debug concat ("  Creating city block ", str(BlockX * BlockCount.z + BlockZ + 1, 0, 0), " of ", str(BlockCount.x * BlockCount.z, 0, 0), "...\n")
				#end
				#ifdef (city_pavement)
					#if (debug_progress)
						#debug "	 Creating pavement..."
					#end
					city_pavement (BlockCorner1 + street_width * <1, 0, 1>, BlockCorner2)
				#end

				// CREATE BUILDINGS FOR CURRENT BLOCK
				#ifdef (city_building)
					#if (debug_progress)
						#debug "\r	 Creating buildings...				"
					#end
					#local FirstBuildingPos = BlockCorner1 + (street_width + pavement_width) * <1, 0, 1>;
					#local CurPos = FirstBuildingPos;
					#local BuildingX = 0;
					#while (BuildingX < BPB.x)
						#local CurPos = CurPos * <1, 1, 0> + FirstBuildingPos * z;
						#local BuildingZ = 0;
						#while (BuildingZ < BPB.z)
							#local BuildingDir = 1;
							#if (BuildingZ = BPB.z - 1)
								#local BuildingDir = 2;
							#end
							#if (BuildingX = 0)
								#local BuildingDir = 3;
							#end
							#if (BuildingZ = 0 & BuildingX < BPB.x - 1)
								#local BuildingDir = 0;
							#end
							city_building (CurPos, CurPos + building_width * <1, 0, 1>, BuildingDir)
							#local CurPos = CurPos + z * (building_width + building_gap);
							#local BuildingZ = BuildingZ + 1;
						#end
						#local CurPos = CurPos + x * (building_width + building_gap);
						#local BuildingX = BuildingX + 1;
					#end
					#if (debug_progress)
						#debug "\r"
					#end
				#end

				// LOOP THROUGH NEXT BLOCK
				#local BlockZ = BlockZ + 1;
			#end
			#local BlockX = BlockX + 1;
		#end

		#ifdef (city_finish)
			city_finish ()
		#end
		#ifdef (city_transform)
			transform city_transform
		#end
	}
	#if (debug_progress)
		#debug "  Finished creating city!\n\n"
	#end

	#version _CT_version;
#end
