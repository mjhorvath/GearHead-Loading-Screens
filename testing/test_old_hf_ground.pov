#if (!NoGround)
	#local hf_pigment1 = pigment
	{
		image_map
		{
//			png "hf_original.png"
//			png "hf_gray.png"
			png "hf_big.png"
		}
		rotate x * 180		// flipped
	}
	#local hf_pigment0 = pigment {color rgb 1}
	#local hf_pigment2 = pigment {color rgb 0}
	#local hf_pigment3 = pigment
	{
		function {sin(acos(f_r(x,y,z)))}
//		function {(sin(f_r(x,y,z) * pi + pi / 2) + 1) / 2}
		pigment_map
		{
			[0 hf_pigment2]
			[1 hf_pigment1 translate <-1/2,-1/2,0,> scale 2]
		}
		scale 1/2
		translate <1/2,1/2,0,>
	}
	#local hf_function1 = function {pigment {hf_pigment3}}
	#local Ground_a = height_field
	{
		function 1024, 1024 {hf_function1(x,y,z).gray}
//		png "hf_big.png"
		smooth
		texture {tx_texture1}
		translate <-1/2,0,-1/2,>
		scale y * 1/16 * HeightScale
		scale SceneScale
	}
#else
	#local WaterLevel = -1;
	#local TreesLevel = -1;
	#local GrassLevel = -1;
	#local RocksLevel = -1;
	#local Ground_a = plane {y, 0 pigment {color rgb 1/2}}
#end