void setup()
{
  asm(
"		JMP start				\n"
"delay: LDI	 r23,  81			\n"	//Delay 1 sec
"w1:	LDI	 r24,  255 			\n"
"w2:	LDI  r25,  255 			\n"
"w3:	DEC  r25  				\n"
"		BRNE w3					\n"
"		DEC  r24				\n"
"		BRNE w2					\n"
"		DEC  r23				\n"
"       BRNE w1					\n"
"		RET						\n"
";Your Functions Code Begin		\n" //Write your code   
"PRINTCARRY:					\n" //  printcarry subroutine
"	CALL delay					\n" //  call delay
"	ROL r17						\n" //  right circular shift   
"								\n"
";Your Functions Code End		\n" 
"								\n"    
"start:							\n" //Write your code
"		IN 	 r16,  0x0A ;		\n"	//              
"		ORI	 r16,  0b11111111	\n"//             
"		LDI	 r17,  0b00000001	\n" //r17 <- 1    
"		OUT  0x0A, r16			\n" 
  );

}

void loop()
{
  asm(
"LOOP:							\n"//Write your code
";Your LOOP Code Begin			\n"    
"		OUT  0x0b, r17 			\n" //PORTD <- r17  
"   	ROL  r17                \n" //right circular shift        
"   	BREQ PRINTCARRY         \n" //if there is carry branch to printcarry           
"		CALL delay				\n"	//Call delay function
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
  );
  
}