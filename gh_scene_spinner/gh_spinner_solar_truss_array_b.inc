#local truss_length = city_units * 1024;
#declare truss_array = union
{
	#include "gh_dome_group.inc"
	object
	{
		dome_group
		translate +x * (outer_shell_radius1 + truss_length/2)
		translate +y * mini_truss_radius
	}
	#declare truss_sides = mini_truss_sides;
	#declare truss_radius = mini_truss_radius;
	#declare truss_thickness = mini_truss_thick;
	#declare truss_point1 = 0;
	#declare truss_point2 = +x * (panel_width + panel_gap) * (panel_number + 0);
	#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
	#local solar_truss1 = object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
	#declare truss_sides = mini_truss_sides;
	#declare truss_radius = mini_truss_radius;
	#declare truss_thickness = mini_truss_thick;
	#declare truss_point1 = -z * (panel_length * 2 + mini_truss_radius);
	#declare truss_point2 = +z * (panel_length * 2 + mini_truss_radius);
	#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
	#local solar_truss2 = object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
	#local solar_panel_texture = texture
	{
		#switch (TexQual)
			#case (-1)
				lowqual_pig(Seed)
			#break
			#case (0)
				pigment
				{
					brick gamma_color_adjust(0/4*<1,1,1>), gamma_color_adjust(1/4*<1,1,1>)
					brick_size panel_width/4
					mortar panel_mortar
				}
				translate +z * panel_width/8
			#break
			#case (1)
			#case (2)
				pigment
				{
					brick gamma_color_adjust(0/4*<1,1,1>), gamma_color_adjust(1/4*<1,1,1>)
					brick_size panel_width/4
					mortar panel_mortar
				}
//				finish {Glossy}
				finish
				{
					reflection
					{
						gamma_color_adjust(<0.722,0.451,0.200>)
						fresnel   0
						falloff   0.000
						exponent  1.000
						metallic  0.500
					} 
				}
				translate +z * panel_width/8
			#break
		#end
	}
	#local solar_panel = union
	{
		box
		{
			<-panel_width/2,-panel_thick/2,-panel_length/2>,
			<+panel_width/2,+panel_thick/2,+panel_length/2>
			texture {solar_panel_texture}
		}
		object {blinky_sphere	translate <-panel_width/2,0,-panel_length/2>}
		object {blinky_sphere	translate <-panel_width/2,0,+panel_length/2>}
		object {blinky_sphere	translate <+panel_width/2,0,-panel_length/2>}
		object {blinky_sphere	translate <+panel_width/2,0,+panel_length/2>}
	}
	#local solar_group = union
	{
		#local panels_max = panel_number;
		#local panels_cnt = 0;
		#while (panels_cnt < panels_max)
			union
			{
				object {solar_panel	translate -z*(panel_length/2+mini_truss_radius)}
				object {solar_panel	translate +z*(panel_length/2+mini_truss_radius)}
				translate +x * ((panel_width + panel_gap) * panels_cnt + panel_width/2 + panel_gap)
			}
			#local panels_cnt = panels_cnt + 1;
		#end
		object {solar_truss1}
	}
	union
	{
		object {solar_group rotate +y * 90}
		object {solar_group rotate -y * 90}
		translate +x * (outer_shell_radius1 + mini_truss_radius + truss_length)
	}
	#declare truss_sides = mini_truss_sides;
	#declare truss_radius = mini_truss_radius;
	#declare truss_thickness = mini_truss_thick;
	#declare truss_point1 = +x * outer_shell_radius1;
	#declare truss_point2 = +x * (outer_shell_radius1 + truss_length - mini_truss_radius);
	#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
	object
	{
		#include "truss.inc"
		texture {white_metal_texture}
	}
	rotate +x * 90
}

union
{
	object
	{
		truss_array
		rotate -z * 030
	}
	object
	{
		truss_array
		rotate -z * 090
	}
	object
	{
		truss_array
		rotate -z * 150
	}
}
