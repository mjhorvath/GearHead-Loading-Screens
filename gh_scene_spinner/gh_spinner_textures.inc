//------------------------------------------------------------------------------Textures & Common Objects

// need to turn off ambient when radiosity is turned on
// also, too shiny to be default IMO
#default
{
	#switch (TexQual)
		#case (-1)
		#case (0)
			finish {ambient 1/16 diffuse 12/16}
		#break
		#case (1)
		#case (2)
			finish {ambient 1/16 diffuse albedo 12/16}
		#break
	#end
}

#declare city_rail_texture = texture
{
	pigment {gamma_color_adjust(<1,1,1>)}
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
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment
			{
				cylindrical
				color_map
				{
					[-1  gamma_color_adjust(<1.00,1.00,1.00>)]
					[0.8 gamma_color_adjust(<0.10,0.25,0.75>)]
					[1.0 gamma_color_adjust(<0.10,0.25,0.75>)]
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
			pigment {lowqual_pig(Seed)}
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
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment
			{
				granite
				color_map
				{
					[0 gamma_color_adjust(<1/2,1/2,1/2>)]
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
					[0 gamma_color_adjust(<1/2,1/2,1/2>)]
					[1 gamma_color_adjust(<0,0,0>)]
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
	gamma_color_adjust(<046/2,104/2,058/2,>/255)
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
			pigment {lowqual_pig(Seed)}
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
// which ring?
#local ring_glass_mat = material
{
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<0.5,0.5,0.5,0.0,0.7>)}}
		#break
		#case (1)
			texture
			{
				pigment {gamma_color_adjust(<0.5,0.5,0.5,0.0,0.7>)}
				normal {bumps .05 scale .1}
				finish {specular .5 roughness .1 reflection <.3, .4, .5>}
			}
			scale Meters
		#break
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<0.5,0.5,0.5,0.0,0.7>)}
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
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(<1,1,1>)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,1,1>)}
			finish {phong 1}
		#break
	#end
}
#declare gray_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(<1,1,1>/2)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<1,1,1>/2)}
			finish {phong 1}
		#break
	#end
}
#declare red_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(x)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(x)}
			finish {phong 1}
		#break
	#end
}
#declare yellow_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(x+y)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(x+y)}
			finish {phong 1}
		#break
	#end
}
#declare green_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(y)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(y)}
			finish {phong 1}
		#break
	#end
}
//T_Silver_5E
#declare engine_nozzle_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(<0.91,0.95,0.91>)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<0.91,0.95,0.91>)}
			finish
			{
				ambient		0.1
				brilliance	6
				diffuse		0.7
				metallic
				specular	0.80
				roughness	1/120
				reflection	0.8
			}
		#break
	#end
}
// based on T_Silver_5E
#declare nose_shield_metal_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
			pigment {gamma_color_adjust(<0.91,0.95,0.91>)}
		#break
		#case (1)
		#case (2)
			pigment {gamma_color_adjust(<0.91,0.95,0.91>)}
			finish
			{
				ambient		0.1
				brilliance	6
				diffuse		0.7
				metallic
				specular	0.80
				roughness	1/120
				reflection	0.8
			}
		#break
	#end
}
#declare nose_function_z = function (x,y,z)
{
	pow(z,1/2)*nose_para_multi*8
}
#declare invisible_texture = texture
{
	pigment {color rgbt 1}
	finish
	{
		ambient	0
		diffuse	0
		diffuse albedo	0
		phong	0
	}
}
#declare nose_shield_combined_texture = texture
{
	function {nose_function_z(x,y,z)}
	texture_map
	{
		[00/16 nose_shield_metal_texture]
		[01/16 nose_shield_metal_texture]
		[01/16 invisible_texture]
		[15/16 invisible_texture]
		[15/16 nose_shield_metal_texture]
		[16/16 nose_shield_metal_texture]
	}
}

#if (GlassColor = 0)
	// gold
	#declare dome_material = material
	{
		#switch (TexQual)
			#case (-1)
				texture {pigment {lowqual_pig(Seed)}}
			#break
			#case (0)
				texture {pigment {gamma_color_adjust(<1.000/2, 0.875/2, 0.575/2, 0.000, 0.950>)}}
			#break
			#case (1)
				texture
				{
					pigment {gamma_color_adjust(<1.000/2, 0.875/2, 0.575/2, 0.000, 0.950>)}
					finish
					{
						ambient		0.35
						brilliance	1
						diffuse		0.3
						metallic
						specular	0.50
						roughness	1/20
						reflection	0.1
					}
				}
			#break
			#case (2)
				texture
				{
					pigment {gamma_color_adjust(<1.000/2, 0.875/2, 0.575/2, 0.000, 0.950>)}
					finish
					{
						ambient		0.35
						brilliance	1
						diffuse		0.3
						metallic
						specular	0.50
						roughness	1/20
						reflection	0.1
					}
				}
				interior {ior 1.5}
			#break
		#end
	}
