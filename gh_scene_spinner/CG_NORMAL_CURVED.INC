// need a global glass_thick variable
// make sure glass_hollow and glass_thin are OK. should make an object hollow using the keyword or CSG, but not both. check if the gold star is set up this way.
// normals of OFFICE BUILDING #7 look really messed up

#version 3.7

#include "glass.inc"
#include "golds.inc"


//------------------------------------------------------------------------------

#declare building_macros[building_types] = "Office_Building_1";		// OFFICE BUILDING #1 - shiny cube
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_2";		// OFFICE BUILDING #2 - white lozenges
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_3";		// OFFICE BUILDING #3 - black padogas
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_4";		// OFFICE BUILDING #4 - gold star
#declare building_chance[building_types] = 1;				// 1/2
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_5";		// OFFICE BUILDING #5 - pink box scatter
#declare building_chance[building_types] = 1;				// 3/4
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_6";		// OFFICE BUILDING #6 - green cylinders
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_7";		// OFFICE BUILDING #7 - tapered helix
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Office_Building_8";		// OFFICE BUILDING #8 - blocky helix
#declare building_chance[building_types] = 1;				// 1
#declare building_types = building_types + 1;


//------------------------------------------------------------------------------1

// OFFICE BUILDING #1 - shiny cube
#macro Office_Building_1(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_1.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <2, .5, 2>;	//<2, .5, 2>
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#switch (TexQual)
		#case (-1)
			#local main_tex		= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<.4,.4,.4>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<.5,.5,.5>) filter 0 transmit 1/2}
				}
			}
		#break
		#case (1)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<.4,.4,.4>)}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<.5,.5,.5>) filter 0 transmit 1/2}
					normal {bumps .05 scale .1}
					finish {specular .5 roughness .1 reflection <.3, .4, .5>}
				}
				scale Meters
			}
		#break
		#case (2)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<.4,.4,.4>)}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<223,230,255>/255) filter 0 transmit .5}
					normal {bumps .05 scale .1}
					finish {specular .5 roughness .1 reflection <.3, .4, .5>}
				}
				scale Meters
			}
		#break
	#end
	#local final_object = difference
	{
		union
		{
			// floors
			#for (Level_Count, 0,  Level_Total - 1)
				#local y_adjust = y * Level_Count * city_storey_height;
				object {cyl_box(<-1.00, -0.01, -1.00> * Scale + y_adjust, <+1.00, +0.01, +1.00> * Scale + y_adjust)}
			#end
			// walls - distance should be according to Meters
			#for (C, -0.75, +0.75, 0.25)
				object {cyl_box(<C-0.01, 0.0,  -1.00> * Scale, <C+0.01, 0.5 * Level_Total,  +1.00> * Scale)}
				object {cyl_box(< -1.00, 0.0, C-0.01> * Scale, < +1.00, 0.5 * Level_Total, C+0.01> * Scale)}
			#end
			// glass
			#if (glass_thin)
				difference
				{
					object {cyl_box(<-0.999, 0.00, -0.999> * Scale, <+0.999, 0.5 * Level_Total - 0.001, +0.999> * Scale)}
					object {cyl_box(<-0.989, 0.01, -0.989> * Scale, <+0.989, 0.5 * Level_Total - 0.011, +0.989> * Scale)}
					material {glass_mat}
					// bounding may not help here
//					bounded_by {cyl_box_bound(<-0.999, 0.00, -0.999> * Scale, <+0.999, 0.5 * Level_Total - 0.001, +0.999> * Scale)}
				}
			#else
				object
				{
					cyl_box(<-0.999, 0.00, -0.999> * Scale, <+0.999, 0.5 * Level_Total - 0.001, +0.999> * Scale)
					#if (glass_hollow)	hollow	#end
					material {glass_mat}
				}
			#end
		}
		difference
		{
			object {cyl_box(<-1.01, 0, -1.01> * Scale, <+1.01, 0.5, +1.01> * Scale)}
			object {cyl_box(<-0.75, 0, -0.75> * Scale, <+0.75, 0.5, +0.75> * Scale)}
			// bounding may not help here
//			bounded_by {cyl_box_bound(<-1.01, 0, -1.01> * Scale, <+1.01, 0.5 * Level_Total, +1.01> * Scale)}
		}
		texture {main_tex}
		// bounding may not help here
		bounded_by {cyl_box_bound(<-1.01, 0, -1.01> * Scale, <+1.01, 0.5 * Level_Total, +1.01> * Scale)}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
#end


//------------------------------------------------------------------------------2

// OFFICE BUILDING #2 - white lozenges
#macro Office_Building_2(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_2.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 16, 32>;
	#local Scale		= <Size.x/building_size.x,(Level_Total-0/2)*city_storey_height/building_size.y,Size.z/building_size.z>;		//Size/building_size;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local main_tex		= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local outer_glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
			#local inner_glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
			}
			#local outer_glass_mat = material
			{
				texture
				{
					pigment	{gamma_color_adjust(<1,1,1,0,1>)}
				}
			}
			#local inner_glass_mat = material
			{
				texture
				{
					pigment	{gamma_color_adjust(<1/4,1/4,1/4,0,3/4>)}
				}
			}
		#break
		#case (1)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				scale Meters
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local outer_glass_mat = material
			{
				texture
				{
					pigment	{gamma_color_adjust(<1,1,1,0,1>)}
					finish
					{
						specular	0.8
						roughness	0.001
//						ambient		0
//						diffuse		0
//						reflection {0.01, 0.1}
						reflection {0.001, 0.01}	// try to tone down reflection
						conserve_energy
					}
				}
				scale Meters
			}
			#local inner_glass_mat = material
			{
				texture
				{
					pigment	{gamma_color_adjust(<1/4,1/4,1/4,0,3/4>)}
					finish
					{
						specular	0.8
						roughness	0.001
//						ambient		0
//						diffuse		0
//						reflection {0.01, 0.1}
						reflection {0.001, 0.01}	// try to tone down reflection
						conserve_energy
					}
				}
				scale Meters
			}
		#break
		#case (2)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
				scale Meters
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local outer_glass_mat = material
			{
				interior {I_Glass4}		//I_Glass4
				texture
				{
					pigment	{gamma_color_adjust(<1,1,1,0,1>)}
					finish
					{
						specular	0.8
						roughness	0.001
//						ambient		0
//						diffuse		0
//						reflection {0.01, 0.1}
						reflection {0.001, 0.01}	// try to tone down reflection
						conserve_energy
					}
				}
				scale Meters
			}
			#local inner_glass_mat = material
			{
				interior {I_Glass4}		//I_Glass4
				texture
				{
					pigment	{gamma_color_adjust(<1/4,1/4,1/4,0,3/4>)}
					finish
					{
						specular	0.8
						roughness	0.001
//						ambient		0
//						diffuse		0
//						reflection {0.01, 0.1}
						reflection {0.001, 0.01}	// try to tone down reflection
						conserve_energy
					}
				}
				scale Meters
			}
		#break
	#end
	#local sph_obj1_out = object {sph_macro(0, 16.0)	scale Scale}
	#local sph_obj1_ins = object {sph_macro(0, 16.0 - 0.01)	scale Scale}
	#local sph_obj2_out = object {sph_macro(0, 15.5)	scale Scale}
	#local sph_obj2_ins = object {sph_macro(0, 15.5 - 0.01)	scale Scale}
	#local sph_bnd1 = sphere {0, 16.0	scale Scale}
	#local sph_bnd2 = sphere {0, 15.0	scale Scale}
	#local cyl_bnd1 = cylinder {0, y*16, 16.0/sind(45)	scale Scale}
	#local final_object = union
	{
		// floors and walls
		intersection
		{
			union
			{
				#local floor_thick = 0.1;
				// floors
				#for (Level_Count, 0, Level_Total - 1)
					#local y_adjust = y * Level_Count * city_storey_height;
					#local y_thick = y * floor_thick;
					#local s_star = <-32, 0, -32> * Scale + y_adjust - y_thick;
					#local s_stop = <+32, 0, +32> * Scale + y_adjust + y_thick;
					object {cyl_box(s_star, s_stop)}
				#end
				// radial walls
				#local Section_Total = 6;
				#for (Section_Count, 0, Section_Total-1)
					box
					{
						<-0.1,  -0,  -0>, <+0.1, +16, +16>
						rotate y * Section_Count * 360/Section_Total
						scale Scale
					}
				#end
			}
			object {sph_obj1_out}
			texture {main_tex}
			// bounding may not help here
			bounded_by {sph_bnd1}
		}
		// cylindrical inner glass shells
		union
		{
			#local floor_thick = 0.1;
			#local fudge_factor = 0.95;
			#for (Level_Count, 0, Level_Total - 2)
				intersection
				{
					#local floor_height = Level_Count * city_storey_height;
					#local y_bot = floor_height + floor_thick;
					#local y_top = floor_height - floor_thick + city_storey_height;
					#local lozng_height = Level_Total * city_storey_height;
					#local lozng_radius = 16 * Scale.x;
					#local floor_radius = sin(acos(y_top/lozng_height)) * lozng_radius * fudge_factor;
					#if (glass_thin)
						difference
						{
							cyl_macro(+y * 0, +y * 1000, floor_radius)
							cyl_macro(-y * 1, +y * 1001, floor_radius - 0.01)
							#if (glass_hollow)	hollow	#end
						}
					#else
						object
						{
							cyl_macro(+y * 0, +y * 1000, floor_radius)
							#if (glass_hollow)	hollow	#end
						}
					#end
					#local y_adjust	= y * Level_Count * city_storey_height;
					#local y_plus = y * city_storey_height;
					#local s_star = <-32, 0, -32> * Scale + y_adjust;
					#local s_stop = <+32, 0, +32> * Scale + y_adjust + y_plus;
					object {cyl_box(s_star, s_stop)}
				}
			#end
			material {inner_glass_mat}
		}
/*
		// ellipsoidal outer glass shell
		difference
		{
			#local y_adjust	= y * (Level_Total) * city_storey_height;
			#if (glass_thin)
				difference
				{
					object {sph_obj2_out}
					object {sph_obj2_ins}
					// bounding may not help here
					bounded_by {sph_bnd2}
				}
			#else
				object {sph_obj2_out}
			#end
			object {cyl_box(<-16,   +0, -16> * Scale + y_adjust,	<+16, +0, +16> * Scale + y_adjust * 2)}
			object {cyl_box(<-16, -100, -16> * Scale,		<+16, +0, +16> * Scale)}
			#if (glass_hollow)	hollow	#end
			material {outer_glass_mat}
			bounded_by {sph_bnd2}
		}
*/
		// grass
		difference
		{
			cyl_box(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
			con_macro(y * city_radius, 0, -0.001, 18 * Scale.x)
			texture {grass_tex}
			// bounding may not help here
//			bounded_by {cyl_box_bound(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 20;
	#for (person_count, 0, person_total-1)
		#local person_theta = rand(_CT_rand2)*2*pi;
		#local person_point = <(rand(_CT_rand2)*2.50+16.25) * cos(person_theta), 0, (rand(_CT_rand2)*2.50+16.25) * sin(person_theta)> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi + pi/4;
		#local trash_point = <17*cos(trash_theta),0,17*sin(trash_theta)> * Scale;
		object {pos_object(trash_can_macro(_CT_rand2), Translate + trash_point)}
	#end
#end


//------------------------------------------------------------------------------3

// OFFICE BUILDING #3 - black pagoda
#macro Office_Building_3(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_3.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 4, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local wall_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<.2,.2,.2>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<.0,.0,.0,1/2,0>)}
				}
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
			}
		#break
		#case (1)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<.2,.2,.2>)}
				normal {bumps .01 scale .01}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<.0,.0,.0,1/2,0>)}
					normal {bumps .01	scale .01}
					finish {specular .5	roughness .1	reflection .1}
				}
				scale Meters
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
		#break
		#case (2)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<.2,.2,.2>)}
				normal {bumps .01 scale .01}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<.0,.0,.0,1/2,0>)}
					normal {bumps .01	scale .01}
					finish {specular .5	roughness .1	reflection .1}
				}
				scale Meters
			}
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
		#break
	#end
	// don't scale or translate!!!
	#local cone_obj1 = object {cone {y * city_radius, 0, 0, Size.x/2}}
	#local cone_obj2 = object {cone_obj1	scale 0.9}
	#local cone_obj3a = object {cone_obj1	scale <5/4,1,5/4>}
	#local cone_obj3b = object {cone_obj1	scale <3/4,1,3/4>}
	#local cone_obj4a = object {cone_obj2	scale <5/4,1,5/4>}
	#local cone_obj4b = object {cone_obj2	scale <3/4,1,3/4>}
	#local cone_obj5 = difference
	{
		object {cone_obj3a}
		object {cone_obj3b}
		// bounding may not help here
//		bounded_by {cone_obj3a}
	}
	#local cone_obj6 = difference
	{
		object {cone_obj4a}
		object {cone_obj4b}
		// bounding may not help here
//		bounded_by {cone_obj4a}
	}
	#local final_object = union
	{
		difference
		{
			intersection
			{
				object {cone_obj1}
				union
				{
					// floors
					#for (Level_Count, 0, Level_Total - 1)
						#local y_adjust	= y * (Level_Count+1) * city_storey_height;
						difference
						{
							object {cyl_box(<-16, -4.0, -16> * Scale + y_adjust, <+16, -0.0, +16> * Scale + y_adjust)}
							object {cyl_box(<-17, -3.8, -17> * Scale + y_adjust, <+17, -0.2, +17> * Scale + y_adjust)}
							// bounding may not help here
//							bounded_by {cyl_box_bound(<-16, -4.0, -16> * Scale + y_adjust, <+16, -0.0, +16> * Scale + y_adjust)}
						}
					#end
					// walls
					intersection
					{
						object {cyl_box(<-16, 0, -16> * Scale, <+16, 4 * Level_Total, +16> * Scale)}
						union
						{
							#local Section_Total = 12;
							#for (Section_Count, 0, Section_Total-1)
								box
								{
									<-0.1,         0, -0.0>,
									<+0.1,4 * Level_Total,+16.0>
									scale		Scale
									rotate		y * Section_Count * 360/Section_Total
								}
							#end
						}
						// bounding may not help here
						bounded_by {cyl_box_bound(<-16, 0, -16> * Scale, <+16, 4 * Level_Total, +16> * Scale)}
					}
				}
				// bounding may not help here
				bounded_by {cone_obj1}
			}
			#for (Level_Count, 0, Level_Total - 1)
				#if ((mod(Level_Count,6) = 0) | (Level_Count = 0) | (Level_Count = Level_Total - 1))
					#local y_adjust	= y * (Level_Count+1) * city_storey_height;
					intersection
					{
						object {cone_obj5}
						object {cyl_box(<-16, -4.001, -16> * Scale + y_adjust, <+16, +0.001, +16> * Scale + y_adjust)}
						// bounding may not help here
//						bounded_by {cone_obj5}
					}
				#end
			#end
			texture {wall_texture}
			// bounding may not help here
			bounded_by {cone_obj1}
		}
		// glass
		difference
		{
			intersection
			{
				#if (glass_thin)
					difference
					{
						object {cone_obj2}
						object {cone_obj2 scale 0.99}
						// bounding may not help here
//						bounded_by {cone_obj2}
					}
				#else
					object {cone_obj2}
				#end
				object {cyl_box(<-16, 0.1, -16> * Scale, <+16, 4 * Level_Total - 0.1, +16> * Scale)}
				// bounding may not help here
				bounded_by {cyl_box_bound(<-16, 0.1, -16> * Scale, <+16, 4 * Level_Total - 0.1, +16> * Scale)}
			}
			#for (Level_Count, 0, Level_Total - 1)
				#if ((mod(Level_Count,6) = 0) | (Level_Count = 0) | (Level_Count = Level_Total - 1))
					#local y_adjust	= y * (Level_Count+1) * city_storey_height;
					intersection
					{
						object {cone_obj6}
						object {cyl_box(<-16, -4.002, -16> * Scale + y_adjust, <+16, +0.002, +16> * Scale + y_adjust)}
						// bounding may not help here
//						bounded_by {cone_obj6}
					}
				#end
			#end
			#if (glass_hollow)	hollow	#end
			material {glass_mat}
			// bounding may not help here
			bounded_by {cyl_box_bound(<-16, 0.0, -16> * Scale, <+16, 4.0 * Level_Total, +16> * Scale)}
		}
		// grass
		difference
		{
			cyl_box(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
			con_macro(y * city_radius, 0, y * -0.001, 18 * Scale.x)
			texture {grass_tex}
			// bounding may not help here
//			bounded_by {}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 20;
	#for (person_count, 0, person_total-1)
		#local person_theta = rand(_CT_rand2)*2*pi;
		#local person_point = <(rand(_CT_rand2)*8+12) * cos(person_theta),0,(rand(_CT_rand2)*8+12) * sin(person_theta)> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi + pi/4;
		#local trash_point = <14*cos(trash_theta),0,14*sin(trash_theta)> * Scale;
		object {pos_object(trash_can_macro(_CT_rand2), Translate + trash_point)}
	#end
#end


//------------------------------------------------------------------------------4

// OFFICE BUILDING #4 - gold star
#macro Office_Building_4(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_4.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 4, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#declare P_GoldF = rgb <0,0,0>;
	#declare R_GoldF = P_GoldF * 0.50 + <0.25,0.25,0.25>;
	#declare A_GoldF = P_GoldF * 0.02 + <0.1,0.1,0.1>;
	#declare D_GoldF = 1-(((R_GoldF.red+R_GoldF.green+R_GoldF.blue)/3)
        	           + ((A_GoldF.red+A_GoldF.green+A_GoldF.blue)/3));
	#declare D_GoldF = max(D_GoldF, 0);
	#switch (TexQual)
		#case (-1)
			#local wall_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
			#local base_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<1/2,1/2,1/2>)}
			}
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(P_Gold3) filter 0 transmit 1/4}
				}
			}
			#local base_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,0,0>) filter 0 transmit 1/4}
				}
			}
		#break
		#case (1)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(1/2)}
				scale Meters
			}
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(P_Gold3) filter 0 transmit 1/4}
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
					normal {bumps 0.01	scale 0.01}
				}
				scale Meters
			}
			#local base_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,0,0>) filter 0 transmit 1/4}
					finish
					{
						brilliance	6
						diffuse		D_GoldF
						ambient		A_GoldF
						reflection	R_GoldF
						metallic	M
						specular	0.80
						roughness	1/120
					}
					normal {bumps 0.01	scale 0.01}
				}
				scale Meters
			}
		#break
		#case (2)
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(1/2)}
				scale Meters
			}
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(P_Gold3) filter 0 transmit 1/4}
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
					normal {bumps 0.01	scale 0.01}
				}
				scale Meters
			}
			#local base_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<0,0,0>) filter 0 transmit 1/4}
					finish
					{
						brilliance	6
						diffuse		D_GoldF
						ambient		A_GoldF
						reflection	R_GoldF
						metallic	M
						specular	0.80
						roughness	1/120
					}
					normal {bumps 0.01	scale 0.01}
				}
				scale Meters
			}
		#break
	#end
	// not configured correctly...
	#local glass0_shell = difference
	{
		object {cyl_pyr(<-16.0, +0.0, -16.0> * Scale, <+16.0, +1.0 + 4 * Level_Total, +16.0> * Scale)}
		object {cyl_tiltB(+16.0 * Scale.x, (+1.0 + 4 * Level_Total) * Scale.y, 1, +16.0 * Scale.x)}
	}
	#local glass1_shell = difference
	{
		object {cyl_pyr(<-16.0, +4.0, -16.0> * Scale, <+16.0, +0.0 + 4 * Level_Total, +16.0> * Scale)}
		object {cyl_tiltB(+16.0 * Scale.x, (+0.0 + 4 * Level_Total) * Scale.y, 1, +16.0 * Scale.x)}
	}
	#local glass2_shell = object
	{
		glass1_shell
		scale 0.99
	}
	// should really be a supercone...
	#local grass_clip = object {cyl_macro(-y*4, +y*4, 12) scale Scale}
	// should really be a cone...
	#local entry_cyl = object {cyl_macro(<0,0,0> * Scale, <0,4,0> * Scale, 16*(1-1/sind(45))*Scale.x)}
	#local final_object = union
	{
		// floors & walls
		intersection
		{
			object {glass2_shell}
			union
			{
				// floors
				#for (Level_Count, 1, Level_Total - 1)
					#local y_adjust	= y * Level_Count * city_storey_height;
					object {cyl_box(<-16, -0.0, -16> * Scale + y_adjust, <+16, +0.1, +16> * Scale + y_adjust)}
					#if (Level_Count = Level_Total - 1)
						// top-most ceiling
						object {cyl_box(<-16, +3.8, -16> * Scale + y_adjust, <+16, +3.9, +16> * Scale + y_adjust)}
					#end
				#end
/*
				// walls
				#local Section_Total = 4;
				#for (Section_Count, 0, Section_Total-1)
					box
					{
						<-0.1,          4,  -0.0>,
						<+0.1, 4 * Level_Total, +15.0>
						scale		Scale
						rotate		y * Section_Count * 360/Section_Total
					}
				#end
*/
			}
			texture {wall_texture}
		}
		union
		{
			#if (glass_thin)
				// base
				difference
				{
					intersection
					{
						object {glass0_shell}
						object {cyl_box(<-16, 0, -16> * Scale, <+16, 4, +16> * Scale)}
						// bounding may not help here
//						bounded_by {glass0_shell}
					}
					object {cyl_box(<-15, -1, -15> * Scale, <+15, +5, +15> * Scale)}
					#if (glass_hollow)	hollow	#end
					// bounding may not help here
//					bounded_by {glass0_shell}
				}
				// glass
				difference
				{
					object {glass1_shell}
					object {glass2_shell}
					#if (glass_hollow)	hollow	#end
					// bounding may not help here
//					bounded_by {glass1_shell}
				}
			#else
				// base
				intersection
				{
					object {glass0_shell}
					object {cyl_box(<-16, 0, -16> * Scale, <+16, 4, +16> * Scale)}
					#if (glass_hollow)	hollow	#end
					// bounding may not help here
//					bounded_by {glass0_shell}
				}
				// glass
				object
				{
					glass1_shell
					#if (glass_hollow)	hollow	#end
				}
			#end
			material {glass_mat}
		}
		// entryway
		intersection
		{
			object {cyl_grad_csg(<0,0,0> * Scale, <0,6,0> * Scale, 6 * Scale.x)}
			object {cyl_box(<-16, 0, -16> * Scale, <+16, 4, +16> * Scale)}
			#if (glass_hollow)	hollow	#end
			material {base_mat}
			// bounding may not help here
//			bounded_by {}
		}
		// grass
		intersection
		{
			object {cyl_box(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)}
			union
			{
				object {grass_clip translate <-16,0,-16> * Scale}
				object {grass_clip translate <-16,0,+16> * Scale}
				object {grass_clip translate <+16,0,+16> * Scale}
				object {grass_clip translate <+16,0,-16> * Scale}
			}
			texture {grass_texture}
			// bounding may not help here
			bounded_by {cyl_box_bound(<-16,0,-16> * Scale, <+16,0,+16> * Scale + <0,city_grass_height,0>)}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// trees
	#local tree_total = 4;
	#for (tree_count, 0, tree_total-1)
		#local tree_theta = tree_count/tree_total*2*pi + pi/4;
		#local tree_radius = (14 + 14/sind(45))/2;
		#local tree_point = <tree_radius * cos(tree_theta),city_grass_height/Scale.y,tree_radius * sin(tree_theta)> * Scale;
		object {pos_object(tree_macro(_CT_rand2), Translate + tree_point)}
	#end
	// people
	#local person_total = 24;
	#for (person_count, 0, person_total-1)
		#local person_theta = rand(_CT_rand2)*2*pi;
		#local person_point = <(rand(_CT_rand2)*4+6) * cos(person_theta),0,(rand(_CT_rand2)*4+6) * sin(person_theta)> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi + pi/4;
		#local trash_point = <8 * cos(trash_theta),0,8 * sin(trash_theta)> * Scale;
		object {pos_object(trash_can_macro(_CT_rand2), Translate + trash_point)}
	#end
#end

//------------------------------------------------------------------------------5

// OFFICE BUILDING #5 - pink box scatter
#macro Office_Building_5(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_5.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, Level_Total*city_storey_height, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * (-1/2+rand(_CT_rand5))
		translate	x * (-1/2+rand(_CT_rand5))
		rotate		x * 90
		scale		building_size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local main_tex		= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
			#local stone_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
		#break
		#case (0)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<0.7, 0.76, 0.75>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<1/2, 1/2, 1/2>)}
				}
			}
			#local stone_texture = texture
			{
				pigment {gamma_color_adjust(<1,1,1>)}
			}
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
			}
		#break
		#case (1)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<0.7, 0.76, 0.75>)}
				normal {bumps 0.3 scale 0.1}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<1/2, 1/2, 1/2>)}
					normal {bumps 0.01	scale <0.5, 0.1, 0.5>}
					finish {specular 0.2	roughness 0.1	reflection 0.5}
				}
				scale Meters
			}
			#local stone_texture = texture
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
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
		#case (2)
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<0.7, 0.76, 0.75>)}
				normal {bumps 0.3 scale 0.1}
				scale Meters
			}
			#local glass_mat = material
			{
//				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<1/4, 0, 0>)}
					normal {bumps 0.01	scale <0.5, 0.1, 0.5>}
					finish {specular 0.2	roughness 0.1	reflection 0.5}
				}
				scale Meters
			}
			#local stone_texture = texture
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
			#local grass_texture = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
		#break
	#end
	#local final_object = union
	{
		// glass, does not support glass_thin or glass_hollow!!! there's also nothing (floors, walls, etc.) inside the glass
		union
		{
			#local box_max = 10;
			#local box_cnt = 0;
			// dont use a #for loop here
			#while (box_cnt < box_max)
				#local mod_factor = <building_size.x/4,city_storey_height,building_size.z/4>;
				#local floor_width = <rand(_CT_rand3),rand(_CT_rand3),rand(_CT_rand3)> * building_size;
				#local floor_start = <rand(_CT_rand3),rand(_CT_rand3),rand(_CT_rand3)> * (building_size - floor_width);
				#local floor_width = vfloor_def(floor_width/mod_factor + 1/2) * mod_factor;
				#local floor_start = vfloor_def(floor_start/mod_factor + 1/2) * mod_factor;
				#local floor_final = floor_start + floor_width;
				#if (vgreat_def(floor_final, floor_start))
					cyl_box((floor_start - <16,0,16>), (floor_final - <16,0,16>))
					#local box_cnt = box_cnt + 1;
				#end
			#end
			cyl_box(<-1/4,-0,-1/4> * building_size,<+1/4,+1/2,+1/4> * building_size)
//			scale Scale			// I think this building needs to be scaled. need to mess with it later
//			hollow
			material {glass_mat}
		}
		// grass
		union
		{
			object {cyl_box(<-15,0,-15,> * Scale, <-09,2,-09,> * Scale)}
			object {cyl_box(<-15,0,+09,> * Scale, <-09,2,+15,> * Scale)}
			object {cyl_box(<+09,0,+09,> * Scale, <+15,2,+15,> * Scale)}
			object {cyl_box(<+09,0,-15,> * Scale, <+15,2,-09,> * Scale)}
			texture {grass_texture}
		}
		// white border around grass
		union
		{
			object {cyl_box(<-16,0,-16,> * Scale, <-08,1.999,-08,> * Scale)}
			object {cyl_box(<-16,0,+08,> * Scale, <-08,1.999,+16,> * Scale)}
			object {cyl_box(<+08,0,+08,> * Scale, <+16,1.999,+16,> * Scale)}
			object {cyl_box(<+08,0,-16,> * Scale, <+16,1.999,-08,> * Scale)}
			texture {stone_texture}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
#end

//------------------------------------------------------------------------------6

// OFFICE BUILDING #6 - green cylinders
#macro Office_Building_6(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_6.\n")
	#local Level_Total	= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 4, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local wall_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0,1/16,0>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,3/16,0,0,12/16>)}
				}
			}
		#break
		#case (1)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0,1/16,0>)}
				normal {bumps 0.01 scale 0.01}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,3/16,0,0,12/16>)}
					normal {bumps 0.01	scale 0.01}
					finish {specular 0.1	roughness 0.1	reflection 0.1}
				}
				scale Meters
			}
		#break
		#case (2)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0,1/16,0>)}
				normal {bumps 0.01 scale 0.01}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<0,3/16,0,0,12/16>)}
					normal {bumps 0.01	scale 0.01}
					finish {specular 0.1	roughness 0.1	reflection 0.1}
				}
				scale Meters
			}
		#break
	#end
	#local Outer_Shell = con_macro(+y * (city_radius/2), 0, +y * 0, 16 * Scale.x)
	#local Inner_Shell = con_macro(+y * (city_radius/2 - Meters/16), 0, +y * Meters/16, 16 * Scale.x - Meters/16)
	#local Post_Shell = con_macro(+y * (city_radius/2), 0, +y * 0, 8 * Scale.x)
	#local final_object = union
	{
		// floors
		#for (Level_Count, 1, Level_Total)
			intersection
			{
				object {Inner_Shell}
				difference
				{
					cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - Level_Count * city_storey_height + Meters/8)
					cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - Level_Count * city_storey_height - Meters/8)
//					bounded_by {}
				}
				texture {wall_texture}
