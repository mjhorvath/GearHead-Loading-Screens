// robo-arm
union
{
	cylinder {0, <0,4,0>, 16}
	sphere {y*8, 8}
	union
	{
		cylinder {<0,0,0>, <256,0,0>, 8}
		cylinder {<256,0,0>, <256,16,0>, 8}
		sphere {<256,0,0>, 8}
		sphere {<256,16,0>, 8}
		union
		{
			cylinder {<-256,0,0>, <0,0,0>, 8}
			cylinder {<-256,0,0>, <-256,16,0>, 8}
			sphere {<-256,0,0>, 8}
			sphere {<-256,16,0>, 8}
			union
			{
				cylinder {<64,0,0>, <0,0,0>, 8}
				cylinder {<64,0,0>, <64,16,0>, 8}
				sphere {<64,0,0>, 8}
				union
				{
					sphere {<0,0,0>, 8}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 000}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 120}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 240}
					translate y * 16
					translate x * 64
				}
				translate y * 16
				rotate -y * 30
				translate x * -256
			}
			translate y * 16
			rotate -y * 15
			translate x * 256
		}
		translate y * 8
		rotate +y * 15
	}
//	pigment {color rgb x}
}
/*
// perspective (default) camera
camera {
	orthographic
	location	z * 256
	look_at	0
	up	y*256
	right	x*image_width/image_height*256
	rotate x * -30
	rotate y * clock * 360
}

// create a regular point light source
light_source {
  0*x                  // light's position (translated below)
  color rgb <1,1,1>    // light's color
  translate <-200, 400, -200>
}

// Set a color of the background (sky)
background { color rgb< 1, 1, 1> }
*/