#else
	// clear white
	#declare dome_material = material
	{
		#switch (TexQual)
			#case (-1)
				texture {pigment {lowqual_pig(Seed)}}
			#break
			#case (0)
				texture {pigment {gamma_color_adjust(<0.980, 0.980, 0.980, 0.000, 0.950>)}}
			#break
			#case (1)
				texture
				{
					pigment {gamma_color_adjust(<0.980, 0.980, 0.980, 0.000, 0.950>)}
					finish {F_MetalA}
				}
			#break
			#case (2)
				texture
				{
					pigment {gamma_color_adjust(<0.980, 0.980, 0.980, 0.000, 0.950>)}
					finish {F_MetalA}
				}
				interior {ior 1.5}
			#break
		#end
	}
#end

#declare water_material = material
{
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<.93,.95,.98,0.825,0>*0.99)}}
		#break
		#case (1)
			texture
			{
				pigment {gamma_color_adjust(<.93,.95,.98,0.825,0>*0.99)}
				finish
				{
					ambient		0.0
					diffuse		0.15
					reflection {0.1,0.1 fresnel on}
					specular	0.6
					roughness	0.005
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
					ambient		0.0
					diffuse		0.15
					reflection {0.1,0.1 fresnel on}
					specular	0.6
					roughness	0.005
					conserve_energy
				}
			}
			interior
			{
				ior				1.33
				fade_power		1001
				fade_distance	0.5
				fade_color		<0.8,0.8,0.8>
				caustics		0.16
			}
		#break
	#end
}

#macro new_random_color()
	#switch (TexQual)
		#case (-1)
			#declare MTX = texture {pigment {lowqual_pig(Seed)}}
			#declare CTX = texture {pigment {lowqual_pig(Seed)}}
			#declare HTX = texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			#if (!NoColors)
				#declare MTX = texture {pigment {lowqual_pig(Seed)}}
				#declare CTX = texture {pigment {lowqual_pig(Seed)}}
				#declare HTX = texture {pigment {lowqual_pig(Seed)}}
			#else
				#declare MTX = texture {pigment {gamma_color_adjust(2/2)}}
				#declare CTX = texture {pigment {gamma_color_adjust(0/2)}}
				#declare HTX = texture {pigment {gamma_color_adjust(1/2)}}
			#end
		#break
		#case (1)
		#case (2)
			#if (!NoColors)
				#declare MTX = texture {pigment {lowqual_pig(Seed)} finish {F_MetalA}}
				#declare CTX = texture {pigment {lowqual_pig(Seed)} finish {F_MetalA}}
				#declare HTX = texture {pigment {lowqual_pig(Seed)} finish {F_MetalA}}
			#else
				#declare MTX = texture {pigment {gamma_color_adjust(2/2)} finish {F_MetalA}}
				#declare CTX = texture {pigment {gamma_color_adjust(0/2)} finish {F_MetalA}}
				#declare HTX = texture {pigment {gamma_color_adjust(1/2)} finish {F_MetalA}}
			#end
		#break
	#end
#end

#switch (TexQual)
	#case (-1)
		#declare Plain_Gray			= texture {pigment {lowqual_pig(Seed)}}
		#declare Plain_LightGray	= texture {pigment {lowqual_pig(Seed)}}
		#declare Plain_DarkGray		= texture {pigment {lowqual_pig(Seed)}}
	#break
	#case (0)
		#declare Plain_Gray			= texture {pigment {gamma_color_adjust(1/2)}}
		#declare Plain_LightGray	= texture {pigment {gamma_color_adjust(3/4)}}
		#declare Plain_DarkGray		= texture {pigment {gamma_color_adjust(1/4)}}
	#break
	#case (1)
	#case (2)
		#declare Plain_Gray			= texture {pigment {gamma_color_adjust(1/2)} finish {F_MetalA}}
		#declare Plain_LightGray	= texture {pigment {gamma_color_adjust(3/4)} finish {F_MetalA}}
		#declare Plain_DarkGray		= texture {pigment {gamma_color_adjust(1/4)} finish {F_MetalA}}
	#break
#end


#declare street_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
		#case (1)
		#case (2)
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
		#break
	#end
}

#declare pavement_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {lowqual_pig(Seed)}
		#break
		#case (0)
		#case (1)
		#case (2)
			pigment
			{
				wrinkles
				color_map
				{
		//			[0 gamma_color_adjust(<0.5,0.5,0.5>)]
		//			[1 gamma_color_adjust(<0.6,0.6,0.6>)]
					[0 gamma_color_adjust(8/8)]
					[1 gamma_color_adjust(8/8)]
		
				}
				scale 1.5
			}
			scale Meters
		#break
	#end
}

#declare planet_texture = texture
{
	pigment
	{
		image_map
		{
			png		"jupiter.png"
			#if (version >= 3.7) file_gamma srgb #end
			map_type	1
		}
	}
	finish
	{
		ambient 0
	}
}

#declare starfield_pigment_0 = pigment
{
	bozo
	color_map
	{
		[0.0 color rgb 3]
		[0.2 color rgb 0]
		[1.0 color rgb 0]
	}
	scale 0.0001
}
