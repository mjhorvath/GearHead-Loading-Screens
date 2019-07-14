/*
	3dto3d engine by tb-software.com (support@tb-software.com)
	Created by POV Export Plugin 1.2 at Thu Jul 07 02:53:03 2011

	Master POV file:
*/
#declare V_WorldBoundMin = <-132.681717, -178.140625, 0.511040>;
#declare V_WorldBoundMax = <120.700874, 322.236694, 209.010437>;

#include "spaceshipturret_g.inc"

camera{ P_camera0 }
object{ P_light0 }
object{ P_light1 }
object{ P_light2 }
object{ P_Bships_pro }
object{ P_Bships_pr0 }
object{ P_Bships_pr1 }


union
{
	sphere		{0,    0.01 pigment{color rgb <0,0,0,>}}
	cylinder	{0, x, 0.01 pigment{color rgb <1,0,0,>}}
	cylinder	{0, y, 0.01 pigment{color rgb <0,1,0,>}}
	cylinder	{0, z, 0.01 pigment{color rgb <0,0,1,>}}
	finish {ambient 1}
	scale		100
	translate	<0,0,0,>
	no_shadow
	no_reflection
}