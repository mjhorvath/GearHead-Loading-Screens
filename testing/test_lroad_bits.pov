	#local RoadMask = intersection
	{
		plane  {+y, 0}
		plane  {-y, 0}
	}
	#local BedMask = intersection						// Object that determines the minimum and maximum height of the road, including the embankment.
	{
		plane  {+y, 0}
		object {LRoad_FloorObject translate -y * roadHgh inverse}
	}