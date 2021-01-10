#define PIOB_PER (volatile int* const)0xFFFFF400 //PIO ENABLE REGISTER
#define PIOC_PER (volatile int* const)0xFFFFF600 //PIO ENABLE REGISTER
#define PIOB_OER (volatile int* const)0xFFFFF410 //OUTPUT ENABLE REGISTER
#define PIOC_OER (volatile int* const)0xFFFFF610 //OUTPUT ENABLE REGISTER
#define PIOB_CODR (volatile int* const)0xFFFFF434 //Clear output data register diodSy ds1
#define PIOB_SODR (volatile int* const)0xFFFFF430 //Set output data register diody ds1
#define PIOC_CODR (volatile int* const)0xFFFFF634 //Clear output data register diody ds2
#define PIOC_SODR (volatile int* const)0xFFFFF630 //Set output data register diody ds2
#define LED1 1<<8
#define LED2 1<<29
#define BUT1 1<<4
#define BUT2 1<<5

#define PIOC_PUER (volatile int* const)0xFFFFF664
#define PIOC_PDSR (volatile int* const)0xFFFFF63C

void initButtons(){
    *PIOC_PER = BUT2;
    *PIOC_PER = BUT1;
    
    *PIOC_PUER = BUT2;
    *PIOC_PUER = BUT1;
}

void initLEDs(){
    *PIOB_PER = LED1;
    *PIOB_OER = LED1;
    *PIOC_PER = LED2;
    *PIOC_OER = LED2;
}

void delay(int ms){
    for(int i = 0; i < ms*2000; i++){
        if(!(*PIOC_PDSR & BUT1)) {
            *PIOC_CODR = LED2;
        } else if(!(*PIOC_PDSR & BUT2)) {
            *PIOC_SODR = LED2;
        }
    }
}

void blink(){
    *PIOB_SODR = LED1;
    delay(5000);
    *PIOB_CODR = LED1;
    delay(5000);
}

int main(){
    initButtons();
    initLEDs();
    while(1){
        blink();
    }
}