//				bounded_by {}
			}
		#end
		// outer glass
		difference
		{
			intersection
			{
				object {Outer_Shell}
				difference
				{
					cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - city_storey_height + Meters/4)
					cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - Level_Total * city_storey_height - Meters/4)
//					bounded_by {}
				}
//				bounded_by {}
			}
			#if (glass_thin)
				intersection
				{
					object {Inner_Shell}
					difference
					{
						cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - city_storey_height + Meters/8 + 0.001 * Meters)
						cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - Level_Total * city_storey_height - Meters/8 - 0.001 * Meters)
//						bounded_by {}
					}
//					bounded_by {}
				}
			#end
			#if (glass_hollow)	hollow	#end
			material {glass_mat}
//			bounded_by {}
		}
		// bottom center post
		intersection
		{
			object {Post_Shell}
			difference
			{
				cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius)
				cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - city_storey_height)
//				bounded_by {}
			}
			texture {wall_texture}
//			bounded_by {}
		}
		// grass
		difference
		{
			cyl_box(<-16,+0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
			con_macro(y * city_radius, 0, -0.001, 18 * Scale.x)
			texture {grass_tex}
//			bounded_by {}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 32;
	#for (person_count, 0, person_total-1)
		#local person_theta = rand(_CT_rand2)*2*pi;
		#local person_point = <(rand(_CT_rand2)*8+12) * cos(person_theta),0,(rand(_CT_rand2)*8+12) * sin(person_theta)> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi + pi/4;
		#local trash_point = <14*cos(trash_theta),0,14*sin(trash_theta)> * Scale;
		object {pos_object(trash_can_macro(_CT_rand2), Translate + trash_point)}
	#end
#end

//------------------------------------------------------------------------------7

// OFFICE BUILDING #7 - tapered helix
#macro Office_Building_7(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_7.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 4, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local main_tex		= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
			}
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>/2)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {P_Chrome5 filter 0 transmit .5}
				}
			}
		#break
		#case (1)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>/2)}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {P_Chrome5 filter 0 transmit .5}
					normal {bumps .05 scale .1}
					finish {specular .5 roughness .1 reflection <.3, .4, .5>}
				}
				scale Meters
			}
		#break
		#case (2)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local main_tex = texture
			{
				pigment {gamma_color_adjust(<1,1,1>/2)}
				finish {metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {P_Chrome5 filter 0 transmit .5}
					normal {bumps .05 scale .1}
					finish {specular .5 roughness .1 reflection <.3, .4, .5>}
				}
				scale Meters
			}
		#break
	#end
	#local Building_Rotate = rand(_CT_rand3) * 360;
	#local Side_A1 = city_radius;
	#local Side_B1 = sind(45) * Size.x / 2;
	#local Side_C1 = sqrt(pow(Side_A1,2) + pow(Side_B1,2));
	#local Theta = acos(Side_A1/Side_C1);

	// floors
	#local floor_mesh = mesh
	{
		#for (Level_Count, 1, Level_Total)
			#local Side_A2 = city_radius - Level_Count * city_storey_height;
			#local Side_C2 = Side_A2 / cos(Theta);
			#local Side_B2 = Side_C2 * sin(Theta);
			#local Corner_TTop_1 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_2 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_3 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_4 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_Top_1  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_2  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_3  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_4  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Bot_1  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_2  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_3  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_4  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_BBot_1 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_2 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_3 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_4 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			triangle
			{
				Corner_Top_3,
				Corner_Top_2,
				Corner_Top_1
			}
			triangle
			{
				Corner_Top_1,
				Corner_Top_4,
				Corner_Top_3
			}
		#end
		inside_vector x
		scale y * 0.999
	}
	// glass
	#local glass_mesh = mesh
	{
		#for (Level_Count, 2, Level_Total)
			#local Side_A2 = city_radius - Level_Count * city_storey_height;
			#local Side_C2 = Side_A2 / cos(Theta);
			#local Side_B2 = Side_C2 * sin(Theta);
			#local Corner_TTop_1 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_2 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_3 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_TTop_4 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
			#local Corner_Top_1  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_2  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_3  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Top_4  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
			#local Corner_Bot_1  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_2  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_3  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_Bot_4  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
			#local Corner_BBot_1 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_2 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_3 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#local Corner_BBot_4 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
			#if (Level_Count = Level_Total)
				triangle
				{
					Corner_Top_3,
					Corner_Top_2,
					Corner_Top_1
				}
				triangle
				{
					Corner_Top_1,
					Corner_Top_4,
					Corner_Top_3
				}
			#end
			#if (Level_Count = 2)
				triangle
				{
					Corner_Bot_3,
					Corner_Bot_2,
					Corner_Bot_1
				}
				triangle
				{
					Corner_Bot_1,
					Corner_Bot_4,
					Corner_Bot_3
				}
			#end

			#local Normal_Top_1a = (vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1))) / 3;
			#local Normal_Top_4a = (vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4))) / 3;
			#local Normal_Bot_1a = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross(Corner_BBot_4-Corner_BBot_1, Corner_Bot_1-Corner_BBot_1))) / 3;
			#local Normal_Bot_4a = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross(Corner_BBot_3-Corner_BBot_1, Corner_Bot_4-Corner_BBot_4))) / 3;
			#local Normal_Top_4b = (vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross(Corner_TTop_1-Corner_TTop_4, Corner_Top_4-Corner_TTop_4))) / 3;
			#local Normal_Bot_4b = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4))) / 3;
			smooth_triangle
			{
				Corner_Top_1, Normal_Top_1a,
				Corner_Bot_1, Normal_Bot_1a,
				Corner_Bot_4, Normal_Bot_4b
			}
			smooth_triangle
			{
				Corner_Bot_4, Normal_Bot_4b,
				Corner_Top_4, Normal_Top_4b,
				Corner_Top_1, Normal_Top_1a
			}

			#local Normal_Top_4a = (vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4))) / 3;
			#local Normal_Top_3a = (vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3))) / 3;
			#local Normal_Bot_4a = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross(Corner_BBot_3-Corner_BBot_4, Corner_Bot_4-Corner_BBot_4))) / 3;
			#local Normal_Bot_3a = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross(Corner_BBot_2-Corner_BBot_4, Corner_Bot_3-Corner_BBot_3))) / 3;
			#local Normal_Top_3b = (vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross(Corner_TTop_4-Corner_TTop_3, Corner_Top_3-Corner_TTop_3))) / 3;
			#local Normal_Bot_3b = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3))) / 3;
			smooth_triangle
			{
				Corner_Top_4, Normal_Top_4a,
				Corner_Bot_4, Normal_Bot_4a,
				Corner_Bot_3, Normal_Bot_3b
			}
			smooth_triangle
			{
				Corner_Bot_3, Normal_Bot_3b,
				Corner_Top_3, Normal_Top_3b,
				Corner_Top_4, Normal_Top_4a
			}

			#local Normal_Top_3a = (vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3))) / 3;
			#local Normal_Top_2a = (vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2))) / 3;
			#local Normal_Bot_3a = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross(Corner_BBot_2-Corner_BBot_3, Corner_Bot_3-Corner_BBot_3))) / 3;
			#local Normal_Bot_2a = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross(Corner_BBot_1-Corner_BBot_3, Corner_Bot_2-Corner_BBot_2))) / 3;
			#local Normal_Top_2b = (vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross(Corner_TTop_3-Corner_TTop_2, Corner_Top_2-Corner_TTop_2))) / 3;
			#local Normal_Bot_2b = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2))) / 3;
			smooth_triangle
			{
				Corner_Top_3, Normal_Top_3a,
				Corner_Bot_3, Normal_Bot_3a,
				Corner_Bot_2, Normal_Bot_2b
			}
			smooth_triangle
			{
				Corner_Bot_2, Normal_Bot_2b,
				Corner_Top_2, Normal_Top_2b,
				Corner_Top_3, Normal_Top_3a
			}

			#local Normal_Top_2a = (vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2))) / 3;
			#local Normal_Top_1a = (vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1))) / 3;
			#local Normal_Bot_2a = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross(Corner_BBot_1-Corner_BBot_2, Corner_Bot_2-Corner_BBot_2))) / 3;
			#local Normal_Bot_1a = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross(Corner_BBot_4-Corner_BBot_2, Corner_Bot_1-Corner_BBot_1))) / 3;
			#local Normal_Top_1b = (vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross(Corner_TTop_2-Corner_TTop_1, Corner_Top_1-Corner_TTop_1))) / 3;
			#local Normal_Bot_1b = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1))) / 3;
			smooth_triangle
			{
				Corner_Top_2, Normal_Top_2a,
				Corner_Bot_2, Normal_Bot_2a,
				Corner_Bot_1, Normal_Bot_1b
			}
			smooth_triangle
			{
				Corner_Bot_1, Normal_Bot_1b,
				Corner_Top_1, Normal_Top_1b,
				Corner_Top_2, Normal_Top_2a
			}

			#local Side_A1 = Side_A2;
			#local Side_C1 = Side_C2;
			#local Side_B1 = Side_B2;
		#end
		inside_vector x
	}
	#local clip_obj = mesh
	{
		#local Level_Count = 1;
		#local Side_A2 = city_radius - Level_Count * city_storey_height;
		#local Side_C2 = Side_A2 / cos(Theta);
		#local Side_B2 = Side_C2 * sin(Theta);
		#local Corner_TTop_1 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
		#local Corner_TTop_2 = vrotate(<-Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
		#local Corner_TTop_3 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
		#local Corner_TTop_4 = vrotate(<+Side_B2, (Level_Count+1) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+1) + Building_Rotate));
		#local Corner_Top_1  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
		#local Corner_Top_2  = vrotate(<-Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
		#local Corner_Top_3  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
		#local Corner_Top_4  = vrotate(<+Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count+0) + Building_Rotate));
		#local Corner_Bot_1  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
		#local Corner_Bot_2  = vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
		#local Corner_Bot_3  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
		#local Corner_Bot_4  = vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate));
		#local Corner_BBot_1 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
		#local Corner_BBot_2 = vrotate(<-Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
		#local Corner_BBot_3 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
		#local Corner_BBot_4 = vrotate(<+Side_B1, (Level_Count-2) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-2) + Building_Rotate));
		triangle
		{
			Corner_Top_3,
			Corner_Top_2,
			Corner_Top_1
		}
		triangle
		{
			Corner_Top_1,
			Corner_Top_4,
			Corner_Top_3
		}
		triangle
		{
			Corner_Bot_3,
			Corner_Bot_2,
			Corner_Bot_1
		}
		triangle
		{
			Corner_Bot_1,
			Corner_Bot_4,
			Corner_Bot_3
		}

		#local Normal_Top_1a = (vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1))) / 3;
		#local Normal_Top_4a = (vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4))) / 3;
		#local Normal_Bot_1a = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross(Corner_BBot_4-Corner_BBot_1, Corner_Bot_1-Corner_BBot_1))) / 3;
		#local Normal_Bot_4a = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross(Corner_BBot_3-Corner_BBot_1, Corner_Bot_4-Corner_BBot_4))) / 3;
		#local Normal_Top_4b = (vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross(Corner_TTop_1-Corner_TTop_4, Corner_Top_4-Corner_TTop_4))) / 3;
		#local Normal_Bot_4b = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4))) / 3;
		smooth_triangle
		{
			Corner_Top_1, Normal_Top_1a,
			Corner_Bot_1, Normal_Bot_1a,
			Corner_Bot_4, Normal_Bot_4b
		}
		smooth_triangle
		{
			Corner_Bot_4, Normal_Bot_4b,
			Corner_Top_4, Normal_Top_4b,
			Corner_Top_1, Normal_Top_1a
		}

		#local Normal_Top_4a = (vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4))) / 3;
		#local Normal_Top_3a = (vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3))) / 3;
		#local Normal_Bot_4a = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross(Corner_BBot_3-Corner_BBot_4, Corner_Bot_4-Corner_BBot_4))) / 3;
		#local Normal_Bot_3a = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross(Corner_BBot_2-Corner_BBot_4, Corner_Bot_3-Corner_BBot_3))) / 3;
		#local Normal_Top_3b = (vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_4,Corner_TTop_4- Corner_Top_4)) + vnormalize(vcross(Corner_TTop_4-Corner_TTop_3, Corner_Top_3-Corner_TTop_3))) / 3;
		#local Normal_Bot_3b = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_3,Corner_BBot_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_4, Corner_Top_4- Corner_Bot_4)) + vnormalize(vcross( Corner_Top_4- Corner_Top_3, Corner_Bot_3- Corner_Top_3))) / 3;
		smooth_triangle
		{
			Corner_Top_4, Normal_Top_4a,
			Corner_Bot_4, Normal_Bot_4a,
			Corner_Bot_3, Normal_Bot_3b
		}
		smooth_triangle
		{
			Corner_Bot_3, Normal_Bot_3b,
			Corner_Top_3, Normal_Top_3b,
			Corner_Top_4, Normal_Top_4a
		}

		#local Normal_Top_3a = (vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3))) / 3;
		#local Normal_Top_2a = (vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2))) / 3;
		#local Normal_Bot_3a = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross(Corner_BBot_2-Corner_BBot_3, Corner_Bot_3-Corner_BBot_3))) / 3;
		#local Normal_Bot_2a = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross(Corner_BBot_1-Corner_BBot_3, Corner_Bot_2-Corner_BBot_2))) / 3;
		#local Normal_Top_2b = (vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_3,Corner_TTop_3- Corner_Top_3)) + vnormalize(vcross(Corner_TTop_3-Corner_TTop_2, Corner_Top_2-Corner_TTop_2))) / 3;
		#local Normal_Bot_2b = (vnormalize(vcross( Corner_Bot_3- Corner_Bot_2,Corner_BBot_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_3, Corner_Top_3- Corner_Bot_3)) + vnormalize(vcross( Corner_Top_3- Corner_Top_2, Corner_Bot_2- Corner_Top_2))) / 3;
		smooth_triangle
		{
			Corner_Top_3, Normal_Top_3a,
			Corner_Bot_3, Normal_Bot_3a,
			Corner_Bot_2, Normal_Bot_2b
		}
		smooth_triangle
		{
			Corner_Bot_2, Normal_Bot_2b,
			Corner_Top_2, Normal_Top_2b,
			Corner_Top_3, Normal_Top_3a
		}

		#local Normal_Top_2a = (vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2))) / 3;
		#local Normal_Top_1a = (vnormalize(vcross( Corner_Top_4- Corner_Top_1,Corner_TTop_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_4, Corner_Bot_4- Corner_Top_4)) + vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1))) / 3;
		#local Normal_Bot_2a = (vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross(Corner_BBot_1-Corner_BBot_2, Corner_Bot_2-Corner_BBot_2))) / 3;
		#local Normal_Bot_1a = (vnormalize(vcross( Corner_Bot_4- Corner_Bot_1, Corner_Top_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_4,Corner_BBot_4- Corner_Bot_4)) + vnormalize(vcross(Corner_BBot_4-Corner_BBot_2, Corner_Bot_1-Corner_BBot_1))) / 3;
		#local Normal_Top_1b = (vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1)) + vnormalize(vcross( Corner_Top_1- Corner_Top_2,Corner_TTop_2- Corner_Top_2)) + vnormalize(vcross(Corner_TTop_2-Corner_TTop_1, Corner_Top_1-Corner_TTop_1))) / 3;
		#local Normal_Bot_1b = (vnormalize(vcross( Corner_Bot_2- Corner_Bot_1,Corner_BBot_1- Corner_Bot_1)) + vnormalize(vcross( Corner_Bot_1- Corner_Bot_2, Corner_Top_2- Corner_Bot_2)) + vnormalize(vcross( Corner_Top_2- Corner_Top_1, Corner_Bot_1- Corner_Top_1))) / 3;
		smooth_triangle
		{
			Corner_Top_2, Normal_Top_2a,
			Corner_Bot_2, Normal_Bot_2a,
			Corner_Bot_1, Normal_Bot_1b
		}
		smooth_triangle
		{
			Corner_Bot_1, Normal_Bot_1b,
			Corner_Top_1, Normal_Top_1b,
			Corner_Top_2, Normal_Top_2a
		}

		#local Side_A1 = Side_A2;
		#local Side_C1 = Side_C2;
		#local Side_B1 = Side_B2;
		#local Level_Count = Level_Count + 1;
		inside_vector x
		scale 1.2
	}
	#local final_object = union
	{
		difference
		{
			cyl_box(<-16,  0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
			cyl_box(< -2, -1,-17> * Scale, < +2, +2,+17> * Scale)
			cyl_box(<-17, -1, -2> * Scale, <+17, +2, +2> * Scale)
			clip_obj
			texture {grass_tex}
//			bounded_by {}
		}
		object
		{
			floor_mesh
			texture {main_tex}
		}
		// does not support glass_thin or glass_hollow!!!
		object
		{
			glass_mesh
			material {glass_mat}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
#end

//------------------------------------------------------------------------------6

// OFFICE BUILDING #8 - blocky helix
// needs to be bounded properly!!!
#macro Office_Building_8(Size, Direction, Translate)
	debug_detail("CG...............Adding Office_Building_8.\n")
	#local Level_Total		= ceil(Size.y/city_storey_height);
	#local building_size	= <32, 4, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local grass_pigment_1 = pigment
	{
		image_map {png "olivepink_marble.png"}
		translate	y * -1/2
		translate	x * -1/2
		rotate		x * 90
		scale		Size
	}
	#local grass_pigment_2 = pigment
	{
//		gamma_color_adjust(<046,104,058,>/255/2)
		gamma_color_adjust(<110,160,008,>/255/2*1.3)	// oyonale makegrass color
	}
	#local grass_pigment_3 = pigment
	{
		average
		pigment_map
		{
			[1	grass_pigment_1]
			[2	grass_pigment_2]
		}
	}
	#switch (TexQual)
		#case (-1)
			#local wall_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local glass_mat	= material {texture {pigment {lowqual_pig(_CT_rand5)}}};
		#break
		#case (0)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0/16,1/16,1/16>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,4/16,4/16,0,12/16>)}
				}
			}
		#break
		#case (1)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0/16,1/16,1/16>)}
				normal {bumps 0.01 scale 0.01}
				finish {specular 0.01	roughness 0.01	reflection 0.01	metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(<0,4/16,4/16,0,12/16>)}
					normal {bumps 0.01	scale 0.01}
					finish {specular 0.1	roughness 0.1	reflection 0.1}
				}
				scale Meters
			}
		#break
		#case (2)
			#local grass_tex = texture
			{
				pigment {grass_pigment_3}
				normal	{wrinkles}
				scale Meters
			}
			#local wall_texture = texture
			{
				pigment {gamma_color_adjust(<0/16,1/16,1/16>)}
				normal {bumps 0.01 scale 0.01}
				finish {specular 0.01	roughness 0.01	reflection 0.01	metallic}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {ior 2.5}
				texture
				{
					pigment {gamma_color_adjust(<0,4/16,4/16,0,12/16>)}
					normal {bumps 0.01	scale 0.01}
					finish {specular 0.1	roughness 0.1	reflection 0.1}
				}
				scale Meters
			}
		#break
	#end
	#if (rand(_CT_rand3) > 1/2)
		#local Building_Direction = +1;
	#else
		#local Building_Direction = -1;
	#end
	#local Building_Rotate = rand(_CT_rand3) * 360 * Building_Direction;
	#local Outer_Shell	= con_macro(+y * (city_radius), 0, +y * 0, 16 * Scale.x)
	#local Inner_Shell1	= con_macro(+y * (city_radius - 1/16 * Scale.x), 0, +y * 1/16 * Scale.x, 16 * Scale.x - 1/16 * Scale.x)
	#local Inner_Shell2	= con_macro(+y * (city_radius - 2/16 * Scale.x), 0, +y * 2/16 * Scale.x, 16 * Scale.x - 2/16 * Scale.x)
	#local Post_Shell	= con_macro(+y * (city_radius), 0, +y * 0, 4 * Scale.x)
	#local final_object = union
	{
		// glass
		difference
		{
			union
			{
				#for (Level_Count, 2, Level_Total)
					intersection
					{
						union
						{
							intersection
							{
								object {Inner_Shell1}
								plane {-x, -1/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 000) * Building_Direction}
								plane {+x, -1/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 120) * Building_Direction}
	//							bounded_by {}
							}
							intersection
							{
								object {Inner_Shell1}
								plane {-x, -1/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 000) * Building_Direction}
								plane {+x, -1/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 120) * Building_Direction}
	//							bounded_by {}
							}
						}
						difference
						{
							cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 1) * city_storey_height)
							cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count - 0) * city_storey_height)
	//						bounded_by {}
						}
	//					bounded_by {}
					}
				#end
			}
			#if (glass_thin)
				union
				{
					#for (Level_Count, 2, Level_Total)
						intersection
						{
							union
							{
								intersection
								{
									object {Inner_Shell2}
									plane {-x, -2/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 000) * Building_Direction}
									plane {+x, -2/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 120) * Building_Direction}
		//							bounded_by {}
								}
								intersection
								{
									object {Inner_Shell2}
									plane {-x, -2/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 000) * Building_Direction}
									plane {+x, -2/16 * Scale.x	rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 120) * Building_Direction}
		//							bounded_by {}
								}
							}
							difference
							{
								cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 1.1) * city_storey_height)
								cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count + 0.1) * city_storey_height)
		//						bounded_by {}
							}
		//					bounded_by {}
						}
					#end
				}
			#end
			material {glass_mat}
