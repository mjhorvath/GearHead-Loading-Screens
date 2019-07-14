#version 3.7
global_settings{assumed_gamma 1.0}

background {color rgb 0}

camera {
  perspective
  location  <0, 0, -5>
  look_at   <0, 0,  0>
  right     x*image_width/image_height
  // angle 67
}

light_source {
  0*x  // light's position (translated below)
  color rgb <1,1,1>
  translate <-20, 40, -20>
}



#local atmos_material =
     material
     {
 // check TexQual here?
     texture {
       pigment {srgbt 1}}
       interior
        {
         media
        {
          scattering
         {
         4, color rgb <0.2,0.4,1.0>// crappy approximaion of TerraPOV value
          extinction 1
          }
          samples 10
          density
               {
               cylindrical
               poly_wave 0.25
              color_map
                {
                 [0 srgb 1.0]
                 [1 srgb 0.0]
                 }
              }
           }
        }
}

sphere{0,1
 hollow // IMPORTANT!
 material{atmos_material}
 }
