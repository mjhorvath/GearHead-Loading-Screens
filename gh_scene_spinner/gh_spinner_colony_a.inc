//------------------------------------------------------------------------------Textures & Common Objects

#default
{
	#switch (TexQual)
		#case (-1)
		#case (0)
		#break
		#case (1)
		#case (2)
			finish {ambient 1/16 diffuse albedo 0.7 phong 1}
		#break
	#end
}

#declare sky_pigment_1 = pigment
{
	bozo
	turbulence	0.65
	octaves		6
	omega		0.7
	lambda		2
	color_map
	{
		[0.0	gamma_color_adjust(<0.85,0.85,0.85,>)]
		[0.1	gamma_color_adjust(<0.75,0.75,0.75,>)]
		[0.5	gamma_color_adjust(< 0.5, 0.6, 1.0 >)]
		[1.0	gamma_color_adjust(< 0.5, 0.6, 1.0 >)]
	}
	scale 16
}
#declare sky_pigment_2 = pigment {sky_pigment_1 transmit 1}
#declare sky_pigment_3 = pigment
{
	radial
	pigment_map
	{
		[0/2 sky_pigment_1]
		[1/2 sky_pigment_2]
		[2/2 sky_pigment_1]
	}
	rotate x * 90
}

#declare sky_texture_a = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment
			{
				cylindrical
				color_map
				{
					[-1  gamma_color_adjust(< 1, 1, 1 >)]
					[0.8 gamma_color_adjust(<0.1,0.25,0.75>)]
					[1.0 gamma_color_adjust(<0.1,0.25,0.75>)]
				}
			}
			rotate x * 90
			scale outer_shell_radius1
		#break
	#end
}

#declare rock_filling_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
			pigment
			{
				granite
				color_map
				{
					[0 DarkBrown]
					[1 gamma_color_adjust(<0,0,0>)]
				}
			}
		#break
		#case (1)
		#case (2)
			pigment
			{
				granite
				color_map
				{
					[0 DarkBrown]
					[1 gamma_color_adjust(<0,0,0>)]
				}
			}
			finish {phong 0}
		#break
	#end
}
#declare steel_filling_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
			pigment
			{
				granite
				color_map
				{
					[0 gamma_color_adjust(1/2)]
					[1 gamma_color_adjust(0)]
				}
			}
		#break
		#case (1)
		#case (2)
			pigment
			{
				granite
				color_map
				{
					[0 gamma_color_adjust(1/2)]
					[1 gamma_color_adjust(0)]
				}
			}
			finish {phong 0}
		#break
	#end
}
#local grass_pigment_1 = pigment
{
	image_map {png "olivepink_marble.png"}
	rotate x * 90
}
#local grass_pigment_2 = pigment
{
	gamma_color_adjust(<046,104,058,>/255/2)
}
#local grass_pigment_3 = pigment
{
	average
	pigment_map
	{
		[2 grass_pigment_1]
		[2 grass_pigment_2]
	}
}
#local grass_texture_1 = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
			pigment {grass_pigment_3}
		#break
		#case (1)
		#case (2)
			pigment {grass_pigment_3}
			normal
			{
				wrinkles
//				scale		1/SceneScale
//				scale		<1,16/HeightScale,1,>
			}
		#break
	#end
}
#local blinky_material = material
{
	// check TexQual here?
	texture {pigment {gamma_color_adjust(1) transmit 1}}
	interior {media {emission x*10}}
}
#local blinky_sphere = sphere
{
	0, blinky_radius
	material {blinky_material}
	hollow
}
#local ring_glass_mat = material
{
	#switch (TexQual)
		#case (-1)
			lowqual_tex(Seed)
		#break
		#case (0)
			texture
			{
				pigment {gamma_color_adjust(<.5,.5,.5,.0,.7>)}
			}
		#break
		#case (1)
			texture
			{
				pigment {gamma_color_adjust(<.5,.5,.5,.0,.7>)}
				normal {bumps .05 scale .1}
				finish {specular .5 roughness .1 reflection <.3, .4, .5>}
			}
			scale city_units
		#break
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<.5,.5,.5,.0,.7>)}
				normal {bumps .05 scale .1}
				finish {specular .5 roughness .1 reflection <.3, .4, .5>}
			}
			interior {ior 2.5}
			scale city_units
		#break
	#end
}
#declare atmos_material = material
{
	// check TexQual here?
	texture {pigment {gamma_color_adjust(1) transmit 1}}
	interior
	{
		media
		{
			scattering
			{ 
				4, <0.2,0.4,1.0>/4000	// crappy approximaion of TerraPOV value
				extinction	1
			}
			samples	1,1
			density
			{
				cylindrical
				poly_wave	0.25
				density_map
				{
					[0	srgb 1]
					[1	srgb 0]
				}
				scale	city_radius
			}
		}
	}
	rotate	x * 90
}
#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
			lowqual_tex(Seed)
		#break
		#case (0)
		#case (1)
			texture {pigment {gamma_color_adjust(light_color)}}		// light source won't work without looks_like!
		#break
		#case (2)
			texture {pigment {gamma_color_adjust(light_color) transmit 1}}
			interior
			{
				media
				{
					emission gamma_color_adjust(light_color)
					density
					{
						cylindrical
						color_map
						{
							[0 srgb 0]
							[1 srgb 1]
						}
						scale	lamp_radius
						rotate	x * 90
					}
				}
			}
		#break
	#end
}
#declare white_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,1,1>*8/8)}
		#break
	#end
}
#declare gray_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,1,1>*1/2)}
		#break
	#end
}
#declare red_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,0,0>)}
		#break
	#end
}
#declare yellow_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,1,0>)}
		#break
	#end
}
#declare green_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<0,1,0>)}
		#break
	#end
}
#declare cutaway_object1 = union
{
//	plane {-y, 0	rotate +z * 015}
//	plane {-y, 0	rotate -z * 015}
	plane {-y, 0}
}
/*
#declare cutaway_object1 = union
{
	plane {-y, 0}
//	plane {-y, 0	rotate +z * 30}
//	plane {-y, 0	rotate -z * 30}
//	plane {+x, 0	rotate -z * 60}
	translate -y * city_units * 2
}
*/
#declare dome_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
			pigment { gamma_color_adjust(<1.000, 0.875, 0.575, 0.000, 0.900>) }
		#break
		#case (1)
			pigment { gamma_color_adjust(<1.000, 0.875, 0.575, 0.000, 0.900>) }
			finish
			{
				brilliance 2
				diffuse D_GoldA
				ambient A_GoldA
				reflection R_GoldA
				metallic M
				specular 0.20
				roughness 1/20
			}
		#break
		#case (2)
			// needs an interior too I think
			pigment { gamma_color_adjust(<1.000, 0.875, 0.575, 0.000, 0.900>) }
			finish
			{
				brilliance 2
				diffuse D_GoldA
				ambient A_GoldA
				reflection R_GoldA
				metallic M
				specular 0.20
				roughness 1/20
			}
		#break
	#end
}

