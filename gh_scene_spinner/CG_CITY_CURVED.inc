/*************************************************************************
		  CITY GENERATOR INCLUDE FILE FOR PERSISTENCE OF VISION 3.x
**************************************************************************

Created by Chris Colefax, 1 February 1999

Modified by Michael Horvath, starting in 2010

See City.htm for more information.

*************************************************************************/

// CHECK VERSION
#if (version < 3.1)
	#warning "The City Generator Include File requires POV-Ray 3.1 or later!\n\n"
#else
	#include "transforms.inc"

	// INCLUDE CITY MACROS/OBJECTS
	#ifndef (debug_progress)
		#declare debug_progress = false;
	#end
	debug_detail("z\nCITY GENERATOR INCLUDE FILE:\n")
	#ifdef (city_macro_file)
		#include city_macro_file
		debug_detail(concat("CG...Including \"", city_macro_file, "\".\n"))
	#end

	// CREATE UNION OF CITY BLOCKS
	#macro VStr(V, C1, C2)
		concat("<", str(V.x, C1, C2), ",", str(V.y, C1, C2), ",", str(V.z, C1, C2), ">")
	#end

	#declare block_size = nominal_building_width * buildings_per_block;
	#declare city_corner1 = (blocks_per_section * block_size + (blocks_per_section - <1, 0, 1>) * street_width) * <-0.5, 0, -0.5> - <!NoStreetX1, 0, !NoStreetZ1> * street_width;
	#declare city_corner2 = (blocks_per_section * block_size + (blocks_per_section - <1, 0, 1>) * street_width) * <+0.5, 0, +0.5> + <!NoStreetX2, 0, !NoStreetZ2> * street_width;

	union
	{
		debug_detail(concat("CG...Creating city base from ", VStr(city_corner1, 0, 2), " to ", VStr(city_corner2, 0, 2), ".\n"))

		city_base(city_corner1, city_corner2)

		// CREATE CITY STREETS & TRAFFIC
		// need separate regular and elevated transport
		// street width needs to be 0 if elevated transport is on
		#if ((!NoStreet) & (nominal_traffic_width > 0))
			debug_detail(concat ("CG...Creating city streets and stations.\n"))
			#local BlockZ = 0;
			#while (BlockZ < blocks_per_section.z + (NoStreetZ2 ? 0 : 1))
				#local count_car_x = 0;
				#local BlockX = 0;
				#while (BlockX < blocks_per_section.x + (NoStreetX2 ? 0 : 1))
					// TRACK PASS 1
					#if (BlockX < blocks_per_section.x)
						#if (!NoStreetZ1 | (BlockZ > 0))
							// TRACK
							#local StreetStartX = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 1/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
							#local StreetStopX = StreetStartX + x*(block_size.x + street_width);
							#if ((BlockZ > 0) & (BlockZ < blocks_per_section.z))
								city_rail_track(StreetStartX, StreetStopX, 0)
							#elseif ((!NoRailZ1) & (BlockZ = 0))
								city_rail_track(StreetStartX, StreetStopX, 0)
							#elseif ((!NoRailZ2) & (BlockZ = blocks_per_section.z))
								city_rail_track(StreetStartX, StreetStopX, 0)
							#end
							// PAVEMENT BENEATH TRACK
							#local StreetStartX = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 0/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
							#local StreetStopX = StreetStartX + x*block_size.x;
							city_rail_pavement(StreetStartX, StreetStopX, 0)
						#end
					#end
					// TRACK PASS 2
					#if (BlockZ < blocks_per_section.z)
						#if (!NoStreetX1 | (BlockX > 0))
							// TRACK
							#local StreetStartZ = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 1/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
							#local StreetStopZ = StreetStartZ + z*(block_size.z + street_width);
							#if ((BlockX > 0) & (BlockX < blocks_per_section.x))
								city_rail_track(StreetStartZ, StreetStopZ, 1)
							#elseif ((!NoRailX1) & (BlockX = 0))
								city_rail_track(StreetStartZ, StreetStopZ, 1)
							#elseif ((!NoRailX2) & (BlockX = blocks_per_section.x))
								city_rail_track(StreetStartZ, StreetStopZ, 1)
							#end
							// PAVEMENT BENEATH TRACK
							#local StreetStartZ = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 0/2) + x*(BlockX*(block_size.x+street_width) - street_width * 1/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
							#local StreetStopZ = StreetStartZ + z*block_size.z;
							city_rail_pavement(StreetStartZ, StreetStopZ, 1)
						#end
					#end
					// INTERSECTIONS
					#if (!NoStation)
						#if ((!NoStreetZ1 | (BlockZ > 0)) & (!NoStreetX1 | (BlockX > 0)))
							#if (((NoRailX1) & (BlockX = 0)) | ((NoRailZ1) & (BlockZ = 0)) | ((NoRailX2) & (BlockX = blocks_per_section.x)) | ((NoRailZ2) & (BlockZ = blocks_per_section.z)))
							#else
								#local PlatformStart = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 1/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
								city_station_track(PlatformStart)		// direction is hardcoded here!!
							#end
						#end
					#else
						// pedestal holding up the track, hardcoded directional behavior since it's only used in one direction in my scene
						#local PedestalStart = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 0/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
						city_rail_pedestal(PedestalStart, 0)
					#end
					// PAVEMENT BENEATH INTERSECTIONS
//					#if ((!NoRailZ1 & !NoStreetZ1 & (BlockX = 0)) | (!NoRailX1 & !NoStreetX1 & (BlockZ = 0)) | (!NoRailZ2 & !NoStreetZ2 & (BlockX = blocks_per_section.x)) | (!NoRailX2 & !NoStreetX2 & (BlockZ = blocks_per_section.z)))
						#local PavementStart = city_corner1 + z*(BlockZ*(block_size.z+street_width) - street_width * 1/2) + x*(BlockX*(block_size.x+street_width) - street_width * 1/2) + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
						city_station_pavement(PavementStart)
//					#end
					#local BlockX = BlockX + 1;
				#end
				#local BlockZ = BlockZ + 1;
			#end
			#if (!NoCars & traffic_spacing > 0)
				debug_detail(concat("CG...Creating city traffic.\n"))
				// TRAFFIC PASS 1
				#if (!NoCarsZ)
					#local BlockZ = 0;
					#while (BlockZ < blocks_per_section.z + (NoStreetZ2 ? 0 : 1))
	
						#local StreetStartX = city_corner1 + z * (BlockZ * (block_size.z + street_width) - street_width * 1/2) + z * !NoStreetZ1 * street_width;
	//					#local StreetStopX = StreetStartX + x * blocks_per_section.x * block_size.x;
						#local StreetStopX = StreetStartX + x * city_circum/2;		// hack to get the cars to show up randomly over the whole circumference of the habitat
	
						#if (!NoStreetZ1 | (BlockZ > 0))
							#if ((BlockZ > 0) & (BlockZ < blocks_per_section.z))
								city_rail_traffic(StreetStartX, StreetStopX, 0)
							#elseif ((!NoRailZ1) & (BlockZ = 0))
								city_rail_traffic(StreetStartX, StreetStopX, 0)
							#elseif ((!NoRailZ2) & (BlockZ = blocks_per_section.z))
								city_rail_traffic(StreetStartX, StreetStopX, 0)
							#end
						#end
	
						#local BlockZ = BlockZ + 1;
					#end
				#end
				// TRAFFIC PASS 2
				#if (!NoCarsX)
					#local BlockX = 0;
					#while (BlockX < blocks_per_section.x + (NoStreetX2 ? 0 : 1))
	
						#local StreetStartZ = city_corner1 + x * (BlockX * (block_size.x + street_width) - street_width * 1/2) + x * !NoStreetX1 * street_width;
						#local StreetStopZ = StreetStartZ + z * blocks_per_section.z * block_size.z;
	
						#if (!NoStreetX1 | (BlockX > 0))
							#if ((BlockX > 0) & (BlockX < blocks_per_section.x))
								city_rail_traffic(StreetStartZ, StreetStopZ, 1)
							#elseif ((!NoRailX1) & (BlockX = 0))
								city_rail_traffic(StreetStartZ, StreetStopZ, 1)
							#elseif ((!NoRailX2) & (BlockX = blocks_per_section.x))
								city_rail_traffic(StreetStartZ, StreetStopZ, 1)
							#end
						#end
	
						#local BlockX = BlockX + 1;
					#end
				#end
			#end
		#end

		// CREATE CITY BLOCKS
		#local BlockX = 0;
		#while (BlockX < blocks_per_section.x)
			#local BlockZ = 0;
			#while (BlockZ < blocks_per_section.z)
				#local BlockCorner1 = city_corner1 + (block_size + street_width) * <BlockX, 0, BlockZ> + <!NoStreetX1, 0, !NoStreetZ1> * street_width;
				#local BlockCorner2 = BlockCorner1 + (block_size + street_width) * <1, 0, 1>;

				// CREATE PAVEMENT FOR CURRENT BLOCK
				debug_detail(concat("\nCG...Creating city block ", str(BlockX * blocks_per_section.z + BlockZ + 1, 0, 0), " of ", str(blocks_per_section.x * blocks_per_section.z, 0, 0), ".\n"))
				#ifdef (city_pavement)
					debug_detail("CG......Creating pavement.\n")

					city_pavement(BlockCorner1, BlockCorner2 - street_width * <1, 0, 1>)
				#end

				// CREATE BUILDINGS & PEDESTRIANS FOR CURRENT BLOCK
				#ifdef (city_building)
					debug_detail("CG......Creating buildings, street decorations & pedestrians.\n")
					#local FirstBuildingPos = BlockCorner1 + (pavement_width) * <1, 0, 1>;
					#local CurPos = FirstBuildingPos;
					#for (BuildingX, 0, buildings_per_block.x - 1)
						#local CurPos = CurPos * <1, 1, 0> + FirstBuildingPos * z;
						#for (BuildingZ, 0, buildings_per_block.z - 1)
							#if (!NoBuildings)
								// north side
								#if ((BuildingZ = 0) & (BuildingX != 0))
									#local BuildingDir = 0;
								// east side
								#elseif (BuildingX = buildings_per_block.x - 1)
									#local BuildingDir = 1;
								// south side
								#elseif (BuildingZ = buildings_per_block.z - 1)
									#local BuildingDir = 2;
								// west side
								#elseif (BuildingX = 0)
									#local BuildingDir = 3;
								// inside
								#else
									#local BuildingDir = floor(rand(_CT_rand4) * 3 + 0.5);
								#end
								city_building(CurPos, CurPos + building_width * <1, 0, 1>, BuildingDir)
							#end
							#if (!NoPedestrians)
								// sidewalk pedestrians
								// 1
								#if ((BuildingX = 0) | (BuildingZ = 0))
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = -pavement_width;
								#local posz1 = -pavement_width;
								#local posx2 = -0;
								#local posz2 = -0;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 2
								#if (BuildingZ = 0)
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = -0;
								#local posz1 = -pavement_width;
								#local posx2 = +building_width;
								#local posz2 = -0;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 3
								#if ((BuildingX = buildings_per_block.x - 1) | (BuildingZ = 0))
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = +building_width;
								#local posz1 = -pavement_width;
								#local posx2 = +building_width + pavement_width;
								#local posz2 = -0;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 4
								#if (BuildingX = buildings_per_block.x - 1)
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = +building_width;
								#local posz1 = -0;
								#local posx2 = +building_width + pavement_width;
								#local posz2 = +building_width;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 5
								#if ((BuildingX = buildings_per_block.x - 1) | (BuildingZ = buildings_per_block.z - 1))
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = +building_width;
								#local posz1 = +building_width;
								#local posx2 = +building_width + pavement_width;
								#local posz2 = +building_width + pavement_width;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 6
								#if (BuildingZ = buildings_per_block.z - 1)
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = -0;
								#local posz1 = +building_width;
								#local posx2 = +building_width;
								#local posz2 = +building_width + pavement_width;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 7
								#if ((BuildingZ = buildings_per_block.z - 1) | (BuildingX = 0))
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = -pavement_width;
								#local posz1 = +building_width;
								#local posx2 = -0;
								#local posz2 = +building_width + pavement_width;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
	
								// 8
								#if (BuildingX = 0)
									#local ped_density = 1;
								#else
									#local ped_density = 2/4;	// was 1/4
								#end
								#local posx1 = -pavement_width;
								#local posz1 = -0;
								#local posx2 = -0;
								#local posz2 = +building_width;
								city_pedestrians(CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, ped_density)
							#end
							// more street lamps, trash cans, potted plants, need to add a little turbulence
							#if (!NoStreetDeco & NewTrain)
								// vertical
								#local posx1 = -pavement_width;
								#local posz1 = -pavement_width;
								#local posx2 = -pavement_width;
								#local posz2 = +building_width + pavement_width;
								city_decorations(street_lamp_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 0, 1, streetlamp_number)
								city_decorations(trash_can_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, trashcan_number)
								city_decorations(potted_plant_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, pottedplant_number)

								// horizontal
								#local posx1 = -pavement_width;
								#local posz1 = -pavement_width;
								#local posx2 = +building_width + pavement_width;
								#local posz2 = -pavement_width;
								city_decorations(street_lamp_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, streetlamp_number)
								city_decorations(trash_can_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, trashcan_number)
								city_decorations(potted_plant_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, pottedplant_number)

								// vertical
								#if (BuildingX = buildings_per_block.x - 1)
									#local posx1 = +building_width + pavement_width;
									#local posz1 = -pavement_width;
									#local posx2 = +building_width + pavement_width;
									#local posz2 = +building_width + pavement_width;
									city_decorations(street_lamp_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 0, 0, streetlamp_number)
									city_decorations(trash_can_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, trashcan_number)
									city_decorations(potted_plant_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, pottedplant_number)
								#end

								// horizontal
								#if (BuildingZ = buildings_per_block.z - 1)
									#local posx1 = -pavement_width;
									#local posz1 = +building_width + pavement_width;
									#local posx2 = +building_width + pavement_width;
									#local posz2 = +building_width + pavement_width;
									city_decorations(street_lamp_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 0, 1, streetlamp_number)
									city_decorations(trash_can_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, trashcan_number)
									city_decorations(potted_plant_macro(_CT_rand2),	CurPos + x * posx1 + z * posz1, CurPos + x * posx2 + z * posz2, 1, 1, pottedplant_number)
								#end
							#end
							#local CurPos = CurPos + z * (building_width + pavement_width * 2);
						#end
						#local CurPos = CurPos + x * (building_width + pavement_width * 2);
					#end
					debug_detail("\n")
				#end
				#local BlockZ = BlockZ + 1;
			#end
			#local BlockX = BlockX + 1;
		#end

		// bounding won't help here
//		bounded_by {cyl_box_bound(<-section_width/2,-10,-section_length/2>,<+section_width/2,max_building_height,+section_length/2>)}

		#ifdef (city_finish)
			city_finish()
		#end
		#ifdef (city_transform)
			transform city_transform
		#end
	}
	debug_detail("CG...FINISHED!\n\n")
#end
