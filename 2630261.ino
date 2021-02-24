void setup()
{
  asm(
"		JMP start				\n"
"delay: LDI	 r23,  8			\n"	//Delay 100 msec
"w1:	LDI	 r24,  26 			\n"
"w2:	LDI  r25,  26 			\n"
"w3:	DEC  r25  				\n"
"		BRNE w3					\n"
"		DEC  r24				\n"
"		BRNE w2					\n"
"		DEC  r23				\n"
"       BRNE w1					\n"
"		JMP maindelay			\n" //jump to main
";Your Functions Code Begin		\n" //Write your code  
"maindelay:     				\n"	//main subroutine for delay
"	DEC r16						\n" //decrement delay counter   
"	CPI r16,0b00000000			\n" //compare if delay counter is 0
"	BRNE delay					\n" //if it is zero branch to delay subroutine    
"	RET							\n" //return from maindelay 
"incrementupper:				\n"	//increment subroutine for upper digit
"	CPI r20, 0b00001001			\n"	//compare if it is 9
"	BREQ tozero					\n"	//if is 9 branch to tozero subroutine
"	INC r20						\n"	//increment upper digit
"	LDI r19, 0b00000000			\n"	//load 0 to lower digit
"	JMP mainincrement			\n"	//jumt to mainincrement
"								\n"
"tozero:						\n"	//to zero subroutine for making zero
"	LDI r20, 0b00000000			\n"	//load zero to upper digit
"	LDI r19, 0b00000000			\n"	//load zero to lower digit
"	JMP mainincrement			\n"	//jump to mainincrement
"mainincrement:     			\n"	//mainincrement subroutine
//in this subroutine we increment our digits according to decrement
//counter
"	DEC r16						\n"	//decrement counter    
"	CPI r16,0b00000000			\n" //compare if decrement counter is 0
"	BRNE incrementlower			\n" //if it is not 0 branch increment lower subrouite    
"	RET							\n" //return from mainincrement     
"incrementlower:				\n"	//increment subrouite for lower digit
"	INC r19 					\n"	//increment lower digit
"	CPI r19, 0b00001010			\n"	//compare if lower digit is 9
"	BREQ incrementupper			\n"	//if it is 9 branch increment upper
"	JMP mainincrement			\n"	//jump to mainincrement
"								\n"
"plusincrement:					\n"	//for increment counter plusincrement subroutine 
"	CPI r22, 0b00001010			\n"	//compare if counter is 10
"	BREQ LOOP					\n"	//if it is branch to loop
"	INC r22						\n" //increase counter
"	JMP LOOP					\n" //jump to loop
"negativeincrement:				\n"	//for increment counter negativeincrement subroutine 
"	CPI r22, 0b00000001			\n"	//compare if counter is 1
"	BREQ LOOP					\n"	//if it is branch to loop
"	DEC r22						\n"	//decrement counter
"	JMP LOOP					\n" //jump to loop

"plusdelay:						\n"	//for delay counter plusdelay
"	CPI r21, 0b00001010			\n"	//compare if counter is 10 it means 1000ms
"	BREQ LOOP					\n"	//branch to loop
"	INC r21						\n" //increase counter
"	JMP LOOP					\n" //jump to loop
"negativedelay:					\n"	//for delay counter negativedelay
"	CPI r21, 0b00000001			\n"	//compare if counter is 1 it means 100ms
"	BREQ LOOP					\n"	//if it is branch to loop
"	DEC r21						\n"	//decrement counter
"	JMP LOOP					\n" //jump loop

"start:							\n" //Write your code
"		IN r17, 0x07			\n" //DDRC analog
"		ORI r17, 0b001111		\n"	//input output
"		OUT 0x07, r17			\n" //assign
"		IN r18, 0x04			\n" //DDRB left digital
"		ORI r18, 0b001111		\n" //input output
"		OUT 0x04, r18 			\n" //assign
"		IN 	 r16,  0x0A ;		\n"	//Get values of DDRD to r16             
"		ORI	 r16,  0b11111111	\n" //Assign ones to define as an output              
"		OUT  0x0A, r16			\n" //Give r16 values to DDRD
"		LDI r19, 0b00000000		\n" // lower digit
"		LDI r20, 0b00000000		\n" // upper digit
"		LDI r21, 0b00000001		\n" // delay counter
"		ORI r22, 0b00000001		\n" // increment counter
"		LDI r16, 0b10000000		\n" // temp-for-loops	
  );
}

void loop()
{
  asm(
"LOOP:							\n"	//Write your code
";Your LOOP Code Begin			\n"	//LOOP function
"		MOV r16,r22				\n" //move counter to temporarly register
"		INC r16					\n"	//increment temp register by one
"		CALL mainincrement		\n"	//call mainincrement
"		MOV r16, r21			\n"	//move counter to temporarly register
"		INC r21					\n"	//increment temp register by one
"		CALL maindelay			\n"	//call maindelay
"		OUT 0x05,r19			\n"	//out lower digit
"		OUT 0x08,r20			\n"	//out upper digit
"		LDI r16, 0b00001010		\n"	//r16 <- 10
"		MUL r16,r20				\n"	//r0<-upperdigit*10
"		ADD r0,r19				\n"	//r0 += lower digit
"		OUT 0x0b ,r0			\n"	//out number to LEDs
"		IN r18, 0x03			\n" //get input from pinb
"		LSR r18					\n"	//right shift input register
"		LSR r18					\n"
"		LSR r18					\n"
"		LSR r18					\n"
"		CPI r18, 0b00000001		\n" //compare if imput register is 1   
"		BREQ plusincrement		\n"	//if it is branch plusincrement
"		LSR r18					\n"	//right shift input register
"		CPI r18, 0b00000001		\n" //compare if input register is 1      
"		BREQ negativeincrement	\n"	//if it is branch negativeincrement
"		IN r17, 0x06			\n" //get input from pinc
"		LSR r17					\n"	//right shift input register
"		LSR r17					\n"
"		LSR r17					\n"
"		LSR r17					\n"
"		CPI r17, 0b00000001		\n" //compare if input register is 1  
"		BREQ plusdelay			\n"	//if it is branch plusdelay
"		LSR r17					\n"	//right shift input register
"		CPI r17, 0b00000001		\n" //compare if input reigster is 1
"		BREQ negativedelay		\n"	//if it is branch negativedelay
"		JMP  LOOP				\n"
  );
}