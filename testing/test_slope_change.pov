	#local dv_G = function(x,y,z)
	{
		min
		(
			max
			(
				1024 *
				sqrt
				(
					dv_Sqr
					(
						  hf_function1(x - dv_D,y,z).gray
						+ hf_function1(x + dv_D,y,z).gray
						- 2 * hf_function1(x,y,z).gray
					)
					+
					dv_Sqr
					(
						  hf_function1(x,y - dv_D,z).gray
						+ hf_function1(x,y + dv_D,z).gray
						- 2 * hf_function1(x,y,z).gray
					)
				)
				,0
			)
			,1
		)
	}