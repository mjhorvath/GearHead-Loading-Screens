// http://news.povray.org/povray.binaries.scene-files/thread/%3Cweb.4208bfe95bb1e0e05a9431fb0%40news.povray.org%3E/
// From "Rocket Chess" by Ralph Roberts

/* Exhaust Plume */

#declare Exhaust_N = function
{
	(sin(0.667*pow(x,4))-pow(1.04*pow(x,2),1.12)-pow(y,2)-pow(z,2)+0.4)-0.0333*x
}

#declare Exhaust_S = density
{
	function {Exhaust_N(x,y,z)}//spherical
	density_map
	{
		[0.00 rgb 0]
		[0.0125 rgb <0.1,0.3,0.9>]
		[0.10 rgb <0.1,0.3,0.9>*0.02]
		[0.60 rgb <0.1,0.3,0.9>*0.06]
		[1.00 rgb <0.1,0.3,0.9>]
	}
	translate -x/6
}

#declare Exhaust_GS = density
{
	gradient x
	density_map
	{
		[0.00 Exhaust_S]
		[0.50 rgb 0]
	}
}

#declare Exhaust_C = density
{
	cylindrical
	density_map
	{
		[0.10 rgb 0]
		[0.25 rgb <0.9,0.3,0.6>*0.25]
		[0.50 rgb <0.9,0.3,0.6>*2]
		[0.75 rgb <0.9,0.3,0.6>*0.25]
		[0.90 rgb 0]
	}
	poly_wave 0.8
	warp {turbulence <0.2+0.1*clock,0,0.2+0.1*clock>}
	warp {repeat y/4 flip y}
	warp {turbulence <0.2,0,0.2>*clock}
	scale <1/3-0.15*clock,1/3,1/3-0.15*clock> //rotate 90*z
}

#declare Exhaust_G = density
{
	gradient y
	density_map
	{
		[0.1 rgb 0.00]
		[0.2 rgb 0.05]
		[0.5 Exhaust_C]
		[0.6 Exhaust_C]
		[0.8 rgb 0.05]
		[0.9 rgb 0.00]
	}
	poly_wave 0.4
	frequency 8
}

#declare Exhaust_GC = density
{
	cylindrical
	density_map
	{
		[0.25 rgb 0]
		[0.75 Exhaust_G]
		[1.00 rgb 0]
	}
	rotate 90*z
}

#declare Exhaust_X = function(x) {x}

#declare Exhaust_Object = sphere
{
	0, 1
	scale <0.5,1,1>
	translate -0.5*x
	pigment
	{
		color rgbt 1
	}
	interior
	{
		media
		{
			samples 15
			emission 1.5/exhaust_scale
			density
			{
				function {abs(Exhaust_X(x))}
				density_map
				{
					[0.00 rgb 0]
					//[0.50 Exhaust_GC]
					[0.75 Exhaust_GS]
				}
			}
		}
		media
		{
			samples 15
			absorption 0.5/exhaust_scale
			density
			{
				function {abs(Exhaust_X(x))}
				density_map
				{
					[0.00 rgb 0]
					//[0.50 Exhaust_GC]
					[0.75 Exhaust_GS]
				}
			}
		}
	}
	scale <12,1.5+1.5*clock,1.5+1.5*clock> translate <11.2+0.4*clock,0,0>
	hollow
}
