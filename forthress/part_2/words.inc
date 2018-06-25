;Block of constants
	const inbuf, current_word
	const mem, user_mem
	const state, state
	const here, [here]
	const last_word, last_word

;Colon block
native "docol", docol
    rpush pc
	add w, 8
    mov pc, w
    jmp next

native "exit", exit
    rpop pc
    jmp next

native "lit", lit
    push qword [pc]
    add pc, 8
    jmp next

native "branch", branch, is_branch
    mov pc, [pc]
    jmp next

native "0branch", branch0, is_branch
    pop rax
    test rax, rax
    jz i_branch
    add pc, 8
    jmp next

native ",", comma
    mov rax, [here]
    pop qword [rax]
    add qword [here], 8
    jmp next

native "create", create
    mov rdx, [last_word]
    mov rsi, [here]
    mov [rsi], rdx
    mov [last_word], rsi
    add rsi, 8
    mov byte [rsi], 0
    pop rdi
    push rsi
    call string_copy
    mov rdi, qword [rsp]
    call string_length
    pop rsi
    add rsi, rax
    inc rsi
    pop rax
    mov [rsi], al
    inc rsi
    mov [here], rsi
    jmp next

colon ":", colon
.restart:
    dq xt_inbuf, xt_word
    branch0 .restart
    dq xt_lit, 0, xt_inbuf, xt_create
    dq xt_lit, 1, xt_state, xt_put_int
    dq xt_lit, i_docol, xt_comma
    dq xt_exit

colon ";", semicolon, 1
    dq xt_lit, 0, xt_state, xt_put_int
    dq xt_lit, xt_exit, xt_comma
    dq xt_exit    

; utils block

native "find", find
  	pop rdi
  	call find_word
  	push rax
  	jmp next
	native "cfa", cfa_
  	pop rdi
  	call cfa
  	push rax
  	jmp next

native "syscall", syscall
 	 pop r9
 	 pop r8
 	 pop r10
 	 pop rdx
 	 pop rsi
 	 pop rdi
 	 pop rax
 	 syscall
	 push rax
	 push rdx
	 jmp next

native "bye", bye
  	mov rax, 60
  	syscall

stack_underflow:
	mov rdi, msg_stack_underflow
	call print_string
	jmp next

;basics block

; (ab - ba)
native "swap", swap
  pop rax
  pop rcx
  push rax
  push rcx
  jmp next

; (a - aa)
native "dup", dup
	pop rax 
	push rax 
	push rax 
	jmp next 

; drop top of stack
native "drop", drop		
	cmp rsp, [stack_head]
	jge stack_underflow
	pop rax
	jmp next

; arifmetics block

;(xy - [x + y])
native "+", plus
  pop rax
  add [rsp], rax
  jmp next

;(xy - [x - y])
native "-", min
  pop rax
  sub [rsp], rax
  jmp next

;(xy - [x * y])
native "*", mult
  pop rax
  pop rdx
  imul rax, r8
  push rax
  jmp next

;(xy - [x / y])
native "/", div
  pop rax
  pop r8
  mov rdx, 0
  idiv r8
  push rax
  jmp next

;(yx - [x mod y])
native "%", mod
    pop rcx
    pop rax
    cqo
    idiv rcx
    push rdx
    jmp next 

;(xy - [x < y])
native "<", less 
  pop rax
  pop rcx
  cmp rcx, rax
  setl al
  movzx rax, al
  push rax
  jmp next   

;logic block

;(a - a') a'= 0 if a!= 0 a'= 1 if a==0
native "not", not
    pop rax
    test rax, rax
    je .yes
    push 0
    jmp next
    .yes: push 1
    jmp next   

; (ab - c) c=1 if a==b c=0 if a!=b
native "=", equals 
  pop rax
  pop rcx
  cmp rax, rcx
  sete al
  movzx rax, al
  push rax
  jmp next

;logical and
native "land", land
    pop rax
    pop rdx
    test rax, rax
    jz .no
    push rdx
    jmp next
.no:
    push rax
    jmp next

;logical or
native "lor", lor
    pop rax
    pop rdx
    test rax, rax
    jnz .yes
    push rdx
    jmp next
.yes:
    push rax
    jmp next

;bitwice block

;bitwice and
native "and", and
    pop rax
    and [rsp], rax
    jmp next

;bitwice or
native "or", or
    pop rax
    or [rsp], rax
    jmp next

;return stack operations

; Push from return stack into data stack
native "r>", push_r
  rpop rax
  push rax
  jmp next

; Pop from data stack into return stack
native ">r", pop_r
  pop rax
  rpush rax
  jmp next

; Non-destructive copy from the top of return stack to the top of data stack
native "r@", copy_rs
    mov rax, [rstack]
    push rax
    jmp next    

;Memory operations

;(val addr --) Store value by address
native "!", put_int
    pop rax
  pop rdx
  mov [rax], rdx
  jmp next

;(char addr --) Store one byte by address
native "c!", put_char
    pop rax
    pop rdx
    mov [rax], dl
    jmp next

;(addr -- value) Fetch value from memory
native "@", get_int
    pop rax
  mov rax, [rax]
  push rax
  jmp next

;(addr -- char) Read one byte starting at addr
native "c@", get_char
    pop rax
    movzx rax, byte [rax]
    push rax
    jmp next

;Input-Output

;Print top of stack
native ".", dot     
  cmp rsp, [stack_head]
  jge stack_underflow
  pop rdi
  call print_int
  jmp next

;Print stack
native ".S", print_stack   
  mov rax, rsp
  .loop:
    cmp rax, [stack_head]
    jge next    
    mov rdi, [rax]
    push rax
    call print_int
    call print_newline
    pop rax
    add rax, 8
    jmp .loop 

; (str -- len ) Accepts a null-terminated string, calculates its length.
native "count", count
  pop rdi
  call string_length
  push rax
  jmp next

; ( str cnt -- ) Prints a certain amount of characters from string.
native "printc", printc
  mov rax, 1
  mov rdi, 1
  pop rsi
  pop rdx
  syscall
  jmp next

;( c -- ) Outputs a single character to stdout
native "emit", emit
    pop rdi
    call print_char
    jmp next

 ; ( addr -- len ) Reads word from stdin and stores it starting at address addr. 
native "word", word
    pop rdi
    call read_word
    push rdx
    jmp next   

;( str -- len num ) Parses an integer from string
native "number", number   
  call read_word
  mov rax, rdi
  call parse_int
  push rax
  jmp next

 ;( addr -- ) Prints a null-terminated string.
native "prints", prints
  pop rdi
  call print_string
  jmp next 











