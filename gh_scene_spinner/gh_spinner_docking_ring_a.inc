//------------------------------------------------------------------------------Cargo and Shiphold

difference
{
	union
	{

		#local dock_labels = polygon
		{
			4, <0,0>,<0,1>,<1,1>,<1,0>
			texture {gray_metal_texture}
			texture
			{
				pigment
				{
					image_map {png "spinner_lot_text.png"}
				}
			}
			translate <-1/2,-1/2,0>
			scale <dock_length*7/8,main_body_radius*2,1>
			rotate y * 90
		}
		#for (i, 1, 3)
			difference
			{
				superellipsoid
				{
					<0.001, 0.1>
					scale <dock_depth + dock_thick,dock_radius1*2,dock_length/2>
					rotate z * (i * 60 + 30)
				}
				superellipsoid
				{
					<0.001, 0.1>
					scale <dock_depth,dock_radius1*2,dock_length/2 - dock_thick>
					rotate z * (i * 60 + 30)
				}
				cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius1 inverse}
				cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius2}
				bounded_by {cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius1}}
			}
		#end
		difference
		{
			union
			{
				#for (i, 1, 3)
					union
					{
						object
						{
							dock_labels
							translate +x * dock_depth * 0.99
							rotate z * (i * 60 + 30)
						}
						object
						{
							dock_labels
							translate -x * dock_depth * 0.99
							rotate z * (i * 60 + 30)
						}
					}
				#end
			}
			cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius1 inverse}
			cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius2}
			bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius1}}
		}
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius1}}
	texture {white_metal_texture}
	translate -z * (dock_start + dock_length/2)
}


//------------------------------------------------------------------------------major trusses

difference
{
	union
	{
		// large arms connecting the ring to the axle
	//	#local truss_rotate = 45;
		#local truss_sides = 4;
		#local truss_sections = 4;
		#local truss_thickness = med_truss_thick;
		#local truss_radius = med_truss_radius - med_truss_thick;
		#local truss_point1 = 0;
		#local truss_point2 = +y * dock_radius2;
		#local truss_arms_max = 3;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			object
			{
				#include "truss.inc"
				rotate +z * 360/truss_arms_max * truss_arms_cnt
				translate -z * dock_length/2
			}
			object
			{
				#include "truss.inc"
				rotate +z * 360/truss_arms_max * truss_arms_cnt
				translate +z * dock_length/2
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		// small short horizontal rods connecting the two outer rings
		#local truss_sides = 4;
		#local truss_sections = 4;
		#local truss_thickness = med_truss_thick;
		#local truss_radius = med_truss_radius;
		#local truss_point1 = -z * dock_length/2;
		#local truss_point2 = +z * dock_length/2;
		#local truss_arms_max = 6;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			object
			{
				#include "truss.inc"
				translate +y * dock_radius2
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		// outermost ring
		#local segment_number = 12;
		#local segment_distance = sind(360/segment_number/2) * dock_radius2;
		#local truss_sides = 4;
		#local truss_sections = 1;
		#local truss_thickness = med_truss_thick;
		#local truss_radius = med_truss_radius;
		#local truss_point1 = -y * segment_distance;
		#local truss_point2 = +y * segment_distance;
		#local truss_arms_max = segment_number;
		#local truss_arms_cnt = 0;
		#while (truss_arms_cnt < truss_arms_max)
			union
			{
				object
				{
					#include "truss.inc"
					translate +z * dock_length/2
				}
				object
				{
					#include "truss.inc"
					translate -z * dock_length/2
				}
				translate +x * dock_radius2
				rotate +z * 360/truss_arms_max * truss_arms_cnt
				rotate +z * 30
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius1}}
	texture {white_metal_texture}
	translate -z * (dock_start + dock_length/2)
}

//------------------------------------------------------------------------------Shiphold Contents

#if (!NoDockShips)
	// vehicles
	verbose_include("Raumschiff5.inc", 0)
	#local raums_object	= Raumschiff5;
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
		scale		32
		scale		z * 3/2
		translate	z * 2
		bounded_by {box {<-32,0,-32>, <+32,+32,+32>}}
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		scale 1
	}
	object
	{
		raums_object
		translate -z * (dock_start+dock_length*1/2)
		translate -y * dock_depth
		translate +y * Meters
		translate -x * dock_length*2/3
	}
	new_random_color()
	verbose_include("ara_kojedo.pov", 0)
	object
	{
		ara_kojedo_
		translate <18.42348,0,-364.0902> * -1
		scale 1/375
		//edit below
		scale 10 * Meters
		translate -z * (dock_start+dock_length*7/12)
		translate -y * dock_depth
		translate +y * Meters
		translate +x * dock_length*9/12
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}
	new_random_color()
	verbose_include("btr_maanji.pov", 0)
	object
	{
		object01
		matrix <1.000000, 0.000000, 0.000000,
		0.000000, 1.000000, 0.000000,
		0.000000, 0.000000, 1.000000,
		0.000000, 0.000000, 0.000000>
		translate <0.000000, 0.000000, 0.000000>
		scale <1.000000, 1.000000, 1.000000>
		translate y * -4.65
		scale 1/115
		//edit below
		rotate y * 360 * rand(Seed)
		scale 18 * Meters
		translate -z * (dock_start+dock_length*3/12)
		translate -y * dock_depth
		translate +y * Meters
		translate +x * dock_radius1*9/12
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}
	new_random_color()
	verbose_include("btr_vadel.pov", 0)
	object
	{
		object01
		matrix <0.707112, 0.000000, -0.707101,
		0.000000, 1.000000, 0.000000,
		0.707101, 0.000000, 0.707112,
		0.000000, 0.000000, 0.000000>
		translate <0.000000, 0.000000, 0.000000>
		scale <1.000000, 1.000000, 1.000000>
		rotate y * -45
		scale 1/75
		//edit below
		rotate y * 360 * rand(Seed)
		scale 16 * Meters
		translate -z * (dock_start+dock_length*3/12)
		translate -y * dock_depth
		translate +y * Meters
		translate -x * dock_radius1*9/12
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}

	verbose_include("Horus.inc", 0)
	#local horus_object	= Horus;
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
		rotate		y * 360 * rand(Seed)
		scale		6
		translate	y
		scale		2 * Meters
		bounded_by {box {<-16,0,-16>, <+16,+32,+16>}}
		#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
	}
	object
	{
		horus_object
		translate -z * (dock_start+dock_length*9/12)
		translate -y * dock_depth
		translate +y * Meters
		translate -x * dock_radius1*8/12
	}

	// cargo containers
	#local cargo_pigment = pigment
	{
		checker
		color srgb <0,0,0>,
		color srgb <1/2,1/2,1/2>
		scale Meters
	}
	#local cargo_box = box
	{
		<-Meters,0,-Meters>,
		<+Meters,+Meters*2,+Meters>
		pigment {cargo_pigment}
	}

	#local cargo_max = 8;
	#local cargo_cnt = 0;
	#while (cargo_cnt < cargo_max)
		#local cargo_rand = rand(Seed);
		object
		{
			union
			{
				object {cargo_box		rotate y * (rand(Seed) * 30 - 15)	translate <0,0,+Meters> * 1.2}
				#if (cargo_rand > 1/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <-Meters,0,-Meters> * 1.2}
				#end
				#if (cargo_rand > 2/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <+Meters,0,-Meters> * 1.2}
				#end
				#if (cargo_rand > 3/4)
					object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <0,Meters*2,0>}
				#end
			}
			rotate y * 360 * rand(Seed)
			translate -z * (dock_start + dock_length/6 + dock_length/3 * rand(Seed))
			translate -x * ((dock_radius1 * 3/4 - dock_radius2) * rand(Seed) + dock_radius2)
			translate -y * (dock_depth)
			translate +y * (Meters)
		}
		#local cargo_cnt = cargo_cnt + 1;
	#end