//			bounded_by {}
		}
		union
		{
			// floors and ceilings
			#for (Level_Count, 2, Level_Total)
				intersection
				{
					union
					{
						intersection
						{
							object {Outer_Shell}
							plane {-x, 0 rotate +y * (10 * Level_Count + Building_Rotate + 000 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (10 * Level_Count + Building_Rotate + 000 + 120) * Building_Direction}
//							bounded_by {}
						}
						intersection
						{
							object {Outer_Shell}
							plane {-x, 0 rotate +y * (10 * Level_Count + Building_Rotate + 180 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (10 * Level_Count + Building_Rotate + 180 + 120) * Building_Direction}
//							bounded_by {}
						}
					}
					union
					{
						difference
						{
							cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 1) * city_storey_height + 1/32 * Scale.x)
							cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count - 1) * city_storey_height - 1/32 * Scale.x)
//							bounded_by {}
						}
						difference
						{
							cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 0) * city_storey_height + 1/32 * Scale.x)
							cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count - 0) * city_storey_height - 1/32 * Scale.x)
//							bounded_by {}
						}
					}
//					bounded_by {}
				}
			#end
			// radial walls
			#for (Level_Count, 2, Level_Total)
				intersection
				{
					union
					{
						intersection
						{
							object {Outer_Shell}
							plane {-x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 120) * Building_Direction}
//							bounded_by {}
						}
						intersection
						{
							object {Outer_Shell}
							plane {-x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 120) * Building_Direction}
//							bounded_by {}
						}
					}
					difference
					{
						cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 1) * city_storey_height)
						cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count - 0) * city_storey_height)
