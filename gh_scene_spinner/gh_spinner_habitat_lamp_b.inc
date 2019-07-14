#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
			texture {pigment {color rgb lamp_color*lamp_num/lamp_mod}}
		#break
		#case (1)
		#case (2)
			texture
			{
				pigment {color rgbt 1}
                //finish
				//{
				//	diffuse		0.1
				//	reflection	0.2
                //	specular	0.8
				//	roughness	0.0003
				//	phong		1
				//	phong_size	400
				//}
			}
			interior
			{
				media
				{
					emission rgb lamp_color*lamp_num/lamp_mod/lamp_radius1
					density
					{
						spherical
						color_map
						{
							[0/3 rgb 0/3]	// one unit away
						//	[1/3 rgb 3/3]	// 
							[3/3 rgb 3/3]	// origin
						}
					}
				}
			}
		#break
	#end
}

#local lamp_bulb = union
{
	// spiral bulbs
	#for (i, 1, lamp_num)
		#local spiral_inc = lamp_length/lamp_num;
		#local spiral_rad = central_axis_radius + lamp_radius1;
		#local spiral_coo = <spiral_rad * cosd(i * lamp_ang), spiral_rad * sind(i * lamp_ang), -lamp_length/2 + i * spiral_inc>;
		sphere
		{
			0, 1
			material {lamp_material}
			scale lamp_radius1
			hollow
			translate spiral_coo
		}
	#end
	// central axis
	difference
	{
		cylinder {+z * (lamp_length/2 + 0), -z * (lamp_length + 0), central_axis_radius}
		cylinder {+z * (lamp_length/2 + 1), -z * (lamp_length + 1), central_axis_radius - metal_thick}
		texture {white_metal_texture}
	}
}

#if (!NoLampLight)
	#if (!SimpleLight)
		#declare lamp_object = light_source
		{
			0, lamp_color
			area_light
			+z * lamp_length, +y, 12, 1
			looks_like {lamp_bulb}
		}
	#else
		#declare lamp_object = light_source
		{
			0, lamp_color
			looks_like {lamp_bulb}
		}
	#end
#else
	#declare lamp_object = object {lamp_bulb}
#end
