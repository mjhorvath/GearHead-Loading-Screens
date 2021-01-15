// Persistence Of Vision Ray Tracer Scene Description File
// -------------------------------------------------------
// File: @(#)earth_simple_free.pov
// Description: low resolution earth render
// Creation Date: $ 26 Jul 2005, 17:23:36 $
// Last modified: $ 27 May 2006, 16:18:18 $
// Author: chris_hormann@gmx.de
//

// ============ basic settings ============

#ifndef (View)
	// 1 = asia, 2 = europe, 3 = north america
	#declare View=1;
#end

// ========== advanced settings ===========
/*
#declare Earth_Radius=6371 * Meters;				// was 6371
#declare Height_Exaggerate=1;
#declare Terrain_Ambient=0.03;
#declare Terrain_Brightness=1.25;
#declare Max_Mountain=9;

#declare Media_Intensity=0.15;
#declare Media_Emission=0.065;
#declare Media_Eccentricity=0.56;
#declare Atmosphere_Top=100 * Meters;			// was 100

#declare Cloud_Brightness=0.42;				// was 0.42
#declare Light_Intensity=4.1;				// not used
*/
// ----------------------------------------

// ============== data files ==============

// set these to your data sources
// URLs given for each file

// ==== Elevation data, for example from:
// http://www.ngdc.noaa.gov/mgg/global/relief/
#declare IMG_Topo="DEM.pgm"

// ==== Color data, for example from:
// http://www.iac.ethz.ch/staff/stockli/bmng/
#declare IMG_Color="world.200406.3x21600x10800.jpg"
//#declare IMG_Color="earth/bmng/world.200407.3x5400x2700.jpg"

// ==== Cloud data, for example from:
// http://xplanet.sourceforge.net/clouds.php
#declare IMG_Clouds="cloud_combined_8192.jpg"

// ----------------------------------------

#macro ImageFile_Auto(Image_Name)

  #local Fnm_len=strlen(Image_Name);

  #local Cnt=Fnm_len;

  #while (Cnt>0)
    #if (strcmp(substr(Image_Name,Cnt,1), ".")=0)
      #local Fnm_ext3=substr(Image_Name,Cnt+1,3)
      #local Fnm_ext4=substr(Image_Name,Cnt+1,min(4, Fnm_len-Cnt))
      #if ((strcmp(Fnm_ext3, "jpg")=0) | (strcmp(Fnm_ext4, "jpeg")=0))
        #local File_type=1;           // jpg image
      #else
        #if ((strcmp(Fnm_ext3, "tif")=0) | (strcmp(Fnm_ext4, "tiff")=0))
          #local File_type=2;         // tif image
        #else
          #if (strcmp(Fnm_ext3, "tga")=0)
            #local File_type=3;       // tga image
          #else
            #if (strcmp(Fnm_ext3, "ppm")=0)
              #local File_type=4;     // ppm image
            #else
              #if (strcmp(Fnm_ext3, "pgm")=0)
                #local File_type=5;   // pgm image
              #else
                #if (strcmp(Fnm_ext3, "gif")=0)
                  #local File_type=6; // gif image
                #else
                  #local File_type=0; // png image (default)
                #end
              #end
            #end
          #end
        #end
      #end
      #local Cnt=0;
    #end
    #local Cnt=Cnt-1;
  #end

  #switch (File_type)
    #case (1)
      jpeg Image_Name
    #break
    #case (2)
      tiff Image_Name
    #break
    #case (3)
      tga Image_Name
    #break
    #case (4)
      ppm Image_Name
    #break
    #case (5)
      pgm Image_Name
    #break
    #case (6)
      gif Image_Name
    #break
  #else
    png Image_Name
  #end

#end

/*
// ----------------------------------------

// ==== Light position:
// x=Latitude, z=Longitude
// realistic Latitues are between +/- 23.5
//#declare Light_Angle=<20,0,30>;

// ==== View_Angle:
// x=Latitude, z=Longitude
//#declare View_Angle=<32,0,75>;

#switch (View)
	#case (1)
		// --- Asia ---
		#declare Light_Angle=<20,0,130>;
		#declare View_Angle=<32,0,75>;
	#break
	#case (2)
		// --- Europe ---
		#declare Light_Angle=<20,0,-43>;
		#declare View_Angle=<32,0,6>;
	#break
	#case(3)
		// --- North America ---
		#declare Light_Angle=<20,0,-22>;
		#declare View_Angle=<32,0,-92>;
	#break
#end

// ----------------------------------------

light_source {
	vrotate(y*250000, Light_Angle)
	color rgb Light_Intensity
}

camera {
	location    y*29000
	direction   z
	sky         z
	up          z
	right       (image_width/image_height)*x
	look_at     <0,0,0>
	angle       38
	rotate View_Angle
}
*/
// ----------------------------------------
// surface
// ----------------------------------------

#include "functions.inc"

#local fn_DEM=
	function {
		pigment {
			image_map {
				ImageFile_Auto(IMG_Topo)
				map_type 1				// was 0
				interpolate 3
				once
//				#if (version >= 3.7) file_gamma srgb #end		// new
			}
		}
	}

#local fn_DEM_Height=function { (fn_DEM(x, y, 0).red - 0.5)*2 * 32.767 }

#local fn_Shape=function { f_sphere(x, y, z, Earth_Radius)  }

#local fn_Pattern=
	function {
		fn_DEM_Height(1-(f_th(x,z,y)+pi)/(2*pi), f_ph(x,-z,y)/pi, 0)
	}

#local fn_Iso=
	function {
		fn_Shape(x,y,z)-
		fn_Pattern(x,y,z)*Height_Exaggerate
	}


