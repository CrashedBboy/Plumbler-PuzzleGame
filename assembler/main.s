	.intel_syntax noprefix
	.comm	window,8
	.comm	draw_area,8
	.comm	maps,1580
	.comm	blank_location,4
	.comm	remain_turns,4
	.comm	remain_str,5
	.comm	level_str,5
	.comm	mask,4
	.comm	current_level_done,4
	.comm	current_level,4
	.comm	mask_x,4
	.comm	mask_y,4
	.comm	mask_width,4

	.text
	
	.globl	main
	.type	main, @function
main:
	push rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	DWORD PTR [rbp-4], edi			# load parameter(argc
	mov	QWORD PTR [rbp-16], rsi			# load parameter(argv
	lea	rsi, [rbp-16]					# get address
	lea	rdi, [rbp-4]
	call gtk_init
	mov	eax, 0
	mov	current_level, eax
	mov mask, eax
	mov	current_level_done, eax
	call game_init
	call layout_init
	call gtk_main
	leave
	ret
