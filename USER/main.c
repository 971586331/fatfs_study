#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h" 
 
 int main(void)
 { 
	 FATFS fs[2];
	int rc = 0;
	 int t = 0;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 
	uart_init(9600);	 
	LED_Init();        										    

	 printf("SD_Initialize\r\n");	

	while(SD_Initialize())				
	{
		delay_ms(200);
		LED0=!LED0;
	}								   	
  rc = f_mount(&fs[0],"0:",1); 					
	printf("f_mount = %d\r\n", rc);
 	rc = f_mount(&fs[1],"1:",1); 				
	printf("f_mount = %d\r\n", rc);											 
	
	FIL fil;
	char buf[20];
	UINT bw;
	UINT br;
	
	printf("open or create file\r\n");
	rc = f_open(&fil, "0:/fatfs4.txt", FA_WRITE | FA_CREATE_ALWAYS);
	printf("rc = %d\r\n", rc);

	printf("write file\r\n");
	rc = f_write(&fil, "HelloWorld\r\n", 12, &bw);
	printf("rc = %d\r\n", rc);

	printf("%d bytes writen\r\n", bw); 
	rc = f_close(&fil);
	printf("rc = %d\r\n", rc);

	rc = f_open(&fil, "0:/fatfs4.txt", FA_READ);
	printf("rc = %d\r\n", rc);

	rc = f_read(&fil, buf, 12, &br);
	printf("rc = %d\r\n", rc);
	printf("%s", buf);
			
	rc = f_close(&fil);
	printf("rc = %d\r\n", rc);
		
	while(1)
	{
		t++;
		delay_ms(200);		 			   
		LED0=!LED0;
	} 
}