/*
	// people (not rendering??)
	#local people_max = 8;
	#local people_cnt = 0;
	#while (people_cnt < people_max)
		object
		{
			ped_macro(Seed)
			translate -z * (dock_start + dock_length/6 + dock_length/3*rand(Seed))
			translate -x * (dock_length/3*rand(Seed))
			translate -y * (dock_radius1*1/4)
			translate +y * (Meters)
		}
		#local people_cnt = people_cnt + 1;
	#end
*/
	// fuel tanks
	union
	{
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius1/2+Meters*16)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius1/2+Meters*24)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius1/2+Meters*16)
			translate -z*(dock_start+dock_thick+Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius1/2+Meters*24)
			translate -z*(dock_start+dock_thick+Meters*8)
		}

		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius1/2+Meters*16)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate -x*(dock_radius1/2+Meters*24)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius1/2+Meters*16)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		object
		{
			fuel_tank(Meters*8,Meters*4)
			rotate x * 90
			translate +y*Meters*8
			translate +x*(dock_radius1/2+Meters*24)
			translate -z*(dock_start+dock_length-dock_thick-Meters*8)
		}
		translate -y*dock_depth
		texture {yellow_metal_texture}
	}
/*
	// robo arm
	object
	{
		#include "gh_roboarm.inc"
		rotate -x*90
		scale Meters/2
		translate -z*(dock_start+Meters*2)
		texture {white_metal_texture}
	}
*/
	// gantry
	#declare gantry_object = union
	{
		//y
		box {<-12,+00,-30>, <-10,+36,-28>}
		box {<+12,+00,-30>, <+10,+36,-28>}
		box {<+12,+00,+30>, <+10,+36,+28>}
		box {<-12,+00,+30>, <-10,+36,+28>}
		//top
		box {<-12,+36,+30>, <+12,+34,+28>}
		box {<-12,+36,-30>, <+12,+34,-28>}
		box {<-12,+36,-30>, <-10,+30,+30>}
		box {<+12,+36,-30>, <+10,+30,+30>}
		//bottom
		box {<-12,+02,+30>, <+12,+03,+28>}
		box {<-12,+02,-30>, <+12,+03,-28>}
		box {<-12,+12,+30>, <+12,+13,+28>}
		box {<-12,+12,-30>, <+12,+13,-28>}
		scale 1/30
		scale Meters * 16
	}
	object
	{
		gantry_object
		rotate y * 15
		translate -y * (dock_depth - Meters)
		translate -z * (dock_start + dock_length*1/4)
		translate +x * (dock_radius1*3/4)
		texture {yellow_metal_texture}
	}
#end
