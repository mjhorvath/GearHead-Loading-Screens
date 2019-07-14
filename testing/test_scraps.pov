				// glass
				#local glass_object = intersection
				{
					box
					{
						<-Side_B2, (Level_Count+0) * city_storey_height, -Side_B2>, <+Side_B2, (Level_Count+1) * city_storey_height, +Side_B2>
						rotate y * (2 * Level_Count + Storey_Rotate) * Storey_Direction
					}
					difference
					{
						cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - (Level_Count+0) * city_storey_height}
						cylinder {<0,city_radius,-32>, <0,city_radius,+32>, city_radius - (Level_Count+1) * city_storey_height}
					}
				}
				object
				{
					pos_object(glass_object, Translate)
					hollow
					material {glass_mat}
				}

	// glass
	#local glass_mesh = mesh
	{
		#local Level_Count = 1;
		#while (Level_Count < Levels)
			#local Side_A2 = city_radius - (Level_Count) * city_storey_height;
			#local Side_C2 = Side_A2 / cos(Theta);
			#local Side_B2 = Side_C2 * sin(Theta);
			#local Storey_Rotate = 2 * Level_Count + Building_Rotate;
			triangle
			{
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate))
				
			}
			triangle
			{
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate))
			}
			triangle
			{
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate))
			}
			triangle
			{
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate))
			}
			triangle
			{
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<+Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate))
			}
			triangle
			{
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<+Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate))
			}
			triangle
			{
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, +Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate))
			}
			triangle
			{
				vrotate(<-Side_B1, (Level_Count-1) * city_storey_height, -Side_B1>, y * (2 * (Level_Count-1) + Building_Rotate)),
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, -Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate)),
				vrotate(<-Side_B2, (Level_Count-0) * city_storey_height, +Side_B2>, y * (2 * (Level_Count-0) + Building_Rotate))
			}

			#local Side_A1 = Side_A2;
			#local Side_C1 = Side_C2;
			#local Side_B1 = Side_B2;
			#local Level_Count = Level_Count + 1;
		#end
	}
