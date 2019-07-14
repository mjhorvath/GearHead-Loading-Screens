#declare EarthRadius =	6375000 * Meters;
#declare CloudMinRad =	   2000 * Meters;
#declare CloudMaxRad =	   3000 * Meters;
#local InnerRadius = EarthRadius + CloudMinRad;
#local OuterRadius = InnerRadius + CloudMaxRad;
#local BoundRadius = 260 * Meters;			// need to use a formula
#local ScaleAmount = BoundRadius / 200;
#local CloudPigment = pigment
{
	average
	pigment_map
	{
		[2 onion	scale CloudMaxRad	phase -mod(OuterRadius,CloudMaxRad)/CloudMaxRad]
		[2 granite	scale 100 * ScaleAmount]
	}
}
#local CloudSphere = difference
{
	sphere {0, OuterRadius}
	sphere {0, InnerRadius}
	bounded_by {cylinder {<0,EarthRadius,0,>, <0,OuterRadius,0,>, BoundRadius}}
	hollow
	texture {pigment {rgbt 1}}
	interior
	{
		media
		{
			scattering	{1, 0.5 * 1/ScaleAmount}
			method		3
			intervals	1
//			samples		30, 100
			samples		10, 40
			density
			{
				pigment_pattern {CloudPigment}
				density_map {[0.60 rgb 0][0.61 rgb 1]}
			}
		}
	}
	translate -y * EarthRadius
}
light_group
{
	light_source
	{
		Source_Location
		rgb 1
		parallel
		looks_like {SunObject}
	}
	object {CloudSphere}
	global_lights off
}
