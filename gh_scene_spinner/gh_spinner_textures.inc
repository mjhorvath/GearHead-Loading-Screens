//------------------------------------------------------------------------------Textures & Common Objects

#default
{
	#switch (TexQual)
		#case (-2)
			finish {diffuse 0 emission 1 ambient 0 specular 0}
		#break
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

#macro city_rail_texture()
	texture
	{
		pigment {gamma_color_adjust(<1,1,1>)}
	}
#end

#declare sky_pigment_1 = pigment
{
	bozo
	turbulence	0.65
	octaves		6
	omega		0.7
	lambda		2
	color_map
	{
		[0.0	gamma_color_adjust(<0.85,0.85,0.85>)]
		[0.1	gamma_color_adjust(<0.75,0.75,0.75>)]
		[0.5	gamma_color_adjust(<0.50,0.60,1.00>)]
		[1.0	gamma_color_adjust(<0.50,0.60,1.00>)]
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

#macro sky_texture_a()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
		#case (1)
		#case (2)
			texture
			{
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
			}
		#break
	#end
#end

#macro rock_filling_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture
			{
				pigment
				{
					granite
					color_map
					{
						[0 DarkBrown]
						[1 gamma_color_adjust(<0,0,0>)]
					}
				}
			}
		#break
		#case (1)
		#case (2)
			texture
			{
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
			}
		#break
	#end
#end
#macro steel_filling_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture
			{
				pigment
				{
					granite
					color_map
					{
						[0 gamma_color_adjust(<1/2,1/2,1/2>)]
						[1 gamma_color_adjust(<0,0,0>)]
					}
				}
			}
		#break
		#case (1)
		#case (2)
			texture
			{
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
			}
		#break
	#end
#end
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
#macro grass_texture_1()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {grass_pigment_3}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {grass_pigment_3}
				normal
				{
					wrinkles
				}
			}
		#break
	#end
#end
// which ring?
#macro ring_glass_mat()
	material
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
#end
#macro white_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<1,1,1>)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				finish {phong 1}
			}
		#break
	#end
#end
#macro gray_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<1,1,1>/2)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(<1,1,1>/2)}
				finish {phong 1}
			}
		#break
	#end
#end
#macro red_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(x)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(x)}
				finish {phong 1}
			}
		#break
	#end
#end
#macro yellow_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(x+y)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(x+y)}
				finish {phong 1}
			}
		#break
	#end
#end
#macro green_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(y)}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {gamma_color_adjust(y)}
				finish {phong 1}
			}
		#break
	#end
#end
//T_Silver_5E
#macro engine_nozzle_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<0.91,0.95,0.91>)}}
		#break
		#case (1)
		#case (2)
			texture
			{
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
			}
		#break
	#end
#end
// based on T_Silver_5E
#macro nose_shield_metal_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {gamma_color_adjust(<0.91,0.95,0.91>)}}
		#break
		#case (1)
		#case (2)
			texture
			{
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
			}
		#break
	#end
#end
#declare nose_function_z = function (x,y,z)
{
	pow(z,1/2)*8/nose_wire_para_thick
}
#macro invisible_texture()
	texture
	{
		pigment {color rgbt 1}
		finish
		{
			emission 0
			ambient	0
			diffuse	0
			diffuse albedo	0
			phong	0
		}
	}
#end
#macro nose_shield_combined_texture()
	texture
	{
		function {nose_function_z(x,y,z)}
		texture_map
		{
			[00/16 nose_shield_metal_texture()]
			[01/16 nose_shield_metal_texture()]
			[01/16 invisible_texture()]
			[15/16 invisible_texture()]
			[15/16 nose_shield_metal_texture()]
			[16/16 nose_shield_metal_texture()]
		}
	}
#end
#macro dirt_texture()
	texture
	{
		pigment
		{
			wrinkles
			color_map
			{
				[0 gamma_color_adjust(1/4*<1,1,1>)]
				[1 gamma_color_adjust(0/4*<1,1,1>)]
			}
		}
	}
#end
#macro dome_material()
	material
	{
		#if (GlassColor = 0)
			// gold
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
		#else
			// clear white
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
		#end
	}
#end

#macro water_material()
	material
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
#end
#macro new_random_color()
	#switch (TexQual)
		#case (-2)
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
	#case (-2)
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

