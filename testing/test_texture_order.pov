//==============================================

#version 3.7;

camera {
  location  <3,5,-7>
  right     x*image_width/image_height
  look_at   <0,1,0>
}

light_source{ <1,2,-3>*3000 colour rgb 1 }

//----------------------------------------------
#default { pigment { colour red 1 } }
//----------------------------------------------

// The plane and box have no texture at all,
// and will remain "open to new suggestions":
#declare Plane  = plane  { <0,1,0>, 0 }
#declare Box    = box    { <-2,0,-1>, <0,2,1> }

// The sphere's texture is fixed forever to red here:
#declare Sphere = sphere { <1,1,0>, 1 texture {} }

//----------------------------------------------
#default { pigment { colour green 1 } }
//----------------------------------------------

// The front union per se has no texture either,
// and will remain "open to new suggestions"
// (except for the sphere, which is fixed to red):
#declare Front = union {
  object { Sphere }
  object { Box }
  translate <0,0,-2>
}

// The back union's texture is fixed forever to green here
// (except for the sphere, which is fixed to red):
#declare Back = union {
  object { Sphere }
  object { Box }
  translate <0,0,2>
  texture {}
}

//----------------------------------------------
#default { pigment { colour rgb 1 } }
//----------------------------------------------

// All unfixed textures are fixed to white now:
object { Front }
object { Back }
object { Plane }

//----------------------------------------------
#default { pigment { colour blue 1 } }
//----------------------------------------------

// Changing the default yet again to blue has
// no further effect.

//==============================================

There is also a third difference, which I'll leave as an exercise to the
reader to verify experimentally, and which is of vital importance to the
original problem:

If you specify "texture{}", the default texture applied to the object
will be subject to any subsequent transformations applied to that
object, whereas if you specify no texture at all, a default texture
applied to the object will remain entirely untransformed (and a texture
inherited from a parent CSG object will only be subject to
transformations of that parent).


Thus, defining all textures as empty and using a gradient default will
most likely not achieve the desired results, as many objects will
probably include some transformation or the other.


The only currently viable solution I can imagine is to alway use some
macro to apply textures, and have it evaluate to /nothing at all/ when
rendering a depth-coded version of the scene, like so:

  #if (DepthRender)
    default { /* some gradient-based texture */ }
    #macro Texture(t) #end
  #else
    #macro Texture(t)
      texture { t }
    #end
  #end
