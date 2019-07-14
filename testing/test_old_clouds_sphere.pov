	#local Radius_Outer = GlobeRadius + Width * 4;
	#local Radius_Inner = GlobeRadius + Width * 3;
	#local Radius_Ratio = Radius_Inner/Radius_Outer;
	#local Radius_Outer_Scale = 200;
	#local Radius_Inner_Scale = Radius_Outer_Scale * Radius_Ratio;
	#local Radius_Difference = Radius_Outer_Scale - Radius_Inner_Scale;
	#local Inc_Scale_Amount = Radius_Outer / Radius_Outer_Scale;
	#local Dec_Scale_Amount = 1 / Inc_Scale_Amount;
//	#local Dec_Scale_Amount = sqrt(3) / vlength(Inc_Scale_Amount);
	#local pigCloudBank = pigment
	{
		average
		pigment_map {[1 spherical scale Radius_Outer_Scale frequency Radius_Outer_Scale/Radius_Difference][1 granite scale 25]}
	}
	#local CloudSphere = difference
	{
		sphere {0, Radius_Outer_Scale}
		sphere {0, Radius_Inner_Scale}
		hollow
		texture {pigment {rgbt 1}}
		interior
		{
			media
			{
				scattering {1, 0.5 * Dec_Scale_Amount}
				method 3
//				samples 30, 100
				intervals 1
				density
				{
					pigment_pattern {pigCloudBank}
					density_map {[.6 rgb 0][.61 rgb 1]}
				}
			}
		}
		scale Inc_Scale_Amount
	}
	object {CloudSphere}