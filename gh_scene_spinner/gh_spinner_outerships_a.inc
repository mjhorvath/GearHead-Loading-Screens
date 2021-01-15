//------------------------------------------------------------------------------Neighboring Craft

#if (!NoOuterShips)
/*
	// http://skotan.deviantart.com/art/Aquila-Mk-I-spacecraft-185944452
	union
	{
		verbose_include("Aquila-Mk_I.pov", 0)
		scale		32
		translate	+x * outer_shell_radius1
		translate	-z * dock_start
	}
*/
	// http://povrayinclude.wytraven.com/links.html
	union
	{
		#local exhaust_scale = nozzle_radius * 3/2;
		verbose_include("SPACESHP.POV", 0)
		scale		2
		rotate		+x * 90
		translate	-x * (outer_shell_radius1 + Meters * 1408)
		translate	-y * 0
		translate	-z * (city_length * 0)
	}

	// http://news.povray.org/povray.binaries.scene-files/thread/%3C4dfdbaad%40news.povray.org%3E/
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		rotate		+y * 90
		scale		1/2
		translate	-x * 0
		translate	+y * (outer_shell_radius1 * 6/4)
		translate	-z * (dock_start * 8/4)
	}
	union
	{
		verbose_include("Anastasia2bX_.pov", 0)
		rotate		+y * 90
		scale		1/2
		translate	-x * 0
		translate	+y * (outer_shell_radius1 * 6/4)
		translate	-z * (dock_start * 8/4)
		translate	-x * (Meters * 64)
		translate	+z * (Meters * 64)
	}
#end
