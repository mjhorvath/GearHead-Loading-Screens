global_settings
{
	hf_gray_16 1
}


#declare Width = 64;

camera
{
	orthographic
	up		+z * Width * Width * image_height/image_width
	right		+x * Width * Width
	location	+y * 1024
	direction	-y * 1024
}

#local hf_pigment_function_pow = function {y * pow(256,3)}
#local hf_pigment_function_b = function {mod(hf_pigment_function_pow(x,y,z), pow(256,1))}
#local hf_pigment_function_g = function {mod(hf_pigment_function_pow(x,y,z) - hf_pigment_function_b(x,y,z), pow(256,2))}
#local hf_pigment_function_r = function {mod(hf_pigment_function_pow(x,y,z) - hf_pigment_function_b(x,y,z) - hf_pigment_function_g(x,y,z), pow(256,3))}
#local hf_pigment_r = pigment
{
	function {hf_pigment_function_r(x,y,z) / pow(256,3)}
	color_map {[0 rgb 0][1 rgb x]}
}
#local hf_pigment_g = pigment
{
	function {hf_pigment_function_g(x,y,z) / pow(256,2)}
	color_map {[0 rgb 0][1 rgb y]}
}
#local hf_pigment_b = pigment
{
	function {hf_pigment_function_b(x,y,z) / pow(256,1)}
	color_map {[0 rgb 0][1 rgb z]}
}
#local hf_pigment_rgb = pigment		// This is the one you want
{
	average
	pigment_map {[3 hf_pigment_b][3 hf_pigment_g][3 hf_pigment_r]}
}

#local hf_pigment_gray = pigment
{
	gradient y
	color_map {[0 rgb 0][1 rgb 1]}
}

height_field
{
	png "Untitled1_hf.png"
	smooth
	texture
	{
//		pigment {hf_pigment_rgb}
		pigment {hf_pigment_gray}
		finish {ambient 1}
	}
	translate <-1/2, 0, -1/2>
	scale y * 1/16
	scale Width * Width
}
