// Persistence of Vision Ray Tracer Scene Description File
//
//      Title: Aquila Mk I spacecraft
//     Author: Frank Bruder <http://purl.org/net/2008,frankbruder/home>
//  Copyright: 2010 Frank Bruder
//    License: Creative Commons Attribution 3.0 <http://creativecommons.org/licenses/by/3.0/>

#ifndef (Included)
	light_source { <-500, 300, -200> color rgb <1, 1, 1> }
	camera {
	  up image_height*y
	  right image_width*x
	  direction (2*image_height)*z
	  
	  sky <0, 1, 1>
	  
	  location <-14, 6, -10>
	  look_at <0, 0, 0>
	}
#end

// The spacecraft:
// Forward direction is +z
// This is just a rough design sketch.
union {
  
  // Radius of the central octagon prism:
  // Must not be smaller than sqrt(2), or construction won't work.
  #local octagon_radius = sqrt(3); // is just an arbitrary value.
  
  // Length of the central octagon prism:
  #local octagon_length = octagon_radius*sqrt(2-sqrt(2)); // chosen so the faces are squares.
  
  // Length of the connecting polytopes between square and octagonal parts:
  #local connector_length = sqrt(1/2); // is just an arbitrary value.
  // use  octagon_radius-1 , for 45 degree angles.
  // use  sqrt(3-pow(octagon_radius-1, 2)) , for equilateral triangles.
  
  // Connecting polytope between square and octagonal parts:
  // This is not cut at the octagonal end, since it will be used in an
  // intersection anyways.
  #local connector = intersection {
    plane { -z, 0 }
    #local c = 0;
    #while (c < 4)
      plane { < 0,  1, 1-octagon_radius>, 0 translate y rotate <0, 0, 90*c> }
      plane { y, 0
        matrix <1, -1+octagon_radius, 1, -1, 1, 0, 1-sqrt(1/2)*octagon_radius, -1+sqrt(1/2)*octagon_radius, 1, -1, 1, 0>
        rotate <0, 0, 90*c>
      }
      plane { y, 0
        matrix <1, -1+octagon_radius, 1, -1, 1, 0, 1-sqrt(1/2)*octagon_radius, -1+sqrt(1/2)*octagon_radius, 1, -1, 1, 0>
        scale <-1, 1, 1>
        rotate <0, 0, 90*c>
      }
      #local c = c + 1;
    #end
    scale <1, 1, connector_length>
  }
  
  // Here we construct the middle piece consisting of an octagon prism
  // and connecters at both ends.
  // (To do: Windows)
  intersection {
    #local c = 0;
    #while (c < 8)
      plane { y, 0 rotate <0, 0, 22.5> translate <0, octagon_radius, 0> rotate <0, 0, 45*c> }
      #local c = c + 1;
    #end
    object { connector translate <0, 0, -octagon_length/2-connector_length> }
    object { connector translate <0, 0, -octagon_length/2-connector_length> rotate <180, 0, 45> }
    bounded_by { cylinder { <0, 0, -octagon_length/2-connector_length>, <0, 0, octagon_length/2+connector_length>, octagon_radius } }
  }
  
  // A cube of side length 2 with pyramids on four sides:
  // Thruster aggregates will be placed at the pyramid tips.
  #local thruster_block = intersection {
    plane { -z, 1 }
    plane {  z, 1 }
    plane { <-1, -1,  0>, 0 translate <-1, -1,  0> }
    plane { <-1,  1,  0>, 0 translate <-1,  1,  0> }
    plane { < 1,  1,  0>, 0 translate < 1,  1,  0> }
    plane { < 1, -1,  0>, 0 translate < 1, -1,  0> }
    plane { < 0, -1, -1>, 0 translate < 0, -1, -1> }
    plane { <-1,  0, -1>, 0 translate <-1,  0, -1> }
    plane { < 1,  0, -1>, 0 translate < 1,  0, -1> }
    plane { < 0,  1, -1>, 0 translate < 0,  1, -1> }
    plane { < 0, -1,  1>, 0 translate < 0, -1,  1> }
    plane { <-1,  0,  1>, 0 translate <-1,  0,  1> }
    plane { < 1,  0,  1>, 0 translate < 1,  0,  1> }
    plane { < 0,  1,  1>, 0 translate < 0,  1,  1> }
    bounded_by { box { <-2, -2, -1>, <2, 2, 1> } }
  }
  
  // A simple thruster:
  #local thruster = union {
    cone { <0, 0, 0>, 0, <0, 0, -2>, 1 open hollow }
    cylinder { <0, 0, 0>, <0, 0, -2*0.4>, 0.4 open hollow }
    pigment { rgb 0.7 }
  }
  
  // Aft thruster block and main thruster:
  union {
    object { thruster_block }
    
    // Aggregate of four manoeuvering thrusters on pyramid tip,
    // to be used four times:
    #local thruster_aggregate = union {
      box { <-1, -1, -2>, <1, 1, 2> }
      object { thruster translate <0, 0, -2> }
      object { thruster rotate <0, 90, 0> translate <-1, 0, 0> }
      object { thruster rotate <0, 270, 0> translate <1, 0, 1> }
      scale 0.1
      translate <0, 2, 0>
    }
    object { thruster_aggregate }
    object { thruster_aggregate rotate  90*z }
    object { thruster_aggregate rotate 180*z }
    object { thruster_aggregate rotate 270*z }
    
    box { <-1, -1, -1>, <1, 1, -2> }
    
    // The main thruster is just a larger copy of the manoeuvering
    // thruster for now.
    object { thruster scale 0.5 translate <0, 0, -2> }
    
    translate <0, 0, -1-octagon_length/2-connector_length>
  }
  
  // Front thruster block:
  union {
    object { thruster_block }
    
    // Aggregate of four manoeuvering thrusters on pyramid tip,
    // to be used four times:
    // Note that these differ from those on the aft thruster block,
    // since the thruster blocks are rotated by 45 degree relative to
    // each other, but the thrusters are aligned to the same set of
    // main axes.
    #local thruster_aggregate = union {
      box { <-1, -1, -2>, <1, 1, 2> }
      object { thruster translate <0, 0, -2> }
      object { thruster rotate <0, 270, 0> translate <1, 0, 0> }
      object { thruster rotate <90, 0, 0> translate <0, 1, 1> }
      scale 0.1
      rotate <0, 0, 45>
      translate <0, 2, 0>
    }
    object { thruster_aggregate }
    object { thruster_aggregate rotate  90*z }
    object { thruster_aggregate rotate 180*z }
    object { thruster_aggregate rotate 270*z }
    
    translate <0, 0, -1-octagon_length/2-connector_length>
    rotate <180, 0, 45>
  }

  // Just a white texture for now.
  pigment { rgb 1 }
  finish {
    diffuse 1
    ambient 0.1
  }
}