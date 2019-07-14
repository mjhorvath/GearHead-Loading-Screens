// Desc: Textures used by many objects created for GearHead.
// Auth: Michael Horvath
// Home Page: http://www.geocities.com/Area51/Quadrant/3864/gearhead.htm
// This file is licensed under the terms of the CC-LGPL.

// -------------------------------------------------------------
// Textures

#declare Finish_Bright = finish
{
	diffuse 1
	ambient 1
	brilliance 1
	conserve_energy
}

#declare Finish_Stark = finish
{
	diffuse 1
	ambient 0
	brilliance 0
//	specular 0
	conserve_energy
}

#declare Finish_Normal = finish
{
	diffuse 0.7	//0.7
	ambient 0.3	//0.3
//	brilliance 1
//	specular 0.2
	conserve_energy
}

#declare Default_Finish = Finish_Normal;

#declare Plain_White = texture
{
	pigment {color rgb 1}
	finish {Default_Finish}
}

#declare Plain_Black = texture
{
	pigment {color rgb 0}
	finish {Default_Finish}
}

#declare Plain_Clear = texture
{
	pigment {color rgbt 1}
	finish {Default_Finish}
}

#declare Plain_Gray = texture
{
	pigment {color rgb 1/2}
	finish {Default_Finish}
}

#declare Plain_DarkGray = texture
{
	pigment {color rgb 1/4}
	finish {Default_Finish}
}

#declare Plain_VeryDarkGray = texture
{
	pigment {color rgb 1/8}
	finish {Default_Finish}
}

#declare Plain_LightGray = texture
{
	pigment {color rgb 3/4}
	finish {Default_Finish}
}

#declare Plain_DarkGreen = texture
{
	pigment {color rgb <073,116,060,>/255}
	finish {Default_Finish}
}

#declare Plain_DarkBlue = texture
{
	pigment{color rgb <000,000,136,>/255}
	finish {Default_Finish}
}

#declare Plain_Brown = texture
{
	pigment {color rgb <098,064,030,>/255}
	finish {Default_Finish}
}

#declare Plain_Beige = texture
{
	pigment {color rgb <140,123,093,>/255}
	finish {Default_Finish}
}

#declare Plain_Red = texture
{
	pigment {color rgb <255,000,000,>/255}
	finish {Default_Finish}
}

#declare Plain_MedRed = texture
{
	pigment {color rgb <128,000,000,>/255}
	finish {Default_Finish}
}

#declare Plain_QrtRed = texture
{
	pigment {color rgb <192,000,000,>/255}
	finish {Default_Finish}
}

#declare Plain_Green = texture
{
	pigment {color rgb <000,255,000,>/255}
	finish {Default_Finish}
}

#declare Plain_MedGreen = texture
{
	pigment {color rgb <000,128,000,>/255}
	finish {Default_Finish}
}

#declare Plain_QrtGreen = texture
{
	pigment {color rgb <000,192,000,>/255}
	finish {Default_Finish}
}

#declare Plain_Blue = texture
{
	pigment {color rgb <000,000,255,>/255}
	finish {Default_Finish}
}

#declare Plain_Yellow = texture
{
	pigment {color rgb <255,255,000,>/255}
	finish {Default_Finish}
}

#declare Plain_MedYellow = texture
{
	pigment {color rgb <128,128,000,>/255}
	finish {Default_Finish}
}

#declare Plain_QrtYellow = texture
{
	pigment {color rgb <224,224,000,>/255}
	finish {Default_Finish}
}

#declare Plain_Pink = texture
{
	pigment {color rgb <191,064,095,>/255}
	finish {Default_Finish}
}

#declare Plain_Magenta = texture
{
	pigment {color rgb <255,000,255,>/255}
	finish {Default_Finish}
}
