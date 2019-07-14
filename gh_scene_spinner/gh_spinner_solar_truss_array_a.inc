#declare truss_array = union
{
	#if (!NoDomes)
		#include "gh_dome_group.inc"
		object
		{
			dome_group
			translate +x * city_units * 1024
			translate +y * mini_truss_radius
		}
	#end

	#if (!NoPanels)
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
						brick_size city_units * 16
						mortar city_units * 1
					}
					translate -city_units/4
					translate +z*city_units * 8
				#break
				#case (1)
				#case (2)
					pigment
					{
						brick gamma_color_adjust(0/4*<1,1,1>), gamma_color_adjust(1/4*<1,1,1>)
						brick_size city_units * 16
						mortar city_units * 1
					}
					finish {Glossy}
					translate -city_units/4
					translate +z*city_units * 8
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
		#macro solar_group(solar_deg_x, solar_deg_z, solar_dis_z)
			union
			{
				#local panels_max = panel_number;
				#local panels_cnt = 0;
				#while (panels_cnt < panels_max)
					union
					{
						object {solar_panel	translate -z*(panel_length/2+panel_gap/2)}
						object {solar_panel	translate +z*(panel_length/2+panel_gap/2)}
						translate x * (panel_width/2 + (panel_width + panel_gap) * (panels_cnt + 0))
					}
					#local panels_cnt = panels_cnt + 1;
				#end
				object {solar_truss1}
				translate +x * (outer_shell_radius1 + mini_truss_radius)
			}
		#end
		object {solar_group(+panel_rotate, 000, 0) translate +z * panel_length * 2}
		object {solar_group(+panel_rotate, 000, 0) translate -z * panel_length * 2}
		object {solar_truss2 translate +x * outer_shell_radius1}
		object {solar_truss1 translate +x * (outer_shell_radius1 + mini_truss_radius)}
	#end
	translate +x * panel_width
}

#declare truss_sides = mini_truss_sides;
#declare truss_radius = mini_truss_radius;
#declare truss_thickness = mini_truss_thick;
#declare truss_point1 = +x * outer_shell_radius1;
#declare truss_point2 = +x * (outer_shell_radius1 + panel_width - mini_truss_radius);
#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
object
{
	#include "truss.inc"
	texture {white_metal_texture}
	rotate +x * panel_rotate
}
object
{
	#include "truss.inc"
	texture {white_metal_texture}
	rotate +y * 180
	rotate +x * panel_rotate
}
object
{
	truss_array
	rotate +x * panel_rotate
}
object
{
	truss_array
	rotate +y * 180
	rotate +x * panel_rotate
}
