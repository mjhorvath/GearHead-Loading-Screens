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
			scale Meters
		#break
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<.5,.5,.5,.0,.7>)}
				normal {bumps .05 scale .1}
				finish {specular .5 roughness .1 reflection <.3, .4, .5>}
			}
			interior {ior 2.5}
			scale Meters
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
	translate -y * Meters * 2
}
*/

#if (GlassColor = 0)
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
#else
	#declare dome_texture = texture
	{
		#switch (TexQual)
			#case (-1)
				lowqual_pig(Seed)
			#break
			#case (0)
				pigment { gamma_color_adjust(<0.98, 0.98, 0.98, 0.000, 0.9>) }
			#break
			#case (1)
				pigment { gamma_color_adjust(<0.98, 0.98, 0.98, 0.000, 0.9>) }
				finish
				{
				    ambient 0.1
				    diffuse 0.1
				    reflection 0.1
				    specular 0.8
				    roughness 0.003
				    phong 1
				    phong_size 400
				}
			#break
			#case (2)
				// needs an interior too I think
				pigment { gamma_color_adjust(<1.000, 0.875, 0.575, 0.000, 0.900>) }
				finish
				{
				    ambient 0.1
				    diffuse 0.1
				    reflection 0.1
				    specular 0.8
				    roughness 0.003
				    phong 1
				    phong_size 400
				}
			#break
		#end
	}
#end

#declare water_material = material
{
	#switch (TexQual)
		#case (-1)
			lowqual_tex(Seed)
		#break
		#case (0)
			texture
			{
				pigment {gamma_color_adjust(<.93,.95,.98,0.825,0>*0.99)}
			}
		#break
		#case (1)
			texture
			{
				pigment {gamma_color_adjust(<.93,.95,.98,0.825,0>*0.99)}
				finish
				{
					ambient 0.0
					diffuse 0.15
					reflection {0.1,0.1 fresnel on}
					specular 0.6
					roughness 0.005
					conserve_energy
				}
			}
		#break
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<.93,.95,.98,0.825,0>*0.99)}
				finish
				{
					ambient 0.0
					diffuse 0.15
					reflection {0.1,0.1 fresnel on}
					specular 0.6
					roughness 0.005
					conserve_energy
				}
			}
			interior
			{
				ior 1.33
				fade_power 1001
				fade_distance 0.5
				fade_color <0.8,0.8,0.8>
				caustics 0.16
			}
		#break
	#end
}

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
			scale Meters
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
			scale Meters
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
//	sky_sphere {pigment {gamma_color_adjust(<223,230,255>/255)}}
//#end

background {color srgb 1/2}

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


//------------------------------------------------------------------------------Shell Primitives

