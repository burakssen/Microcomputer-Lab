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
"plusdelay:						\n"	//for delay counter plusdelay
"	CPI r21, 0b00001001			\n"	//compare if counter is 9 it means 1000ms
"	BREQ LOOP					\n"	//branch to loop
"	INC r21						\n" //increase counter
"	JMP LOOP					\n" //jump to loop
"negativedelay:					\n"	//for delay counter negativedelay
"	CPI r21, 0b00000001			\n"	//compare if counter is 1 it means 100ms
"	BREQ LOOP					\n"	//if it is branch to loop
"	DEC r21						\n"	//decrement counter
"	JMP LOOP					\n" //jump loop
"plussequence:					\n"	//Makes transition to upper patterns
"	CPI r21, 0b00000100			\n"	//if pattern number is 4
"	BREQ LOOP					\n"	//branch to loop
"	INC r20						\n" //increase pattern number
"	LDI r19, 0b00000000			\n"	//sets step number to 0
"	LDI r22, 0b00000000			\n"	//sets flag to 0
"	JMP LOOP					\n" //jump to loop
"negativesequence:				\n"	//Makes transition to lower patterns
"	CPI r21, 0b00000001			\n"	//if pattern number is 1
"	BREQ LOOP					\n"	// branch to loop
"	DEC r20						\n"	//decrease pattern number
"	LDI r19, 0b00000000			\n"	//sets step number to 0
"	LDI r22, 0b00000000			\n"	//sets flag number to 0
"	JMP LOOP					\n" //jump loop    
"returnright:					\n"	//it returns right from left edge
"	LDI r22, 0b00000001			\n" //set flag to 1	
"	JMP sequenceoneright		\n" //jump to sequenceoneright   
"returnleft:					\n"	//it returns left from right edge
"	LDI r22, 0b00000000			\n" //set flag to 0	
"	JMP sequenceoneleft			\n" //jump to sequenceoneleft         
"sequenceoneleft:				\n"	//left transition of sequence one
"	CPI r20, 0b10000000			\n"	//if LED is comes to left edge
"	BREQ returnright			\n"	//branch to return right
"	INC r19						\n"	//increment step number
"	LSL r20						\n" //left shift to pattern
"	OUT 0x0b, r20				\n"	//gives output to LEDs
"	JMP LOOP					\n" //jump to loop        
"sequenceoneright:				\n" //right transition of sequence one	
"	CPI r20, 0b00000001			\n"	//if LED is comes to right edge
"	BREQ returnleft				\n"	//branch to return left
"	INC r19						\n"	//increment step number
"	LSR r20						\n" //right shift to pattern
"	OUT 0x0b, r20				\n"	//gives output to LEDs	
"	JMP LOOP					\n" //jump to loop      
"sequenceone:					\n"	//main label for sequence one
"	CPI r19, 0b00000000			\n"	//if is is first step
"	BREQ sequenceonefirst		\n"	//branch to sequenceonefirst
"	CPI r22, 0b00000000			\n"	//flag check
"	BREQ sequenceoneleft		\n" //if it is 0, branch to sequenceoneleft
"	CPI r22, 0b00000001			\n"	//flag check
"	BREQ sequenceoneright		\n"	//if it is 1, branch to sequenceoneright       
"sequenceonefirst:				\n"	//label for initialize first pattern
"	INC r19						\n"	//increment step number
"	LDI r20, 0b00000001			\n" //initilaize
"	OUT 0x0b, r20				\n"	//give output to LEDs
"	JMP LOOP					\n" //jump to loop      
"start:							\n" //Write your code
"	IN r17, 0x07				\n" //DDRC analog
"	ORI r17, 0b001111			\n"	//input output
"	OUT 0x07, r17				\n" //assign
"	IN r18, 0x04				\n" //DDRB left digital
"	ORI r18, 0b001111			\n" //input output
"	OUT 0x04, r18 				\n" //assign
"	IN 	 r16,  0x0A ;			\n"	//Get values of DDRD to r16             
"	ORI	 r16,  0b11111111		\n" //Assign ones to define as an output              
"	OUT  0x0A, r16				\n" //Give r16 values to DDRD
"	LDI r19, 0b00000000			\n" // pattern
"	LDI r20, 0b00000001			\n" // sequence counter
"	LDI r21, 0b00000101			\n" // delay counter initialized with 5
"	LDI r22, 0b00000000			\n" // flag
"	LDI r16, 0b10000000			\n" // temp	
  );+
}

void loop()
{
  asm(
"LOOP:						\n"	//LOOP function
";Your LOOP Code Begin		\n"
"	OUT 0x05,r21			\n"	//out delay multiplier
"	OUT 0x08,r20			\n"	//out pattern number
"	MOV r16, r21			\n"	//move counter to temporarly register
"	INC r21					\n"	//increment temp register by one
"	CALL maindelay			\n"	//call maindelay
"	IN r18, 0x03			\n" //get input from pinb
"	LSR r18					\n"	//right shift input register
"	LSR r18					\n"
"	LSR r18					\n"
"	LSR r18					\n"
"	CPI r18, 0b00000001		\n" //compare if imput register is 1   
"	BREQ negativesequence	\n"	//if it is branch negativesequence
"	LSR r18					\n"	//right shift input register
"	CPI r18, 0b00000001		\n" //compare if input register is 1      
"	BREQ plussequence   	\n"	//if it is branch plussequence
"	IN r17, 0x06			\n" //get input from pinc
"	LSR r17					\n"	//right shift input register
"	LSR r17					\n"
"	LSR r17					\n"
"	LSR r17					\n"
"	CPI r17, 0b00000001		\n" //compare if input register is 1  
"	BREQ plusdelay			\n"	//if it is branch plusdelay
"	LSR r17					\n"	//right shift input register
"	CPI r17, 0b00000001		\n" //compare if input reigster is 1
"	BREQ negativedelay		\n"	//if it is branch negativedelay
"	CPI r20, 0b00000001		\n" //if pattern is 1
"	BREQ sequenceone		\n" //branch to sequence one
"	JMP  LOOP				\n"
  );
}