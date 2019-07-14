// use the Jupiter model for a small solar system model too
// soccer fields, swimming pools, ponds
// raumschiff needs a bounding box

//#version 3.7		// can't set the version here

#include "glass.inc"
verbose_include("gh_deciduous_tree.inc", defined(TREE))
verbose_include("Raumschiff5.inc", 0)
#declare park_deco_raums	= object {Raumschiff5}
verbose_include("Horus.inc", 0)
#declare park_deco_horus	= object {Horus}
#declare park_deco_eagle	= object {verbose_include("eagle.inc", 0)}
#declare park_deco_vultr	= object {verbose_include("vulture.inc", 0)}


//------------------------------------------------------------------------------

#declare building_macros[building_types] = "Public_Park_1";		// just trees and people I think
#declare building_chance[building_types] = 1;					// float, between 0 and 1
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Public_Park_2";		// large white metal sculptures, museum pieces, etc.
#declare building_chance[building_types] = 1/8;					// 1/2
#declare building_types = building_types + 1;
#declare building_macros[building_types] = "Public_Park_3";		// white spindle
#declare building_chance[building_types] = 1/8;					// 1/4
#declare building_types = building_types + 1;
// some additional ones with ponds & stuff would be nice


//------------------------------------------------------------------------------

// Park 1
// check the newsgroups, someone responded with a better way of positioning the trees on 10-06
#macro Public_Park_1(Size, Direction, Translate)
	debug_detail("CG...............Adding Public_Park_1.\n")
	#local building_size	= <32, 32, 32>;
	#local Scale		= <Size.x/building_size.x,Size.x/building_size.y,Size.z/building_size.z>;
	#local base_height	= city_grass_height/Scale.y;
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
		gamma_color_adjust(<110,160,008,>/255/2*1.3) 	// oyonale makegrass color
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
			#local stone_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
		#break
		#case (0)
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
		#case (2)
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
		// border
		difference
		{
			object {cyl_box(<-16,+0,-16,> * Scale, <+16,base_height,+16,> * Scale)}
			object {cyl_box(<-15,-1,-15,> * Scale, <+15,+2,+15,> * Scale)}
			// bounding may not help here
			bounded_by {cyl_box_bound(<-16,+0,-16,> * Scale, <+16,base_height,+16,> * Scale)}
			texture {stone_texture}
		}
		// grass
		object
		{
			cyl_box(<-15,0,-15,> * Scale, <+15,base_height,+15,> * Scale)
			texture {grass_texture}
		}
		bounded_by {cyl_box_bound(<-16,+0,-16,> * Scale, <+16,base_height + city_tree_height,+16,> * Scale)}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// trees
	#local tree_total	= 16;
	#for (tree_count, 0, tree_total - 1)
		#local tree_point	= <rand(_CT_rand2) * 26 - 13,base_height,rand(_CT_rand2) * 26 - 13> * Scale;
		object {pos_object(tree_macro(_CT_rand2), Translate + tree_point)}
	#end
	// people
	#local person_total = 10;
	#for (person_count, 0,  person_total-1)
		#local person_point = <rand(_CT_rand2)*28-14,base_height,rand(_CT_rand2)*28-14> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
#end


//------------------------------------------------------------------------------

// large white metal sculptures
#macro Public_Park_2(Size, Direction, Translate)
	#if (park_deco_number < 1)
		debug_detail("CG...............Value of park_deco_number is 0, switching to a different object.\n")
		Public_Park_1(Size, Direction, Translate)
		#break
	#end
	debug_detail("CG...............Adding Public_Park_2.\n")
	#local building_size	= <32, 32, 32>;
