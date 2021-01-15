// Truss Example Scene Description File
// File: spaceshp.pov
// Vers: 3
// Desc:
// Date:
// Auth: Theran Cochran

#declare radius_mod = 1/2;

//#declare camera_location	= <0, 200, -500>;
#declare camera_location	= <0, -100, -500>;
#declare camera_look_at		= <0, -100, 0>;
#declare camera_angle		= 40;
#declare flare_position		= <20, 30, -60>*100;

#include "colors.inc"
#include "textures.inc"
#include "metals.inc"
#include "skies.inc"
#include "stones.inc"
#include "woods.inc"

#ifndef (Included)
	//#include "lensflar.inc"
	light_source { flare_position color rgb 1.5 }
	
	global_settings { assumed_gamma 1.5 }
	camera {
		orthographic
		location camera_location
		look_at camera_look_at
		angle camera_angle
	}
#end

#declare metal1 = texture { T_Chrome_3A }

union { //Habitat area
	union {
		sphere { 0, 30 clipped_by { box { <-30.1, 0, -30.1>, <30.1, 30.1, 30.1> } } scale <1, .75, 1> }
		sphere { 0, 30 clipped_by { box { <-30.1, -30.1, -30.1>, <30.1, 0, 30.1> } } }
		texture {
			pigment {
				gradient y
				scale 60
				translate -y*30
				pigment_map {
					[.55 bozo turbulence 2 scale <.3, 10, .3> color_map { [0 Gray95][.5 Gray95][1 Gray75]}]
					[.55 bozo turbulence 2 scale <.3, 10, .3> color_map { [0 Gray60][.5 Gray60][1 Gray40]}]
					[.7  bozo turbulence 2 scale <.3, 10, .3> color_map { [0 Gray60][.5 Gray60][1 Gray40]}]
					[.7  bozo turbulence 2 scale <.3, 10, .3> color_map { [0 Gray95][.5 Gray95][1 Gray75]}]
					[.85 bozo turbulence 2 scale <.3, 10, .3> color_map { [0 Gray95][.5 Gray95][1 Gray75]}]
					[.85 Scarlet]
				}
			}
		}
	}

	cylinder { -y*60, -y*30, 5
		pigment { bozo turbulence 2 scale <10, 300, 10> color_map { [0 Gray95][1 Gray75]}}
	}


	#declare truss_point1 = <0, -2, 0>;
	#declare truss_point2 = <0, -80, 0>;
	#declare truss_radius1 = 31;
	#declare truss_radius2 = 10;
	#declare truss_thickness = .5 * radius_mod;
	#declare truss_sides = 12;
	#declare truss_sections = 6;
	#declare truss_type = 3;
	object {
		#include "truss_c.inc"
		texture { metal1 }
	}

	#declare tor_y = -45;
	#declare tor_t = 8;
	#declare tor_r = abs((truss_radius1 - truss_radius2) / _TG_length * (truss_point1.y - tor_y + truss_point2.y))+truss_radius2 + tor_t;
	torus { tor_r, tor_t translate y*tor_y
		pigment { bozo turbulence 2 scale <10, 300, 10> color_map { [0 Gray95][1 Gray75]}}
	}
	#declare tor_t = 12;
	#declare tor_y = (tor_y - 9 - tor_t);
	#declare tor_r = abs((truss_radius1 - truss_radius2) / _TG_length * (truss_point1.y - tor_y + truss_point2.y))+truss_radius2 + tor_t;
	torus { tor_r, tor_t translate y*tor_y
		pigment { bozo turbulence 2 scale <10, 300, 10> color_map { [0 Gray95][1 Gray75]}}
	}
	translate y*30
}

