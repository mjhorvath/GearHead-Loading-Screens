#local lamp_function = function {f_helix1(x,y,z, 1, lamp_frequency, lamp_radius1, lamp_radius2, 1, 1, 0)}

#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
//			texture {pigment {lowqual_pig(Seed)}}		// proper seed value?
//		#break
		#case (0)
//			texture {pigment {color rgb lamp_color}}
			texture
			{
				pigment {color rgb lamp_color}
				finish
				{
					ambient		0
					diffuse		0
					emission	lamp_color
				}
			}
		#break
		#case (1)
			texture
			{
				pigment {color rgb lamp_color}
				finish
				{
					ambient		srgb <0,0,0>
					diffuse		0.6
					emission	lamp_color
					phong		0.3
				}
			}
		#break
		#case (2)
			texture
			{
				pigment {color rgb lamp_color transmit 1}
				finish
				{
					ambient		srgb <0,0,0>
					diffuse		0.6
					emission	srgb <0,0,0>
					phong		0.3
				}
			}
			interior
			{
				ior 1
				media
				{
					method       3
					samples      500,500
					confidence   0.9
					variance     0.0078125
					jitter       0
					aa_level     4
					aa_threshold 0.1
					emission     rgbft lamp_color/lamp_radius1
					density
					{
						function {max(0, lamp_function(x,y,z))}
						color_map
						{
							[0 color rgb 1]
							[1 color rgb 0]
						}
					}
				}
			}
		#break
	#end
}

#local lamp_axis_texture = texture
{
	#switch (TexQual)
		#case (-1)
			pigment {srgb 1}
		#case (0)
		#break
		#case (1)
		#case (2)
			pigment {srgb 1}
			finish
			{
				phong		1
				phong_size	100
				reflection	0.10
			}
		#break
	#end
}

#local lamp_bulb = union
{
	// spiral lamp
	isosurface
	{
		function {lamp_function(x,y,z)}
			//P0= number of helixes
			//P1= frequency
			//P2= minor radius
			//P3= major radius
			//P4= Y scale cross section
			//P5= cross section
			//P6= cross section rotation (¡)
			//P0 is set to 1 to get only a single helix. Non integer may cause unexpected results. (not used if f_helix2)
			//P1, P2 and P3 are renamed to reflect their functions.
			//P4 elongate the section along the Y axis. Set to 1 to leave the shape unchanged. (not used if f_helix2)
			//P5 is set to 1 whitch correspond to a circular section.
			//0 = square section.
			//1 = circular section
			//2 = losange section (I don't get it that a square rotated 45° could be called "diamond")
			//>2 = concave losange section, may become degenarate if larger than 3.
			//For a circular section, P6 have no effect. It rotate the section shape when it's not circular.
		contained_by
		{
			box {<-lamp_radius3,-lamp_length/2,-lamp_radius3>, <+lamp_radius3,+lamp_length/2,+lamp_radius3>}
		}
		threshold		0
		accuracy		0.001
		max_gradient	4.1
		all_intersections
		material {lamp_material}
		hollow
		rotate +x * 90
	}
	// central axis
	difference
	{
		cylinder {+z * (lamp_length/2 + 0), -z * (lamp_length/2 + 0), central_axis_radius}
		cylinder {+z * (lamp_length/2 + 1), -z * (lamp_length/2 + 1), central_axis_radius - metal_thick}
		texture {lamp_axis_texture}
	}
	no_shadow
	no_radiosity
}

#if (!NoLampLight)
	#if (!SimpleLamp)
		#declare lamp_object = light_source
		{
			0, lamp_color * (1 + pow(city_radius/lamp_radius2, 2))
			area_light
			+z * lamp_length, +y, lamp_number, 1
			area_illumination	on
			fade_distance		lamp_radius2
			fade_power			2
			adaptive			1
			looks_like {lamp_bulb}
		}
	#else
		#declare lamp_object = light_source
		{
			0, lamp_color * (1 + pow(city_radius/lamp_radius2, 2))
			fade_distance	lamp_radius2
			fade_power		2
			looks_like {lamp_bulb}
		}
	#end
#else
	#declare lamp_object = lamp_bulb
#end
