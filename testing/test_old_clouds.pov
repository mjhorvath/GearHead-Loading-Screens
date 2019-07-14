#local ScaleAmount = 32;
#local CloudPigment = pigment
{
	average
	pigment_map {[1 planar][1 granite scale 100]}
}
#local CloudBox = box
{
	<-200,-10,-200,>,<+200,+10,+200,>
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
				density_map {[.6 rgb 0][.61 rgb 1]}
			}
		}
	}
	scale		ScaleAmount
	translate	y * 32 * 16
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
	object {CloudBox}
	global_lights off
}
