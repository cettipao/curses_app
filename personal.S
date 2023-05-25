main
		mov		sp,#stackptr
		mov		r0,#delayptr
		mov		r1,#nameptr
		bl		sequence
		end
		
		
		;		@param r0 - delay ptr
		;		@param r1 - name ptr
		;		@var r4 - table ptr
		;		@var r5 - index
		;		@var r6 - table size
sequence
		stmfd	sp!,{r4,r5,r6,r7,lr} ; push
		mov		r4,#table
		mov		r5,#0 ; index
		mov		r6,#12 ; table size - counter
		
loop
		;		DISPLAY
		ldrb		r7,[r4,r5] ; select byte
		stmfd	sp!,{r0,r1,r2} ; push params
		mov		r2,r1
		mov		r1,r0
		mov		r0,r7
		bl		display
		ldmfd	sp!,{r0,r1,r2} ; pop params
		
		;		DELAY
		;		stmfd	sp!,{r0} ; push params
		;bl		delay
		;		ldmfd	sp!,{r0} ; pop params
		
		;		LOOP
		add		r5,r5,#1
		subs		r6,r6,#1
		bne		loop
		
		;		END
		ldmfd	sp!,{r4,r5,r6,r7,lr} ; pop
		mov		pc,lr
		
		
		;		@param r0 - data
		;		@param r1 - delay ptr
		;		@param r2 - name ptr
display
		mov		pc,lr
		
		
		;		@param r0 - delay ptr
		;		r4 - counter
delay
		stmfd	sp!,{r4}
		ldr		r4,[r0]
		
while
		subs		r4,r4,#1
		bne		while
		
		ldmfd	sp!,{r4}
		mov		pc,lr
		
		
delayptr	dcd		0x0A
nameptr	dcb		'p','e','r','s','o','n','a','l',0x00
table	dcb		0x81, 0x42, 0x81, 0x42, 0x24, 0x42, 0x81, 0x42, 0x24, 0x18, 0x24, 0x42
		
stack	fill		400
stackptr	dcd		0