#if (!NoShell)
	#local outer_shell_1 = cylinder
	{
		-z*(habitat_length/2), +z*(habitat_length/2), outer_shell_radius1
	}
	#local outer_shell_2 = cylinder
	{
		-z*(habitat_length/2-metal_thick), +z*(habitat_length/2-metal_thick), outer_shell_radius2
	}
	#local outer_shell_3 = cylinder
	{
		-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius3
	}
	#local outer_shell_4 = cylinder
	{
		-z*(habitat_length/2-metal_thick), +z*(habitat_length/2-metal_thick), outer_shell_radius3
	}
	#local outer_shell_5 = cylinder
	{
		-z*(Meters*10000), +z*(Meters*10000), outer_shell_radius4
	}
	#local inner_shell_1 = cylinder
	{
		-z*(city_length/2+metal_thick*3), +z*(city_length/2+metal_thick*3), inner_shell_radius1
	}
	#local inner_shell_2 = cylinder
	{
		-z*(city_length/2+metal_thick*2), +z*(city_length/2+metal_thick*2), inner_shell_radius2
	}
	#local inner_shell_3 = cylinder
	{
		-z*(city_length/2), +z*(city_length/2), inner_shell_radius2
	}
	#local inner_shell_4 = cylinder
	{
		-z*(Meters*10000), +z*(Meters*10000), inner_shell_radius3
	}

	// inner lozenge cutout 2
	#local cap_cutout_2a = cylinder
	{
		-z*Meters*10000, +z*Meters*10000, window_radius
		translate -y * outer_shell_radius2/2
	}
	#local cap_cutout_2b = union
	{
		object {cap_cutout_2a rotate z * 000}
		object {cap_cutout_2a rotate z * 060}
		object {cap_cutout_2a rotate z * 120}
		object {cap_cutout_2a rotate z * 180}
		object {cap_cutout_2a rotate z * 240}
		object {cap_cutout_2a rotate z * 300}
	}
	// inner lozenge glass 2
	#local cap_glass_2a = difference
	{
		sphere
		{
			0, window_radius*0.999
			scale z * 4/8
		}
		sphere
		{
			0, window_radius*0.999
			scale z * 4/8
			scale 15/16
		}
		plane {-z,0}
		translate -y * outer_shell_radius2/2
	}
	#local cap_glass_2b = union
	{
		object {cap_glass_2a	rotate z * 000}
		object {cap_glass_2a	rotate z * 060}
		object {cap_glass_2a	rotate z * 120}
		object {cap_glass_2a	rotate z * 180}
		object {cap_glass_2a	rotate z * 240}
		object {cap_glass_2a	rotate z * 300}
	}
	// section letters
	#local cap_letter_a =	text {ttf "space age.ttf" "A" 1, 0}
	#local cap_letter_b =	text {ttf "space age.ttf" "B" 1, 0}
	#local cap_letter_c =	text {ttf "space age.ttf" "C" 1, 0}
	#local cap_letter_d =	text {ttf "space age.ttf" "D" 1, 0}
	#local cap_letter_e =	text {ttf "space age.ttf" "E" 1, 0}
	#local cap_letter_f =	text {ttf "space age.ttf" "F" 1, 0}
	#local letter_cutout = union
	{
		object
		{
			cap_letter_a
			Center_Trans(cap_letter_a, x)
			Center_Trans(cap_letter_a, y)
			Center_Trans(cap_letter_a, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 330
		}
		object
		{
			cap_letter_b
			Center_Trans(cap_letter_b, x)
			Center_Trans(cap_letter_b, y)
			Center_Trans(cap_letter_b, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 030
		}
		object
		{
			cap_letter_c
			Center_Trans(cap_letter_c, x)
			Center_Trans(cap_letter_c, y)
			Center_Trans(cap_letter_c, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 090
		}
		object
		{
			cap_letter_d
			Center_Trans(cap_letter_d, x)
			Center_Trans(cap_letter_d, y)
			Center_Trans(cap_letter_d, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 150
		}
		object
		{
			cap_letter_e
			Center_Trans(cap_letter_e, x)
			Center_Trans(cap_letter_e, y)
			Center_Trans(cap_letter_e, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 210
		}
		object
		{
			cap_letter_f
			Center_Trans(cap_letter_f, x)
			Center_Trans(cap_letter_f, y)
			Center_Trans(cap_letter_f, z)
			scale <outer_shell_radius1/6,outer_shell_radius1/6,Meters>
			translate -y*outer_shell_radius1*2/3
			rotate z * 270
		}
	}
	// smaller rings in end caps
	#local cap_hub_r9_inn = cylinder {-z*metal_thick/2, +z*metal_thick/2, inner_shell_radius2}
	#local cap_hub_r9 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*9/9}
	#local cap_hub_r8 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*8/9}
	#local cap_hub_r7 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*7/9}
	#local cap_hub_r6 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*6/9}
	#local cap_hub_r3 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*3/9}
	#local cap_hub_r2 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*2/9}
	#local cap_hub_r1 = cylinder {-z*metal_thick/2, +z*metal_thick/2, outer_shell_radius1*1/9}
	// end bevels
	#local inner_end_bevel = union
	{
		difference
		{
			object {cap_hub_r9_inn}
			object {cap_hub_r7	scale 1.0001}
		}
		difference
		{
			object {cap_hub_r2}
			object {cap_hub_r1	scale 1.0001}
		}
		cylinder
		{
			-z*metal_thick/2,+z*metal_thick/2,inner_shell_radius2
			translate -z * metal_thick
		}
		translate +z * metal_thick/2
	}
	#local outer_end_bevel = union
	{
		difference
		{
			object {cap_hub_r9}
			object {cap_hub_r7	scale 1.0001}
		}
		difference
		{
			object {cap_hub_r2}
			object {cap_hub_r1	scale 1.0001}
		}
	}


	//------------------------------------------------------------------------------Outer Shell

	difference
	{
		union
		{
			// outermost metal ring
			difference
			{
				object {outer_shell_1}
				object {outer_shell_2}
			}
			difference
			{
				object {outer_shell_4}
				object {outer_shell_5}
			}
		}
		object {cap_cutout_2b	translate +z*(habitat_length/2)}
		object {cap_cutout_2b	translate -z*(habitat_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}

	// outermost rock ring
	difference
	{
		object {outer_shell_2}
		object {outer_shell_3}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {steel_filling_texture}
	}

	// end cap bevel
	difference
	{
		union
		{
			object
			{
				outer_end_bevel
				rotate +y * 180
				translate -z*(habitat_length/2+metal_thick/2)
			}
			object
			{
				outer_end_bevel
				translate +z*(habitat_length/2+metal_thick/2)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
	}


	//------------------------------------------------------------------------------Inner Shell & End Caps

	// inner shell
	difference
	{
		object {inner_shell_1}
		object {inner_shell_2}
		object {cap_cutout_2b	translate +z*(habitat_length/2)}
		object {cap_cutout_2b	translate -z*(habitat_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {white_metal_texture}
		rotate +z * city_rotate
	}

	// end cap bevel
	difference
	{
		union
		{
			object
			{
				inner_end_bevel
				translate -z*(city_length/2+metal_thick)
			}
			object
			{
				inner_end_bevel
				rotate +y * 180
				translate +z*(city_length/2+metal_thick)
			}
		}
		union
		{
			object
			{
				letter_cutout
				translate +z*(city_length/2+Meters*4)
			}
			object
			{
				letter_cutout
				translate -z*(city_length/2+Meters*4)
			}
			texture {white_metal_texture}
		}
		object {cap_cutout_2b	translate +z*(habitat_length/2)}
		object {cap_cutout_2b	translate -z*(habitat_length/2)}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {sky_texture_a}
		rotate +z * city_rotate
	}

	// inner rock layer
	difference
	{
		object {inner_shell_3}
		object {inner_shell_4}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {rock_filling_texture}
		rotate +z * city_rotate
	}

	// end glass bubbles
	difference
	{
		union
		{
			object
			{
				cap_glass_2b
				translate +z*(city_length/2+metal_thick)
			}
			object
			{
				cap_glass_2b
				rotate +y * 180
				translate -z*(city_length/2+metal_thick)
			}
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {dome_texture}
		rotate +z * city_rotate
	}
#end

//------------------------------------------------------------------------------Central axis

difference
{
	union
	{
		cylinder
		{
			+z * trusshub_length/2, -z * trusshub_length/2, Meters * 16
		}
		cylinder
		{
			+z * Meters * 16, -z * Meters * 16, Meters * 64
		}
		translate -z * (habitat_length/2 + trusshub_length/2)
	}
//		#if (!ShowWhole)
//			object {cutaway_object1}
//		#end
	texture {white_metal_texture}
}


//------------------------------------------------------------------------------Lamp & Spindles

#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
			lowqual_tex(Seed)
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(lamp_color)}}
		#break
		#case (1)
		#case (2)
			texture {pigment {gamma_color_adjust(lamp_color) transmit 1}}
			interior
			{
				media
				{
					emission gamma_color_adjust(lamp_color)
					density
					{
						cylindrical
						color_map
						{
							[0 srgb 0]
							[1 srgb 2/3]
						}
						scale	lamp_radius
						rotate	x * 90
					}
				}
			}
		#break
	#end
}

#declare lamp_object = object
{
	cylinder {z*-(lamp_length/2), z*+(lamp_length/2), lamp_radius}
	material {lamp_material}
	hollow
	scale	0.9999
	no_shadow
}

#if (quick_interior_light)
	light_source
	{
		0, gamma_color_adjust(light_color)
		looks_like {lamp_object}
	}
#end

#if (!NoLampLight)
	light_source
	{
		0, gamma_color_adjust(lamp_color)
		area_light z*lamp_length/2, y, 16, 1
		looks_like {lamp_object}
	}
#end

#if (!NoLampObject)
	lamp_object
#end

#if (!NoSpindle)
	#local spindle_arm = cylinder
	{
		0, +y*inner_shell_radius2, Meters*2
	}
	#local spindle_hub = union
	{
		difference
		{
			union
			{
				object {spindle_arm rotate z * 030}
//					object {spindle_arm rotate z * 090}
				object {spindle_arm rotate z * 150}
//					object {spindle_arm rotate z * 210}
				object {spindle_arm rotate z * 270}
//					object {spindle_arm rotate z * 330}
			}
			cylinder {-z*city_radius, +z*city_radius, Meters * 16}
		}
		torus
		{
			Meters * 16, Meters*2
			rotate x * 90
		}
		texture {white_metal_texture}
	}
	object {spindle_hub	translate -z * lamp_length/4 rotate +z * city_rotate}
	object {spindle_hub	translate +z * lamp_length/4 rotate +z * city_rotate}
#end


//------------------------------------------------------------------------------Reactor

#if (!NoReactor)
	difference
	{
		union
		{
			#local ring_max = 5;
			#local ring_cnt = 0;
			#while (ring_cnt < ring_max)
				difference
				{
					sphere {0,reactor_radius-city_storey_height*ring_cnt*10+Meters}
					sphere {0,reactor_radius-city_storey_height*ring_cnt*10-Meters}
				}
				#local ring_cnt = ring_cnt + 1;
			#end
			#local ring_max = 50;
			#local ring_cnt = 0;
			#while (ring_cnt < ring_max)
				difference
				{
					sphere {0,reactor_radius-city_storey_height*ring_cnt+Meters/4}
					sphere {0,reactor_radius-city_storey_height*ring_cnt-Meters/4}
				}
				#local ring_cnt = ring_cnt + 1;
			#end
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		translate -z * (habitat_length/2 + trusshub_length + reactor_radius)
		texture {white_metal_texture}
	}

	difference
	{
		sphere {0,reactor_radius			scale <0.99,0.99,1>}
		sphere {0,reactor_radius-city_storey_height*50	scale <0.99,0.99,1>}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		translate -z * (habitat_length/2 + trusshub_length + reactor_radius)
		material {water_material}
	}

	union
	{
		#local ball_radius = Meters * 16;
		#local ball_center = habitat_length/2 + trusshub_length + reactor_radius;
		#local trumpet_length = reactor_radius*2-ball_radius-ring_gap;
		#declare Fx2 = function(u,v) {v}
		#declare Fy2 = function(u,v) {Meters*16/pow(v+1,0.7)*cos(u)}
		#declare Fz2 = function(u,v) {Meters*16/pow(v+1,0.7)*sin(u)}
		object
		{
			Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate -y * 90
			translate -z*(ball_center+Meters*2-ball_radius)
		}
		object
		{
			Parametric(Fx2,Fy2,Fz2,<0,0>,<2*pi,trumpet_length>,30,30,"")
			rotate +y * 90
			translate -z*(ball_center-Meters*2+ball_radius)
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


//------------------------------------------------------------------------------Cargo and Shiphold

#if (!NoShiphold)
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
#end


//------------------------------------------------------------------------------body trusses x-long

difference
{
	union
	{
		// cylindrical trusses around habitat
		#if (!NoShell)
			#declare truss_sides = 12;
			#declare truss_sections = 16;
			#declare truss_thickness = Meters*2;
			#declare truss_radius = outer_shell_radius1 * sqrt(pow(tand(360/2/truss_sides),2) + 1) + truss_thickness;
			#declare truss_point1 = -z*habitat_length/2;
			#declare truss_point2 = +z*habitat_length/2;
			object {#include "truss.inc"}
		#end

		// spherical trusses around reactor
		#if (!NoReactor)
			#declare N = 2;
			#declare Half = 0;
			#declare Method = 1;
			#declare Disc = 0;
			#declare R_Ten = 0.01 / N;
			#declare R_Hen = 0.01 / N;
			#declare Thickness = truss_thickness;
			#include "sphere.inc"
			union
			{
				object {Ten}
				object {Hen}
				scale		truss_radius
				translate	-z * (habitat_length/2 + trusshub_length + reactor_radius)
			}
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	texture {white_metal_texture}
}


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
		translate +y * Meters
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
		scale 10 * Meters
		translate -z * (dock_start+dock_length*7/12)
		translate -y * dock_depth
		translate +y * Meters
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
		scale 18 * Meters
		translate -z * (dock_start+dock_length*3/12)
		translate -y * dock_depth
		translate +y * Meters
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
		scale 16 * Meters
		translate -z * (dock_start+dock_length*3/12)
		translate -y * dock_depth
		translate +y * Meters
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
		scale		2 * Meters
		bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}
	object
	{
		horus_object
		translate -z * (dock_start+dock_length*9/12)
		translate -y * dock_depth
		translate +y * Meters
		translate -x * dock_radius_outer*8/12
	}

	// cargo containers
	#local cargo_pigment = pigment
	{
		checker
		color srgb <0,0,0>,
		color srgb <1/2,1/2,1/2>
		scale Meters
	}
	#local cargo_box = box
	{
		<-Meters,0,-Meters>,
		<+Meters,+Meters*2,+Meters>
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
				object {cargo_box		rotate y * (rand(Seed) * 30 - 15)	translate <0,0,+Meters> * 1.2}
				#if (cargo_rand > 1/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <-Meters,0,-Meters> * 1.2}
				#end
				#if (cargo_rand > 2/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <+Meters,0,-Meters> * 1.2}
				#end
				#if (cargo_rand > 3/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <0,Meters*2,0>}
				#end
			}
			rotate y * 360 * rand(Seed)
			translate -z * (dock_start + dock_length/6 + dock_length/3 * rand(Seed))
			translate -x * ((dock_radius_outer * 3/4 - dock_radius_inner) * rand(Seed) + dock_radius_inner)
			translate -y * (dock_depth)
			translate +y * (Meters)
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
			translate +y * (Meters)
		}
		#local people_cnt = people_cnt + 1;
	#end
*/
	// fuel tanks
	union
	{
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius_outer/2+Meters*16)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius_outer/2+Meters*24)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius_outer/2+Meters*16)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius_outer/2+Meters*24)
			translate -z*(dock_start+dock_thick+Meters*8)
		}

		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius_outer/2+Meters*16)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius_outer/2+Meters*24)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius_outer/2+Meters*16)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius_outer/2+Meters*24)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		translate -y*dock_depth
		texture {yellow_metal_texture}
	}

	// robo arm
	object
	{
		#include "gh_roboarm.inc"
		rotate -x*90
		scale Meters/2
		translate -z*(dock_start+Meters*2)
		texture {white_metal_texture}
	}

	// rafters
	#declare rafter_object_a = union
	{
		#declare truss_sides = 3;
		#declare truss_sections = 8;
		#declare truss_radius = Meters*8;
		#declare truss_thickness = Meters;
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
		scale Meters * 16
	}
	object
	{
		gantry_object
		rotate y*15
		translate -y*(dock_depth-Meters)
		translate -z*(city_length/2+reactor_radius*2+dock_length*1/4)
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
			translate -z * (habitat_length/2+trusshub_length+reactor_radius*2+dock_length+fuel_radius)
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
				translate z * Meters * 2
			}
		}
		plane {+z, z_position}
		rotate y * 180
		translate -z * (habitat_length/2+trusshub_length+reactor_radius*2+dock_length)
///////
		texture {T_Silver_5E }
///////
	}
#end


//------------------------------------------------------------------------------Tanks

#local tank_radius = Meters * 16;
#local tank_length = Meters * 128;
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


//------------------------------------------------------------------------------Comms & Nose Cone

#if (!NoCone)
	#local p_radius = outer_shell_radius1;
	#local p_scale = p_radius;
	#local z_position = pow(p_radius, 2)/p_scale;
	#local main_cone = difference
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
			translate +z * Meters * 2
		}
	}
	difference
	{
		union
		{
			// glass portion
			intersection
			{
				object {main_cone}
				plane {+z, z_position * 2}
				scale 0.99
			}
			// longitudinal arcs
			#local count_max = 4;
			#local count_itr = 0;
			#while (count_itr < count_max)
				#local turn_angle = count_itr * 45;
				intersection
				{
					object {main_cone}
					plane {+z, z_position * 2}
					plane {+x, Meters * 8}
					plane {-x, Meters * 8}
					rotate +z * turn_angle
					texture {white_metal_texture}
				}
				#local count_itr = count_itr + 1;
			#end
			// latitudinal rings
			intersection
			{
				object {main_cone}
				plane {+z, Meters * 8 translate +z * z_position * 1/2}
				plane {-z, Meters * 8 translate +z * z_position * 1/2}
				texture {white_metal_texture}
			}
//				intersection
//				{
//					object {main_cone}
//					plane {+z, Meters * 8 translate +z * z_position * 2/2}
//					plane {-z, Meters * 8 translate +z * z_position * 2/2}
//					texture {white_metal_texture}
//				}
			intersection
			{
				object {main_cone}
				plane {+z, Meters * 8 translate +z * z_position * 3/2}
				plane {-z, Meters * 8 translate +z * z_position * 3/2}
				texture {white_metal_texture}
			}
//				intersection
//				{
//					object {main_cone}
//					plane {+z, Meters * 8 translate +z * z_position * 4/2}
//					plane {-z, Meters * 8 translate +z * z_position * 4/2}
//					texture {white_metal_texture}
//				}
			rotate +y * 180
			translate +z * (habitat_length/2 + z_position)
		}
		#if (!ShowWhole)
			object {cutaway_object1}
		#end
		texture {dome_texture}
	}
	// tip
	intersection
	{
		object {main_cone}
		plane {+z, Meters * 16}
		rotate +y * 180
		translate +z * (habitat_length/2 + z_position)
		texture {white_metal_texture}
	}
	// comms trusses
	#declare truss_sides = 6;
	#declare truss_sections = 1;
	#declare truss_radius = Meters*16;
	#declare truss_thickness = Meters/2;
	#declare truss_point1 = -z*Meters*16;
	#declare truss_point2 = 0;
	#local comm_truss = object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
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
		cylinder {<0,0,0>, <0,0,-Meters*8>, Meters/2}
		scale 2
		translate -z*Meters*16
	}
	#local comm_dome = difference
	{
		sphere {-z*Meters*16, Meters*16}
		plane {-z,0}
	}
	#local comm_anten = union
	{
		cylinder {<0,0,0>, <0,0,-city_length/16>, Meters}
		cylinder {<0,0,0>, <0,0,-city_length/4>, Meters/2}
		cylinder {<0,-Meters*32,0>, <0,-Meters*32,-city_length/32>, Meters}
		cylinder {<0,-Meters*32,0>, <0,-Meters*32,-city_length/8>, Meters/2}
		object {blinky_sphere	translate <0,0,-city_length/4-blinky_radius>}
		sphere {blinky_sphere	translate <0,-Meters*32,-city_length/8-blinky_radius>}
	}
	union
	{
		object
		{
			comm_dome
			translate	-y * Meters * 64
			rotate		+z * 000
		}
		object
		{
			comm_truss
			translate	-y * Meters * 64
			rotate		+z * 000
		}
		object
		{
			comm_dish
			translate	-y * Meters * 64
			rotate		+z * 120
		}
		object
		{
			comm_truss
			translate	-y * Meters * 64
			rotate		+z * 120
		}
		object
		{
			comm_anten
		}
		rotate		+y * 180
		translate 	+z * (habitat_length/2 + z_position)
		texture {white_metal_texture}
	}
