// Desc: GearHead boulders generator, based on POV-Ray tutorial
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.

#macro Boulders_Object()
	union
	{
		#local Count = 0;
		#local Number = 1;
		#while (Count < Number)
			#local Size = rand(Seed) * rand(Seed) * Width/8;
			isosurface
			{
				function {(f_sphere(x, y, z, 1/4) - f_noise3d(x, y, z))}
				max_gradient 4
				contained_by {box {-1, +1}}
				texture
				{
					pigment {gamma_color_adjust(<1,1,1>/2)}
					normal
					{
						facets
						coords	0.5
						//size	1.0
						no_bump_scale
						scale	2
					}
				}
				scale Size
				rotate <rand(Seed) * 360, rand(Seed) * 360, rand(Seed) * 360,>
			}
			#local Count = Count + 1;
		#end
	}
#end
