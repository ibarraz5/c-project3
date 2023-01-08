/*
Ivan Barraza Duran 
SER 486
Homework 3
Initialize uart 
Sets PB1 as an output
Prints HW assignment and name to console
Calls writehex8 and writehex16 to display numeric value of number in hex
Loops forever blinking the led in morse code for ok
*/

#include "hw4lib.h"
#include "output.h"

#define PINB (*((volatile char *)0x23))
#define DDRB (*((volatile char *)0x24))

int main(void)
{
    // Do the required initialization
    uart_init(); // Call uart_init to intialize ability to write messages to console
    DDRB |= 0x2; // Set PB1 as an output pin

    void writestr(char* message){
        unsigned int i = 0; 
        while(message[i] != '\0'){
            uart_writechar(message[i]);
            i++;
        }
    }
    //Output assignment details
    writestr("SER486 HW3 - Ivan Barraza Duran\n\r"); // \r is required by console to display the carriage return

    // Now call the writeHex functions to print out the required sections for part 2 of the HW
    writehex8(0x0A);
    writestr("\n\r");

    writehex16(0xC0DE);
    writestr("\n\r");

    // loop forever blinking the led with morse code
    while(1){
        blink_led("--- -.-"); // Morse Code = OK
        writestr(" Loop forever... ");
    }

    return 0;
}