//#declare dome_texture = texture{T_Glass3}

#macro new_random_color()
	#switch (TexQual)
		#case (-1)
			#declare MTX = lowqual_tex(Seed);
			#declare CTX = lowqual_tex(Seed);
			#declare HTX = lowqual_tex(Seed);
		#break
		#case (0)
			#if (!NoColors)
				#declare MTX = lowqual_tex(Seed);
				#declare CTX = lowqual_tex(Seed);
				#declare HTX = lowqual_tex(Seed);
			#else
				#declare MTX = texture { pigment { gamma_color_adjust(1) } }
				#declare CTX = texture { pigment { gamma_color_adjust(0) } }
				#declare HTX = texture { pigment { gamma_color_adjust(1/2) } }
			#end
		#break
		#case (1)
		#case (2)
			#if (!NoColors)
				#declare MTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
				#declare CTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
				#declare HTX = texture { pigment { gamma_color_adjust(<rand(Seed),rand(Seed),rand(Seed)>) } finish { F_MetalA } }
			#else
				#declare MTX = texture { pigment { gamma_color_adjust(1) } finish { F_MetalA } }
				#declare CTX = texture { pigment { gamma_color_adjust(0) } finish { F_MetalA } }
				#declare HTX = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA } }
			#end
		#break
	#end
#end

#switch (TexQual)
	#case (-1)
		#declare Plain_Gray = lowqual_tex(Seed);
		#declare Plain_LightGray = lowqual_tex(Seed);
		#declare Plain_DarkGray = lowqual_tex(Seed);
	#break
	#case (0)
		#declare Plain_Gray = texture { pigment { gamma_color_adjust(1/2) } }
		#declare Plain_LightGray = texture { pigment { gamma_color_adjust(3/4) } }
		#declare Plain_DarkGray = texture { pigment { gamma_color_adjust(1/4) } }
	#break
	#case (1)
	#case (2)
		#declare Plain_Gray = texture { pigment { gamma_color_adjust(1/2) } finish { F_MetalA } }
		#declare Plain_LightGray = texture { pigment { gamma_color_adjust(3/4) } finish { F_MetalA } }
		#declare Plain_DarkGray = texture { pigment { gamma_color_adjust(1/4) } finish { F_MetalA } }
	#break
#end


#declare street_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment
			{
				bozo
				color_map
				{
					[0 gamma_color_adjust(<.2,.2,.2>)]
					[1 gamma_color_adjust(<.4,.4,.4>)]
				}
				scale 10
			}
			scale city_units
		#break
	#end
}

#declare pavement_texture = texture
{
	#switch (TexQual)
		#case (-1)
			lowqual_pig(Seed)
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment
			{
				wrinkles
				color_map
				{
		//			[0 gamma_color_adjust(<.5,.5,.5>)]
		//			[1 gamma_color_adjust(<.6,.6,.6>)]
					[0 gamma_color_adjust(8/8)]
					[1 gamma_color_adjust(8/8)]
		
				}
				scale 1.5
			}
			scale city_units
		#break
	#end
}

#macro fuel_tank(in_len, in_rad)
	union
	{
		sphere {-z*in_len/2, in_rad}
		sphere {+z*in_len/2, in_rad}
		cylinder {-z*in_len/2,+z*in_len/2,in_rad}
	}
#end


//------------------------------------------------------------------------------Sun & Sky

#if (quick_interior_light)
	light_source
	{
		0, gamma_color_adjust(light_color)
	}
#end
#if (!NoSun)
	light_source
	{
		<-15000, +15000, -15000> * <1/4,1,1/2>
		gamma_color_adjust(light_color)
		rotate y * 090
		translate -y * city_radius
		parallel
	}
#end

//#if (NoRadiosity)
//	sky_sphere {pigment {color srgb <223,230,255>/255)}}
//#end

background {color srgb 0}

// Galaxy variables
#if (!NoGalaxy)
	#declare galaxy_bg = 1;			// on or off
	#declare galaxy_objects = 1;		// on or off
	#declare galaxy_starfield = 1;		// on or off
	#declare galaxy_bgstars = 1;		// type or off, not working?
	#declare galaxy_bgnebula = 1;		// type or off, not working?
	#declare galaxy_nebula_sphere = 0;	// type or off, not working?
	#declare galaxy_distance = 100000;
	#declare galaxy_colouration = 0.2;
	#declare star_type = 3;
	#declare star_scale = 1/4;
	#declare star_count = 10000;
	#include "GALAXY.BG"
	#include "GALAXY.SF"