//						bounded_by {}
					}
					union
					{
						#for (Wall_Count, 1, 2, 1)
							intersection
							{
								plane {+x, +1/16 * Scale.x rotate +y * (360/36 * Level_Count + 360/9 * Wall_Count + Building_Rotate) * Building_Direction}
								plane {-x, +1/16 * Scale.x rotate +y * (360/36 * Level_Count + 360/9 * Wall_Count + Building_Rotate) * Building_Direction}
//								bounded_by {}
							}
						#end
					}
//					bounded_by {}
				}
			#end
			// cylindrical walls
			#for (Level_Count, 2, Level_Total)
				intersection
				{
					union
					{
						intersection
						{
							union
							{
								#for (Wall_Count, 4, 12, 4)
									difference
									{
										object {con_macro(+y * (city_radius), 0, +y * 0, (16-Wall_Count+1/16) * Scale.x)}
										object {con_macro(+y * (city_radius), 0, +y * 0, (16-Wall_Count-1/16) * Scale.x)}
//										bounded_by {}
									}
								#end
							}
							plane {-x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 000 + 120) * Building_Direction}
//							bounded_by {}
						}
						intersection
						{
							union
							{
								#for (Wall_Count, 4, 12, 4)
									difference
									{
										object {con_macro(+y * (city_radius), 0, +y * 0, (16-Wall_Count+1/16) * Scale.x)}
										object {con_macro(+y * (city_radius), 0, +y * 0, (16-Wall_Count-1/16) * Scale.x)}
//										bounded_by {}
									}
								#end
							}
							plane {-x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 000) * Building_Direction}
							plane {+x, 0 rotate +y * (360/36 * Level_Count + Building_Rotate + 180 + 120) * Building_Direction}
//							bounded_by {}
						}
					}
					difference
					{
						cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - (Level_Count - 1) * city_storey_height)
						cyl_macro(<0,city_radius,-33 * Scale.x>, <0,city_radius,+33 * Scale.x>, city_radius - (Level_Count - 0) * city_storey_height)
