#local Sprite_Height = 128;
#local Height = 16;
#local Burst = 1;
#ifndef (Width) #local Width = 64; #end

#ifndef (Included)
	light_source
	{
		0                  // light's position (translated below)
		color rgb <1,1,1>    // light's color
		translate <20, 40, 20>
		parallel
	}
	// Create an infinite sphere around scene and allow any pigment on it
	sky_sphere
	{
	  pigment
	  {
	    bozo
	    color_map { [0.0 color rgb <0.7,0.7,1.0>] [1.0 color blue 0.5] }
	  }
	}
	camera
	{
		orthographic
		sky y
		up y * 64 * image_height / image_width
		right x * 64
		location <256,256,256,>
		look_at <0,0,0,>
	}
#end


// -------------------------------------------------------------
// Textures

#local Default_Finish = finish
{
	diffuse 0.7
	ambient 0.3	//0.3
//	brilliance 1
//	specular 0.2
	conserve_energy
}

#local Plain_White = texture
{
	pigment {color rgb 1}
	finish {Default_Finish}
}

#local Plain_Black = texture
{
	pigment {color rgb 0}
	finish {Default_Finish}
}

#local Plain_Clear = texture
{
	pigment {color rgbt 1}
	finish {Default_Finish}
}

//------------------------------------------------------------------

#local Exhaust_Texture_a = texture
{
	pigment
	{
		bozo
		color_map
		{
			[1/4 color rgbt <1,1,1,0,>]
			[1 color rgbt <1,1,1,1,>]
		}
	}
	finish {Default_Finish}
	scale 4
}

#local Exhaust_Texture_b = texture
{
	pigment
	{
		gradient -y
		color_map
		{
			[0/4 rgbt <1,	1,	1/2,	0,>]
			[1/4 rgbt <1,	1/2,	0,	1,>]
		}
	}
	normal
	{
		bumps 4
	}
	finish {Default_Finish}
	scale Width * 4
}

#local Exhaust_Texture_e = texture
{
	gradient -y
	texture_map
	{
		[0 Exhaust_Texture_a]
		[1 Plain_Clear]
	}
	scale Width * 4
}

#local Exhaust_Texture_c = texture
{
	average
	texture_map
	{
		[1 Exhaust_Texture_e]
		[1 Exhaust_Texture_b]
	}
}

#local Fire_Material = material
{
	texture
	{
		pigment {color rgbt 1}
	}
	interior
	{
		media
		{
			emission rgbt <1,1/2,0,0,> * 10
			density
			{
				gradient y
				/*
				color_map
				{
					[0.0 rgbt <1,1/2,0,0,>]
					[1.0 rgbt <1,1/2,0,1,>]
//					[0.0 rgbt <1,0,0,0,>]
//					[1.0 rgbt <0,1,0,0,>]
				}
				*/
				scale 4
			}
		}

	}
}


#declare Missile = union
{
	cylinder
	{
		<0,2,0,>, <0,12,0,>, 1
		texture {Plain_White}
	}
	cone
	{
		<0,12,0,>, 1, <0,16,0,>, 0
		texture {Plain_White}
	}
	/*
	cone
	{
		<0,2,0,>, 2 <0,4,0,>, 0
		texture {Plain_Black}
	}
	*/
	cone
	{
		<0,0,0,>, 0 <0,4,0,>, 1
//		open
		hollow
		material {Fire_Material}
		translate y * -2
	}
	cone
	{
		<0,-256,0,>, 8 <0,0,0,>, 2
		open
//		hollow
		texture {Exhaust_Texture_c}
	}
	translate y * 24
	rotate x * 90
	scale 1/2
//	scale z * 2
	translate y * Height
//	no_shadow
}

#ifndef (Included)
	union
	{
		object {Missile}
		no_shadow
//		scale 1/4
	}
#end