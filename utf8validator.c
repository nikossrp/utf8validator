#include <stdio.h>


int main()
{
	int ch, head, tail, count = 0, count_asci=0;		//count metritis gia ta multi-bytes, ch o xarakthras
	int temp1, temp2, temp3, temp4;								//temp1,2,3,4 oi prosorines metablhtes gia ton elenxo tou code point
	int code_point;					
									

	ch = getchar();
	
	while(ch != EOF)
	{	
		
	
														//Gia ta 4 bytes elenxos head , tail
														
		head = (unsigned int)ch >> 3;					// ton kanw unsigned int  gia otan ton kanw olisthisi na mhn parw arnhtiko arithmo
		
		temp1 = ch & (0xF >> 1);						//11110xxx & 111 == xxx gia ta 3 bits tis kefalhs
		
		temp1 = (unsigned long int)temp1 <<6;
		
													
		if(head == 30)								// elenxos gia to head ton 4 bytes
		{
			ch = getchar();							// pairnw to epomeno byte
	
	
			tail = (unsigned int) ch >> 6;	
			temp2 = ch & (0xFF >> 2); 						// 10xxxxxx & 111111  = xxxxxx pairnw ta 6 bits tis prwths ouras
					
			
			if(tail == 2)									// an einai duo einai tis morfhs 10xxxxxx ara pame stin epomenh oura kok
			{
			
			
				
				ch = getchar();
				tail = (unsigned int) ch >> 6;	
				
				temp3 = ch & (0xFF >> 2);					//pairnw ta 6 bits tis defteris ouras
					
				if(tail == 2)
				{
				
					ch = getchar();
					
					tail = (unsigned int) ch >> 6;
					temp4 = ch & (0xFF >> 2);				//pairnw ta 6 bits tis tritis ouras
					
					
					if(tail == 2)
					{
						code_point = temp1 | temp2;			  							//bazw ta 6 bits tis prwths ouras sthn kefalh
						code_point = ((unsigned long int)code_point << 6) | temp3;		//bazw ta 6 bits tis defteris ouras	
						code_point = (code_point	<< 6) | temp4;						//bazw ta 6 bits tis tritis ouras
						
					
						if(code_point < 0x010000 )										//shmenei oti kwdikopoihte kai se ligotera bytes
						{ 
							printf("Oversized UTF-8 code point U+%X\n", code_point);
							return 0;
						}
						else if(code_point >= 0x010000 && code_point <= 0x10FFFF)
						{
						
								count++;											//o metritis gia tous multi- bytes au3anei kata 1
						
						}else if(code_point > 0x10FFFF){
							
							printf("Invalid code point: U+%X\n", code_point);
							return 0;
						}
						
								
						
					}else 
					{
						printf("Invalid tail byte: 0x%X\n", ch);
						return 0;
					}
					
				}else 
					{
						printf("Invalid tail byte: 0x%X\n", ch);
						return 0;
					}
				
			}else {
						printf("Invalid tail byte: 0x%X\n", ch);			//an estw kai mia oura den antistixh sthn morfh 10xxxxxx den einai UTF-8
						return 0;
					}
			
		
	
		}else if(head != 30){						//an den einai 4bytes
			
				
				head = head >> 1;					// gia ta 3 bytes	elenxos head , tail
			
				temp1 = ch & (0xF);							//pairnw ta 4 teleftaia bits tis keffalhs
				
					
				if(head == 14)					
				{
				
					
					ch = getchar();							//prwth oura
					
					tail = (unsigned int) ch >> 6;			//pairnw ta 2 prwta bits tis ouras
					
					temp2 = ch & (0xFF >> 2);				//apomonwnw ta 6 bits tis prwths ouras
					
				
					if(tail == 2)
					{
						
						ch = getchar();
						
						tail = (unsigned int) ch >> 6;			// ta 2 bits tis defterhs ouras
						
						temp3 = ch & (0xFF >> 2);			//apomonwnw ta 6 bits tis defterhs ouras
						
						
						if(tail == 2)
						{											//elenxos code point
							temp1 = (unsigned long int)temp1 << 6;
							code_point = temp1 | temp2;						//1h oura
							code_point = (unsigned long int)code_point << 6;	
							code_point = code_point | temp3;				//2h oura
							
							
							if(code_point < 0x0800){
								printf("Oversized code point U+%X\n", code_point);
								return 0;
							}
							else if(code_point >= 0xD800 && code_point <= 0xDFFF) 		//το [D800 , DFFF] einai to anepitrepto diastima
							{
								printf("Invalid code point: U+%X\n", code_point);
								return 0;
								
							}
							else if(code_point >= 0x0800 && code_point <= 0xFFFF)		//auto einai to diastima gia to 3 bytes \ [D800 , DFFF]
							{
								count++;
								
							}
							else{
							
							printf("Invalid code point: U+%X\n", code_point);
							return 0;
						}
						
							
							
						}else {
							
							printf("Invalid tail byte: 0x%X\n", ch);
							return 0;
						
						}
						
					}else {
						
						printf("Invalid tail byte: 0x%X\n", ch);
						return 0;
						
						}
					
				}else if(head != 14){							//gia ta 2 bytes head,tail
						
						head = head >> 1;	
						
						temp1 = ch & (0xFF >> 3);
						
						if(head == 6)
						{
							ch = getchar();
							
							tail = (unsigned int) ch >> 6;
							
							temp2 = ch & (0xFF >> 2);
							
						
							if(tail == 2)
							{
								
								temp1 =(unsigned long int)temp1 << 6;
								code_point = temp1 | temp2;				// bazw thn 1h kai monadiki oura
							
								if(code_point < 0x0080){
									printf("Oversized code point U+%X", code_point);
									return 0;
								}
								else if(code_point >= 0x0080 && code_point <= 0x07FF)		// to epitreptw diastima gia ta 2 bytes
								{
									count++;
									
								}else{
							
									printf("Invalid code point: U+%X\n", code_point);
									return 0;
								}
								
							}else{
								
							 printf("Invalid tail byte: 0x%X \n", ch);
							 return 0;
							 
							}
							
						}else if(head != 6){					//gia to 1 byte elenos head
							
							head = head >> 2;
							
							if(head == 0)
							{
								code_point = ch & (0xFF >> 1);  	//0xxxxxxx & 1111111 == xxxxxxx	
								
							
								if(code_point >= 0x0000 && code_point <= 0x007F)			//to epitrepto diastima gia to 1 byte
								{
									
									count_asci++;				//afxanw to metriti gia tous ASCII kwdikous
									
								}else{
							
									printf("Invalid code point: U+%X\n", code_point);
									return 0;
								}
								
								
								
							}else if(head != 0){
								
								printf("Invalid head byte: 0x%X \n", ch);		//sthn periptwsh pou den einai oute 1 byte tote exoume allh kwdikopoihsh
								return 0;
							}													//tote ektupwse se 16adikh morfi to ch (%x)
						}
					
				}
				
		}
		
	
			ch = getchar();	
			
	}
	
	printf("Found %d ASCII and %d multi-byte UTF-8 characters\n", count_asci, count );
		
}