//						bounded_by {}
					}
//					bounded_by {}
				}
			#end
			texture {wall_texture}
		}
		// center post
		difference
		{
			object {Post_Shell}
			cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - Level_Total * city_storey_height - 1/32 * Scale.x)
			texture {wall_texture}
//			bounded_by {}
		}
		// grass
		difference
		{
			cyl_box(<-16,+0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
			con_macro(y * city_radius, 0, -0.001, 18 * Scale.x)
			texture {grass_tex}
//			bounded_by {}
		}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
/*
	// support posts
	#local cut_object = cyl_macro(<0,city_radius,-32 * Scale.x>, <0,city_radius,+32 * Scale.x>, city_radius - Level_Total * city_storey_height + Meters/4)
	difference
	{
		union
		{
			#local support_total = 6;
			#for (support_count, 0, support_total-1)
				#local support_theta = support_count/support_total*2*pi;
				#local support_point = <16*cos(support_theta),0,16*sin(support_theta)> * Scale;
				cylinder
				{
					pos_point(support_point + Translate), +y * 0, 1/4 * Scale.x
					texture {wall_texture}
				}
			#end
		}
		object {pos_object(cut_object, Translate)}
	}
*/
	// people
	#local person_total = 32;
	#for (person_count, 0, person_total-1)
		#local person_theta = rand(_CT_rand2)*2*pi;
		#local person_point = <(rand(_CT_rand2)*8+12) * cos(person_theta),0,(rand(_CT_rand2)*8+12) * sin(person_theta)> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
	// trash cans
	#local trash_total = 4;
	#for (trash_count, 0, trash_total-1)
		#local trash_theta = trash_count/trash_total*2*pi + pi/4;
		#local trash_point = <14*cos(trash_theta),0,14*sin(trash_theta)> * Scale;
		object {pos_object(trash_can_macro(_CT_rand2), Translate + trash_point)}
	#end
#end
