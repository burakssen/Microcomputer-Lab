void setup()
{
  asm(
"   JMP start                   \n"
"delay: LDI  r23,  40           \n" //Delay 1 sec
"w1:	LDI  r24,  120 	        \n"
"w2:	LDI  r25,  120 	        \n"
"w3:	DEC  r25  	        \n"
"       BRNE w3		        \n"
"	DEC  r24	        \n"
"	BRNE w2		        \n"
"	DEC  r23	        \n"
"       BRNE w1		        \n"
"	RET		        \n"
";Your Functions Code Begin     \n" //Write your code   
"incrementupper:                \n" 
//incrementupper subroutine for incrementing upper digit
"	CALL delay		\n" //call delay
"	CPI r20, 0b00001001	\n" //compare if upper digit is 9 or not
"	BREQ tozero		\n" //if it is 9 branch to to ninty nine
"	INC r20			\n" //increment upper digit
"	LDI r19, 0b00000000	\n" //load lower digit with 0
"	JMP LOOP		\n" //jump to loop
"				\n"
"tozero:			\n" 
//tozero subroutine for making both digits 0
"	LDI r20, 0b00000000	\n" //load upper digit with 0
"	LDI r19, 0b00000000	\n" //load lower digit with 0
"	JMP LOOP		\n" //jump to loop
"tonintynine:			\n" 
// tonintynine subroutine for making both digits 9
"	LDI r20, 0b00001001	\n" //load upper digit with 9
"	LDI r19, 0b00001001	\n" //load lower digit with 9
"	JMP LOOP		\n" //jump to loop



"incrementlower:	\n" 
//incrementlower subroutine for incrementing lower digit
"	CALL delay		\n" //cal delay
"	INC r19 		\n" //increment lower digit
"	CPI r19, 0b00001010	\n" //compare if lower digit is 10
"	BREQ incrementupper	\n" //if it is branch to increment upper
"	JMP LOOP		\n" //jump to loop
"				\n"
"decrementupper:		\n" 
//decrementupper subroutine for decrementing upper digit
"	CALL delay		\n" //call delay
"	CPI r20, 0b00000000	\n" //compare if upper digit is 0 or not
"	BREQ tonintynine	\n" 
// if it is 0 branch to subroutine tonintynine
"	DEC r20			\n" //decrement upper digit
"	ORI r19, 0b00001001	\n" //or immediate lower digit with 9 
"	JMP LOOP		\n" //jump to loop
"				\n"
"decrementlower:		\n" 
//decrement lower subroutine for decrementing lower digit
"	CALL delay		\n" //  call delay
"	CPI r19, 0b00000000	\n" 
//compare if lower digit is zero or not
"	BREQ decrementupper	\n" 
//if it is 0 branch decrementupper subroutine
"	DEC r19			\n" //decrement lower digit
"	JMP LOOP		\n" //jumo to loop
"				\n" 
"calldelay:			\n" 
//calldelay subroutine for controlling buttons
"	CALL delay  	        \n" //call delay
"	JMP LOOP	        \n" //jump to loop

"start:			        \n" //Write your code
"	IN r17, 0x07	        \n" //	<-----	DDRC analog
"	ORI r17, 0b001111       \n"	// input output
"	OUT 0x07, r17	        \n" // assign etme
"	IN r18, 0x04	        \n" //DDRB soldaki digital
"	ORI r18, 0b001111       \n" //input output
"	OUT 0x04, r18 	        \n" //assgin
"	LDI r19, 0b00000000     \n" // lowerdaki sayı
"	LDI r20, 0b00000000     \n" // upperdaki sayı
"	LDI r21, 0b000000       \n" //temp 
"	LDI r22, 0b100000       \n" //temp_for_12
"	LDI r16, 0b100000       \n" //temp_for_13
  );
}

void loop()
{
  asm(
"LOOP:				\n"//Write your code
";Your LOOP Code Begin			\n"
"	OUT 0x05,r19		\n" //out lower digit
"	OUT 0x08,r20		\n" //out upper digit
"	IN r17, 0x03		\n" //take inputs from buttons
"	CP r21, r17	        \n" 
//compare if inputs are the same inputs from before
"	BREQ calldelay	        \n"  //if it is branch to calldelay
"	LSR r21		        \n" //  right shift for taking inputs
"	LSR r21		        \n" 
"	LSR r21		        \n" 
"	LSR r21		        \n" 
"	CPI r21, 0b00000001	\n" //compare if input is 1
"	BREQ incrementlower	\n" // if it is branch to incrementlower   
"	LSR r21			\n"  //right shift again
"	CPI r21, 0b00000001	\n" //compare if input is 1
"	BREQ decrementlower	\n" //if it is branch decrementlower
"	MOV r21, r17		\n" 
//mov input value to previnput register
"	JMP  LOOP		\n" //jump loop
  );
}