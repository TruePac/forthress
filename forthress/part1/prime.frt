: is_prime 
	dup 2 < if ." Incorrect argument. Must be positive integer greater than 1" else
  		1 >r 
		repeat  
			dup 
			r> 1 + dup >r  
			% 0 =  	
		until 
		r> = 
	then
; IMMEDIATE
