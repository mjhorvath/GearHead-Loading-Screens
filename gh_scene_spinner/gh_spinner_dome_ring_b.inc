// grass setup
verbose_include("grasspatch.inc", 0)
#local someseed				= seed(2345);
#local xseed				= seed(422);
#local zseed				= seed(369);
#local Patch_Tranlation		= <0,0,0>;		// typo?
#local PlotPoints			= false;
#local Blade_Density		= 8;		// per unit length. Square this to know how many will be in each unit squared of landscape
#local Patch_Shape			= 0;		// Circular
#local Spread_Correction	= 0.9;
#local Blade_Height_Minimum	= 1/2;		// Blade_Heights are in standard POV units
#local Blade_Height_Maximum	= 1;
#local Use_Blade_Distance	= true;
#local Blade_Detail			= 4;
#local Max_Blade_Angle		= 0;
#local Min_Blade_Angle		= 0;
#local Blade_Scale			= 0.5;
#local Blade_Width			= 0.1;
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
#local N				= 2;		// 2
#local Half				= 1;
#local Method			= 1;
#local Disc				= 0;
#local R_Ten			= 0.01 / N;
#local R_Hen			= 0.01 / N;
#local Thickness		= R_Hen / 2;
verbose_include("sphere.inc", 0)
#local ring_radius		= agridome_ringrad/agridome_radius;
#local ring_circum		= 2 * pi * agridome_ringrad;
#local small_angle		= agridome_radius/ring_circum * 360;
// better shape
#local dome_base = intersection
{
	cone {-y*1/8,1,+y*ring_radius,0}
	difference
	{
		cylinder {-z*1,+z*1,ring_radius+1/8}
		cylinder {-z*2,+z*2,ring_radius}
		translate +y * ring_radius
	}
}
#local dome_object = union
{
	object {Ten			white_metal_texture()}
	object {Hen			white_metal_texture()}
	object {Men			dome_material()}
	object {dome_base	white_metal_texture()}
//	cylinder {0,+y/128,1	dirt_texture()}
//	cylinder {-y/8,0,1	white_metal_texture()}
}
#local dome_plants = union
{
	PlantPatch()
	scale	1/2 * 0.9
	scale	y*2/3
}


#declare dome_group = union
{
	// center row of 5
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 2
	}

	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 4
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 4
	}

	// next row of 4
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 1
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 1
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 3
		translate -z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 3
		translate -z * sind(60) * 2
	}

	// next row of 4	
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 1
		translate +z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 1
		translate +z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 3
		translate +z * sind(60) * 2
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 3
		translate +z * sind(60) * 2
	}

	// next row of 3
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		translate -z * sind(60) * 4
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 2
		translate -z * sind(60) * 4
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 2
		translate -z * sind(60) * 4
	}

	// next row of 3
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		translate +z * sind(60) * 4
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate -z * small_angle * 2
		translate +z * sind(60) * 4
	}
	union
	{
		object {dome_object}
		object {dome_plants	rotate	y * rand(Seed) * 360}
		translate -y * ring_radius
		rotate +z * small_angle * 2
		translate +z * sind(60) * 4
	}

	scale agridome_radius
}
