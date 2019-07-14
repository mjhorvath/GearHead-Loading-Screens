union
{
	#declare truss_sides = 3;
	#declare truss_sections = 16;
	#declare truss_thickness = Meters * 2;
	#declare truss_radius = Meters * 16;
	#declare truss_point1 = 0;
	#declare truss_point2 = +x * agridome_ringrad;
	union
	{
		#local truss_arms_max = 6;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			object
			{
				#include "truss.inc"
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		texture {white_metal_texture}
	}

	#local segment_number = 12;
	#local segment_distance = sind(360/segment_number/2) * agridome_ringrad;
	#declare truss_sides = 3;
	#declare truss_sections = 8;
	#declare truss_thickness = Meters * 2;
	#declare truss_radius = Meters * 16;
	#declare truss_point1 = -y * segment_distance;
	#declare truss_point2 = +y * segment_distance;
	union
	{
		#local truss_arms_max = segment_number;
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

	#include "gh_dome_ring.inc"
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
				translate -y * (tank_radius)
			}
			object
			{
				fuel_tank(tank_length,tank_radius)
				rotate +y * 90
				translate -z * tank_radius
				translate -y * (tank_radius)
			}
			translate -y * agridome_ringrad
			rotate +z * 360/dome_max * dome_cnt
			texture {white_metal_texture}
		}
		#local dome_cnt = dome_cnt + 1;
	#end

	#declare solar_array = union
	{
		#declare truss_sides = mini_truss_sides;
		#declare truss_radius = mini_truss_radius;
		#declare truss_thickness = mini_truss_thick;
		#declare truss_point1 = 0;
		#declare truss_point2 = +x * (panel_width + panel_gap) * (panel_number + 0);
//		#declare truss_sections = VDist(truss_point1, truss_point2) / mini_truss_section_size;
		#declare truss_sections = 4;
		#local solar_truss1 = object
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
					translate +y * panel_width/16
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
					finish {Glossy}
					translate +y * panel_width/16
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
			object {solar_group rotate +y * 90 rotate +z * 90}
			object {solar_group rotate -y * 90 rotate +z * 90}
			translate +x * (agridome_ringrad + mini_truss_radius)
		}
	}
	object {solar_array	rotate -z * 000}
	object {solar_array rotate -z * 060}
	object {solar_array rotate -z * 120}
	object {solar_array rotate -z * 180}
	object {solar_array rotate -z * 240}
	object {solar_array rotate -z * 300}
	translate -z * (habitat_length/2 + trusshub_length/2)
}
