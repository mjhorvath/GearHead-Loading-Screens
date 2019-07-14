#macro make_my_city()
	union
	{
		#if (ShowWhole)
			#local sections_max = city_sections.x;
		#else
			#local sections_max = city_sections.x/2;
		#end
		#for (i, 0, sections_max - 1)
			union
			{
				verbose_include("CG_INIT_CURVED.INC", 0)
				verbose_include("CG_PAVEMENT_CURVED.INC", 0)
				verbose_include("CG_VEHICLES_CURVED.inc", 0)

				//------------------------------------------------------------------------------
				// city buildings - main sections
				#local buildings_per_block	= <3,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 0;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 0;
				#local NoCarsX			= 0;
				#local NoCarsZ			= 0;
				init_building_types()
				verbose_include("CG_NORMAL_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 0/2 + sml_block_angle * 0/2)
				}

				#local buildings_per_block	= <3,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 0;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 0;
				#local NoCarsX			= 0;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_NORMAL_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 2/2 + sml_block_angle * 2/2)
				}

				#local buildings_per_block	= <3,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 0;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 0;
				#local NoCarsX			= 0;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_NORMAL_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 4/2 + sml_block_angle * 4/2)
				}
/*
				//------------------------------------------------------------------------------
				// city buildings - end parks

				// back
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 0/2 + sml_block_angle * 0/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 2/2 + sml_block_angle * 2/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 4/2 + sml_block_angle * 4/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				// front
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 0/2 + sml_block_angle * 0/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 2/2 + sml_block_angle * 2/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <3,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 0;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 4/2 + sml_block_angle * 4/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
*/
				//------------------------------------------------------------------------------
				// city buildings - long axis parks
				#local buildings_per_block	= <1,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 1/2 + sml_block_angle * 1/2 - street_angle * 1/2)
				}

				#local buildings_per_block	= <1,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 3/2 + sml_block_angle * 3/2 - street_angle * 1/2)
				}

				#local buildings_per_block	= <1,0,3,>;
				#local blocks_per_section	= <1,0,2,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 0;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 0;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_PARK_CURVED.inc", 0)
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 5/2 + sml_block_angle * 5/2 - street_angle * 1/2)
				}
/*
				//------------------------------------------------------------------------------
				// city buildings - fountain squares

				// back
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 1/2 + sml_block_angle * 1/2 - street_angle * 1/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 3/2 + sml_block_angle * 3/2 - street_angle * 1/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 0;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 1;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 5/2 + sml_block_angle * 5/2 - street_angle * 1/2)
					translate -z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				// front
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 1/2 + sml_block_angle * 1/2 - street_angle * 1/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 3/2 + sml_block_angle * 3/2 - street_angle * 1/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
				#local buildings_per_block	= <1,0,1,>;
				#local blocks_per_section	= <1,0,1,>;
				#local NoRailX1			= 1;
				#local NoRailZ1			= 1;
				#local NoRailX2			= 1;
				#local NoRailZ2			= 1;
				#local NoStreetX1		= 1;
				#local NoStreetZ1		= 1;
				#local NoStreetX2		= 1;
				#local NoStreetZ2		= 0;
				#local NoStation		= 1;
				#local NoCarsX			= 1;
				#local NoCarsZ			= 1;
				init_building_types()
				verbose_include("CG_SQUARE_CURVED.inc", 0)
				object
				{
					verbose_include("CG_CITY_CURVED.inc", 0)
					rotate +z * (big_block_angle * 5/2 + sml_block_angle * 5/2 - street_angle * 1/2)
					translate +z * (big_block_length_z * 1/2 + sml_block_length_z * 1/2 - street_width/2)
				}
*/
				rotate +z * i * 360/sections_max - z * 90
			}
		#end
		scale	<0.999,0.999,1>
		rotate +z * street_angle/2
	}
#end
#if (BothHabitats)
	object
	{
		make_my_city()
		rotate -z * big_block_angle/2
		rotate -z * street_angle/2
		rotate -z * city_rotate
		translate -z * hab_section_offset
	}
#end
object
{
	make_my_city()
	rotate +z * big_block_angle/2
	rotate +z * street_angle/2
	rotate +z * city_rotate
	translate +z * hab_section_offset
}
