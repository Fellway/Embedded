.global main
.arm
.section .text

.EQU 	PIOB_PER, 	0xFFFFF400 	// PIOB enable
.EQU 	PIOC_PER, 	0xFFFFF600	// PIOC enable

.EQU 	PIOB_OER, 	0xFFFFF410 	//output enable register
.EQU 	PIOC_OER, 	0xFFFFF610 	//output enable register

.EQU 	PIOB_CODR, 	0xFFFFF434	//clear ds1
.EQU 	PIOB_SODR, 	0xFFFFF430	//set ds1

.EQU 	PIOC_CODR, 	0xFFFFF634	//clear ds1
.EQU 	PIOC_SODR, 	0xFFFFF630	//set ds1

.EQU 	LED_B,	    0x00000100	// PIN 8
.EQU    BUT_A,		0x00000010  // PIN 5 

.EQU 	PIOC_PUER	0xFFFFF664
.EQU 	PIOC_ODR	0xFFFFF614
.EQU 	PIOC_PDSR	0xFFFFF63C

.EQU 	BLINK_DELAY, 20000000

.EQU 	PRESSED 	0x00

main:
	ldr r1,=LED_B
	ldr r2,=PIOB_PER
	ldr r3,=PIOB_OER
	ldr r4,=PIOB_SODR
	ldr r5,=PIOB_CODR
	
	ldr r6,=BUT_A
	ldr r7,=PIOC_PER
	ldr r8,=PIOC_ODR
	ldr r9,=PIOC_PUER
	
	ldr r10,=PRESSED

	str r1,[r2]
	str r1,[r3]
	
	str r6,[r7]
	str r6,[r8]
	str r6,[r9]
	
loop:
	b1 delay
	ldr r0,=BLINK_DELAY
	str r1,[r4]
	b1 delay
	ldr r0,=BLINK_DELAY
	str r1,[r5]
	b loop
	
delay: 
	subs r0,r0,#1
	bne delay
	mov pc,r14
	

	
	
	

	
	
	
