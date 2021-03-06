// Auth: Michael Horvath
// Home Page: http://isometricland.net
// This file is licensed under the terms of the CC-LGPL.
// Dependencies:
// 1. CITY GENERATOR INCLUDE FILE by Chris Colefax which I have heavily modified.
// 2. Rune's particle system
// 3. GALAXY INCLUDE FILE FOR PERSISTENCE OF VISION by Chris Colefax
// 4. Meshmerizing Mesh Maker Macros, param.inc from http://www.econym.demon.co.uk/isotut/param.htm
// 5. Lightsys IV from http://www.ignorancia.org/en/index.php?page=Lightsys
// 6. Truss Generator include by Theran Cochran
// 7. sphere.inc by Shuhei Kawachi
// 8. grasspatch.inc by Josh English
// 9. SPACE AGE TrueType font
// 10. mecha models by Joseph Hewitt, myself and TurboSquid
// 11. Raumschiff5.inc, Horus.inc by Frank Bruder
// 12. eagle.pov from the POV-Ray Object Collection
// 13. vulture.pov from the POV-Ray Object Collection

// Question: do light sources need to be gamma corrected?

//+KFI0 +KFF5 +KC +KI0 +KF0
//+KFI5 +KFF5 +KC
//+K0 +KC
//+SR0.5 +SC0.6 +ER0.9 +EC0.9
//+a0.0


//------------------------------------------------------------------------------Variables

#version 3.7;				// ommitting this seriously messes up the colors

#include "CIE.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys.inc"			// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "lightsys_constants.inc"	// http://www.ignorancia.org/en/index.php?page=Lightsys
#include "math.inc"
#include "shapes.inc"
#include "shapesq.inc"
#include "finish.inc"
#include "metals.inc"
#include "colors.inc"
#include "glass.inc"
#include "param.inc"		// Meshmerizing Mesh Maker Macros

// inter-scene variables, may be obsolete at this time
#declare pov_version	= 1;					// integer, 0 = 3.6; 1 = 3.7; 3.7 also has gamma adjustments in INI file
#declare Seed			= seed(8829464);
#declare Tiles			= 1;					// integer, the default size of the scene, measured in tiles. Use this to zoom in/out.
#declare Sprite_Height	= 128;					// float, still used? changes the camera's position. 0 for mecha, 1 for walls & terrain.
#declare Width			= 8;					// float, the default width of a tile.
#declare Included		= 1;					// boolean, tells any included files that they are being included.
#declare TexQual		= 2;					// integer, -1 = random colors, no finishes, no normals, no interiors; 0 = no finishes, no normals, no interiors; 1 = no interiors; 2 = everything
#declare Minimal		= 0;					// boolean, a minimal render with lots of features turned off
#declare Meters			= 1;					// float, 1 meter
#declare Subdivision	= 0;					// boolean, needed for some mecha, only works in unofficial build EXE of POV-Ray 3.6
#declare Camera_Inside	= 1;					// boolean
#declare Camera_CubeMap	= frame_number;			// integer, 0 = default orientation or off, 1 to 5 = the other cardinal directions

// toggles
#declare NoRadiosity	= 0;//					// boolean, very slowwwww!!!
#declare NoColors		= 0;//					// boolean, use grayscale colors for ships/mecha
#declare NoSky			= 0;					// boolean
#declare NoGalaxy		= 0;					// boolean, Chris Colefax's galaxy include
#declare NoPlanet		= 0;					// boolean, planet Jupiter
#declare NoLensFlare	= 1;//					// boolean, lens flare at sun position, usually not visible anyway
#declare NoOuterShips	= 1;//					// boolean
#declare NoHabitat		= 0;					// boolean, toggle outer shell, spokes and endcaps
#declare NoLampObject	= 0;					// boolean
#declare NoLampLight	= 0;					// boolean, very slowwwww!!!
#declare NoSpindle		= 1;//					// boolean
#declare NoAtmos		= 0;//					// boolean, very slowwwww!!!
#declare NoCity			= 0;					// boolean
#declare NoBuildings	= 0;					// boolean, render maglev and cars only
#declare NoCars			= 0;					// boolean
#declare NoStreet		= 0;					// boolean
#declare NoReactor		= 0;					// boolean
#declare NoDock			= 0;					// boolean
#declare NoDockShips	= 0;					// boolean
#declare NoNoseCone		= 0;					// boolean
#declare NoEngines		= 0;					// boolean
#declare NoArray		= 0;					// boolean
#declare NoPanels		= 0;					// boolean
#declare NoDomes		= 0;					// boolean
#declare NoStruts		= 0;					// boolean, everything not already disabled
#declare NoGreebles		= 0;					// boolean, blinkies, tanks, thrusters
#declare NoMeasure		= 1;//					// boolean, the distance measurement image map
#declare NoWeapons		= 1;//					// boolean, still used? mecha only?
#declare NewTrain		= 1;//					// boolean, use maglev instead of streetcars
#declare ShowWhole		= 1;					// boolean, show the entire outer shell, not finished
#declare glass_hollow	= 0;//					// boolean, used by CityGen, does this render faster or slower? should really always be off
#declare glass_thin		= 1;//					// boolean, used by CityGen, should not be mutually exclusive with glass_hollow, not all buildings' glass has an ior value, need to double check
#declare bound_fit		= 0;//					// boolean, used by CityGen, should bounding boxes be rotated and closer fit but not parallel to coordinate axes? otherwise, bounding boxes are parallel to coordinate axes but larger and less fit
#declare debug_progress	= 0;//					// boolean, used by CityGen, see CityGen docs
#declare GlassColor		= 0;//					// integer, dome glass color, 0 = gold, 1 = clear white
#declare NoseMode		= 0;//					// integer, 0 for textured paraboloid, 1 for web of connected cylinders (textured version is slower)
#declare SimpleLamp		= 0;//					// boolean, type of light at center of each habitat section, 0 = area light, 1 = single point light
#declare city_use_mesh	= 0;//					// boolean, replace some basic CSG shapes with meshes? may not work 100% of the time
#declare BothHabitats	= 1;					// boolean, render both habitats, or just one


