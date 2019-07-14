//------------------------------------------------------------------------------Sun, Sky & Planets

#if (!NoSky)
	#local sun_object = sphere
	{
		0, sun_radius
		texture
		{
			pigment {color rgb sun_color}
			finish {emission sun_color}
		}
	}
	// should I set a fade distance as well?
	light_source
	{
		sun_location
		color rgb sun_color
		looks_like {sun_object}
		parallel
		point_at 0
	}
	#if (!NoLensFlare)
		#declare camera_location	= Camera_Location;
		#declare camera_look_at		= Camera_LookAt;
		#declare camera_off		= true;
		#declare effect_location	= sun_location;
		#declare effect_type		= "Sun";
		#declare effect_scale		= 1/4;
		verbose_include("LENS_MOD.INC", 0)
	#end
	background {color srgb 0}
	sky_sphere {pigment {starfield_pigment_0}}
	// Galaxy variables, not very attractive
	#if (!NoGalaxy)
		#declare galaxy_bg		= 0;		// on or off
		#declare galaxy_objects		= 0;		// on or off
		#declare galaxy_starfield	= 0;		// on or off
		#declare galaxy_bgstars		= 0;		// type or off, not working?
		#declare galaxy_bgnebula	= 0;		// type or off, not working?
		#declare galaxy_nebula_sphere	= 0;		// type or off, not working?
		#declare galaxy_distance	= 100000;
		#declare galaxy_colouration	= 0.2;
		#declare star_type		= 3;
		#declare star_scale		= 1/10;
		#declare star_count		= 100000;
		verbose_include("GALAXY.BG", 0)
		verbose_include("GALAXY.SF", 0)
//		verbose_include("galaxy.inc", 0)
	#end
	#if (!NoPlanet)
		sphere
		{
			0, planet_radius
			texture {planet_texture}
			translate	planet_location
		}
	#end
#else
	light_source
	{
		<-15000, +15000, -15000> * <1/4,1,1/2>
		color rgb sun_color
		rotate +y * 090
		parallel
		point_at 0
	}
	background {color srgb 1/2}
#end