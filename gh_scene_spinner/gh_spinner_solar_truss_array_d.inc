union
{
	//------------------------------------------------------------------------------major trusses

	#debug "\n>>>>Start truss array trusses\n"
	// large arms connecting the ring to the axle
//	#local truss_rotate = 45;
	#local truss_sides = 4;
	#local truss_sections = 4;
	#local truss_thickness = big_truss_thick;
	#local truss_radius = big_truss_radius - big_truss_thick;
	#local truss_point1 = +x * main_body_radius;
	#local truss_point2 = +x * agridome_ringrad;
	union
	{
		#local truss_arms_max = 6;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			union
			{
				object {#include "truss.inc"}
				cylinder {truss_point1, truss_point2, Meters * 4}
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		texture {white_metal_texture}
	}

	// small short horizontal rods connecting the two outer rings
	#local truss_sides = 4;
	#local truss_sections = 4;
	#local truss_thickness = big_truss_thick;
	#local truss_radius = big_truss_radius;
	#local truss_point1 = -z * agridome_ringgap/2;
	#local truss_point2 = +z * agridome_ringgap/2;
	union
	{
		#local truss_arms_max = 6;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			object
			{
				#include "truss.inc"
				translate +x * agridome_ringrad
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		texture {white_metal_texture}
	}

	// outermost ring
	#local segment_number = 36;
	#local segment_distance = sind(360/segment_number/2) * agridome_ringrad;
	#local truss_sides = 4;
	#local truss_sections = 1;
	#local truss_thickness = big_truss_thick;
	#local truss_radius = big_truss_radius;
	#local truss_point1 = -y * segment_distance;
	#local truss_point2 = +y * segment_distance;
	union
	{
		#local truss_arms_max = segment_number;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			union
			{
				object
				{
					#include "truss.inc"
					translate +z * agridome_ringgap/2
				}
				object
				{
					#include "truss.inc"
					translate -z * agridome_ringgap/2
				}
				translate +x * agridome_ringrad
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		texture {white_metal_texture}
	}
	#debug "\n<<<<Finish truss array trusses\n"


	//------------------------------------------------------------------------------agridomes

	#debug "\n>>>>Start truss array domes\n"
	#if (!NoDomes)
		#include "gh_spinner_dome_ring_b.inc"
		#local tank_radius = Meters * 16;
		#local tank_length = Meters * 64;
		#local dome_max = 6;
		#local dome_cnt = 0;
		#while (dome_cnt < dome_max)
			union
			{
				object
				{
					dome_group
					translate +y * truss_radius
				}
				object
				{
					fuel_tank(tank_length,tank_radius)
					rotate +y * 90
					translate +z * tank_radius
					translate -y * (tank_radius + agridome_ringrad)
				}
				object
				{
					fuel_tank(tank_length,tank_radius)
					rotate +y * 90
					translate -z * tank_radius
					translate -y * (tank_radius + agridome_ringrad)
				}
	//			translate -y * agridome_ringrad
				rotate +z * 360/dome_max * dome_cnt
				texture {white_metal_texture}
			}
			#local dome_cnt = dome_cnt + 1;
		#end
	#end
	#debug "\n<<<<Finish truss array domes\n"


	//------------------------------------------------------------------------------solar panels

	#debug "\n>>>>Start truss array solar panels\n"
	#if (!NoPanels)
		#local panel_radius = agridome_ringrad + Meters * 32;
		#local panel_circum = panel_radius * 2 * pi;
		#local panel_length_angle = panel_length/panel_circum * 360;
		#local panel_gap_angle = panel_gap/2/panel_circum * 360;
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
		#local solar_panel_texture = texture
		{
			#switch (TexQual)
				#case (-1)
					pigment {lowqual_pig(Seed)}
				#break
				#case (0)
					pigment {solar_panel_pigment_2}
					translate +y * panel_width/16
					translate +z * panel_width/8
				#break
				#case (1)
				#case (2)
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
				#break
			#end
		}
		#local solar_blinky = object
		{
			blinky_sphere(blinky_radius)
			translate +y * panel_radius
		}
		#local solar_panel = union
		{
			difference
			{
				cylinder {-z*panel_width/2,+z*panel_width/2,panel_radius}
				cylinder {-z*panel_width/1,+z*panel_width/1,panel_radius-panel_thick}
				plane {+x, 0    rotate -z * (panel_gap_angle)}
				plane {-x, 0    rotate -z * (panel_gap_angle + panel_length_angle)}
				bounded_by {box {<-panel_radius,-panel_radius,-panel_width/2>, <+panel_radius,+panel_radius,+panel_width/2>}}
			}
			// there are simply too many of these blinkies
//			object {solar_blinky    translate -z*panel_width/2    rotate -z * (panel_gap_angle)}
//			object {solar_blinky    translate -z*panel_width/2    rotate -z * (panel_gap_angle + panel_length_angle)}
//			object {solar_blinky    translate +z*panel_width/2    rotate -z * (panel_gap_angle)}
//			object {solar_blinky    translate +z*panel_width/2    rotate -z * (panel_gap_angle + panel_length_angle)}
			texture {solar_panel_texture}
		}
		#local solar_group = union
		{
			#local panel_cnt = 0;
			#while (panel_cnt < panel_number)
				object {solar_panel    translate -z * (panel_width + panel_gap) * panel_cnt}
				#local panel_cnt = panel_cnt + 1;
			#end
			translate +z * (panel_width + panel_gap) * (panel_number-1)/2
		}
		#local solar_array = union
		{
			object {solar_group}
			object {solar_group    rotate +y * 180}
			#declare truss_sides = sml_truss_sides;
			#declare truss_sections = panel_number * 8;
			#declare truss_radius = sml_truss_radius;
			#declare truss_thickness = sml_truss_thick;
			#declare truss_point1 = -z * (panel_width + panel_gap) * (panel_number)/2;
			#declare truss_point2 = +z * (panel_width + panel_gap) * (panel_number)/2;
			object
			{
				#include "truss.inc"
				translate +y * panel_radius
				texture {white_metal_texture}
			}
			object {solar_blinky    translate truss_point1}
			object {solar_blinky    translate truss_point2}
		}
		#local truss_arms_max = 6;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			object
			{
				solar_array
				rotate +z * (360/truss_arms_max * truss_arms_cnt + 30)
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
	#end
	#debug "\n<<<<Finish truss array solar panels\n"


	//------------------------------------------------------------------------------Central hub

	#debug "\n>>>>Start truss array central hub\n"
	union
	{
		difference
		{
			cylinder {+z * Meters * 16, -z * Meters * 16, main_body_radius + Meters * 8}
			cylinder {+z * Meters * 17, -z * Meters * 17, main_body_radius + Meters * 2}
			bounded_by {box {<+main_body_radius + Meters * 8,+main_body_radius + Meters * 8,+Meters * 16>, <-main_body_radius + Meters * 8,-main_body_radius + Meters * 8,-Meters * 16>}}
		}
		difference
		{
			cylinder {+z * Meters * 16, -z * Meters * 16, main_body_radius}
			cylinder {+z * Meters * 17, -z * Meters * 17, main_body_radius - main_strut_radius * 2}
			bounded_by {box {<+main_body_radius,+main_body_radius,+Meters * 16>, <-main_body_radius,-main_body_radius,-Meters * 16>}}

		}
		texture {white_metal_texture}
	}
	#debug "\n<<<<Finish truss array central hub\n"

	translate -z * (trusshub_start + trusshub_length/2)
}
