#include "gh_deciduous_tree.inc"
#local Tex_1 = texture
{
	pigment {gamma_color_adjust(<1,1,1>)}
	finish
	{
		ambient 0.0
		diffuse 0.6
		specular 0.1
	}
}
#local grass_pigment_1 = pigment
{
	image_map {png "olivepink_marble.png"}
	translate	y * -1/2
	translate	x * -1/2
	rotate		x * 90
	scale		32
}
#local grass_pigment_2 = pigment
{
//	color rgb <046,104,058,>/255/4
	color rgb 1.3 * <110,160,8,>/255/4	// oyonale makegrass color
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
#local grass_texture_1 = texture
{
	pigment {grass_pigment_3}
	normal	{wrinkles}
}
#local grass_texture_2 = texture
{
	pigment {gamma_color_adjust(<110,160,008>/255)}
	normal {wrinkles scale 16}
}


#local tree_seed	= seed(8829464);
#macro rand_woods()
	union
	{
		#local temp_height	= 1/4;
		#local tree_total	= 16;
		#local tree_count	= 0;
		#while (tree_count < tree_total)
			object
			{
				TREE
				scale		16 * (rand(tree_seed) * 1/3 + 2/3)
				translate	x * (rand(tree_seed) * 28 - 14)
				translate	z * (rand(tree_seed) * 28 - 14)
				translate	y * temp_height
			}
			#local tree_count = tree_count + 1;
		#end
		difference
		{
			box {<-16, 0,-16,>, <+16, temp_height,+16,>}
			box {<-15,-1,-15,>, <+15,+2,+15,>}
			texture {Tex_1}
		}
		box
		{
			<-15,0,-15,>, <+15,temp_height,+15,>
			texture {grass_texture_1}
		}
	}
#end


// INCLUDE DEFAULT OBJECTS FILE IF REQUIRED
#ifndef (building_size) #include "DEFAULT.OBJ" #end

// WOODS 1
#declare building_size[building_types]		= <32, 32, 32>;
#declare building_options[building_types]	= build_base;
#declare building_base[building_types]		= rand_woods()
#declare building_types				= building_types + 1;

// WOODS 2
#declare building_size[building_types]		= <32, 32, 32>;
#declare building_options[building_types]	= build_base;
#declare building_base[building_types]		= rand_woods()
#declare building_types				= building_types + 1;
