/*
	3dto3d engine by tb-software.com (support@tb-software.com)
	Created by POV Export Plugin 1.2 at Thu Jul 07 01:59:15 2011

	Master POV file:
*/
#declare V_WorldBoundMin = <-2.592900, -2.461200, -1.583200>;
#declare V_WorldBoundMax = <3.157600, 2.767800, -2.216900>;

#include "Radar_1_g.inc"


light_source
{
	z*1000,1
	parallel
}
light_source
{
	x*1000,1
	parallel
}
light_source
{
	y*1000,1
	parallel
}

object{ P_mat_0 rotate x * -90 translate y * 0.5}
object{ P_mat_1 rotate x * -90 translate y * 0.5}

camera
{
	up		y*10
	right		x*10
	location	+z*10
	direction	-z*10
	rotate	x * -30
}

union
{
	sphere		{0,    0.001 pigment{color rgb <0,0,0,>}}
	cylinder	{0, x, 0.001 pigment{color rgb <1,0,0,>}}
	cylinder	{0, y, 0.001 pigment{color rgb <0,1,0,>}}
	cylinder	{0, z, 0.001 pigment{color rgb <0,0,1,>}}
	finish {ambient 1}
	scale		100
	translate	<0,0,0,>
	no_shadow
	no_reflection
}