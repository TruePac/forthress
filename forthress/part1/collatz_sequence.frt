: is_even 2 % not ;

: inc 1 + ;

: collatz
	dup 1 < if drop ." Illegal argument. Number must be positive integer"
	else
		dup >r
		repeat
			dup 1 > if
				dup is_even if
					dup 2 / 
				else
					dup 3 * inc 
				then
			else 1
			then
		dup 1 = until
	then
	r> 
; IMMEDIATE

: print_collatz
	>r 
	repeat
		dup . ."  "
		r@ =	
	until
	cr r> drop 
;