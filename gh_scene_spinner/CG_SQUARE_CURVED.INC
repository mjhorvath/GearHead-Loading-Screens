#include "glass.inc"
#include "golds.inc"
verbose_include("keplerpoinsot_solids.inc", defined(KeplerPoinsot_small_stellated_dodecahedron_edges))
verbose_include("platonic_solids.inc", defined(Platonic_icosahedron_edges))


//------------------------------------------------------------------------------

#declare building_macros[building_types] = "Public_Square_1";	// reflecting pool
#declare building_chance[building_types] = 1/8;
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Public_Square_2";	// from radiosity scene
#declare building_chance[building_types] = 1/16;
#declare building_types = building_types + 1;


//------------------------------------------------------------------------------

#macro pos_bill_solid(in_obj1, in_obj2)
	#local ext_min		= min_extent(in_obj1);
	#local ext_max		= max_extent(in_obj1);
	#local ext_box		= ext_max - ext_min;
	#local ext_nrm		= vnormalize(ext_box);
	union
	{
//		object {in_obj1}
		object {in_obj2}
		translate	-ext_min
		scale		1/ext_box
		translate	-1/2
		scale		ext_nrm * 2
		scale		6
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}
#end


//------------------------------------------------------------------------------

// reflecting pool
#macro Public_Square_1(Size, Direction, Translate)
	#if (square_deco_number < 1)
		debug_detail("CG...............Value of square_deco_number is 0, switching to a different object.\n")
		Public_Square_2(Size, Direction, Translate)
		#break
	#end
	debug_detail("CG...............Adding Public_Square_1.\n")
	#local building_size	= <32, 32, 32>;
	#local Scale		= <Size.x/building_size.x,Size.x/building_size.y,Size.z/building_size.z>;
	#switch (TexQual)
		#case (-2)
			#local Tex_1 = texture {};
			#local Tex_2 = texture {};
			#local Mat_1 = material {};
		#break
		#case (-1)
			#local Tex_1 = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local Tex_2 = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local Mat_1 = material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local Tex_1 = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
			}
			#local Tex_2 = texture
			{
				pigment {gamma_color_adjust(<0,0,0,0,0> + P_Gold3)}
			}
			#local Mat_1 = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0.4,0.4,0.4,0.0,0.0>)}
				}
			}
		#break
		#case (1)
			#local Tex_1 = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				finish
				{
					ambient		0.0
					diffuse		0.6
					specular	0.1
				}
				scale Meters
			}
			#local Tex_2 = texture
			{
				pigment {gamma_color_adjust(<0,0,0,0,0> + P_Gold3)}
				finish
				{
					brilliance	6
					diffuse		D_GoldE
					ambient		A_GoldE
					reflection	R_GoldE
					metallic	M
					specular	0.80
					roughness	1/120
				}
				normal {bumps .01	scale .01}
				scale Meters
			}
			#local Mat_1 = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0.4,0.4,0.4,0.0,0.0>)}
					normal {wrinkles	scale 0.1}
					finish {F_Glass5}
				}
				scale Meters
			}
		#break
		#case (2)
			#local Tex_1 = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				finish
				{
					ambient 0.0
					diffuse 0.6
					specular 0.1
				}
				scale Meters
			}
			#local Tex_2 = texture
			{
				pigment {gamma_color_adjust(<0,0,0,0,0> + P_Gold3)}
				finish
				{
					brilliance	6
					diffuse		D_GoldE
					ambient		A_GoldE
					reflection	R_GoldE
					metallic	M
					specular	0.80
					roughness	1/120
				}
				normal {bumps .01	scale .01}
				scale Meters
			}
			#local Mat_1 = material
			{
				interior {I_Glass_Dispersion1}
				texture
				{
					pigment {gamma_color_adjust(<0.8,0.8,1.0,0.0,0.5>)}
					normal {wrinkles	scale 0.1}
					finish {F_Glass5}
				}
				scale Meters
			}
		#break
	#end
	#local final_object = union
	{
		#local EdgeT	= texture {};
		#local VertT	= texture {};
		#local R_Vertex	= 1/8;
		#local R_Edge	= R_Vertex/2;
		debug_detail(concat("square_deco_number # = ",str(square_deco_number,0,0),"\n"))
		#switch (square_deco_number)
			#case (1)
				#local obj1 = object {KeplerPoinsot_small_stellated_dodecahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)};
				#local obj2 = object {KeplerPoinsot_small_stellated_dodecahedron_faces2(no)};
			#break
			#case (2)
				#local obj1 = object {KeplerPoinsot_great_dodecahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)};
				#local obj2 = object {KeplerPoinsot_great_dodecahedron_faces2(no)};
			#break
			#case (3)
				#local obj1 = object {KeplerPoinsot_great_stellated_dodecahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)};
				#local obj2 = object {KeplerPoinsot_great_stellated_dodecahedron_faces2(no)};
			#break
			#case (4)
				#local obj1 = object {KeplerPoinsot_great_icosahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)};
				#local obj2 = object {KeplerPoinsot_great_icosahedron_faces2(no)};
			#break
			#case (5)
				#local obj1 = object {Platonic_tetrahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)}
				#local obj2 = object {Platonic_tetrahedron_faces2(no)}
			#break
			#case (6)
				#local obj1 = object {Platonic_cube_edges(R_Edge, R_Vertex, EdgeT, VertT, no)}
				#local obj2 = object {Platonic_cube_faces2(no)}
			#break
			#case (7)
				#local obj1 = object {Platonic_octahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)}
				#local obj2 = object {Platonic_octahedron_faces2(no)}
			#break
			#case (8)
				#local obj1 = object {Platonic_dodecahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)}
				#local obj2 = object {Platonic_dodecahedron_faces2(no)}
			#break
			#case (9)
				#local obj1 = object {Platonic_icosahedron_edges(R_Edge, R_Vertex, EdgeT, VertT, no)}
				#local obj2 = object {Platonic_icosahedron_faces2(no)}
			#break
		#end
		object
		{
			pos_bill_solid(obj1, obj2)
			translate <0,5,0>
			scale Scale
			texture {Tex_2}
		}
		object
		{
			con_macro(<0,0,0,> * Scale, 2/4 * Scale.x, <0,4,0,> * Scale, 1/4 * Scale.x)
			texture {Tex_2}
		}
		// low basin
		difference
		{
			object {cyl_box(<-13,0/8,-13,> * Scale, <+13,3/8,+13,> * Scale)}
			object {cyl_box(<-12,1/8,-12,> * Scale, <+12,4/8,+12,> * Scale)}
			// bounding may not help here
//			bounded_by {cyl_box_bound(<-13,0/8,-13,> * Scale, <+13,3/8,+13,> * Scale)}
			texture {Tex_1}
		}
		object
		{
			cyl_box(<-11.9999,1/8 + 0.0001,-11.9999,> * Scale, <+11.9999,2/8,+11.9999,> * Scale)
			#if (glass_hollow)	hollow		#end
			material {Mat_1}
		}
		// high basin
		difference
		{
			object {cyl_box(<-7,2/8,-7,> * Scale, <+7,5/8,+7,> * Scale)}
			object {cyl_box(<-6,3/8,-6,> * Scale, <+6,6/8,+6,> * Scale)}
			// bounding may not help here
//			bounded_by {cyl_box_bound(<-7,2/8,-7,> * Scale, <+7,5/8,+7,> * Scale)}
			texture {Tex_1}
		}
		object
		{
			cyl_box(<-5.9999,3/8 + 0.0001,-5.9999,> * Scale, <+5.9999,4/8,+5.9999,> * Scale)
			#if (glass_hollow)	hollow	#end
			material {Mat_1}
		}
		// corner posts
		union
		{
			object {cyl_box(<-7,0,-7,> * Scale, <-6,3,-6,> * Scale)}
			object {cyl_box(<-7,0,+6,> * Scale, <-6,3,+7,> * Scale)}
			object {cyl_box(<+6,0,+6,> * Scale, <+7,3,+7,> * Scale)}
			object {cyl_box(<+6,0,-7,> * Scale, <+7,3,-6,> * Scale)}
			texture {Tex_1}
		}
	}
	#declare square_deco_number = square_deco_number - 1;
