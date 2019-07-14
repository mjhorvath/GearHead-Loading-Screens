/*************************************************************************
 CITY GENERATOR HOTEL BUILDINGS FILE FOR PERSISTENCE OF VISION 3.x

 Created by Chris Colefax, 1 February 1999
 NOTE: This file is designed for use with City.mcr and City.inc
       To use, include the file before including City.inc, with any other
       object/building files you want to use.

**************************************************************************/

// INCLUDE DEFAULT OBJECTS FILE IF REQUIRED
   #ifndef (building_size) #include "DEFAULT.OBJ" #end

// COMMON TEXTURES AND FINISHES
   #local FMetal = finish {specular .2 roughness .1 metallic brilliance 10}
   #local FGlass = finish {specular .5 roughness .05 reflection .4}

// HOTEL #1 (White marble)
   #declare building_size[building_types] = <30, 5, 30>;
   #declare building_options[building_types] = build_texture + build_base + build_profile + build_details + build_roof + build_window_profile;
   #declare building_texture[building_types] = texture {
      pigment {wrinkles color_map {[.45 gamma_color_adjust(<1,1,1>*.9)] [.5 gamma_color_adjust(<1,1,1>*.8)] [.55 gamma_color_adjust(<1,1,1>*.9)]} scale 4}
      normal {bumps .2 scale .05}
      finish {phong .1 phong_size 3}}
   #local Column = cylinder {0, y * 5, .5 texture {building_texture[building_types]
      normal {radial bump_size -.5 scallop_wave frequency 9}}}
   #declare building_profile[building_types] = union {
      object {Column translate <-12, 0, -8>} object {Column translate <-4, 0, -8>}
      object {Column translate <4, 0, -8>} object {Column translate <12, 0, -8>}}
   #declare building_base[building_types] = union {
      box {<-14.5, 0, -7>, <14.5, 5, 14.5>}
      #local C = 0; #while (C <= 1)
         box {<-15, C*3, -15+(C*5)>, <15, (C+.1)*3, 15>}
      #local C = C + .1; #end }
   #local WindowCutout = union {box {<-.8, 1.8, -7.1>, <.8, 3.5, 14.6>}
      cylinder {<0, 3.3, -7.1>, <0, 3.3, 14.6>, .8}}
   #declare building_details[building_types] = union {
      box {<-15, 4.6, -9>, <15, 5, 15>}
      difference {box {<-14.5, 0, -7>, <14.5, 5, 14.5>}
      #local C = -10; #while (C <= 10)
         object {WindowCutout translate x * C}
      #local C = C + 4; #end }}
   #declare building_windows[building_types] = box {<-14.4, 0, -6.8>, <14.4, 4.99, 14.3>}
   set_window_texture (
      texture {pigment {gamma_color_adjust(<0, 0, .1>)} finish {FGlass}},
      texture {pigment {gamma_color_adjust(<1, 1, .8>)} finish {FGlass ambient 1}},
      <4, 5, 0>)
   #declare building_roof[building_types] = union {
      box {<-15, 0, -8>, <15, 1.5, -7>}
      cylinder {<0, -6, -8>, <0, -6, -7>, 11 clipped_by {box {<-15, 1.5, -8.1>, <15, 5, -6.9>}}}}
   #declare building_types = building_types + 1;

