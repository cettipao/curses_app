 main
		mov		sp,#stackptr
		mov		r0,#password
		mov		r1,#input
		bl		strcompare
		end


		; @param r0 - password ptr
		; @param r1 - input ptr
		; @var r4 - str size / counter
		; @var r5 - char from r0
		; @var r6 - char from r1
		; @return r0 - bool (true if they are equal)
strcmp
		stmfd	sp!,{r4,r5,r6} ; push
		mov		r4,#4 ; counter - offset
		
loop
		ldrb		r5,[r0,r4] ; pwd byte
		ldrb		r6,[r1,r4] ; input byte
		cmp		r5,r6
		bne		fn_end
		subs		r4,r4,#1
		bpl		loop
		mov		r2,#1 ; equal
		
fn_end
		movpl	r2,#0 ; not equal
		ldmfd	sp!,{r4,r5,r6} ; pop
		mov		pc,lr


password	dcb		'a','b','c','d','e'
input	dcb		'a','a','a','a','a'
		
stack	fill		40
stackptr	dcd		0
