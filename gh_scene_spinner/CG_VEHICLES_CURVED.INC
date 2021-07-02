/*************************************************************************
CITY GENERATOR VEHICLE OBJECTS FILE FOR PERSISTENCE OF VISION 3.x

Created by Chris Colefax, 1 February 1999
NOTE: This file is designed for use with City.mcr and City.inc
To use, include the file before including City.inc, with any other
object/building files you want to use.

**************************************************************************/


// VEHICLE COMPONENTS
// NB: Vehicles should travel along +z axis (LH drive), or -z axis (RH drive)
#macro curve_train(dist)
	transform
	{
		translate	-y * city_radius
		rotate		+x * atan2d(dist, city_radius)
		translate	+y * city_radius
	}
#end
// dimensions are all based off height at the moment, whereas they should each be configurable, maybe
#macro TrainMacro(in_color, Direction)
	#local adjusted_height = rail_cars_height/1.8;	// normalized so that the top of a train car is 1 * rail_cars_height units high
	#switch (TexQual)
		#case (-2)
			#local brake_light_tex	= texture {};
			#local head_light_tex	= texture {};
			#local train_texture	= texture {};
			#local train_texture	= texture {};
		#break
		#case (-1)
			#local brake_light_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local head_light_tex	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local train_texture	= texture {pigment {lowqual_pig(_CT_rand5)}};
			#local train_texture = texture
			{
				pigment
				{
					gradient y
					color_map
					{
						[0.6 gamma_color_adjust(<rand(_CT_rand5),rand(_CT_rand5),rand(_CT_rand5)>)]
						[0.6 gamma_color_adjust(<rand(_CT_rand5),rand(_CT_rand5),rand(_CT_rand5)>)]
					}
					scale		1.5
					translate	y * 0.8
				}
			}
		#break
		#case (0)
			#local brake_light_tex = texture
			{
				pigment {gamma_color_adjust(<1, 0.3, 0.2>)}
			}
			#local head_light_tex = texture
			{
				pigment {gamma_color_adjust(<1, 1, 0.9>)}
			}
			#local train_texture = texture
			{
				pigment
				{
					gradient y
					color_map
					{
						[0.6 gamma_color_adjust(in_color)]
						[0.6 gamma_color_adjust(<0.2, 0.2, 0.2>)]
					}
					scale		1.5
					translate	y * 0.8
				}
			}
		#break
		#case (1)
		#case (2)
			#local brake_light_tex = texture
			{
				pigment {gamma_color_adjust(<1, 0.3, 0.2>)}
				#if (city_night)
					finish {ambient 1.3}
				#end
			}
			#local head_light_tex = texture
			{
				pigment {gamma_color_adjust(<1, 1, 0.9>)}
				#if (city_night)
					finish {ambient 1.3}
				#end
			}
			#local train_texture = texture
			{
				pigment
				{
					gradient y
					color_map
					{
						[0.6 gamma_color_adjust(in_color)]
						[0.6 gamma_color_adjust(<0.2, 0.2, 0.2>)]
					}
					scale		1.5
					translate	y * 0.8
				}
				finish
				{
					ambient		0.35
					brilliance	2
					diffuse		0.3
					metallic
					specular	0.80
					roughness	1/20
					reflection	0.1
				}
			}
		#break
	#end	
	#local TrainCar = union
	{
		// no mesh version!!!
		superellipsoid {<0.4, 0.5>	scale < 1.1, 0.5, 4.0>	translate y * 0.6}
		superellipsoid {<0.5, 0.5>	scale < 1.1, 0.5, 3.8>	translate y * 1.3}
		scale adjusted_height
		texture {train_texture}
	}
	#local HeadLights = union
	{
		object {sph_macro(<-0.6, 0.7, 0>, 0.15)	scale <1, 1, 0.3>}
		object {sph_macro(<+0.6, 0.7, 0>, 0.15)	scale <1, 1, 0.3>}
		#if (city_night)
			union
			{
				spotlight_cone(<-0.6, 0, 0>, 0.1, <-0.6, -0.7, 0>, 1, gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.8>), 1)
				spotlight_cone(<+0.6, 0, 0>, 0.1, <+0.6, -0.7, 0>, 1, gamma_color_adjust(<1.5, 1.4, 1.2, 0.0, 0.8>), 1)
				matrix <1, 0, 0, 0, 1, -5, 0, 0, 1, 0, 0.7, -0.1>
			}
		#end
		scale adjusted_height
		texture {head_light_tex}
	}
	#local BrakeLights = union
	{
		object {sph_macro(<-0.5, 0.7, 0>, 0.15)}
		object {sph_macro(<+0.5, 0.7, 0>, 0.15)}
		scale <1, 1, 0.3>
		scale adjusted_height
		texture {brake_light_tex}
	}
	union
	{
		object {TrainCar}
		#local cars_max = floor(rail_cars_number/2);
		#local cars_cnt = 0;
		#while (cars_cnt < cars_max)
			#local cars_cnt_pad = 8.25 * (cars_cnt+1) * adjusted_height;
			#if (Direction)
				object {TrainCar	translate -z * cars_cnt_pad}
				object {TrainCar	translate +z * cars_cnt_pad}
			#else
				object {TrainCar	transform {curve_train(-cars_cnt_pad)}}
				object {TrainCar	transform {curve_train(+cars_cnt_pad)}}
			#end
			#local cars_cnt = cars_cnt + 1;
		#end
		#local cars_max_pad = 8.25 * cars_max * adjusted_height;
		#local cars_lght_dist = 4.125 * adjusted_height;
		#if (Direction)
			object {HeadLights	translate z * (-cars_lght_dist - cars_max_pad)}
			object {BrakeLights	translate z * (+cars_lght_dist + cars_max_pad)}
		#else
			object {HeadLights	transform {curve_train(-cars_lght_dist - cars_max_pad)}}
			object {BrakeLights	transform {curve_train(+cars_lght_dist + cars_max_pad)}}
		#end
		#if (city_right_hand_drive)
			rotate y * 180
		#end
	}
#end

#macro Train(Direction, VD)
	#local bit1 = (VD < 0 ? 0 : 1);
	#local bit2 = Direction * 2;
	#local bitTot = bit1 + bit2;
	#switch (bitTot)
		#case (0)
			#local TColor = <0.8,0.6,0.2>;
		#break
		#case (1)
			#local TColor = <0.0,0.4,0.2>;
		#break
		#case (2)
			#local TColor = <0.9,0.9,0.9>;
		#break
		#case (3)
			#local TColor = <0.6,0.0,0.0>;
		#break
	#end
	TrainMacro(TColor, Direction)
#end

#declare city_vehicle_macros	= array[1] {"Train"}
#declare city_vehicle_spacing	= array[1] {128 * Meters}
