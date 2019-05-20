@ Due to instruction rev, armv6 and above are required
@ e.g. 3ds's arm11
@ I'll leave armv6k as default since it's normally used to build for 3ds's arm11
	.arch armv6k
	.arm
	.section .text.KeyScrambler, "ax", %progbits
	.align  2
	.global KeyScrambler
	.syntax unified
	.type   KeyScrambler, %function
	@ argument registers should point to long aligned memory.
KeyScrambler:
	@ r0 = NormalKey
	@ r1 = KeyX
	@ r2 = KeyY
	push    {r0,r4-r5,lr}
	ldm     r1, {r0-r1,r3-r4}
	rev     r0, r0
	rev     r1, r1
	rev     r3, r3
	rev     r4, r4
	mov     lr, r0, LSR#30
	lsl     r0, r0, #2
	orr     r0, r0, r1, LSR#30
	lsl     r1, r1, #2
	orr     r1, r1, r3, LSR#30
	lsl     r3, r3, #2
	orr     r3, r3, r4, LSR#30
	lsl     r4, r4, #2
	orr     r4, r4, lr
	ldm     r2, {r2,r5,r12,lr}
	rev     r2, r2
	eor     r0, r2
	rev     r5, r5
	eor     r1, r5
	rev     r12, r12
	eor     r3, r12
	rev     lr, lr
	eor     r4, lr
	adr     r2, .ConstantC
	ldm     r2, {r2,r5,r12,lr}
	adds    r4, r4, lr
	adcs    r3, r3, r12
	adcs    r1, r1, r5
	adc     r0, r0, r2
	mov     lr, r0, LSR#9
	lsl     r0, r0, #23
	orr     r0, r0, r1, LSR#9
	lsl     r1, r1, #23
	orr     r1, r1, r3, LSR#9
	lsl     r3, r3, #23
	orr     r3, r3, r4, LSR#9
	lsl     r4, r4, #23
	orr     r4, r4, lr
	rev     r12, r0
	rev     lr, r1
	rev     r2, r3
	rev     r5, r4
	pop     {r0}
	stm     r0, {r2,r5,r12,lr}
	pop     {r4-r5,pc}
	.size   KeyScrambler, .-KeyScrambler
	.align  2
.ConstantC:
	@ if key is, for example, "00112233445566778899AABBCCDDEEFF"
	@ set as, 0x00112233, 0x44556677, 0x8899AABB, 0xCCDDEEFF
	@ basically, don't thing too hard about it if endianness comes to mind
	.long   0x00000000, 0x00000000, 0x00000000, 0x00000000
	.size   .ConstantC, .-.ConstantC