//	#include "galaxy.inc"
#end


//------------------------------------------------------------------------------City

#if (!NoCity)
	union
	{
		//------------------------------------------------------------------------------Central Area
	
//		verbose_include("CG_UNIQUE_CURVED_MESH.INC", 0)			// not implemented yet
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
		verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
		verbose_include("CG_PARK_CURVED_MESH.INC", 0)
		verbose_include("CG_SQUARE_CURVED_MESH.INC", 0)
		verbose_include("CG_NORMAL_CURVED_MESH.INC", 0)
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object}
	
		//------------------------------------------------------------------------------End Parks
	
		#declare buildings_per_block	= <buildings_per_block.x,1>;
		#declare city_block_count	= <city_block_count.x,1>;
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
		verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
		verbose_include("CG_PARK_CURVED_MESH.INC", 0)
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object translate +z * (city_length - nominal_building_width - nominal_traffic_width)/2}
	
		#declare buildings_per_block	= <buildings_per_block.x,1>;
		#declare city_block_count	= <city_block_count.x,1>;
		verbose_include("CG_DEFAULT_CURVED_MESH.INC", 0)
		verbose_include("CG_VEHICLES_CURVED_MESH.INC", 0)
		verbose_include("CG_PAVEMENT_CURVED_MESH.INC", 0)		// needs to be updated for new maglev system
		verbose_include("CG_PARK_CURVED_MESH.INC", 0)
		#declare NoCars			= 1;
		#declare NoStreet		= 1;
		#local city_object = object {#include "CG_CITY_CURVED_MESH.inc"}
		object {city_object translate -z * (city_length - nominal_building_width - nominal_traffic_width)/2}

		rotate +z * (city_rotate)
	}
#end


//------------------------------------------------------------------------------Shell

