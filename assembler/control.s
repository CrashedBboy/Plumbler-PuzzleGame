	.intel_syntax noprefix
.MODE:
	.string	"r"
.FILE:
	.string	"map.info"
.FORMAT1:
	.string	"%d\n"
.FORMAT2:
	.string	"%d %d %d %d\n"
##################################################
	.text

	.globl	game_init
	.type	game_init, @function
game_init:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	esi, OFFSET .MODE
	mov	edi, OFFSET .FILE
	call	fopen
	mov	QWORD PTR [rbp-8], rax	# fopen's output(file) will put at rax, mov to stack
	lea	rdx, [rbp-20]			# store total_levels
	mov	rdi, QWORD PTR [rbp-8]	# opened file
	mov	esi, OFFSET .FORMAT1	# scan format
	call	__isoc99_fscanf
	mov	DWORD PTR [rbp-16], 0	# set a counter i
	jmp	.LOOP0
.LOOP0B:
	mov	eax, DWORD PTR [rbp-16]	# load i
	movsx rax, eax
	imul	rax, rax, 316		# i * map size
	add	rax, 288				# add base
	lea	rdx, maps[rax]			# parameter(total_turns address
	mov	rdi, QWORD PTR [rbp-8]	# parameter(opened file
	mov	esi, OFFSET .FORMAT1	# parameter(scan format
	call	__isoc99_fscanf
	###
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, 288
	add	rax, OFFSET maps
	lea	rdx, [rax+4]			# parameter(default_blank_location addr
	mov	rdi, QWORD PTR [rbp-8]	# parameter(file
	mov	esi, OFFSET .FORMAT1	# parameter(scan format
	call	__isoc99_fscanf
	###
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, 288
	add	rax, OFFSET maps
	lea	rdx, [rax+12]			# parameter(entry_block addr)
	mov	rdi, QWORD PTR [rbp-8]	# parameter(file
	mov	esi, OFFSET .FORMAT1	# parameter(scan format
	call	__isoc99_fscanf
	###
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, 304
	lea	rdx, maps[rax]			# parameter(entry_direction
	mov	rdi, QWORD PTR [rbp-8]	# parameter(file
	mov	esi, OFFSET .FORMAT1	# parameter
	call	__isoc99_fscanf
	###
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, 304
	add	rax, OFFSET maps
	lea	rdx, [rax+4]			# parameter(exit_block
	mov	rdi, QWORD PTR [rbp-8]	# parameter(map_info
	mov	esi, OFFSET .FORMAT1	# parameter(scan format
	call	__isoc99_fscanf
	###
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, 304
	add	rax, OFFSET maps
	lea	rdx, [rax+8]			# exit_direction addr
	mov	rdi, QWORD PTR [rbp-8]	# file
	mov	esi, OFFSET .FORMAT1	# scan format
	call	__isoc99_fscanf
	###
	mov	DWORD PTR [rbp-12], 0	# set a new counter(j
	jmp	.LOOP1

.LOOP1B:
	mov	eax, DWORD PTR [rbp-16]	# load i
	movsx rax, eax
	imul	rax, rax, 316		# i * map size
	add	rax, OFFSET maps+292	# add offset
	mov	eax, DWORD PTR [rax]	# default_blank_location
	cmp	eax, DWORD PTR [rbp-12]	# j compare to default_blank_location
	je	.SKIP0

	mov	eax, DWORD PTR [rbp-12]	# load j
	movsx rax, eax
	sal	rax, 4					# j * block size
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]	# load i
	movsx rax, eax
	imul	rax, rax, 316		# i * map size
	add	rax, rdx				# addr of map[i].block[j]
	add	rax, 12					# dimension[0] in block
	lea	rdi, maps[rax]			# get it addr
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx
	add	rax, 8					# dimension[1] in block
	lea	rsi, maps[rax]			# get addr
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx
	add	rax, 4					# dimension[2] in block
	lea	rcx, maps[rax]			# get addr(parameter)
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx				# dimension[3] in block
	lea	rdx, maps[rax]			# get addr(parameter)
	###
	mov	r9, rdi					# parameter(addr
	mov	r8, rsi					# parameter
	mov	esi, OFFSET .FORMAT2	# parameter(scan format
	mov	rdi, QWORD PTR [rbp-8]	# parameter(file
	call	__isoc99_fscanf
.SKIP0:
	add	DWORD PTR [rbp-12], 1	# j += 1 every loop
.LOOP1:
	cmp	DWORD PTR [rbp-12], 8	# j go from 0 to 8
	jle	.LOOP1B					# go into loop

	# get answer_blank_location
	mov	eax, DWORD PTR [rbp-16]	# tmp151, i
	movsx rax, eax
	imul rax, rax, 316			# i * map size
	add	rax, 288				# offset
	add	rax, OFFSET maps		# map[0] addr
	lea	rdx, [rax+8]			# map[i].answer_blank_location addr
	mov	rdi, QWORD PTR [rbp-8]	# parameter(file
	mov	esi, OFFSET .FORMAT1	# parameter(format
	call	__isoc99_fscanf

	mov	DWORD PTR [rbp-12], 0	# reset j to 0
	jmp	.LOOP2	#
