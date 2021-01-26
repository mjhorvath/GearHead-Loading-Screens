// robo-arm
union
{
	// base
	cylinder {0, <0,4,0>, 16}
	// nub
	cylinder {0, y*8, 8}
	sphere {y*8, 8}
	// arm
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
	#ifndef (Included)
		pigment {color rgb 1}
	#end
}

#ifndef (Included)
	// perspective (default) camera
	camera {
		orthographic
		location	z * 256
		look_at		0
		up			y*512
		right		x*image_width/image_height*512
		rotate		x * -30
		rotate		y * 45
	}
	
	// create a regular point light source
	light_source {
		0*x                  // light's position (translated below)
		color rgb <1,1,1>    // light's color
		translate <-200, 400, -200>
		parallel
		point_at 0
	}
	
	// Set a color of the background (sky)
	background { color rgb< 1, 1, 1> }

	// floor
	plane {
		y, 0
		pigment {color rgb x}
	}

	// axes
	cylinder {
		0, x*1000, 1
		pigment {color rgb x}
		finish {emission x}
	}
	cylinder {
		0, y*1000, 1
		pigment {color rgb y}
		finish {emission y}
	}
	cylinder {
		0, z*1000, 1
		pigment {color rgb z}
		finish {emission z}
	}
	
#end
