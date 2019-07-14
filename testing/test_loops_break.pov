#local start = 0;
#local stop = 4;

#while (start < stop)
	#if (start = 1)
		#debug "yep\n\n"
		#break
	#else
		#debug "nope\n\n"
	#end
	#local start = start + 1;
#end