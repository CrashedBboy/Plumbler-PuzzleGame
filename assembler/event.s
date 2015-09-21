	.intel_syntax noprefix
	.text
	.globl	on_key_press
	.type	on_key_press, @function
on_key_press:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	QWORD PTR [rbp-16], rsi	# load parameter(event
	mov	rax, QWORD PTR [rbp-16]
	mov	eax, DWORD PTR [rax+28]	# event->keyval
	cmp	eax, 65362				# "Up" clicked
	je	.UP
	cmp	eax, 65363				# "right" clicked
	je	.RIGHT
	cmp	eax, 65364				# "down" clicked
	je	.DOWN
	cmp	eax, 65361				# "Left" clicked
	je	.LEFT
	cmp	eax, 32					# "space" clicked
	je	.SPACE
	jmp	.FINAL
.UP:
	mov	eax, blank_location
	cmp	eax, 2								# blank_location must > 2
	jle	.FINAL
	mov	eax, remain_turns
	test	eax, eax						# test if remain_turns is 0
	jle	.FINAL
	mov	esi, blank_location
	mov	edi, blank_location
	sub	edi, 3
	call	block_value_copy
	mov	eax, blank_location
	mov edi, eax							# preserve for parameter
	sub	eax, 3
	mov	blank_location, eax					# blank_location -= 3
	mov	eax, remain_turns
	sub	eax, 1
	mov	remain_turns, eax					# remain_rurns -= 1
	call	slide_block
	jmp	.FINAL
.RIGHT:
	mov eax, blank_location
	mov edx, 0
	mov ecx, 3
	idiv ecx 
	cmp edx, 1								# compare blank_location%3
	jg	.FINAL 								# blank_location%3 must < 2
	mov	eax, remain_turns
	test	eax, eax
	jle	.FINAL
	mov	esi, blank_location
	mov	edi, blank_location
	add	edi, 1
	call	block_value_copy
	mov	eax, blank_location
	mov edi, eax
	add	eax, 1
	mov	blank_location, eax
	mov	eax, remain_turns
	sub	eax, 1
	mov	remain_turns, eax
	call	slide_block
	jmp	.FINAL
.DOWN:
	mov	eax, blank_location
	cmp	eax, 5								# blank_location must < 5
	jg	.FINAL
	mov	eax, remain_turns
	test eax, eax							# check if remain_turns is 0
	jle	.FINAL
	mov	esi, blank_location
	mov	edi, blank_location
	add	edi, 3
	call block_value_copy
	mov	eax, blank_location
	mov edi, eax
	add	eax, 3
	mov	blank_location, eax					# blank_location += 3
	mov	eax, remain_turns
	sub	eax, 1
	mov	remain_turns, eax					# remain_turns -= 1
	call slide_block
	jmp	.FINAL
.LEFT:
	mov eax, blank_location
	mov edx, 0
	mov ecx, 3
	idiv ecx
	test edx, edx
	jle	.FINAL
	mov	eax, remain_turns
	test eax, eax
	jle	.FINAL
	mov	esi, blank_location
	mov	edi, blank_location
	sub	edi, 1
	call block_value_copy
	mov	eax, blank_location
	mov edi, eax
	sub	eax, 1
	mov	blank_location, eax
	mov	eax, remain_turns
	sub	eax, 1
	mov	remain_turns, eax
	call	slide_block
	jmp	.FINAL
.SPACE:
	mov	eax, current_level_done
	test	eax, eax				# if current_level_done==1(TRUE), can goto next level
	je	.FINAL
	call next_level
.FINAL:
	mov	eax, remain_turns
	test eax, eax
	jg	.EXIT0
	call game_judge
.EXIT0:
	mov	eax, 0						# like "return FALSE"
	leave
	ret
##########################################################################################################
	.globl	block_value_copy
	.type	block_value_copy, @function
block_value_copy:
	push	rbp
	mov	rbp, rsp
	mov	DWORD PTR [rbp-20], edi	# load parameter(source
	mov	DWORD PTR [rbp-24], esi	# load parameter(destination
	mov	DWORD PTR [rbp-4], 0	# set a counter(i
	jmp	.LOOP0
.LOOP0B:
	mov eax, current_level
	movsx rax, eax
	imul rax, rax, 316				# current_level*316
	mov ecx, DWORD PTR [rbp-20]		# source
	movsx rcx, ecx
	sal rcx, 4
	add rax, rcx 					# current_level*316+source*16
	mov ecx, DWORD PTR [rbp-4]		# i
	movsx rcx, ecx
	sal rcx, 2
	add rax, rcx					# current_level*316+source*16+i*4
	mov	ecx, DWORD PTR maps[rax]	
	# use the addr to locate maps[current_level].blocks[source].dimension[i]
	mov eax, current_level
	movsx rax, eax
	imul rax, rax, 316				# current_level*316
	mov edx, DWORD PTR [rbp-24] 	# destination
	movsx rdx, edx
	sal rdx, 4
	add rax, rdx					# current_level*316+source*16
	mov edx, DWORD PTR [rbp-4]		# i
	movsx rdx, edx
	sal rdx, 2
	add rax, rdx					# current_level*316+source*16+i*4
	mov DWORD PTR maps[rax], ecx	# load to maps[current_level].blocks[destination].dimension[i]
	add	DWORD PTR [rbp-4], 1		# i++
.LOOP0:
	cmp	DWORD PTR [rbp-4], 3	# compare i to loop max
	jle	.LOOP0B
	pop	rbp
	ret
#########################################################################################################33
	.globl	slide_block
	.type	slide_block, @function
slide_block:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	DWORD PTR [rbp-4], edi		# load parameter(source
	mov	rdi, window
	call	gtk_widget_queue_draw
	mov eax, 1
	mov	mask, eax					# set mask = TRUE
	mov eax, 120
	mov	mask_width, eax

	mov eax, DWORD PTR [rbp-4] 		#source
	mov edx, 0
	mov ecx, 3
	idiv ecx
	mov eax, edx
	imul eax, eax, 120
	add eax, 48
	mov	mask_x, eax

	mov eax, DWORD PTR [rbp-4]
	mov edx, 0
	mov ecx, 3
	idiv ecx
	imul eax, eax, 120
	add eax, 118
	mov	DWORD PTR mask_y[rip], eax
	mov	mask_y, eax

	mov	edx, 0						# data(addr) to pass to function
	mov	esi, OFFSET block_mask		# repeat function name
	mov	edi, 10						# repeat time interval
	call	g_timeout_add
	mov	eax, 1						# return TRUE
	leave
	ret
	.size	slide_block, .-slide_block
#########################################################################################################
	.globl	block_mask
	.type	block_mask, @function
block_mask:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	QWORD PTR [rbp-8], rdi		# load parameter(data
	mov	rdi, window
	call	gtk_widget_queue_draw
	mov	eax, mask_width
	sub	eax, 10						# mask's width is decreasing
	mov	mask_width, eax
	test	eax, eax				# if mask_width is 0 then exit
	jg	.EXIT1
	mov eax, 0
	mov	mask, eax					# mask = FALSE
.EXIT1:
	mov	eax, mask					# return mask(TRUE/FALSE)
	leave
	ret
