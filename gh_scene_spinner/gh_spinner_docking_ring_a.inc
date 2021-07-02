//------------------------------------------------------------------------------Cargo and Shiphold

difference
{
	union
	{

		#local dock_labels = polygon
		{
			4, <0,0>,<0,1>,<1,1>,<1,0>
			gray_metal_texture()
			parking_texture()
			translate <-1/2,-1/2,0>
			scale <dock_length*7/8,dock_radius_outer*2,1>
			rotate y * 90
		}
		#for (i, 1, 3)
			difference
			{
				superellipsoid
				{
					<0.001, 0.1>
					scale <dock_depth + dock_thick,dock_radius_outer*2,dock_length/2>
					rotate +z * (i * 60 + 30)
				}
				superellipsoid
				{
					<0.001, 0.1>
					scale <dock_depth,dock_radius_outer*2,dock_length/2 - dock_thick>
					rotate +z * (i * 60 + 30)
				}
				cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius_outer inverse}
				cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius_inner}
				bounded_by {cylinder {<0,0,+dock_length/2+1>, <0,0,-dock_length/2-1>, dock_radius_outer}}
			}
			difference
			{
				union
				{
					object
					{
						dock_labels
						translate +x * dock_depth * 0.99
						rotate +z * (i * 60 + 30)
					}
					object
					{
						dock_labels
						translate -x * dock_depth * 0.99
						rotate +z * (i * 60 + 30)
					}
				}
				cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius_outer inverse}
				cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius_inner}
				bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius_outer}}
			}
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius_outer}}
	white_metal_texture()
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
		#local truss_point2 = +y * dock_radius_inner;
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
				translate +y * dock_radius_inner
				rotate +z * 360/truss_arms_max * truss_arms_cnt
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
		// outermost ring
		#local segment_number = 12;
		#local segment_distance = sind(360/segment_number/2) * dock_radius_inner;
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
				translate +x * dock_radius_inner
				rotate +z * 360/truss_arms_max * truss_arms_cnt
				rotate +z * 30
			}
			#local truss_arms_cnt = truss_arms_cnt + 1;
		#end
	}
	#if (!ShowWhole)
		object {cutaway_object1}
	#end
	bounded_by {cylinder {<0,0,+dock_length/2>, <0,0,-dock_length/2>, dock_radius_outer}}
	white_metal_texture()
	translate -z * (dock_start + dock_length/2)
}

//------------------------------------------------------------------------------Shiphold Contents
// needs to be clipped by the half plane too

#if (!NoDockShips)
	#local dock_front = dock_start + dock_thick + Meters*2;
	#local dock_back  = dock_start + dock_length - dock_thick - Meters*2;
	#local dock_outer = dock_radius_outer - Meters*2;
	#local dock_inner = dock_radius_inner + Meters*2;
	union
	{
		// large yellow spaceship
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
			scale		Meters
		}
		object
		{
			raums_object
			translate -z * (dock_start+dock_length*1/2)
			translate -y * dock_depth
			translate +y * Meters						// why is this necessary?
			translate -x * dock_radius_outer*10/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		// mecha
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
			translate +y * Meters						// why is this necessary?
			translate +x * dock_radius_outer*9/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		// mecha
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
			translate -z * (dock_start+dock_length*6/12)
			translate -y * dock_depth
			translate +y * Meters						// why is this necessary?
			translate +x * dock_radius_outer*8/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		// mecha
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
			translate -z * (dock_start+dock_length*2/12)
			translate -y * dock_depth
			translate +y * Meters						// why is this necessary?
			translate -x * dock_radius_outer*8/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
		// small double pointed spaceship
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
			bounded_by {box {<-8,0,-8>, <+8,+16,+8>}}
			scale		2 * Meters
		}
		object
		{
			horus_object
			translate -z * (dock_start+dock_length*9/12)
			translate -y * dock_depth
			translate +y * Meters						// why is this necessary?
			translate -x * dock_radius_outer*11/12
			#if (TexQual < 1)	no_reflection 	#end	// for sanity's sake!!!
		}
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
			translate -z * (dock_start + dock_length*1/4)
			translate -y * dock_depth
			translate +y * Meters						// why is this necessary?
			translate -x * dock_radius_outer*9/12
			yellow_metal_texture()
		}
		// each of the six docking areas needs these
		#for (i, 0, 5)
			union
			{
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
				#local cargo_max = floor(rand(Seed) * 16);
				#local cargo_cnt = 0;
				#while (cargo_cnt < cargo_max)
					#local cargo_rand = rand(Seed);
					object
					{
						union
						{
							#if (cargo_rand > 0/4)
								object {cargo_box	rotate y * (rand(Seed) * 30 - 15)	translate <0,0,+Meters> * 1.2}
							#end
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
						translate -z * ((dock_back  - dock_front) * rand(Seed) + dock_front)
						translate -x * ((dock_outer - dock_inner) * rand(Seed) + dock_inner)
						translate -y * (dock_depth)
						translate +y * (Meters)
					}
					#local cargo_cnt = cargo_cnt + 1;
				#end
				// people (not rendering??)
				#if (!NoCity)
					#local people_max = floor(rand(Seed) * 16);
					#local people_cnt = 0;
					#while (people_cnt < people_max)
						object
						{
							ped_macro(Seed)
							translate -z * ((dock_back  - dock_front) * rand(Seed) + dock_front)
							translate -x * ((dock_outer - dock_inner) * rand(Seed) + dock_inner)
							translate -y * (dock_depth)
							translate +y * (Meters)
						}
						#local people_cnt = people_cnt + 1;
					#end
				#end
				// fuel tanks and robo arm
				// need some more fuel tanks on the "top" side of each compartment too
				#local tank_radius = Meters*4;
				#local tank_height = Meters*16;
				union
				{
					// side 1a bottom
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					// side 1b bottom
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					// side 2a bottom
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					// side 2b bottom
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate -y*dock_depth
						translate +y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					// side 1a top
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					// side 1b top
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_thick+tank_radius*2)
					}
					// side 2a top
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*1/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					// side 2b top
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner-tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					object
					{
						fuel_tank(tank_height/2,tank_radius)
						rotate +x * 90
						translate +y*dock_depth
						translate -y*tank_height/2
						translate -x*((dock_radius_outer-dock_radius_inner)*3/4+dock_radius_inner+tank_radius)
						translate -z*(dock_start+dock_length-dock_thick-tank_radius*2)
					}
					// robo arms
					object
					{
						#include "gh_spinner_roboarm.inc"
						scale Meters/4
						rotate +x * 90
						rotate +z * 180
						translate -x*((dock_radius_outer-dock_radius_inner)/2 + dock_radius_inner)
						translate -z*(dock_start+dock_length-dock_thick)
					}
					object
					{
						#include "gh_spinner_roboarm.inc"
						scale Meters/4
						rotate -x * 90
						rotate +z * 180
						translate -x*((dock_radius_outer-dock_radius_inner)/2 + dock_radius_inner)
						translate -z*(dock_start+dock_thick)
					}
					yellow_metal_texture()
				}
				rotate		-z*i*60
			}
		#end
	}
#end
