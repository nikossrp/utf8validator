#include <stdio.h>


int main()
{
	int ch, head, tail, count = 0, count_asci=0;		//counter for multi-bytes
	int temp1, temp2, temp3, temp4;								//temp1,2,3,4 for code point
	int code_point;					
									

	ch = getchar();
	
	while(ch != EOF)
	{	
		
	
														//for 4 bytes check head , tail
														
		head = (unsigned int)ch >> 3;					// ton kanw unsigned int  gia otan ton kanw olisthisi na mhn parw arnhtiko arithmo
		
		temp1 = ch & (0xF >> 1);						//11110xxx & 111 == xxx gia ta 3 bits tis kefalhs
		
		temp1 = (unsigned long int)temp1 <<6;
		
													
		if(head == 30)								// check head for 4 bytes
		{
			ch = getchar();							// take the next byte
	
	
			tail = (unsigned int) ch >> 6;	
			temp2 = ch & (0xFF >> 2); 				// 10xxxxxx & 111111  = xxxxxx take the 6 bits from first tail 
					
			
			if(tail == 2)							// if tail == 2 it has the form 10xxxxxx so we go to the next tail and so on
			{
			
			
				
				ch = getchar();
				tail = (unsigned int) ch >> 6;	
				
				temp3 = ch & (0xFF >> 2);					//first we take the 6bits from 2nd tail
					
				if(tail == 2)
				{
				
					ch = getchar();
					
					tail = (unsigned int) ch >> 6;
					temp4 = ch & (0xFF >> 2);				//6bits from 3rd tail
					
					
					if(tail == 2)
					{
						code_point = temp1 | temp2;			  		//put the 6bits from first tail in head
						code_point = ((unsigned long int)code_point << 6) | temp3;		//put the 6bits from second tail	
						code_point = (code_point	<< 6) | temp4;						//6bits from 3rd tail						
					
						if(code_point < 0x010000 )						//this mean we could have fewer bytes
						{ 
							printf("Oversized UTF-8 code point U+%X\n", code_point);
							return 0;
						}
						else if(code_point >= 0x010000 && code_point <= 0x10FFFF)
						{
						
								count++;						
						
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
						printf("Invalid tail byte: 0x%X\n", ch);	//if a tail not corrensponse on form 10xxxxxx, it is not UTF8
						return 0;
					}
			
		
	
		}else if(head != 30){						//if it isn't 4 bytes
			
				
				head = head >> 1;					// for 3 bytes	check head , tail
			
				temp1 = ch & (0xF);							//take the  4 last bits from head
				
					
				if(head == 14)					
				{
				
					
					ch = getchar();					//first tail
					
					tail = (unsigned int) ch >> 6;			//take the 2 first bits from tail
					
					temp2 = ch & (0xFF >> 2);				//isolate the 6 bits from first tail
					
				
					if(tail == 2)
					{
						
						ch = getchar();
						
						tail = (unsigned int) ch >> 6;			// 2 bits from second tail
						
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
							else if(code_point >= 0xD800 && code_point <= 0xDFFF) 		// [D800 , DFFF] einai to invalid space
							{
								printf("Invalid code point: U+%X\n", code_point);
								return 0;
								
							}
							else if(code_point >= 0x0800 && code_point <= 0xFFFF)		//this is the space for 3 bytes \ [D800 , DFFF]
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
					
				}else if(head != 14){							//for 2 bytes head,tail
						
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
								code_point = temp1 | temp2;				// put the 1h tail
							
								if(code_point < 0x0080){
									printf("Oversized code point U+%X", code_point);
									return 0;
								}
								else if(code_point >= 0x0080 && code_point <= 0x07FF)		// the valid psace for 2 bytes
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
							
						}else if(head != 6){					//for 1 byte check head
							
							head = head >> 2;
							
							if(head == 0)
							{
								code_point = ch & (0xFF >> 1);  	//0xxxxxxx & 1111111 == xxxxxxx	
								
							
								if(code_point >= 0x0000 && code_point <= 0x007F)			//the valid space for 1 byte
								{
									
									count_asci++;				//increace the counter for ascii numbers
									
								}else{
							
									printf("Invalid code point: U+%X\n", code_point);
									return 0;
								}
								
								
								
							}else if(head != 0){
								
								printf("Invalid head byte: 0x%X \n", ch);		//in case that isn't 1 bytes we have neither ASCII nor UTF8 code
								return 0;
							}								//so print the hex form ( ch (%x) )
						}
					
				}
				
		}
		
	
			ch = getchar();	
			
	}
	
	printf("Found %d ASCII and %d multi-byte UTF-8 characters\n", count_asci, count );
		
}
