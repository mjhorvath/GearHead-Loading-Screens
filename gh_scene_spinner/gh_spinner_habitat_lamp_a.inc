#local lamp_material = material
{
	#switch (TexQual)
		#case (-1)
			texture {pigment {lowqual_pig(Seed)}}
		#break
		#case (0)
//			texture {pigment {color rgb lamp_color_adjust}}
			texture {pigment {color rgb lamp_color}}
		#break
		#case (1)
		#case (2)
			texture
			{
//				pigment {color rgb lamp_color_adjust transmit 1}
				pigment {color rgb lamp_color transmit 1}
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
//					emission rgb lamp_color_adjust/lamp_radius1
					emission rgb lamp_color/lamp_radius1
					density
					{
						spherical
						color_map
						{
							[0 rgb 0]	// one unit away
							[1 rgb 1]	// at the origin
						}
					}
				}
			}
		#break
	#end
}

#declare lamp_bulb = union
{
	#for (i, 1, lamp_num, 1)
		#local spiral_coo = <lamp_radius2 * cosd(i * lamp_ang), lamp_radius2 * sind(i * lamp_ang), -lamp_length/2 + i * lamp_length/lamp_num>;		// need to take into account lamp_radius at each end
		#local lamp_sphere = sphere
		{
			0, 1
			material {lamp_material}
			scale lamp_radius1
			hollow
		}
		#if ((!NoLampLight) | (!SimpleLamp))
			#if (mod(i, lamp_mod) = 0)
				light_source
				{
					0, lamp_color_adjust
					looks_like {lamp_sphere}
					translate spiral_coo
				}
			#else
				object {lamp_sphere	translate spiral_coo no_shadow}
			#end
		#else
			object {lamp_sphere	translate spiral_coo no_shadow}
		#end
	#end
	// central axis
	difference
	{
		cylinder {+z * (lamp_length/2 + 0), -z * (lamp_length/2 + 0), central_axis_radius}
		cylinder {+z * (lamp_length/2 + 1), -z * (lamp_length/2 + 1), central_axis_radius - metal_thick}
		texture {white_metal_texture}
		no_shadow
	}
}
#if ((SimpleLamp = 1) & (!NoLampLight))
	#declare lamp_object = light_source
	{
		0, lamp_color
		looks_like {lamp_bulb}
	}
#elseif (NoLampLight)
	#declare lamp_object 
#end