#if (!NoShell)
	// outer metal shell
	#local shell_a1 = cylinder
	{
		-z*(habitat_length/2+ring_length), +z*(habitat_length/2), outer_shell_radius1
	}
	#local shell_b1 = cylinder
	{
		-z*(city_length*10), +z*(city_length*10), outer_shell_radius2
	}
	// outer rock shell
	#local shell_a2 = cylinder
	{
		-z*(habitat_length/2+ring_length-city_units*4), +z*(habitat_length/2-city_units*4), outer_shell_radius1-city_units*4
	}
	#local shell_b2 = cylinder
	{
		-z*(city_length*10), +z*(city_length*10), outer_shell_radius2+city_units*4
	}
	// inner metal shell
	#local shell_a3 = cylinder
	{
		-z*(city_length/2-city_units*0), +z*(city_length/2-city_units*0), inner_shell_radius1
	}
	#local shell_b3 = cylinder
	{
		-z*(city_length/2-city_units*4), +z*(city_length/2-city_units*4), inner_shell_radius2
	}
	// inner rock shell
	#local shell_a4 = cylinder
	{
		-z*(city_length/2-city_units*4), +z*(city_length/2-city_units*4), inner_shell_radius2
	}
	#local shell_b4 = cylinder
	{
		-z*(city_length/2-city_units*0), +z*(city_length/2-city_units*0), city_radius
	}
	// inner end spokes
	#local inn_spoke = cylinder
	{
		0, x * inner_shell_radius2, city_units * 6
	}
	#local cap_letter_a =	text {ttf "space age.ttf" "A" 1, 0}
	#local cap_letter_b =	text {ttf "space age.ttf" "B" 1, 0}
	#local cap_letter_c =	text {ttf "space age.ttf" "C" 1, 0}
	#local cap_letter_d =	text {ttf "space age.ttf" "D" 1, 0}
	#local cap_letter_e =	text {ttf "space age.ttf" "E" 1, 0}
	#local cap_letter_f =	text {ttf "space age.ttf" "F" 1, 0}
	// large gray cylinder end cap
	#local cap_1 = cylinder
	{
		-z*city_units, +z*city_units, outer_shell_radius1
	}
	// inner lozenge cutout 2
	#local cap_cutout_2 = cylinder
	{
		-z*city_units*3, +z*city_units*3, outer_shell_radius2/5
		translate -y * outer_shell_radius2/2
	}
	#local cap_cutout_2b = union
	{
		object {cap_cutout_2 rotate z * 000}
		object {cap_cutout_2 rotate z * 060}
		object {cap_cutout_2 rotate z * 120}
		object {cap_cutout_2 rotate z * 180}
		object {cap_cutout_2 rotate z * 240}
		object {cap_cutout_2 rotate z * 300}
	}
	// inner lozenge glass 2
	#local cap_glass_2 = difference
	{
		sphere
		{
			0, outer_shell_radius2/5*0.999
			scale z * 4/8
		}
		sphere
		{
			0, outer_shell_radius2/5*0.999
			scale z * 4/8
			scale 15/16
		}
		plane {-z,0}
		translate -y * outer_shell_radius2/2
	}
	#local cap_glass_2b = union
	{
		object {cap_glass_2	rotate z * 000}
		object {cap_glass_2	rotate z * 060}
		object {cap_glass_2	rotate z * 120}
		object {cap_glass_2	rotate z * 180}
		object {cap_glass_2	rotate z * 240}
		object {cap_glass_2	rotate z * 300}
	}
	// end cap bevel
	#local cap_hub_r8 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*8/9}
	#local cap_hub_r7 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*7/9}
	#local cap_hub_r6 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*6/9}
	#local cap_hub_r3 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*3/9}
	#local cap_hub_r2 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*2/9}
	#local cap_hub_r1 = cylinder {-z*city_units*2, +z*city_units*2, outer_shell_radius2*1/9}

	#local cap_object_a = union
	{
		difference
		{
			object {cap_1}
			object {cap_cutout_2b}
		}
//		difference
//		{
//			object {cap_hub_r7}
//			object {cap_hub_r6	scale 1.0001}
//		}
//		difference
//		{
//			object {cap_hub_r3}
//			object {cap_hub_r2	scale 1.0001}
//		}
		object {cap_hub_r1}
	}
	#local cap_object_b = union
	{
		object {cap_1}
		difference
		{
			object {cap_hub_r7}
			object {cap_hub_r6	scale 1.0001}
		}
//		difference
//		{
//			object {cap_hub_r3}
//			object {cap_hub_r2	scale 1.0001}
//		}
		object {cap_hub_r1}
	}
	#local outer_rock_ring = difference
	{
		object {shell_a2}
		object {shell_b2}
	}
	#local inner_rock_ring = difference
	{
		object {shell_a4}
		object {shell_b4}
	}

	//------------------------------------------------------------------------------Outer Shell & Mid Walls


	difference
	{
		union
		{

			difference
			{
				object {shell_a1}
				object {shell_b1}
				object {outer_rock_ring}
			}
			object {cap_object_a	translate +z*(habitat_length/2)}
//			object {cap_object_b	translate -z*(dock_start)}
//			object {cap_object_b	translate -z*(dock_start+dock_length)}	// was <3/4,3/4,1>
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	difference
	{
		object {outer_rock_ring}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {steel_filling_texture}
	}

	//------------------------------------------------------------------------------Inner Shell & End Caps

	// this stuff really needs to be double-checked to make sure things line up correctly

	difference
	{
		union
		{
			difference
			{
				object {shell_a3}
				object {shell_b3}
				object {cap_cutout_2b	translate +z*(city_length/2-city_units*2)}
				union
				{
					// side a
					object
					{
						cap_letter_a
						Center_Trans(cap_letter_a, x)
						Center_Trans(cap_letter_a, y)
						Center_Trans(cap_letter_a, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 330
					}
					object
					{
						cap_letter_b
						Center_Trans(cap_letter_b, x)
						Center_Trans(cap_letter_b, y)
						Center_Trans(cap_letter_b, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 030
					}
					object
					{
						cap_letter_c
						Center_Trans(cap_letter_c, x)
						Center_Trans(cap_letter_c, y)
						Center_Trans(cap_letter_c, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 090
					}
					object
					{
						cap_letter_d
						Center_Trans(cap_letter_d, x)
						Center_Trans(cap_letter_d, y)
						Center_Trans(cap_letter_d, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 150
					}
					object
					{
						cap_letter_e
						Center_Trans(cap_letter_e, x)
						Center_Trans(cap_letter_e, y)
						Center_Trans(cap_letter_e, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 210
					}
					object
					{
						cap_letter_f
						Center_Trans(cap_letter_f, x)
						Center_Trans(cap_letter_f, y)
						Center_Trans(cap_letter_f, z)
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate +z*(city_length/2-city_units*4)
						rotate z * 270
					}
					// side b
					object {cap_cutout_2b	translate -z*(dock_start-city_units*2)}
					object
					{
						cap_letter_a
						Center_Trans(cap_letter_a, x)
						Center_Trans(cap_letter_a, y)
						Center_Trans(cap_letter_a, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 330
					}
					object
					{
						cap_letter_b
						Center_Trans(cap_letter_b, x)
						Center_Trans(cap_letter_b, y)
						Center_Trans(cap_letter_b, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 030
					}
					object
					{
						cap_letter_c
						Center_Trans(cap_letter_c, x)
						Center_Trans(cap_letter_c, y)
						Center_Trans(cap_letter_c, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 090
					}
					object
					{
						cap_letter_d
						Center_Trans(cap_letter_d, x)
						Center_Trans(cap_letter_d, y)
						Center_Trans(cap_letter_d, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 150
					}
					object
					{
						cap_letter_e
						Center_Trans(cap_letter_e, x)
						Center_Trans(cap_letter_e, y)
						Center_Trans(cap_letter_e, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 210
					}
					object
					{
						cap_letter_f
						Center_Trans(cap_letter_f, x)
						Center_Trans(cap_letter_f, y)
						Center_Trans(cap_letter_f, z)
						rotate y * 180
						scale <outer_shell_radius1/6,outer_shell_radius1/6,city_units>
						translate -y*outer_shell_radius1*2/3
						translate -z*(city_length/2-city_units*4)
						rotate z * 270
					}
					texture {white_metal_texture}
				}
			}
			union
			{
				// side a
				difference
				{
					object {cap_hub_r8}
					object {cap_hub_r7	scale 1.0001}
				}
				difference
				{
					object {cap_hub_r2}
					object {cap_hub_r1	scale 1.0001}
				}
				translate +z*(city_length/2-city_units*8)
			}
			union
			{
				// side b
				difference
				{
					object {cap_hub_r8}
					object {cap_hub_r7	scale 1.0001}
				}
				difference
				{
					object {cap_hub_r2}
					object {cap_hub_r1	scale 1.0001}
				}
				translate -z*(city_length/2-city_units*8)
			}
			// end spokes
/*
			union
			{
				#local ring_max = 6;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					// side a
					object
					{
						inn_spoke
						rotate z * ring_cnt * 60
						translate -z*city_length/2
					}
					// side b
					object
					{
						inn_spoke
						rotate z * ring_cnt * 60
						translate +z*city_length/2
					}
					#local ring_cnt = ring_cnt + 1;
				#end
			}
*/
			#if (!NoDomes)
				// side a
				object
				{
					cap_glass_2b
					translate +z*(city_length/2-city_units*2)
					texture {dome_texture}
				}
/*
				// side b
				object
				{
					cap_glass_2b
					translate -z*(dock_start-city_units*2)
					texture {dome_texture}
				}
*/
			#end
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {sky_texture_a}
		rotate +z * city_rotate
	}

	difference
	{
		object {inner_rock_ring}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {rock_filling_texture}
		rotate +z * city_rotate
	}


	//------------------------------------------------------------------------------Lamp & Spindles

	#if (!NoLampLight)
		light_source
		{
			0, gamma_color_adjust(light_color)
			area_light z*lamp_length/2, y, 16, 1
		}
	#end

	#if (!NoLamp)
		object
		{
			cylinder {z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius}
			material {lamp_material}
			hollow
			scale	0.9999
			no_shadow
		}
	#end

	#if (!NoSpindle)
		#local spindle_arm = cylinder
		{
			0, +y*city_radius, city_units*2
		}
		#local spindle_hub = union
		{
			difference
			{
				union
				{
					object {spindle_arm rotate z * 030}
					object {spindle_arm rotate z * 090}
					object {spindle_arm rotate z * 150}
					object {spindle_arm rotate z * 210}
					object {spindle_arm rotate z * 270}
					object {spindle_arm rotate z * 330}
				}
				cylinder {-z*city_radius, +z*city_radius, city_units * 16}
			}
			torus
			{
				city_units * 16, city_units*2
				rotate x * 90
			}
			texture {white_metal_texture}
		}
		object {spindle_hub	translate -z * lamp_length/4 rotate +z * city_rotate}
		object {spindle_hub	translate +z * lamp_length/4 rotate +z * city_rotate}
	#end


	//------------------------------------------------------------------------------Compact Ring

	#if (!InsideOnly)
		difference
		{
			union
			{
				#local ring_max = 6;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					difference
					{
						cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*ring_cnt*10+city_units}
						cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1-city_storey_height*ring_cnt*10-city_units}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
				#local ring_max = 50;
				#local ring_cnt = 0;
				#while (ring_cnt < ring_max)
					difference
					{
						cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*ring_cnt+city_units/4}
						cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1-city_storey_height*ring_cnt-city_units/4}
					}
					#local ring_cnt = ring_cnt + 1;
				#end
			}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			texture {white_metal_texture}
		}
	
		difference
		{
			cylinder {-z*(habitat_length/2+city_units),-z*(city_length/2+ring_length-city_units),inner_shell_radius1			scale <0.99,0.99,1>}
			cylinder {-z*(habitat_length/2-city_units),-z*(city_length/2+ring_length+city_units),inner_shell_radius1-city_storey_height*50	scale <0.99,0.99,1>}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			material {ring_glass_mat}
		}

		//------------------------------------------------------------------------------Cargo and Shiphold
	
		difference
		{
			union
			{
	
				#local dock_labels = polygon
				{
					4, <0,0>,<0,1>,<1,1>,<1,0>
					texture {gray_metal_texture}
					texture
					{
						pigment
						{
							image_map {png "spinner_lot_text.png"}
						}
					}
					translate <-1/2,-1/2,0>
					scale <dock_length*7/8,outer_shell_radius1*2,1>
					rotate y * 90
				}
	
				#local dock_cnt = 0;
				#local dock_max = 3;
				#while (dock_cnt < dock_max)
					difference
					{
						superellipsoid
						{
							<0.001, 0.1>
							scale <dock_depth + dock_thick,dock_radius_outer*2,dock_length/2>
							translate -z * dock_length/2
							rotate z * (dock_cnt * 60 + 30)
						}
						superellipsoid
						{
							<0.001, 0.1>
							scale <dock_depth,dock_radius_outer*2,dock_length/2 - dock_thick>
							translate -z * dock_length/2
							rotate z * (dock_cnt * 60 + 30)
						}
						cylinder {<0,0,+1>, <0,0,-dock_length-1>, dock_radius_outer inverse}
						cylinder {<0,0,+1>, <0,0,-dock_length-1>, dock_radius_inner}
						translate -z * (dock_start)
					}
					#local dock_cnt = dock_cnt + 1;
				#end
	
				difference
				{
					union
					{
						#local dock_cnt = 0;
						#local dock_max = 3;
						#while (dock_cnt < dock_max)
							union
							{
								object
								{
									dock_labels
									translate +x * dock_depth * 0.99
									rotate z * (dock_cnt * 60 + 30)
								}
								object
								{
									dock_labels
									translate -x * dock_depth * 0.99
									rotate z * (dock_cnt * 60 + 30)
								}
							}
							#local dock_cnt = dock_cnt + 1;
						#end
					}
					cylinder {<0,0,-dock_length/2>, <0,0,+dock_length/2>, dock_radius_inner}
					cylinder {<0,0,-dock_length/2>, <0,0,+dock_length/2>, dock_radius_outer inverse}
					translate -z * (dock_start + dock_length/2)
				}
			}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			texture {white_metal_texture}
		}

	
		//------------------------------------------------------------------------------Nose cone

		#if (!NoCone)	
			difference
			{
				union
				{
					#local p_radius = outer_shell_radius1;
					#local p_scale = p_radius;
					#local z_position = pow(p_radius, 2)/p_scale;
					intersection
					{
						difference
						{
							object
							{
								Paraboloid_Z
								scale p_scale
							}
							object
							{
								Paraboloid_Z
								scale p_scale
								translate +z * city_units * 2
							}
						}
						plane {+z, z_position}
						rotate y * 180
						translate +z * z_position
						translate +z * habitat_length/2
					}
				}
				#if (!ShowWhole)
					object {cutaway_object1}
				#end
				texture {dome_texture}
			}
		#end

	
		//------------------------------------------------------------------------------body trusses x-long
	
		#declare truss_sides = 12;
		#declare truss_sections = 16;
		#declare truss_thickness = city_units*2;
		#declare truss_radius = outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1) + truss_thickness;
		#declare truss_point1 = -z*(habitat_length/2+ring_length);	//+dock_length
		#declare truss_point2 = +z*habitat_length/2;
		difference
		{
			object {#include "truss.inc"}
			#if (!ShowWhole)
				object {cutaway_object1}
			#end
			texture {white_metal_texture}
		}
	#end


	//------------------------------------------------------------------------------Reactor Core

	#if (!NoReactor)
		union
		{
			#local ball_radius = city_units * 16;
			#local ball_center = habitat_length/2+ring_length/2;
			#local trumpet_length = ring_length/2-ball_radius-ring_gap;
			#declare Fx2 = function(u,v) {v}
			#declare Fy2 = function(u,v) {city_units*16/pow(v+1,0.7)*cos(u)}
			#declare Fz2 = function(u,v) {city_units*16/pow(v+1,0.7)*sin(u)}
			object
			{
				Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
				rotate -y * 90
				translate -z*(ball_center+city_units*2-ball_radius)
			}
			object
			{
				Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
				rotate +y * 90
				translate -z*(ball_center-city_units*2+ball_radius)
			}
			sphere
			{
				0, ball_radius*5/4
				translate -z*(ball_center)
			}
//			torus
//			{
//				ball_radius*3, ball_radius*3/4
//				rotate x * 90
//				translate -z*(ball_center)
//			}
			texture
			{
				white_metal_texture
//				finish {reflection 1}
			}
		}
	#end


	//------------------------------------------------------------------------------Shiphold Contents

	#if (!NoShips)

		// vehicles
		verbose_include("Raumschiff5.inc", 0)
		#local raums_object	= Raumschiff5;
		#local raums_min	= min_extent(raums_object);
		#local raums_max	= max_extent(raums_object);
		#local raums_box	= raums_max - raums_min;
		#local raums_nrm	= vnormalize(raums_box);
		#local raums_object = object
		{
			raums_object
			translate	-raums_min
			scale		1/raums_box
			translate	<-1/2,0,-1/2>
			scale		raums_nrm * 2
			rotate		y * 180
			scale		32
			scale		z * 3/2
			translate	z * 2
			bounded_by {box {<-32,0,-32>, <+32,+32,+32>}}
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
			scale 1
		}
		object
		{
			raums_object
			translate -z * (dock_start+dock_length*1/2)
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_length*2/3
		}
		new_random_color()
		verbose_include("ara_kojedo.pov", 0)
		object
		{
			ara_kojedo_
			translate <18.42348,0,-364.0902> * -1
			scale 1/375
			//edit below
			scale 10 * city_units
			translate -z * (dock_start+dock_length*7/12)
			translate -y * dock_depth
			translate +y * city_units
			translate +x * dock_length*9/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		new_random_color()
		verbose_include("btr_maanji.pov", 0)
		object
		{
			object01
			matrix <1.000000, 0.000000, 0.000000,
			0.000000, 1.000000, 0.000000,
			0.000000, 0.000000, 1.000000,
			0.000000, 0.000000, 0.000000>
			translate <0.000000, 0.000000, 0.000000>
			scale <1.000000, 1.000000, 1.000000>
			translate y * -4.65
			scale 1/115
			//edit below
			rotate y * 360 * rand(Seed)
			scale 18 * city_units
			translate -z * (dock_start+dock_length*3/12)
			translate -y * dock_depth
			translate +y * city_units
			translate +x * dock_radius_outer*9/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		new_random_color()
		verbose_include("btr_vadel.pov", 0)
		object
		{
			object01
			matrix <0.707112, 0.000000, -0.707101,
			0.000000, 1.000000, 0.000000,
			0.707101, 0.000000, 0.707112,
			0.000000, 0.000000, 0.000000>
			translate <0.000000, 0.000000, 0.000000>
			scale <1.000000, 1.000000, 1.000000>
			rotate y * -45
			scale 1/75
			//edit below
			rotate y * 360 * rand(Seed)
			scale 16 * city_units
			translate -z * (dock_start+dock_length*3/12)
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_radius_outer*9/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}

		verbose_include("Horus.inc", 0)
		#local horus_object	= Horus;
		#local horus_min	= min_extent(horus_object);
		#local horus_max	= max_extent(horus_object);
		#local horus_box	= horus_max - horus_min;
		#local horus_nrm	= vnormalize(horus_box);
		#local horus_object = object
		{
			horus_object
			translate	-horus_min
			scale		1/horus_box
			translate	<-1/2,0,-1/2>
			scale		horus_nrm * 2
			rotate		y * 360 * rand(Seed)
			scale		6
			translate	y
			scale		2 * city_units
			bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		object
		{
			horus_object
			translate -z * (dock_start+dock_length*9/12)
			translate -y * dock_depth
			translate +y * city_units
			translate -x * dock_radius_outer*8/12
		}

		// cargo containers
		#local cargo_pigment = pigment
		{
			checker
			color srgb <0,0,0>,
			color srgb <1/2,1/2,1/2>
			scale city_units
		}
		#local cargo_box = box
		{
			<-city_units,0,-city_units>,
			<+city_units,+city_units*2,+city_units>
			pigment {cargo_pigment}
		}

		#local cargo_max = 8;
		#local cargo_cnt = 0;
		#while (cargo_cnt < cargo_max)
			#local cargo_rand = rand(Seed);
			object
			{
				union
				{
					object {cargo_box		rotate y * (rand(Seed) * 30 - 15)	translate <0,0,+city_units> * 1.2}
					#if (cargo_rand > 1/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <-city_units,0,-city_units> * 1.2}
					#end
					#if (cargo_rand > 2/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <+city_units,0,-city_units> * 1.2}
					#end
					#if (cargo_rand > 3/4)
						object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <0,city_units*2,0>}
					#end
				}
				rotate y * 360 * rand(Seed)
				translate -z * (dock_start + dock_length/6 + dock_length/3 * rand(Seed))
				translate -x * ((dock_radius_outer * 3/4 - dock_radius_inner) * rand(Seed) + dock_radius_inner)
				translate -y * (dock_depth)
				translate +y * (city_units)
			}
			#local cargo_cnt = cargo_cnt + 1;
		#end
/*
		// people (not rendering??)
		#local people_max = 8;
		#local people_cnt = 0;
		#while (people_cnt < people_max)
			object
			{
				ped_macro(Seed)
				translate -z * (dock_start + dock_length/6 + dock_length/3*rand(Seed))
				translate -x * (dock_length/3*rand(Seed))
				translate -y * (dock_radius_outer*1/4)
				translate +y * (city_units)
			}
			#local people_cnt = people_cnt + 1;
		#end
*/
		// fuel tanks
		union
		{
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius_outer/2+city_units*16)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius_outer/2+city_units*24)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius_outer/2+city_units*16)
				translate -z*(dock_start+dock_thick+city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius_outer/2+city_units*24)
				translate -z*(dock_start+dock_thick+city_units*8)
			}

			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius_outer/2+city_units*16)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate -x*(dock_radius_outer/2+city_units*24)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius_outer/2+city_units*16)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			object
			{
				fuel_tank(city_units*8,city_units*4)
				rotate x * 90
				translate +y*city_units*8
				translate +x*(dock_radius_outer/2+city_units*24)
				translate -z*(dock_start+dock_length-dock_thick-city_units*8)
			}
			translate -y*dock_depth
			texture {yellow_metal_texture}
		}

		// robo arm
		object
		{
			#include "gh_roboarm.inc"
			rotate -x*90
			scale city_units/2
			translate -z*(dock_start+city_units*2)
			texture {white_metal_texture}
		}

		// rafters
		#declare rafter_object_a = union
		{
			#declare truss_sides = 3;
			#declare truss_sections = 8;
			#declare truss_radius = city_units*8;
			#declare truss_thickness = city_units;
			#declare truss_point1 = <dock_radius_inner-truss_radius-truss_thickness,0,-dock_start - dock_length*15/16>;
			#declare truss_point2 = <dock_radius_inner-truss_radius-truss_thickness,0,-dock_start - dock_length*01/16>;
			#declare truss_rotate = 180;
			object
			{
				#include "truss.inc"
				rotate -z * 030
			}
			object
			{
				#include "truss.inc"
				rotate -z * 090
			}
			object
			{
				#include "truss.inc"
				rotate -z * 150
			}
			texture {white_metal_texture}
		}
		object {rafter_object_a}

		// gantry
		#declare gantry_object = union
		{
			//y
			box {<-12,+00,-30>, <-10,+36,-28>}
			box {<+12,+00,-30>, <+10,+36,-28>}
			box {<+12,+00,+30>, <+10,+36,+28>}
			box {<-12,+00,+30>, <-10,+36,+28>}
			//top
			box {<-12,+36,+30>, <+12,+34,+28>}
			box {<-12,+36,-30>, <+12,+34,-28>}
			box {<-12,+36,-30>, <-10,+30,+30>}
			box {<+12,+36,-30>, <+10,+30,+30>}
			//bottom
			box {<-12,+02,+30>, <+12,+03,+28>}
			box {<-12,+02,-30>, <+12,+03,-28>}
			box {<-12,+12,+30>, <+12,+13,+28>}
			box {<-12,+12,-30>, <+12,+13,-28>}
			scale 1/30
			scale city_units * 16
		}
		object
		{
			gantry_object
			rotate y*15
			translate -y*(dock_depth-city_units)
			translate -z*(city_length/2+ring_length+dock_length*1/4)
			translate +x*(dock_radius_outer*3/4)
			texture {yellow_metal_texture}
		}
	#end

	//------------------------------------------------------------------------------Engines

	#if (!NoEngines)
		#local fuel_radius = outer_shell_radius1*1/4;
		#local tank_cnt = 0;
		#local tank_max = 6;
		#while (tank_cnt < tank_max)
			sphere
			{
				-y*(outer_shell_radius1-fuel_radius),
				fuel_radius
				rotate z * tank_cnt * 60
				translate -z * (habitat_length/2+ring_length+dock_length+fuel_radius)
				texture {white_metal_texture}
			}
			#local tank_cnt = tank_cnt + 1;
		#end

		#local p_radius = outer_shell_radius1/2;
		#local p_scale = outer_shell_radius1/2;
		#local z_position = pow(p_radius,2)/p_scale;
		intersection
		{
			difference
			{
				object
				{
					Paraboloid_Z
					scale p_scale
				}
				object
				{
					Paraboloid_Z
					scale p_scale
					translate z * city_units * 2
				}
			}
			plane {+z,z_position}
			rotate y * 180
//				translate -z * z_position
			translate -z * (habitat_length/2+ring_length+dock_length)
			#if (!NoDomes)
				texture {dome_texture}
			#else
				pigment {color srgb 1}
			#end
		}
	#end


	//------------------------------------------------------------------------------Tanks

	#local tank_radius = city_units * 16;
	#local tank_length = city_units * 128;
	#local tank_object = object
	{
		fuel_tank(tank_length,tank_radius)
		translate -y*(outer_shell_radius1+tank_radius)
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

	//------------------------------------------------------------------------------Comms

	#if (!NoComms)
		#local comm_dish = union
		{
			difference
			{
				object {Paraboloid_Z}
				object {Paraboloid_Z	scale 0.999}
				plane {-z,-0.05}
				rotate y * 180
				scale		dock_radius_outer/4
			}
			cylinder {<0,0,0>, <0,0,-city_units*8>, city_units/2}
			scale 2
			translate -z*city_units*16
		}
		#local comm_dome = difference
		{
			sphere {-z*city_units*16, city_units*16}
			plane {-z,0}
		}
	
		// comms trusses
		#declare truss_sides = 6;
		#declare truss_sections = 1;
		#declare truss_radius = city_units*16;
		#declare truss_thickness = city_units/2;
		#declare truss_point1 = -z*city_units*16;
		#declare truss_point2 = 0;
		#local comm_truss = object
		{
			#include "truss.inc"
			texture {white_metal_texture}
		}
		#local comm_anten = union
		{
			cylinder {<0,0,0>, <0,0,-city_length/16>, city_units}
			cylinder {<0,0,0>, <0,0,-city_length/4>, city_units/2}
			cylinder {<0,-city_units*32,0>, <0,-city_units*32,-city_length/32>, city_units}
			cylinder {<0,-city_units*32,0>, <0,-city_units*32,-city_length/8>, city_units/2}
			object {blinky_sphere	translate <0,0,-city_length/4-blinky_radius>}
			sphere {blinky_sphere	translate <0,-city_units*32,-city_length/8-blinky_radius>}
		}
		union
		{
			object
			{
				comm_dome
				translate	-y*dock_radius_outer * 5/6
				rotate		+z * 000
			}
			object
			{
				comm_truss
				translate	-y*dock_radius_outer * 5/6
				rotate		+z * 000
			}
			object
			{
				comm_dish
				translate	-y*dock_radius_outer * 5/6
				rotate		+z * 040
			}
			object
			{
				comm_truss
				translate	-y*dock_radius_outer * 5/6
				rotate		+z * 040
			}
			object
			{
				comm_anten
				translate	-y*dock_radius_outer * 5/6
				rotate		+z * 330
			}
			translate	-z*(habitat_length/2)
			rotate		y * 180
			texture {white_metal_texture}
		}
	#end


	//------------------------------------------------------------------------------Solar Panels & Agridomes

	#if (!NoPanels)
		#include "gh_truss_array_b.inc"
	#end
	

	//------------------------------------------------------------------------------Blinky Lights & Thrusters

	#local blinky_group = union
	{
		object {blinky_sphere	translate <0,-dock_radius_outer-blinky_radius,-habitat_length/2-ring_length-dock_length>}
		object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,-habitat_length/2>}
		object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,+habitat_length/2>}
	}
	#local thruster = union
	{
		cone {<0, 0, 0>, 0, <0, 0, -2>, 1 open hollow}
		cylinder {<0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow}
		scale 1/2
	}
	#local thruster_tank_radius = city_units*12;
	#local thruster_aggregate = union
	{
		sphere {0,1}
		object {thruster	translate <0, 0, -3>}
		object {thruster	rotate <0, 180, 0> translate <0, 0, +3>}
		object {thruster	rotate <0, 090, 0> translate <-1, 0, 0>}
		object {thruster	rotate <0, 270, 0> translate <+1, 0, 0>}
		object {thruster	rotate <270, 0, 0> translate <0, -1, 0>}
		object {fuel_tank(4,1)}
		scale thruster_tank_radius
	}
	#local thruster_group = union
	{
//		object {thruster_aggregate	translate <0,-dock_radius_outer-thruster_tank_radius,-habitat_length/2-ring_length-dock_length>}
		object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),-habitat_length/2>}
		object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),+habitat_length/2-ring_length>}
		texture {white_metal_texture}
	}

	#declare thruster_blinky_union = union
	{
		object {thruster_group}
		object {blinky_group}
	}
	object {thruster_blinky_union	rotate +z * 270}
	object {thruster_blinky_union	rotate +z * 000}
	object {thruster_blinky_union	rotate +z * 090}
	#if (ShowWhole)
		object {thruster_blinky_union	rotate +z * 180}
	#end

//	object {thruster	scale 32 rotate y * 180	translate <0,0,+dock_start>}
#end


//------------------------------------------------------------------------------Neighboring Craft

#if (!NoShips)
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
		translate	+x * (outer_shell_radius1 + city_units * 128)
		translate	-z * (city_length/2 + ring_length)
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
		translate -x*city_units*32
		translate +z*city_units*32
	}
#end

//------------------------------------------------------------------------------Atmosphere

// very slowwww!!!
#if (!NoAtmos)
	difference
	{
		cylinder
		{
			+z*(city_length/2-city_units*4), -z*(city_length/2-city_units*4), city_radius
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		hollow
		material {atmos_material}
		rotate +z * (city_rotate)
//		scale 0.999999999
		scale 1.000000001
	}
#end
