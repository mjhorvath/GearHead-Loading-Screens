// grass setup
verbose_include("grasspatch.inc", 0)
#local someseed			= seed(2345);
#local xseed			= seed(422);
#local zseed			= seed(369);
#local Patch_Tranlation		= <0,0,0>;
#local PlotPoints		= false;
#local Blade_Density		= 8;		// per unit length. Square this to know how many will be in each unit squared of landscape
#local Patch_Shape		= 0;		// Circular
#local Spread_Correction	= 0.9;
#local Blade_Height_Minimum	= 1/2;		// Blade_Heights are in standard POV units
#local Blade_Height_Maximum	= 1;
#local Use_Blade_Distance	= true;
#local Blade_Detail		= 4;
#local Max_Blade_Angle		= 0;
#local Min_Blade_Angle		= 0;
#local Blade_Scale		= 0.5;
#local Blade_Width		= 0.1;
#local Use_Blade_Distance	= true;
#local Max_Blade_Detail		= 20;
#local Min_Blade_Detail		= 5;
#local Max_Detail_Distance	= 1;
#local Min_Detail_Distance	= 10;
#local Blade_Tex = texture			// And of course the texture. This is the default:
{
	pigment {gamma_color_adjust(<64/255,104/255,72/255,> * 2)}
}

// dome setup
#local N			= 2;
#local Half			= 1;
#local Method			= 1;
#local Disc			= 0;
#local R_Ten			= 0.01 / N;
#local R_Hen			= 0.01 / N;
verbose_include("sphere.inc", 0)
#local RibTexture		= texture {white_metal_texture}
#local PaneTexture		= texture {dome_texture}
#local DirtTexture		= texture
{
	pigment
	{
		wrinkles
		color_map
		{
			[0 gamma_color_adjust(1/4*<1,1,1>)]
			[1 gamma_color_adjust(0/4*<1,1,1>)]
		}
	}
}
#local dome_object = union
{
	object {Ten		texture {RibTexture}}
	object {Hen		texture {RibTexture}}
	object {Men		texture {PaneTexture}}
	cylinder {0,+y/128,1	texture {DirtTexture}}
	cylinder {-y/8,0,1	texture {RibTexture}}
}
#local dome_plants = union
{
	PlantPatch()
	scale	1/2 * 0.9
	scale	y*2/3
}

#declare dome_individual = union
{
	object {dome_object}
	object {dome_plants	rotate	y * rand(Seed) * 360}
	translate +y/8
	scale dome_radius
}

#declare dome_group = union
{
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 0
		translate +z * 0
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 2
		translate -z * 0
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 2
		translate -z * 0
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 4
		translate -z * 0
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 4
		translate -z * 0
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 1
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 1
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 1
		translate +z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 1
		translate +z * sind(60) * 2
	}

	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 3
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 3
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate +x * 3
		translate +z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -x * 3
		translate +z * sind(60) * 2
	}
//	difference
//	{
//		sphere {0, 1.86603}
//		plane {-y, 0}
//		scale y * 1/4
//		texture {RibTexture}
//	}
	translate +y/8
	scale dome_radius
	translate -x * dome_radius * 2
}