// HOTEL #2 (Tan stucco)
   #declare building_size[building_types] = <100, 20, 100>;
   #declare building_options[building_types] = build_texture + build_profile + build_window_profile + build_base + build_roof;
   #declare building_texture[building_types] = texture {
      pigment {gamma_color_adjust(<.7, .65, .5>)}
      normal {granite -.8 scallop_wave scale <100, 50, 100>}}
   #declare building_profile[building_types] = union {
      box {<-45, 0, -35>, <45, 20, 45>}
      cylinder {<-45, 0, -35>, <-45, 20, -35>, 4} cylinder {<45, 0, -35>, <45, 20, -35>, 4}
      cylinder {<-45, 0, 45>, <-45, 20, 45>, 4} cylinder {<45, 0, 45>, <45, 20, 45>, 4}
      cylinder {<0, 0, -35>, <0, 20, -35>, 8 scale <4, 1, 1>}}
   #declare building_windows[building_types] = union {
      box {<-45.01, 0, -35.01>, <45.01, 20, 45.01>}
      cylinder {<0, 0, -35>, <0, 20, -35>, 8.01 scale <4, 1, 1>}}
   #local Glass = texture {normal {bumps .01 scale .001} finish {FGlass reflection <.6, .7, .5>}}
   #declare  building_window_texture[building_types] = texture {
      gradient y texture_map {
      [.6 pigment {gamma_color_adjust(<1,1,1,0,1>)}] [.6 window_texture (
         texture {Glass pigment {gamma_color_adjust(<1,1,1>*0)}},
         texture {Glass pigment {gamma_color_adjust(<.65, .7, .6>)} finish {ambient 1}},
         <.2, 1, .2>)]}
      scale 20 translate -y*4}
   #declare building_window_size[building_types] = <4, 0, 4>;
   #local LightFitting = union {cylinder {<0, 18, -5>, <0, 18, 0>, .3}
      sphere {0, .6 scale <1, .5, 1> translate <0, 18, -5>}
      #if (city_night) spotlight_cone (<0, 18, -5>, .3, <0, 0, -5>, 7, gamma_color_adjust(<1.3, 1.2, 1, 0, .8>), 3) #end
      pigment {gamma_color_adjust(<1,1,1>*.1)}}
   #declare building_base[building_types] = union {
      cylinder {<0, 18, -60>, <0, 18, -42>, 7 clipped_by {box {<-7, 18, -61>, <7, 25, -42>}}
         pigment {gamma_color_adjust(<.1, .35, 0>)} normal {gradient z bump_size .2 scallop_wave scale 3}}
      cylinder {<-6.5, 0, -59.5>, <-6.5, 18, -59.5>, .5 pigment {gamma_color_adjust(<1,1,1>*.1)}}
      cylinder {<6.5, 0, -59.5>, <6.5, 18, -59.5>, .5 pigment {gamma_color_adjust(<1,1,1>*.1)}}
      object {LightFitting translate <-36, 0, -35>} object {LightFitting translate <36, 0, -35>}
      object {LightFitting rotate y * 45 translate <-7, 0, -60>} object {LightFitting rotate y * -45 translate <7, 0, -60>}}
   #local RoundRoof = union {torus {4, 1.5}
      cylinder {<0, 10, 0>, <0, 11.5, 0>, 4} torus {4, 1.5 translate y*10}}
   #declare building_roof[building_types] = union {
      union {
         torus {8, 1.5 scale <3.53, 1, 1> translate <0, 0, -35>}
         cylinder {<-45, 0, -35>, <45, 0, -35>, 1.5} cylinder {<-45, 0, 45>, <45, 0, 45>, 1.5}
         cylinder {<-45, 0, -35>, <-45, 0, 45>, 1.5} cylinder {<45, 0, -35>, <45, 0, 45>, 1.5}
         object {RoundRoof translate <-45, 0, -35>} object {RoundRoof translate <45, 0, -35>} 
         object {RoundRoof translate <-45, 0, 45>} object {RoundRoof translate <45, 0, 45>} 
         object {building_profile[building_types] scale <1, 1.5/20, 1>}
         texture {building_texture[building_types] pigment {gamma_color_adjust(<.5, .4, .3>)}}}
      cylinder {0, y*10, 4 translate <-45, 0, -35>} cylinder {0, y*10, 4 translate <45, 0, -35>}
      cylinder {0, y*10, 4 translate <-45, 0, 45>} cylinder {0, y*10, 4 translate <45, 0, 45>}}
   #declare building_types = building_types + 1;