#declare connector = union {
	#declare ctr1 = y*(tor_y + 30);
	#declare ctr2 = <35, -82.5, 0>;
	#declare rad1 = tor_r + tor_t +.5;
	#declare rad2 = 13.75;
	#declare ang1 = 60;
	#declare ang2 = 120;
	#declare rot1 = -22.5;
	#declare rot2 = -60;
	#declare sides = 3;

	#declare truss_sections = 3;

	#declare truss_pointb1 = vrotate(x * rad1, y*rot1)+ctr1;
	#declare truss_pointb2 = vrotate(x * rad2, y*rot2)+ctr2;

	cylinder { truss_pointb1, truss_pointb2, truss_thickness }

	#declare foo = 1;
	#while(foo <= sides)
		#declare truss_pointa1 = truss_pointb1;
		#declare truss_pointa2 = truss_pointb2;
		#declare truss_pointb1 = vrotate(x * rad1, y*(ang1*foo/sides+rot1))+ctr1;
		#declare truss_pointb2 = vrotate(x * rad2, y*(ang2*foo/sides+rot2))+ctr2;
		cylinder { truss_pointb1, truss_pointb2, truss_thickness }
		#include "truss_s.inc"
		#declare foo = foo + 1;
	#end

	texture { metal1 }
}


#declare engine = union { //Engine and tanks
	sphere { 0, 12.5
		pigment { color srgb 1 }
		finish { specular .5 }
	}
	union {
		sphere { 0, 12.5 }
		cylinder { 0, -y*50, 12.5 }
		sphere { -y*50, 12.5 }
		translate -y*25
		pigment { color srgb 1 }
		finish { specular .5 }
	}

	#declare truss_point1 = <0, 12.5, 0>;
	#declare truss_point2 = <0, -82.5, 0>;
	#declare truss_radius = 13;
	#declare truss_sides = 3;
	#declare truss_sections = 10;
	#declare truss_angle = 120;
	#declare truss_rotate = -60;
	#declare truss_type = 4;
	object {
		#include "truss.inc"
		texture { metal1 }
	}

	#declare truss_point1 = <0, -85, 0>;
	#declare truss_point2 = <0, -95, 0>;
	#declare truss_radius1 = 7.5;
	#declare truss_radius2 = 12.5;
	#declare truss_sides = 9;
	#declare truss_sections = 4;
	#declare truss_angle = 360;
	#declare truss_rotate = -60;
	object {
		#include "truss_c.inc"
		texture { metal1 }
	}

	#declare truss_point2 = (truss_point1 - truss_point2) / 4 * 3 + truss_point2;
	#declare truss_point1 = -y*82.5;
	#declare truss_radius1 = 12.5;
	#declare truss_radius2 = 8.125;
	#declare truss_rings = false;
	#declare truss_sides = 9;
	#declare truss_sections = 1;
	#declare truss_type = 3;
	object {
		#include "truss_c.inc"
		texture { metal1 }
	}
}

union {
	cylinder { -y*70, -y*175, 22.5 }
	cone { -y*50, 10, -y*70, 22.5 }
	pigment { bozo turbulence 2 scale <10, 300, 10> color_map { [0 Gray95][1 Gray75]}}
}


object { engine translate <35, -95, 0> }
object { engine translate <35, -95, 0> rotate y*60 }
object { engine translate <35, -95, 0> rotate y*120 }
object { engine translate <35, -95, 0> rotate y*180 }
object { engine translate <35, -95, 0> rotate y*-60 }
object { engine translate <35, -95, 0> rotate y*-120 }

object { connector }
object { connector rotate y*60 }
object { connector rotate y*120 }
object { connector rotate y*180 }
object { connector rotate y*-60 }
object { connector rotate y*-120 }


//-------------------------------------------------------------------------

#local exhaust_scale		= 10;

#ifndef (Exhaust_Object)
	#include "gh_rocket_chess_exhaust.inc"
#end

#local fixed_exhaust = object
{
	Exhaust_Object
	rotate		-z * 90
	scale		<5,4,5>
}

object { fixed_exhaust translate <35, -95*2, 0> rotate y*+000 }
object { fixed_exhaust translate <35, -95*2, 0> rotate y*+060 }
object { fixed_exhaust translate <35, -95*2, 0> rotate y*+120 }
object { fixed_exhaust translate <35, -95*2, 0> rotate y*+180 }
object { fixed_exhaust translate <35, -95*2, 0> rotate y*+240 }
object { fixed_exhaust translate <35, -95*2, 0> rotate y*+300 }