#end


//------------------------------------------------------------------------------Solar Panels & Agridomes

#if (!NoPanels)
	#include "gh_truss_array_c.inc"
#end


//------------------------------------------------------------------------------Blinky Lights & Thrusters

#local blinky_group = union
{
	object {blinky_sphere	translate <0,-dock_radius_outer-blinky_radius,-habitat_length/2-reactor_radius*2-dock_length>}
	object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,-habitat_length/2>}
	object {blinky_sphere	translate <0,-outer_shell_radius1-blinky_radius,+habitat_length/2>}
}
#local thruster = union
{
	cone {<0, 0, 0>, 0, <0, 0, -2>, 1 open hollow}
	cylinder {<0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow}
	scale 1/2
}
#local thruster_tank_radius = Meters*12;
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
	object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),-habitat_length/2-trusshub_length-reactor_radius>}
	object {thruster_aggregate	translate <0,-(outer_shell_radius1+thruster_tank_radius*2),0>}
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
		translate	+x * (outer_shell_radius1 + Meters * 128)
		translate	-z * (city_length/2 + reactor_radius*2)
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

//------------------------------------------------------------------------------Atmosphere

// very slowwww!!!
#if (!NoAtmos)
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
	difference
	{
		cylinder
		{
			+z*(city_length/2-Meters*4), -z*(city_length/2-Meters*4), city_radius
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
