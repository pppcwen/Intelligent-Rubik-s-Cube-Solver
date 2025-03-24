/*
 * File:   main.c
 * Author: user
 *
 * Created on 2025?1?12?, ??3:59
 */

#include <xc.h>
#include <pic18f4520.h>
#include <string.h>
#include "solution.h" 

#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config LVP = OFF        // Low Voltage In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF     
void motor_down_1(void);
void motor_down_2(void);
void motor_down_3(void);
void motor_down_4(void);
void motor_down_1_re(void);
void motor_down_2_re(void);
void motor_down_3_re(void);
void motor_down_4_re(void);
void motor_up_1(void);
void motor_up_2(void);
void motor_up_3(void);
void motor_up_4(void);
void motor_1_3_clockwise(void);
void motor_1_3_Counter_clockwise(void);
void reset(void);
void U(void);
void U_(void);
void R(void);
void R_(void);
void L(void);
void L_(void);
void B(void);
void B_(void);
void F(void);
void F_(void);
void D(void);
void D_(void);

#define _XTAL_FREQ 4000000 // ??????? 4 MHz
int angle=0;
int state=0;
void __interrupt() ISR() {
    angle=0;
    if(state==0){
       angle=1;
        motor_down_1();
         __delay_ms(8);
        angle=1;
        motor_down_2();
        __delay_ms(8);
        angle=1;
        motor_down_3();
        __delay_ms(8);
        angle=1;
        motor_down_4();
        __delay_ms(8);
        angle=0;
        motor_up_1();
        __delay_ms(8);
        angle=0;
        motor_up_2();
        __delay_ms(8);
        angle=1;
        motor_up_3();
        __delay_ms(8);
        angle=1;
        motor_up_4();
        __delay_ms(8);
        angle=0;
        motor_down_1();
        __delay_ms(8);
        angle=0;
        motor_down_2();
        __delay_ms(8);
        angle=0;
        motor_down_3();
        __delay_ms(8);
        angle=0;
        motor_down_4();
        __delay_ms(8);
        state++;
    }
    else if(state==1){
        INTCONbits.INT0IF = 0;
        state++;
        int length=(int)strlen(solution);
        for(int i=0;i<length;i++){
            if(solution[i]=='U') U();
            else if(solution[i]=='u') U_();
            else if(solution[i]=='F') F();
            else if(solution[i]=='f') F_();
            else if(solution[i]=='R') R();
            else if(solution[i]=='r') R_();
            else if(solution[i]=='L') L();
            else if(solution[i]=='l') L_();
            else if(solution[i]=='D') D();
            else if(solution[i]=='d') D_();
            else if(solution[i]=='B') B();
            else if(solution[i]=='b') B_();
        }
    }
    else if(state==2){
        angle=1;
        motor_down_1();
        __delay_ms(8);
        motor_down_2();
        __delay_ms(8);
        motor_down_3();
        __delay_ms(8);
        motor_down_4();
        __delay_ms(8);
        state=0;
    }
    INTCONbits.INT0IF = 0;
}
void main(void) {
    ADCON1 = 0x0F; // ????????
    TRISA = 0xFF;  // ?? PORTA ???
    LATA = 0x00;   // ?? PORTA
    RCONbits.IPEN = 0;    // ???????
    INTCONbits.INT0IF = 0; // ??????
    INTCONbits.GIE = 1;    // ??????
    INTCONbits.INT0IE = 1; // ?? INT0 ??
    TRISBbits.TRISB1 = 1; // ?? RB0 ???
    PORTB = 0;

    // Timer2 -> ???????? 4
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2CKPS = 0b01;

    // ??????????Fosc = 125 kHz?Tosc = 8 ?s
    OSCCONbits.IRCF = 0b001;

    // ?? CCP ??? PWM
    CCP1CONbits.CCP1M = 0b1100;

    // CCP1/RC2 -> ??
    TRISC = 0;
    LATC = 0;

    // ?? PR2 ? CCP ?? PWM ??????
    PR2 = 0x9b; // ?? PWM ???? 20ms
    CCPR1L = 0x04; // ?? PWM ???
    CCP1CONbits.DC1B = 0;
    
    
    while(1){

    }
}
void U(void){
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=0;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_Counter_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=0;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    __delay_ms(8);
    L();
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=1;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
}
void U_(void){
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=0;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_Counter_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=0;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    __delay_ms(8);
    L_();
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=1;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
}
void D(void){
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=0;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_Counter_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=0;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    __delay_ms(8);
    R();
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=1;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
}
void D_(void){
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=0;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_Counter_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=0;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    __delay_ms(8);
    R_();
    angle=1;
    motor_down_1();
    __delay_ms(8);
    angle=1;
    motor_up_1();
    __delay_ms(8);
    angle=0;
    motor_down_1();
    angle=1;
    motor_down_2();
    __delay_ms(8);
    angle=1;
    motor_down_4();
    __delay_ms(8);
    motor_1_3_clockwise();
    __delay_ms(20);
    angle=0;
    motor_down_2();
    __delay_ms(8);
    angle=0;
    motor_down_4();
    __delay_ms(8);
    angle=1;
    motor_down_3();
    __delay_ms(8);
    angle=1;
    motor_up_3();
    __delay_ms(8);
    angle=0;
    motor_down_3();
    __delay_ms(8);
}
void F(void){
        angle=1;
        motor_down_1();
        __delay_ms(8);
        angle=1;
        motor_up_1();
        __delay_ms(8);
        angle=0;
        motor_down_1();
        __delay_ms(8);
        angle=0;
        motor_up_1();
        reset();
        __delay_ms(8);
}
void F_(void){
        angle=1;
        motor_up_1();
        __delay_ms(8);
        angle=1;
        motor_down_1();
        __delay_ms(8);
        angle=0;
        motor_up_1();
        __delay_ms(8);
        angle=0;
        motor_down_1();
        reset();
        __delay_ms(8);
}
void R(void){
        angle=1;
        motor_down_2();
        __delay_ms(8);
        angle=1;
        motor_up_2();
        __delay_ms(8);
        angle=0;
        motor_down_2();
        __delay_ms(8);
        angle=0;
        motor_up_2();
        reset();
        __delay_ms(8);
}
void R_(void){
        angle=1;
        motor_up_2();
        __delay_ms(8);
        angle=1;
        motor_down_2();
        __delay_ms(8);
        angle=0;
        motor_up_2();
        __delay_ms(8);
        angle=0;
        motor_down_2();
        reset();
        __delay_ms(8);
}
void B_(void){
        angle=0;
        motor_up_3();
        __delay_ms(8);
        angle=1;
        motor_down_3();
        __delay_ms(8);
        angle=1;
        motor_up_3();
        __delay_ms(8);
        angle=0;
        motor_down_3();
        reset();
        __delay_ms(5);
}
void B(void){
        angle=1;
        motor_down_3();
        __delay_ms(8);
        angle=0;
        motor_up_3();
        __delay_ms(8);
        angle=0;
        motor_down_3();
        __delay_ms(8);
        angle=1;
        motor_up_3();
        reset();
        __delay_ms(8);
}
void L_(void){
        angle=0;
        motor_up_4();
        __delay_ms(8);
        angle=1;
        motor_down_4();
        __delay_ms(8);
        angle=1;
        motor_up_4();
        __delay_ms(8);
        angle=0;
        motor_down_4();
        reset();
        __delay_ms(8);
}
void L(void){
        angle=1;
        motor_down_4();
        __delay_ms(8);
        angle=0;
        motor_up_4();
        __delay_ms(8);
        angle=0;
        motor_down_4();
        __delay_ms(8);
        angle=1;
        motor_up_4();
        reset();
        __delay_ms(8);
}
void motor_down_1(void){
    TRISAbits.TRISA0=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA0 = 1;
         __delay_us(60);
         LATAbits.LATA0 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA0 = 1;
         __delay_us(20);
         LATAbits.LATA0 = 0;
         __delay_us(480);
        }
    }
    TRISAbits.TRISA0=1;
}
void motor_down_2(){
    TRISAbits.TRISA1=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA1 = 1;
         __delay_us(60);
         LATAbits.LATA1 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA1 = 1;
         __delay_us(20);
         LATAbits.LATA1 = 0;
         __delay_us(480);
        }
    }
    TRISAbits.TRISA1=1;
}
void motor_down_3(){
    TRISAbits.TRISA2=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA2 = 1;
         __delay_us(60);
         LATAbits.LATA2 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA2 = 1;
         __delay_us(20);
         LATAbits.LATA2 = 0;
         __delay_us(480);
        }
    }
    TRISAbits.TRISA2=1;
}
void motor_down_4(){
    TRISAbits.TRISA3=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA3 = 1;
         __delay_us(60);
         LATAbits.LATA3 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA3 = 1;
         __delay_us(20);
         LATAbits.LATA3 = 0;
         __delay_us(480);
        }
    }
    TRISAbits.TRISA3=1;
}
void motor_up_1(void){
    TRISAbits.TRISA4=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         __delay_us(60);
         LATAbits.LATA4 = 0;
         __delay_us(480);
    }
        for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         __delay_us(57);
         LATAbits.LATA4 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         __delay_us(20);
         LATAbits.LATA4 = 0;
         __delay_us(480);
    }
         for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         __delay_us(23);
         LATAbits.LATA4 = 0;
         __delay_us(480);
        }
    }
    
     TRISAbits.TRISA4=1;  
}
void motor_up_2(){
    TRISAbits.TRISA5=0;
    if(angle==0){
        for(int i=0;i<80;i++){
         LATAbits.LATA5 = 1;
         __delay_us(50);
         LATAbits.LATA5 = 0;
         __delay_us(480);
    }
        for(int i=0;i<80;i++){
         LATAbits.LATA5 = 1;
         __delay_us(47);
         LATAbits.LATA5 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATAbits.LATA5 = 1;
         __delay_us(18.5);
         LATAbits.LATA5 = 0;
         __delay_us(480);
    }
         for(int i=0;i<80;i++){
         LATAbits.LATA5 = 1;
         __delay_us(21.5);
         LATAbits.LATA5 = 0;
         __delay_us(480);
        }
    }
    TRISAbits.TRISA5=1;
}
void motor_up_3(){
    TRISBbits.TRISB2=0;
    if(angle==1){
        for(int i=0;i<80;i++){
         LATBbits.LATB2 = 1;
         __delay_us(61);
         LATBbits.LATB2 = 0;
         __delay_us(480);
    }
        for(int i=0;i<80;i++){
         LATBbits.LATB2 = 1;
         __delay_us(58);
         LATBbits.LATB2 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATBbits.LATB2 = 1;
         __delay_us(22.5);
         LATBbits.LATB2 = 0;
         __delay_us(480);
    }
         for(int i=0;i<80;i++){
         LATBbits.LATB2 = 1;
         __delay_us(25);
         LATBbits.LATB2 = 0;
         __delay_us(480);
        }
    }
    TRISBbits.TRISB2=1;
}
void motor_up_4(){
    TRISBbits.TRISB3=0;
    if(angle==1){
        for(int i=0;i<80;i++){
         LATBbits.LATB3 = 1;
         __delay_us(59);
         LATBbits.LATB3 = 0;
         __delay_us(480);
    }
        for(int i=0;i<80;i++){
         LATBbits.LATB3 = 1;
         __delay_us(56);
         LATBbits.LATB3 = 0;
         __delay_us(480);
        }
    }
    else{
        for(int i=0;i<80;i++){
         LATBbits.LATB3 = 1;
         __delay_us(22.5);
         LATBbits.LATB3 = 0;
         __delay_us(480);
    }
         for(int i=0;i<80;i++){
         LATBbits.LATB3 = 1;
         __delay_us(25);
         LATBbits.LATB3 = 0;
         __delay_us(480);
        }
    }
    TRISBbits.TRISB3=1;
}
void motor_1_3_Counter_clockwise(void){
    TRISAbits.TRISA4=0;
    TRISBbits.TRISB2=0;
         for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         LATBbits.LATB2 = 1;
         __delay_us(23);
         LATAbits.LATA4 = 0;
         __delay_us(33);
         LATBbits.LATB2 = 0;
         __delay_us(447);
    }
     TRISAbits.TRISA4=1;  
     TRISBbits.TRISB3=1;
}
void motor_1_3_clockwise(void){
    TRISAbits.TRISA4=0;
    TRISBbits.TRISB2=0;
        for(int i=0;i<80;i++){
         LATAbits.LATA4 = 1;
         LATBbits.LATB2 = 1;
         __delay_us(25);
         LATBbits.LATB2 = 0;
         __delay_us(32);
         LATAbits.LATA4 = 0;
         __delay_us(448);
    }
     TRISAbits.TRISA4=1;  
     TRISBbits.TRISB3=1;
}
void reset(void){
    motor_down_1_re();
    __delay_ms(2);
    motor_down_2_re();
    __delay_ms(2);
    motor_down_3_re();
    __delay_ms(2);
    motor_down_4_re();
    __delay_ms(2);
}
void motor_down_1_re(void){
    TRISAbits.TRISA0=0;
        for(int i=0;i<10;i++){
         LATAbits.LATA0 = 1;
         __delay_us(60);
         LATAbits.LATA0 = 0;
         __delay_us(480);
        }
    TRISAbits.TRISA0=1;
}
void motor_down_2_re(){
    TRISAbits.TRISA1=0;
        for(int i=0;i<10;i++){
         LATAbits.LATA1 = 1;
         __delay_us(60);
         LATAbits.LATA1 = 0;
         __delay_us(480);
        }
    TRISAbits.TRISA1=1;
}
void motor_down_3_re(){
    TRISAbits.TRISA2=0;
        for(int i=0;i<10;i++){
         LATAbits.LATA2 = 1;
         __delay_us(60);
         LATAbits.LATA2 = 0;
         __delay_us(480);
        }
    TRISAbits.TRISA2=1;
}
void motor_down_4_re(){
    TRISAbits.TRISA3=0;
        for(int i=0;i<10;i++){
         LATAbits.LATA3 = 1;
         __delay_us(60);
         LATAbits.LATA3 = 0;
         __delay_us(480);
        }
    TRISAbits.TRISA3=1;
}