//	#declare square_deco_number = floor(rand(_CT_rand4) * square_deco_max) + 1;
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 5;
	#for (person_count, 0, person_total-1)
		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*32-16,0,+(14+rand(_CT_rand2)*2)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*32-16,0,-(14+rand(_CT_rand2)*2)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <+(14+rand(_CT_rand2)*2),0,rand(_CT_rand2)*32-16> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <-(14+rand(_CT_rand2)*2),0,rand(_CT_rand2)*32-16> * Scale)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi;
		#local trash_point = <15*cos(trash_theta),0,15*sin(trash_theta)> * Scale;
		// not scaled properly. needs to be fixed
//		object {pos_object(trash_can_macro(), Translate + trash_point)}
	#end
#end


//------------------------------------------------------------------------------

// from radiosity scene
#macro Public_Square_2(Size, Direction, Translate)
	debug_detail("CG...............Adding Public_Square_2.\n")
	#local building_size	= <24, 3, 24>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local door_radius	= 4/4*city_storey_height;
	#switch (TexQual)
		#case (-2)
			#local Tex_1 = texture {};
		#break
		#case (-1)
			#local Tex_1 = texture {pigment {lowqual_pig(_CT_rand5)}};
		#break
		#case (0)
			#local Tex_1 = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
			}
		#break
		#case (1)
		#case (2)
			#local Tex_1 = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				finish
				{
					ambient 0.0
					diffuse 0.6
					specular 0.1
				}
				normal {bumps .05 scale .1}
				scale Meters
			}
		#break
	#end
	// should really be cones due to curvature
	#local Column_Block = union
	{
		#local Cnt = 0;
		#while (Cnt < 8.8)
			object {cyl_macro(<4.4, 0.2, 4.4-Cnt>, <4.4, 3.6, 4.4-Cnt>, 0.2)}
			#local Cnt = Cnt  + (8.8/3);
		#end
		scale Scale
	}
	#local Columns = union
	{
		object {object {Column_Block             }}
		object {object {Column_Block rotate 090*y}}
		object {object {Column_Block rotate 180*y}}
		object {object {Column_Block rotate 270*y}}
	}
	#local Door1 = object
	{
		cyl_macro(<0,0,-12>*Scale, <0,0,+12>*Scale, door_radius)
	}
	// no mesh macro for torus!!!
	#local Door2 = torus
	{
		city_radius*Scale.y, door_radius
		rotate		x * 90
		translate	y * city_radius
	}
	#local Walls = difference
	{
		object {cyl_box(<-10, 0.0, -10> * Scale, <+10, 4.0, +10> * Scale)}
		object {cyl_box(< -9, 0.3,  -9> * Scale, < +9, 3.5,  +9> * Scale)}
		object {cyl_box(< -8, 0.1,  -8> * Scale, < +8, 5.0,  +8> * Scale)}
		intersection
		{
			union
			{
				object {Door1}
				object {Door2}
			}
			object {cyl_box(<-12, 0.3, -12> * Scale, <+12, 4.3, +12> * Scale)}
			// bounding may not help here
			bounded_by {cyl_box_bound(<-12, 0.3, -12> * Scale, <+12, 4.3, +12> * Scale)}
		}
		bounded_by {cyl_box_bound(<-10, 0.0, -10> * Scale, <+10, 4.0, +10> * Scale)}
	}
	#local Col_Base = difference
	{
		object {cyl_box(<-4.8,    0, -4.8> * Scale, <4.8, +3.6, +4.8> * Scale)}
		object {cyl_box(<-4.0, -0.1, -4.0> * Scale, <+4.0, 4.0, +4.0> * Scale)}
		object {cyl_box(<-5.0,  0.5, -5.0> * Scale, <+5.0, 3.3, +5.0> * Scale)}
		// bounding may not help here
		bounded_by {cyl_box_bound(<-4.8,    0, -4.8> * Scale, <4.8, +3.6, +4.8> * Scale)}
	}
	#local final_object = union
	{
		object {Walls}
		object {Columns}
		object {Col_Base}
		texture {Tex_1}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 5;
	#for (person_count, 0, person_total-1)
		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*24-12,0,+(10+rand(_CT_rand2)*2)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*24-12,0,-(10+rand(_CT_rand2)*2)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <+(10+rand(_CT_rand2)*2),0,rand(_CT_rand2)*24-12> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <-(10+rand(_CT_rand2)*2),0,rand(_CT_rand2)*24-12> * Scale)}

		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*13-6.5,0,+(5+rand(_CT_rand2)*3)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*13-6.5,0,-(5+rand(_CT_rand2)*3)> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <+(5+rand(_CT_rand2)*3),0,rand(_CT_rand2)*13-6.5> * Scale)}
		object {pos_object(ped_macro(_CT_rand2), Translate + <-(5+rand(_CT_rand2)*3),0,rand(_CT_rand2)*13-6.5> * Scale)}

		object {pos_object(ped_macro(_CT_rand2), Translate + <rand(_CT_rand2)*8-4,0,rand(_CT_rand2)*8-4> * Scale)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi;
		#local trash_point = <11*cos(trash_theta),0,11*sin(trash_theta)> * Scale;
		// not scaled properly. needs to be fixed
//		object {pos_object(trash_can_macro(), Translate + trash_point)}
	#end
#end
