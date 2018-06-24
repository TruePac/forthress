;Block of constants
	const inbuf, current_word
	const mem, user_memory
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

error_underflow:
	mov rdi, msg_stack_underflow
	call print_string
	jmp next

;Print top of stack
native ".", dot			
	cmp rsp, [stack_head]
	jge error_underflow
	pop rdi
	call print_int
	jmp next

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
	jge error_underflow
	pop rax
	jmp next




