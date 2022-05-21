void SysTick_wait(unsigned long delay){ 
 	NVIC_ST_CTRL_R=0x00; 
 	NVIC_ST_RELOAD_R=delay-1; 
 	NVIC_ST_CURRENT_R=0;  	NVIC_ST_CTRL_R=0x05; 
 	while((NVIC_ST_CTRL_R&0x00010000)==0){} 
} 
 
void genericDelay(unsigned long time){ 
 	int i; 
 	for(i=0;i<time;i++){ 
 	 	SysTick_wait(16000); //1ms 
 	} 
