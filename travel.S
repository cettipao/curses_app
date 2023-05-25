main
		mov		sp,#stackptr
		mov		r0,#delayptr
		mov		r1,#name
		bl		travel
		end
		
		
		;		@param r0 - delay ptr
		;		@param r1 - sequence name
		;		@var r4 - counter
		;		@var r5 - data
travel
		stmfd	sp!,{r4,r5,lr} ; push
		mov		r4,#7 ; counter
		mov		r5,#0x01 ; data
		
left
		;		DISPLAY
		stmfd	sp!,{r0,r1,r2} ; push params
		mov		r2,r1 ; name ptr
		mov		r1,r0 ; delay ptr
		mov		r0,r5 ; data
		bl		display
		ldmfd	sp!,{r0,r1,r2} ; pop params
		
		;		ALGORITHM - UPDATE
		orr		r5,r5,r5,LSL #1
		
		;		DELAY
		stmfd	sp!,{r0,r1} ; push params
		bl		delay
		ldmfd	sp!,{r0,r1} ; pop params
		
		;		LOOP
		subs		r4,r4,#1
		bne		left
		
		mov		r4,#5
		mov		r5,#0x7F
right
		;		DISPLAY
		stmfd	sp!,{r0,r1,r2} ; push params
		mov		r2,r1 ; name ptr
		mov		r1,r0 ; delay ptr
		mov		r0,r5 ; data
		bl		display
		ldmfd	sp!,{r0,r1,r2} ; pop params
		
		;		ALGORITHM - UPDATE
		mov		r5,r5,LSR #1
		
		;		DELAY
		stmfd	sp!,{r0,r1} ; push params
		bl		delay
		ldmfd	sp!,{r0,r1} ; params
		
		;		LOOP
		subs		r4,r4,#1
		bne		right
		
		;		END
		ldmfd	sp!,{r4,r5,lr}
		mov		pc,lr
		
		
		;		@param r0 - data
		;		@param r1 - delay ptr
		;		@param r2 - name ptr
display
		mov		pc,lr
		
		
		
		;		@param r0 - delay ptr
		;		@var r4 - counter
delay
		stmfd	sp!,{r4}
		ldr		r4,[r0]
		
while
		subs		r4,r4,#1
		bne		while
		
		ldmfd	sp!,{r4}
		mov		pc,lr
		
		
name		DCB		'V','i','a','j','e',0x00
delayptr	DCD		0x01
		
stack	fill		400
stackptr	dcd		0