//------------------------------------------------------------------------------Global settings

global_settings
{
	charset utf8
	assumed_gamma	1.0
	#if (!NoRadiosity)
		ambient_light	0
		radiosity
		{
			pretrace_start	0.08
			pretrace_end	0.02
			count			20
			error_bound		1
			recursion_limit	1
			normal			on
			brightness		0.8
			always_sample	no
			gray_threshold	0.8
			media			on
		}
	#end
	#switch (TexQual)
		#case (-1)
			max_trace_level 0
		#break
		#case (0)
			max_trace_level 4
		#break
		#case (1)
			max_trace_level 4
		#break
		#case (2)
			max_trace_level 4
		#break
	#end
}

#include "gh_spinner_variables_c.inc"
#include "gh_spinner_textures.inc"


//------------------------------------------------------------------------------Camera


#if (!Camera_Inside)
	// outside view, mode 2
	#declare Camera_Eye			= 0;					// integer, -1 is neither, 0 is left, 1 is right
	#declare Camera_Mode		= 2;					// 1 to 9; 1 = oblique; 2 = perspective; 3 = orthographic
	#declare Camera_Diagonal	= cosd(45);				// cosd(45)
	#declare Camera_Vertical	= 135;					// 135
	#declare Camera_Horizontal	= 30;			// asind(tand(30)) or 30
	#declare Camera_Aspect		= image_height/image_width;
	#declare Camera_Distance	= Meters * 256;
	#declare Camera_Translate	= <0,0,-Meters * 512>;		// <0,0,-Meters * 512>
	#declare Camera_Scale		= 256;					// 256
	#include "gh_camera.inc"
#else
	// inside view, modes 10 or 11
	#declare Camera_Mode		= 10;
	#include "gh_camera.inc"
#end


//------------------------------------------------------------------------------Text

#if (!NoMeasure)
	polygon
	{
		4, <0,0>,<0,1>,<1,1>,<1,0>
		texture
		{
			pigment
			{
				image_map {png "spinner_units_distance_b.png" once}
			}
		}
		translate <-1/2,-1/2,0>
		scale <Meters*2000,Meters*2000,1>
		rotate +x * 90
		rotate +y * 90
		translate -x * Meters * 1000
		translate -z * Meters * 500
	}
#end


//------------------------------------------------------------------------------Common Objects

// modifying this will mess up one of the habitats since the z rotation angle for the habitat is reversed
#declare cutaway_object1 = union
{
//	plane {-y, 0	rotate +z * 015}
//	plane {-y, 0	rotate -z * 015}
	plane {-y, 0}
}

#macro fuel_tank(in_len, in_rad)
	merge
	{
		sphere {-z*in_len/2, in_rad}
		sphere {+z*in_len/2, in_rad}
		cylinder {-z*in_len/2,+z*in_len/2,in_rad}
	}
#end

#macro blinky_sphere(in_rad)
	#local blinky_material = material
	{
		// check TexQual here?
		texture {pigment {color srgbt 1}}
		interior {media {emission x/in_rad*10}}
	}
	sphere
	{
		0, 1
		hollow
		material {blinky_material}
		scale in_rad
	}
#end


//------------------------------------------------------------------------------Spinner object

// Habitat shell
#if (!NoHabitat)
	#debug "\n>>Start habitat\n"
	#include "gh_spinner_habitat_shell_d.inc"
	#debug "\n<<Finish habitat\n"
#end

// Comms & nose cone
#if (!NoNoseCone)
	#debug "\n>>Start nose cone\n"
	#include "gh_spinner_nose_cone_c.inc"
	#debug "\n<<Finish nose cone\n"
#end

// Solar panels & agridomes
#if (!NoArray)
	#debug "\n>>Start truss array\n"
	#include "gh_spinner_solar_truss_array_d.inc"
	#debug "\n<<Finish truss array\n"
#end

// Docking ring
#if (!NoDock)
	#debug "\n>>Start docking bay\n"
	#include "gh_spinner_docking_ring_a.inc"
	#debug "\n<<Finish docking bay\n"
#end

// City buildings
#if (!NoCity)
	#debug "\n>>Start city buildings\n"
	#include "gh_spinner_citybuildings_c.inc"
	#debug "\n<<Finish city buildings\n"
#end

// Everything else
#debug "\n>>Start everything else\n"
#include "gh_spinner_colony_c.inc"
#debug "\n<<Finish everything else\n"


//------------------------------------------------------------------------------Debug

#debug "\n"
#debug concat("city_length = ", str(city_length,0,-1), "\n")
#debug concat("city_circum = ", str(city_circum,0,-1), "\n")
#debug concat("city_radius = ", str(city_radius,0,-1), "\n")
#debug concat("total_length = ",str(total_length,0,-1),"\n")
#debug concat("lamp_color = <",vstr(5,lamp_color,",",0,-1),">\n")
#debug concat("lamp_num = ",str(lamp_num,0,-1),"\n")
#debug concat("lamp_frq = ",str(lamp_frq,0,-1),"\n")
#debug concat("lamp_mod = ",str(lamp_mod,0,-1),"\n")
#debug concat("lamp_lit_num = ",str(lamp_lit_num,0,-1),"\n")
#debug "\n"
