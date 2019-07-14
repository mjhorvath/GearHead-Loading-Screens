#local big_city_angle		= big_block_length/city_circum * 360;
#local sml_city_angle		= sml_block_length/city_circum * 360;
#local str_city_angle		= street_width/city_circum * 360;
#local blocks_per_section	= <1,0,1,>;

union
{
	#local sections_cnt = 0;
	#if (ShowWhole)
		#local sections_max = city_sections.x;
	#else
		#local sections_max = 1;
	#end
	#while (sections_cnt < sections_max)
		union
		{
			verbose_include("CG_DEFAULT_CURVED.inc", 0)
			verbose_include("CG_PAVEMENT_CURVED.INC", 0)
			verbose_include("CG_VEHICLES_CURVED.inc", 0)
		
			// city buildings - pass 1 - city buildings
			#local buildings_per_block	= <4,0,4,>;
			#local NoCars				= 0;
			#local NoStreet				= 0;
			verbose_include("CG_NORMAL_CURVED.inc", 0)
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 1/2 + sml_block_length * 1/2)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 3/2 + sml_block_length * 1/2)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 1/2 + sml_block_length * 1/2)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 3/2 + sml_block_length * 1/2)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 1/2 + sml_block_length * 1/2)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 3/2 + sml_block_length * 1/2)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 1/2 + sml_block_length * 1/2)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 3/2 + sml_block_length * 1/2)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
		
			// city buildings - pass 2 - fountain squares
			#local buildings_per_block	= <1,0,1,>;
			#local show_square			= 0;
			#local NoCars				= 0;
			#local NoStreet				= 0;
			verbose_include("CG_DEFAULT_CURVED.inc", 0)
			verbose_include("CG_SQUARE_CURVED.inc", 0)
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
			}
			#local show_square		= 1;
			#local NoCars			= 1;
			#local NoStreet			= 1;
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
			#local show_square		= 1;
			#local NoCars			= 0;
			#local NoStreet			= 0;
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
		
			// city buildings - pass 3 - long axis parks
			#local buildings_per_block	= <1,0,4,>;
			#local NoCars				= 0;
			#local NoStreet				= 0;
			verbose_include("CG_DEFAULT_CURVED.inc", 0)
			verbose_include("CG_PARK_CURVED.inc", 0)
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 1/2 + sml_block_length * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate -z * (big_block_length * 3/2 + sml_block_length * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 1/2 + sml_block_length * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				translate +z * (big_block_length * 3/2 + sml_block_length * 1/2)
			}
		
			// city buildings - pass 4 - circumference parks
			#local buildings_per_block	= <4,0,1,>;
			#local NoCars				= 0;
			#local NoStreet				= 0;
	//		verbose_include("CG_DEFAULT_CURVED.inc", 0)
	//		verbose_include("CG_PARK_CURVED.inc", 0)
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
			}


			// city buildings - pass 5 - end parks
			#local buildings_per_block	= <4,0,1,>;
			#local NoCars				= 1;
			#local NoStreet				= 1;
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
				translate -z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
				translate -z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
			#local NoCars				= 0;
			#local NoStreet				= 0;
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate +z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
				translate +z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
			object
			{
				verbose_include("CG_CITY_CURVED.inc", 0)
				rotate -z * (big_city_angle * 1/2 + sml_city_angle * 1/2)
				translate +z * (big_block_length * 4/2 + sml_block_length * 2/2)
			}
			rotate +z * sections_cnt * 360/sections_max
		}
		#local sections_cnt = sections_cnt + 1;
	#end
	scale	<0.999,0.999,1>
	#if (!ShowWhole)
		rotate +z * (str_city_angle * 1/2)
	#end
	rotate +z * city_rotate
}
