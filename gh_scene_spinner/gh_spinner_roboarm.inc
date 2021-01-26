// robo-arm
// need to add some knuckles and joints in the fingers
#local robo_radius = 4;
#local robo_length = 256;
union
{
	// base
	cylinder {0, +y*robo_radius/2, robo_radius*2}
	// nub
	cylinder {0, +y*robo_radius, robo_radius}
	sphere {+y*robo_radius, robo_radius}
	// arm
	union
	{
		cylinder {0, +x*robo_length, robo_radius}
		cylinder {+x*robo_length, <+robo_length,+robo_radius*2,0>, robo_radius}
		sphere {+x*robo_length, robo_radius}
		sphere {<+robo_length,+robo_radius*2,0>, robo_radius}
		union
		{
			cylinder {-x*robo_length, 0, robo_radius}
			cylinder {-x*robo_length, <-robo_length,+robo_radius*2,0>, robo_radius}
			sphere {-x*robo_length, robo_radius}
			sphere {<-robo_length,+robo_radius*2,0>, robo_radius}
			union
			{
				cylinder {+x*robo_length/4, 0, robo_radius}
				cylinder {+x*robo_length/4, <+robo_length/4,+robo_radius*2,0>, robo_radius}
				sphere {+x*robo_length/4, robo_radius}
				union
				{
					sphere {0, robo_radius}
					sphere {y*4,2 translate z*4 rotate x * 15 rotate y * 000}
					sphere {y*4,2 translate z*4 rotate x * 15 rotate y * 120}
					sphere {y*4,2 translate z*4 rotate x * 15 rotate y * 240}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 000}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 120}
					cone {y*4, 2, y*16, 0 translate z*4 rotate x * 15 rotate y * 240}
					translate	+y*robo_radius*2
					translate	+x*robo_length/4
				}
				translate	+y*robo_radius*2
				rotate		-y*30
				translate	-x*robo_length
			}
			translate	+y*robo_radius*2
			rotate		-y*15
			translate	+x*robo_length
		}
		translate	+y*robo_radius
		rotate		+y*15
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