#declare planet_texture = texture
{
	pigment
	{
		image_map
		{
			// http://planetpixelemporium.com/mars.html
			#if (planet_name = "Mars")
				jpeg	"mars_1k_color.jpg"
			// http://planetpixelemporium.com/jupiter.html
			#elseif (planet_name = "Jupiter")
				jpeg	"jupiter2_6k.jpg"
			#elseif (planet_name = "Earth")
				jpeg	"world.200406.3x21600x10800.jpg"
			// https://www.deviantart.com/kvikki/art/Earth-like-Planet-Texture-466813840
			#elseif (planet_name = "Alien")
				jpeg	"alien_planet.jpg"
			#end
//			#if (version >= 3.7) file_gamma srgb #end
			map_type	1
		}
	}
	finish
	{
		ambient 0
	}
}

#declare planet_atmosphere_1 = media
{
	scattering {4, rgb planet_atmos_scat/planet_radius}
	intervals 5
	samples 2, 20
	confidence 0.9999
	variance 1/1000
	density
	{
		spherical
		color_map
		{
			[0.000 rgbf <0,0,0,1>]
			[1-planet_atmos_invert rgbf <1,1,1,1>]
			[1.000 rgbf <1,1,1,1>]
		}
	}
}

#declare planet_atmosphere_2 = media
{
	absorption rgb planet_atmos_abso/planet_radius
	intervals 5
	samples 2, 20
	confidence 0.9999
	variance 1/1000
	density
	{
		spherical
		color_map
		{
			[0.000 rgbf <0,0,0,1>]
			[1-planet_atmos_invert rgbf <1,1,1,1>]
			[1.000 rgbf <1,1,1,1>]
		}
	}
}

#declare planet_atmosphere = material
{
	texture
	{
		pigment {rgbf 1}
		finish {ambient 0}
	}
	interior
	{
		media {planet_atmosphere_1}
		media {planet_atmosphere_2}
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

#macro solar_panel_texture(panel_length_angle, panel_gap_angle)
	#local solar_panel_pigment_1 = pigment
	{
		radial
		color_map
		{
			[00/32 gamma_color_adjust(0/4*<1,1,1>)]
			[01/32 gamma_color_adjust(0/4*<1,1,1>)]
			[01/32 gamma_color_adjust(1/4*<1,1,1>)]
			[31/32 gamma_color_adjust(1/4*<1,1,1>)]
			[31/32 gamma_color_adjust(0/4*<1,1,1>)]
			[32/32 gamma_color_adjust(0/4*<1,1,1>)]
		}
		rotate x * 90
		frequency 360/panel_length_angle * 8
		rotate -z * panel_gap_angle
		scale 8/panel_width
	}
	#local solar_panel_Pigment_3 = pigment {gamma_color_adjust(0/4*<1,1,1>)}
	#local solar_panel_pigment_2 = pigment
	{
		gradient z
		pigment_map
		{
			[00/32 solar_panel_Pigment_3]
			[01/32 solar_panel_Pigment_3]
			[01/32 solar_panel_pigment_1]
			[31/32 solar_panel_pigment_1]
			[31/32 solar_panel_Pigment_3]
			[32/32 solar_panel_Pigment_3]
		}
		scale panel_width/8
	}
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture
			{
				pigment {solar_panel_pigment_2}
				translate +y * panel_width/16
				translate +z * panel_width/8
			}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {solar_panel_pigment_2}
//				finish {Glossy}
				finish
				{
					ambient     srgb <0.100,0.100,0.100>
					brilliance  1.000
					crand       0.000
					diffuse     0.600
					metallic    1.000
					phong       0.000
					phong_size  40.000
					specular    0.000
					roughness   0.050
					reflection
					{
						srgb <0.481,0.301,0.133>, srgb <0.722,0.451,0.200>
						fresnel   0
						falloff   0.000
						exponent  1.000
						metallic  0.000
					}
				} 
				translate +y * panel_width/16
				translate +z * panel_width/8
			}
		#break
	#end
#end

#macro parking_texture()
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
		#case (1)
		#case (2)
			texture
			{
				pigment
				{
					image_map {png "spinner_lot_text.png"}
				}
			}
		#break
	#end
#end
