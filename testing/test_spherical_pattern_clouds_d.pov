camera {location <1.5, 1.5,-3> look_at 0}
light_source {<1,50,-100> color rgb 1}

box {<-1,-1,-0.01>,<1,1,2>
 pigment {gradient z
   pigment_map {
     [0   granite scale 0.1]
     [0.5 granite scale 0.1]
     [0.5 gradient z]
     [1   gradient z]
   }
   turbulence 0.01
   warp {black_hole <0,0,-0.1>,1}
 }
} 