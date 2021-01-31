#include <stdbool.h>
#include "at91sam9263.h"
#include "AT91SAM9263-EK.h"
 
#define A AT91C_PIO_PB25
#define B AT91C_PIO_PB24
#define C AT91C_PIO_PB22
#define D AT91C_PIO_PB21
#define E AT91C_PIO_PB20
#define F AT91C_PIO_PB27
#define G AT91C_PIO_PB26
#define DEC 1<<30
#define ENTITY 1<<28
 
unsigned volatile int timeCounter = 0;
unsigned volatile int refreshCounter = 0;
volatile int counter = 0;
 
bool flag = true;
 
unsigned int numbers[10] = {
        A|B|C|D|E|F,
        B|C,
        A|B|D|E|G,
        A|B|C|G|D,
        F|B|G|C,
        A|F|G|C|D,
        A|F|G|E|D|C,
        A|B|C,
        A|B|C|D|E|F|G,
        A|B|F|G|C|D
};
 
void PIOB_init(){
    *AT91C_PIOB_PER = A|B|C|D|E|F|G;
    *AT91C_PIOB_OER = A|B|C|D|E|F|G;
}
 
void initButton(){
    *AT91C_PIOC_PER = AT91B_BP1;
    *AT91C_PIOC_ODR = AT91B_BP1;
    *AT91C_PIOC_PPUER = AT91B_BP1;
}
 
void printNumber(int number) {
    switch(number) {
        case 0: AT91C_BASE_PIOB->PIO_SODR = numbers[0];break;
        case 1: AT91C_BASE_PIOB->PIO_SODR = numbers[1];break;
        case 2: AT91C_BASE_PIOB->PIO_SODR = numbers[2];break;
        case 3: AT91C_BASE_PIOB->PIO_SODR = numbers[3];break;
        case 4: AT91C_BASE_PIOB->PIO_SODR = numbers[4];break;
        case 5: AT91C_BASE_PIOB->PIO_SODR = numbers[5];break;
        case 6: AT91C_BASE_PIOB->PIO_SODR = numbers[6];break;
        case 7: AT91C_BASE_PIOB->PIO_SODR = numbers[7];break;
        case 8: AT91C_BASE_PIOB->PIO_SODR = numbers[8];break;
        case 9: AT91C_BASE_PIOB->PIO_SODR = numbers[9];break;
    }
}
 
void clearDisplay() {
    AT91C_BASE_PIOB->PIO_CODR = A|B|C|D|E|F|G;
}
 
void setNumDec(int num) {
    AT91C_BASE_PIOB->PIO_SODR = DEC;
    AT91C_BASE_PIOB->PIO_CODR = ENTITY;
    clearDisplay();
    printNumber(num);
}
 
void setNumEntity(int num) {
    AT91C_BASE_PIOB->PIO_SODR = ENTITY;
    AT91C_BASE_PIOB->PIO_CODR = DEC;
    clearDisplay();
    printNumber(num);
}
 
void setNumber(int i) {
    if(refreshCounter > 1) {
        refreshCounter = 0;
        if (flag) {
            setNumEntity(i % 10);
            flag = false;
        } else {
            setNumDec(i / 10);
            flag = true;
        }
    }
}
 
void increase() {
    if(counter == 100) {
        counter = -1;
    }
    counter++;
}
 
void decrease() {
    if (counter == -1) {
        counter = 100;
    }
    counter--;
}
 
int main(){
    PIOB_init();
    initButton();
 
    AT91C_BASE_PITC->PITC_PIMR = 6249;
    AT91C_BASE_PITC->PITC_PIMR |= 1 << 24;
 
    while(1) {
        if(AT91C_BASE_PITC->PITC_PISR) {
            timeCounter++;
            refreshCounter++;
            AT91C_BASE_PITC->PITC_PIVR;
        } else if (timeCounter >= 10) {
            if(*AT91C_PIOC_PDSR & AT91B_BP1) {
                increase();
            } else {
                decrease();
            }
            timeCounter = 0;
        }
        setNumber(counter);
    }
}