//	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local Scale		= <Size.x/building_size.x,Size.x/building_size.y,Size.z/building_size.z>;
	#local base_height	= city_grass_height/Scale.y;
	#local clip_total	= 4;
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
			#local metal_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local stone_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
			#local grass_texture = texture {pigment {lowqual_pig(_CT_rand5)}};
		#break
		#case (0)
			#local metal_texture = texture
			{	
				pigment {gamma_color_adjust(<0.8,0.8,0.8>)}
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
		#case (2)
			#local metal_texture = texture
			{	
				pigment {gamma_color_adjust(<0.8,0.8,0.8>)}
				finish
				{
					ambient		0
					specular	1
					roughness	0.01
					metallic
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
		debug_detail(concat("park_deco_number = ",str(park_deco_number,0,0),"\n"))
		#switch (park_deco_number)
			#case (1)
				// spiral arcs
				union
				{
					#local arch_radis	= 12;
					#local arch_radmx	= 1;
					#local arch_thick	= 1/16;
					#local arch_total	= 12;
					#for (arch_count, 0, arch_total-1)
						intersection
						{
							difference
							{
								object {cyl_macro(<0,0,-arch_thick*1>, <0,0,+arch_thick*1>, arch_radis - arch_count * arch_radmx - arch_radmx * 1)}
								object {cyl_macro(<0,0,-arch_thick*2>, <0,0,+arch_thick*2>, arch_radis - arch_count * arch_radmx - arch_radmx * 2)}
								bounded_by {cylinder {<0,0,-arch_thick*1>, <0,0,+arch_thick*1>, arch_radis - arch_count * arch_radmx - arch_radmx * 1}}
							}
							// should be cyl_box
							plane {x,0}
							rotate y * 360 * arch_count/arch_total
							bounded_by {cylinder {<0,0,0>, <0,arch_radis,0>, arch_radis}}
						}
					#end
					bounded_by {cylinder {<0,0,0>, <0,arch_radis/2,0>, arch_radis}}
					scale Scale
					texture {metal_texture}
				}
			#break
			#case (2)
				// "bird's nest"
				union
				{
					#local arch_radis	= 12;
					#local arch_total	= 6;
					#local arch_thick	= 1/16;
					#for (arch_count, 0, arch_total-1)
						#local arch_theta = 90 - arch_count/arch_total * 90;
						#local arch_radth = arch_radis/2 * cosd(arch_theta);
						#local arch_heigh = arch_radis/2 - arch_radis/2 * sind(arch_theta);
						difference
						{
							object {cyl_macro(<0,arch_heigh-arch_thick*1,0>, <0,arch_heigh+arch_thick*1,0>, arch_radth - 0)}
							object {cyl_macro(<0,arch_heigh-arch_thick*2,0>, <0,arch_heigh+arch_thick*2,0>, arch_radth - 1)}
							bounded_by {cylinder {<0,0,0>, <0,arch_radis,0>, arch_radis}}
						}
						#local arch_theta = 90 - arch_count/arch_total * 90;
						#local arch_radth = arch_radis/2 + arch_radis/2 * cosd(arch_theta);
						#local arch_heigh = arch_radis/2 * sind(arch_theta);
						difference
						{
							object {cyl_macro(<0,arch_heigh-1/8,0>, <0,arch_heigh+1/8,0>, arch_radth - 0)}
							object {cyl_macro(<0,arch_heigh-1/2,0>, <0,arch_heigh+1/2,0>, arch_radth - 1)}
							bounded_by {cylinder {<0,0,0>, <0,arch_radis,0>, arch_radis}}
						}
					#end
					bounded_by {cylinder {<0,0,0>, <0,arch_radis,0>, arch_radis}}
					translate <0,base_height,0>
					scale Scale
					texture {metal_texture}
				}
			#break
			#case (3)
				// "armadillo"
				union
				{
					#local arch_radis	= 8;
					#local arch_total	= 12;
					#local arch_thick	= 1/16;
					#for (arch_count, 0, arch_total)
						#local arch_dista = arch_count/arch_total * 24 - 12;
						#local arch_rotat = arch_count/arch_total * 60 - 30;
						intersection
						{
							difference
							{
								object {cyl_macro(<0,0,arch_dista-arch_thick*1>, <0,0,arch_dista+arch_thick*1>, arch_radis - 0)}
								object {cyl_macro(<0,0,arch_dista-arch_thick*2>, <0,0,arch_dista+arch_thick*2>, arch_radis - 1)}
								bounded_by {cylinder {<0,0,arch_dista-arch_thick*1>, <0,0,arch_dista+arch_thick*1>, arch_radis - 0}}
							}
							// should be cyl_box
							plane {-y,0}
							rotate x * arch_rotat
							bounded_by {box {<-16,0,-16>, <+16,+arch_radis,+16>}}
						}
					#end
					translate <0,base_height,0>
					scale Scale
					texture {metal_texture}
				}
			#break
			#case (4)
				// museum piece 1
				#local eagle_object	= park_deco_eagle;
				#local eagle_min	= min_extent(eagle_object);
				#local eagle_max	= max_extent(eagle_object);
				#local eagle_box	= eagle_max - eagle_min;
				#local eagle_nrm	= vnormalize(eagle_box);
				#local eagle_object = object
				{
					eagle_object
					translate	-eagle_min
					scale		1/eagle_box
					translate	<-1/2,0,-1/2>
					scale		eagle_nrm * 2
					rotate		y * 90
					scale		14
					bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
					scale		Scale.x
					#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
				}
				#local vultr_object	= park_deco_vultr;
				#local vultr_min	= min_extent(vultr_object);
				#local vultr_max	= max_extent(vultr_object);
				#local vultr_box	= vultr_max - vultr_min;
				#local vultr_nrm	= vnormalize(vultr_box);
				#local vultr_object = object
				{
					vultr_object
					translate	-vultr_min
					scale		1/vultr_box
					translate	<-1/2,0,-1/2>
					scale		vultr_nrm * 2
					rotate		y * 90
					scale		8
					bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
					scale		Scale.x
					#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
				}
				#local horus_object	= park_deco_horus;
				#local horus_min	= min_extent(horus_object);
				#local horus_max	= max_extent(horus_object);
				#local horus_box	= horus_max - horus_min;
				#local horus_nrm	= vnormalize(horus_box);
				#local horus_object = object
				{
					horus_object
					translate	-horus_min
					scale		1/horus_box
					translate	<-1/2,0,-1/2>
					scale		horus_nrm * 2
		//			rotate		y * 90
					scale		6
					translate	y
					bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
					scale		Scale.x
					#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
				}
				#local jupiter_object = sphere
				{
					<0,0,0>, 3/2
					texture
					{
						pigment
						{
							image_map
							{
								png		"jupiter.png"
								map_type	1
							}
						}
					}
					scale Scale.x
				}
				union
				{
					object {cyl_box(<-13.0,-0,-13.0,> * Scale, < -3.0,+base_height*2,+13.0,> * Scale)}
					object {cyl_box(< +4.5,-0, +4.5,> * Scale, <+11.5,+base_height*2,+11.5,> * Scale)}
					object {cyl_box(< +4.5,-0,-12.5,> * Scale, <+11.5,+base_height*2, -3.5,> * Scale)}
					texture {stone_texture}
				}
				object {jupiter_object translate <0,3,0> * Scale}
				object {eagle_object translate <-8,base_height,+0> * Scale}
				object {vultr_object translate <+8,base_height,+8> * Scale}
				object {horus_object translate <+8,base_height,-8> * Scale}
			#break
			#case (5)
				// museum piece 2
				#local raums_object	= park_deco_raums;
				#local raums_min	= min_extent(raums_object);
				#local raums_max	= max_extent(raums_object);
				#local raums_box	= raums_max - raums_min;
				#local raums_nrm	= vnormalize(raums_box);
				#local raums_object = object
				{
					raums_object
					translate	-raums_min
					scale		1/raums_box
					translate	<-1/2,0,-1/2>
					scale		raums_nrm * 2
					rotate		y * 180
					scale		16
					scale		z * 3/2
					translate	z * 2
					bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
					scale		Scale.x
					#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
				}
				#local sign_poly_1 = polygon
				{
					4, <0,0,0>, <1,0,0>, <1,1,0>, <0,1,0>
					texture
					{
						pigment
						{
							image_map
							{
								png "holo_sign.png"
							}
						}
						finish {ambient 1}
					}
					translate	-x/2
					scale		2
					scale		Scale
				}
				object
				{
					cyl_box(<-12.0,-0,-12.0,> * Scale, <+12.0,+base_height*2,+12.0,> * Scale)
					texture {stone_texture}
				}
				object {sign_poly_1 translate <8,1,-14> * Scale}
				object {raums_object translate <+0,base_height,-2> * Scale}
			#break
		#end
		// border
		difference
		{
			object {cyl_box(<-16,+0,-16,> * Scale, <+16,base_height,+16,> * Scale)}
			object {cyl_box(<-15,-1,-15,> * Scale, <+15,+2,+15,> * Scale)}
			// bounding may not help here
//			bounded_by {cyl_box_bound(<-16,+0,-16,> * Scale, <+16,base_height,+16,> * Scale)}
			texture {stone_texture}
		}
		// grass
		object
		{
			cyl_box(<-15,0,-15,> * Scale, <+15,base_height,+15,> * Scale)
			texture {grass_texture}
		}
	}
	#declare park_deco_number = park_deco_number - 1;
//	#declare park_deco_number = floor(rand(_CT_rand4) * park_deco_max) + 1;
	#switch (park_deco_number)
		#case (1)
		#break
		#case (2)
		#break
		#case (3)
		#break
	#end
	// building and grass
	object {pos_object(final_object, Translate)}
	// people
	#local person_total = 20;
	#for (person_count, 0, person_total-1)
		#local person_point = <rand(_CT_rand2)*28-14,base_height,rand(_CT_rand2)*28-14> * Scale;
		object {pos_object(ped_macro(_CT_rand2), Translate + person_point)}
	#end
#end


//------------------------------------------------------------------------------8

// white spindle
#macro Public_Park_3(Size, Direction, Translate)
	debug_detail("CG...............Adding Public_Park_3.\n")
	#local Size		= <Size.x,city_storey_height*6,Size.z>;		// I don't want this to be random
	#local Level_Total	= ceil(Size.y/city_storey_height);
	#local building_size	= <32, city_storey_height/2, 32>;
	#local Scale		= <Size.x/building_size.x,city_storey_height/building_size.y,Size.z/building_size.z>;
	#local Height_Adjust	= 3;
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
				pigment {gamma_color_adjust(<1,1,1>)}
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(1) filter 0 transmit .5}
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
				pigment {gamma_color_adjust(<1,1,1>)}
				scale Meters
			}
			#local glass_mat = material
			{
				texture
				{
					pigment {gamma_color_adjust(1) filter 0 transmit .5}
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
				pigment {gamma_color_adjust(<1,1,1>)}
				scale Meters
			}
			#local glass_mat = material
			{
				interior {I_Glass4}		//I_Glass4
				texture
				{
					pigment {gamma_color_adjust(1) filter 0 transmit .5}
					normal {bumps .05 scale .1}
					finish {specular .5 roughness .1 reflection <.3, .4, .5>}
				}
				scale Meters
			}
		#break
	#end
	#local torus_obj = intersection
	{
		torus
		{
			Size.x/2, Size.x/2
			translate y * Size.x/2
			inverse
			scale y * Size.y/Size.x * Height_Adjust
		}
		cylinder {0, y * Size.y/2 * Height_Adjust, Size.x/2}
		bounded_by {cylinder {0, y * Size.y/2 * Height_Adjust, Size.x/2}}
	}
	#local floor_obj = union
	{
		#for (Level_Count, 0, Level_Total * Height_Adjust - 1)
			intersection
			{
				object {torus_obj}
				difference
				{
					cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - (Level_Count+1) * city_storey_height}
					cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - (Level_Count+1) * city_storey_height - Meters/4}
				}
//				bounded_by {cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - (Level_Count+1) * city_storey_height}}
			}
		#end
	}
	#local wall_obj = union
	{
		#local Radial_Total = 6;
		#for (Radial_Count, 0, Radial_Total-1)
			intersection
			{
				object {torus_obj}
				box
				{
					<-0.1,  -0,  -0>, <+0.1, +128, +16>
					rotate y * Radial_Count * 360/Radial_Total
					scale Scale
				}
//				bounded_by
//				{
//					box
//					{
//						<-0.1,  -0,  -0>, <+0.1, +128, +16>
//						rotate y * Radial_Count * 360/Radial_Total
//						scale Scale
//					}
//				}
			}
		#end
	}
	#local glass_obj = difference
	{
		object {torus_obj scale 0.99}
		object {torus_obj scale 0.98}
		cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - city_storey_height inverse}
		hollow
		bounded_by {cylinder {0, y * Size.y/2 * Height_Adjust, Size.x/2}}
	}
	#local grass_obj = difference
	{
		cyl_box(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)
//		cyl_box(<-2,-1,-17> * Scale, <+2,2,+17> * Scale)
//		cyl_box(<-17,-1,-2> * Scale, <+17,2,+2> * Scale)
		con_macro(y * city_radius, 0, 0, 10 * Scale.x)
		object {wall_obj rotate y * 0 scale 16}
		bounded_by {cyl_box_bound(<-16,0,-16> * Scale, <+16,city_grass_height,+16> * Scale)}
	}
	#local final_object = union
	{
		object {floor_obj	texture {main_tex}}
		object {wall_obj	texture {main_tex}}
		object {glass_obj	material {glass_mat}}
		object {grass_obj	texture {grass_tex}}
	}
	// building and grass
	object {pos_object(final_object, Translate)}
	// trees
	#local tree_total = 6;
	#for (tree_count, 0, tree_total-1)
		#local tree_theta = tree_count/tree_total*2*pi;
		#local tree_radius = 13;
		#local tree_point = <tree_radius * cos(tree_theta),city_grass_height/Scale.y,tree_radius * sin(tree_theta)> * Scale;
		object {pos_object(tree_macro(_CT_rand2), Translate + tree_point)}
	#end
#end