.LOOP2B:
	mov	eax, DWORD PTR [rbp-16]	# load i
	movsx rax, eax
	imul	rax, rax, 316		# i * map size
	add	rax, OFFSET maps+296	# answer_blank_location
	mov	eax, DWORD PTR [rax]	# answer_blank_location
	cmp	eax, DWORD PTR [rbp-12]	# compare j to answer_blank_location
	je	.SKIP1	

	mov	eax, DWORD PTR [rbp-12]	# j
	movsx rax, eax
	sal	rax, 4					# j * block size
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]	# i
	movsx rax, eax
	imul	rax, rax, 316		# i * map size
	add	rax, rdx
	add	rax, 156				# map[i].block[j].dimension[0]
	lea	rdi, maps[rax]
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx
	add	rax, 152				# map[i].block[j].dimension[1]
	lea	rsi, maps[rax]
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx
	add	rax, 148				# map[i].block[j].dimension[2]
	lea	rcx, maps[rax]
	###
	mov	eax, DWORD PTR [rbp-12]
	movsx rax, eax
	add	rax, 9
	sal	rax, 4
	mov	rdx, rax
	mov	eax, DWORD PTR [rbp-16]
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, rdx				# map[i].block[j].dimension[0]
	lea	rdx, maps[rax]
	###
	mov	r9, rdi					# parameter(addr)
	mov	r8, rsi
	mov	esi, OFFSET .FORMAT2	# parameter(scan format)
	mov	rdi, QWORD PTR [rbp-8]	# parameter(map_info
	call	__isoc99_fscanf
.SKIP1:
	add	DWORD PTR [rbp-12], 1	# j++
.LOOP2:
	cmp	DWORD PTR [rbp-12], 8	# compare j to loop max
	jle	.LOOP2B
	add	DWORD PTR [rbp-16], 1	# i++
.LOOP0:
	mov	eax, DWORD PTR [rbp-20]	# total_levels
	cmp	DWORD PTR [rbp-16], eax	# compare i to total_levels(max)
	jl	.LOOP0B					# if less then goto loop
	mov	edi, 0	
	call	set_map_level		# set_map_level(0)
	leave
	ret
###########################################################################################################
	.globl	set_map_level
	.type	set_map_level, @function
set_map_level:
	push	rbp
	mov	rbp, rsp
	mov	DWORD PTR [rbp-4], edi	# load level
	mov	eax, DWORD PTR [rbp-4]
	movsx rax, eax
	imul rax, rax, 316
	add	rax, OFFSET maps+288
	mov	eax, DWORD PTR [rax]	# maps[level].total_turns
	mov	remain_turns, eax		# remain_turns = maps[level].total_turns

	mov	eax, DWORD PTR [rbp-4]	# level
	movsx rax, eax
	imul	rax, rax, 316
	add	rax, OFFSET maps+292
	mov	eax, DWORD PTR [rax]	# maps[level].default_blank_location
	mov	blank_location, eax		# blank_location = maps[level].default_blank_location
	
	mov eax, 0
	mov	mask, eax				# set mask and level_done = FALSE
	mov	current_level_done, eax
	pop	rbp
	ret
#############################################################################################################
	.globl	game_judge
	.type	game_judge, @function
game_judge:
	push	rbp
	mov	rbp, rsp
	mov	eax, current_level
	movsx rax, eax
	imul rax, rax, 316
	add	rax, OFFSET maps+296	# map[current_level].answer_blank_location addr
	mov	edx, DWORD PTR [rax]
	cmp edx, blank_location
	jne .EXIT1
	mov	DWORD PTR [rbp-8], 0	# set counter(i
	jmp	.LOOP3
.LOOP3B:
	mov	eax, current_level
	movsx rax, eax
	imul rax, rax, 316
	add	rax, OFFSET maps+296	# maps[current_level].answer_blank_location addr
	mov	eax, DWORD PTR [rax]
	cmp	eax, DWORD PTR [rbp-8]	# i
	je	.SKIP2
	mov	DWORD PTR [rbp-4], 0	# reset counter(j) to 0
	jmp	.LOOP4
.LOOP4B:
	mov eax, current_level
	movsx rax, eax
	imul rax, rax, 316
	movsx	rdx, DWORD PTR [rbp-8] 	# i
	sal rdx, 4
	movsx rcx, DWORD PTR [rbp-4]	# j
	sal rcx, 2
	add rcx, rax
	add rcx, rdx
	mov ecx, DWORD PTR maps[rcx]			# map[current_level].blocks[i].dimension[j]

	mov eax, current_level
	movsx rax, eax
	imul rax, rax, 316
	movsx rdx, DWORD PTR [rbp-8]	# i
	sal rdx, 4
	add rax, rdx
	movsx rdx, DWORD PTR [rbp-4]	# j
	sal rdx, 2
	add rax, rdx
	mov eax, DWORD PTR maps[rax]	# maps[current_level].answer[i].dimension[j]

	cmp	ecx, eax
	jne	.EXIT1
	add	DWORD PTR [rbp-4], 1	# j++
.LOOP4:
	cmp	DWORD PTR [rbp-4], 3	# compare j to loop max
	jle	.LOOP4B
.SKIP2:
	add	DWORD PTR [rbp-8], 1	# i++
.LOOP3:
	cmp	DWORD PTR [rbp-8], 8	# compare i to loop max
	jle	.LOOP3B
	mov eax, 1
	mov	current_level_done, eax
.EXIT1:
	pop	rbp
	ret
#######################################################################################################
	.globl	next_level
	.type	next_level, @function
next_level:
	push	rbp
	mov	rbp, rsp
	mov	edi, current_level
	add	edi, 1					# current_level + 1
	mov	current_level, edi
	call	set_map_level
	mov	rdi, window
	call	gtk_widget_queue_draw
	pop	rbp
	ret