#declare Pig_Relief=
	pigment {
		image_map {
			ImageFile_Auto(IMG_Color)
			map_type 1
			interpolate 2
//			#if (version >= 3.7) file_gamma srgb #end		// new
		}
		rotate -90*x
		scale <1,1,-1>
		rotate -90*z
	}

union
{


// slow
isosurface {
	function { fn_Iso(x,y,z) }
//	max_gradient 1.2
	accuracy 0.001
	contained_by{ sphere{ <0,0,0> Earth_Radius+Max_Mountain*Height_Exaggerate } }
	texture {
		pigment {
			Pig_Relief
		}
		finish {
			ambient Terrain_Ambient
			diffuse 0.5*Terrain_Brightness
		}
	}
	hollow on
}
/*
sphere {
	0, 1
	texture {
		pigment {
			Pig_Relief
		}
		finish {
			ambient Terrain_Ambient
			diffuse 0.5*Terrain_Brightness
		}
	}
	scale Earth_Radius
}
*/
// ----------------------------------------
// clouds
// ----------------------------------------

#declare Pig_Cloud=
	pigment {
		image_pattern {
			ImageFile_Auto(IMG_Clouds)
			map_type 1
			interpolate 2
//			#if (version >= 3.7) file_gamma srgb #end		// new
		}
		color_map {
			[0.36 color rgbt 1]
			[1.00 color rgbt <0.9,0.95,1.1,0.1> ]
		}
		rotate -90*x
		scale <1,1,-1>
		rotate -90*z
	}

#declare Tex_Cloud=
	texture {
		pigment {
			Pig_Cloud
		}
		normal {
			pigment_pattern {
				Pig_Cloud
			}
			0.5
		}
		finish {
			ambient Terrain_Ambient
			diffuse Cloud_Brightness
			brilliance 0.4
		}
	}

sphere {
	0, 1
	texture {
		Tex_Cloud
	}
	scale Earth_Radius+5*Height_Exaggerate
	hollow on
}


// ----------------------------------------
// atmosphere
// ----------------------------------------

#declare Fact=1-(Earth_Radius+0.001)/(Earth_Radius+Atmosphere_Top);

#declare Density2=
  density {
    spherical
    color_map {
      [ 0.0      rgb 0.0 ]
      [ Fact*0.1 rgb 0.0*<0.02, 0.05, 0.2>*0.03 ]
      [ Fact*0.2 rgb 0.0*<0.02, 0.07, 0.3>*0.12 ]
      [ Fact*0.3 rgb 0.0*<0.08, 0.18, 0.4>*0.36 ]
      [ Fact*0.4 rgb 0.0*<0.08, 0.18, 0.4>*1.0 ]
      [ Fact*0.5 rgb 0.0*<0.08, 0.18, 0.4>*2.0 ]
      [ Fact*0.6 rgb <0.08, 0.18, 0.4>*5 ]
      [ Fact*0.7 rgb <0.08, 0.18, 0.4>*12 ]
      [ Fact*0.95 rgb <0.12, 0.18, 0.28>*28 ]
      [ Fact rgb <0.0, 0.0, 0.0> ]
    }
  }

#declare Density1=
  density {
    spherical
    poly_wave 3
    color_map {
      [ 0.0  rgb 0.0 ]
      [ 0.5294*0.25e-6  rgb <0.02, 0.05, 0.2>*0.07 ]
      [ 0.5294*0.4e-6   rgb <0.02, 0.07, 0.3>*0.32 ]
      [ 0.5294*0.5e-6   rgb <0.08, 0.18, 0.4>*0.5 ]
      [ 0.5412*0.6e-6   rgb <0.08, 0.18, 0.4>*0.9 ]
      [ 0.5471*0.65e-6  rgb <0.08, 0.18, 0.4>*1.5 ]
      [ 0.5471*0.675e-6 rgb <0.08, 0.18, 0.4>*4.5 ]
      [ 0.5471*0.71e-6  rgb <0.08, 0.18, 0.4>*12 ]
      [ (Earth_Radius+0.001)/(Earth_Radius+Atmosphere_Top) rgb <0.0, 0.0, 0.0> ]
    }
  }


#declare Mat_Atm =
  material {
    texture {
      pigment {
        color rgbt <1.0, 1.0, 1.0, 1.0>
      }
    }
    interior {
      media {
        method 3
        scattering { 5 color rgb 0.01*Media_Intensity/(1000/astro_adjust) eccentricity Media_Eccentricity }
        emission rgb Media_Emission*0.01*Media_Intensity/(1000/astro_adjust)
        density {
          Density1
        }
      }
    }
  }

difference {
	sphere {
		<0,0,0>, 1
	}
	sphere { 
		<0,0,0>, 1
		scale (Earth_Radius+0.001)/(Earth_Radius+Atmosphere_Top)
	}
	bounded_by {
		sphere {<0,0,0>, 1}
	}
	material { Mat_Atm }
	scale Earth_Radius+Atmosphere_Top
	hollow on
}

// ----------------------------------------
// water
// ----------------------------------------

sphere {
	<0,0,0>, 1
	texture {
		pigment {
			color rgbft <0.07, 0.45, 0.8, 0.1, 0.75>
		}
		finish {
			ambient Terrain_Ambient*0.5
			diffuse 0.55
			reflection {
				0.1, 0.75
				falloff 2
			}
			conserve_energy
		}
	}
	scale Earth_Radius
	hollow on
}

rotate		+z * 90
scale		<1,1,-1>
rotate		+x * 90
rotate		<0,180,0>
translate	planet_location

}

// ----------------------------------------
