	#local CloudBall = sphere
	{
		0,2
		hollow
		texture	{pigment {rgbt 1}}
		interior
		{
			media
			{
				scattering {1, 1 * ScaleAmount_Dec}
				density
				{
					spherical
					scale <1,.5,1>
					warp {turbulence .3}
					density_map {[0 rgb 0][.1 rgb 1]}
				}
			}
		}
		scale ScaleAmount_Inc
		translate y * Width * 8
	}
	object {CloudBall}
