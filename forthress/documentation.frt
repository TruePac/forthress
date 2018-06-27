' dup g" 
( a - a a )
Duplicate the cell on top of the stack.
" doc-word 

' drop g"
( a -- )
Drop the topmost element of the stack.
" doc-word

' swap g" 
( a b -- b a )
Swap two topmost elements of the stack.
" doc-word

' 2over g"
( a b c -- a b c a )
Copy third element from the top of the stack to the top of the stack.
" doc-word

' 2drop g" 
( a b -- )
Drop 2 elements from the top of the stack.
" doc-word

' ( g" 
Start a comment. Reads from input stream until ) symbol.
" doc-word

' readc g" 
Read char from input stream.
" doc-word

' readc@ g" 
Read char from an open fd.
" doc-word

' sys-write g" 
Perform write syscall. 
" doc-word

' sys-read g" 
Perform read syscall.
" doc-word

' sys-write-no g" 
 Constant used in sys-write.
" doc-word

' sys-read-no g" 
Constant used in sys-read.
" doc-word

' loop g" 
End of do ... loop block. do loop block reads limit and index from the top of the stack and repeats block of code between do and loop (limit - index) times.
" doc-word

' do g" 
Begin of do ... loop block. do loop block reads limit and index from the top of the stack and repeats block of code between do and loop (limit - index) times.
" doc-word

' endfor g" 
End of for ... endfor block. Similar to do ... loop block, but will perform at least once if index is more than limit.
" doc-word

' for g" 
Begin of for ... endfor block. Similar to do ... loop block, but will perform at least once if index is more than limit.
" doc-word

' until g" 
End of repeat ... until block. At the end of each iteration, checks number at the top of the stack? If it is 0, then remove it and start the loop again; if not zero, then remove it and exit the loop.
" doc-word

' repeat g" 
Begin of repeat ... until block. At the end of each iteration, checks number at the top of the stack? If it is 0, then remove it and start the loop again; if not zero, then remove it and exit the loop.
" doc-word

' endif g" 
Exit if ... then block.
" doc-word

' then g" 
End of if ... then block.
" doc-word

' else g" 
Used indide if ... then block. Perform the body if the top of the stack is zero.
" doc-word

' if g" 
Begin of if ... then block. Perform the body if the top of the stack is non-zero.
" doc-word

' again g" 
Performs unconditional branch to the previous begin block.
" doc-word

' begin g" 
Begin of begin ... again block.
" doc-word

' allot g" 
Accept the number of bytes to allocate in the global data area.
" doc-word

' KB g" 
( a -- a * 1024)
Multiply the topmost element of the stack by 1024.
" doc-word

' MB g" 
( a -- a * 1048576)
Multiply the topmost element of the stack by 1024 twice.
" doc-word