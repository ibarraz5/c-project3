/********************************************************
 * output.c
 *
 * SER486 Assignment 4
 * Spring 2018
 * Written By:  Doug Sandy (instructor)
 * Modified By:
 *
 * this file implements functions associated with SER486
 * homework assignment 4.  The procedures implemented
 * provide led and console output support for debugging
 * of future SER 486 assignments.
 *
 * functions are:
 *    writestr(char *)  - a function to write an ascii
 *                        null-terminated string to the
 *                        avr atmega 328P uart port.
 *                        (instructor provided)
 *
 *    writehex8(unsigned char) - a function to write the
 *                        hexadecimal representation of
 *                        an 8-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    writehex16(unsigned int) - a function to write the
 *                        hexadecimal representation of
 *                        a 16-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    blink_led(char *) - a function to send a specific
 *                        blink pattern to the development
 *                        board's user-programmable LED.
 *
 *    delay(unsigned int) - delay code execution for
 *                        the specified amount of milliseconds.
 *                        (instructor provided)
 */

 #include "hw4lib.h"

 /* macro definitions used by delay() */
 #define MSEC_PER_SEC     1000
 #define CLOCKS_PER_LOOP  16
 #define LOOPS_PER_MSEC   ((F_CPU/MSEC_PER_SEC)/CLOCKS_PER_LOOP)

 // macro defintion for PORTB register
 #define PORTB (*((volatile char *)0x25))
/**********************************
 * delay(unsigned int msec)
 *
 * This code delays execution for for
 * the specified amount of milliseconds.
 *
 * arguments:
 *   msec - the amount of milliseconds to delay
 *
 * returns:
 *   nothing
 *
 * changes:
 *   nothing
 *
 * NOTE: this is not ideal coding practice since the
 * amount of time spent in this delay may change with
 * future hardware changes.  Ideally a timer should be
 * used instead of a set of for loops.  Timers will be
 * taught later in the semester.
 */
void delay(unsigned int msec)
{
    volatile unsigned i,j ;  /* volatile prevents loops from being optimized away */

    /* outer loop, loops for specified number of milliseconds */
    for (i=0; i<msec; i++) {
        /* inner loop, loops for 1 millisecond delay */
        for (j=0;j<LOOPS_PER_MSEC;j++) {}
    }
}


/**********************************
 * writestr(char * str)
 *
 * This code writes a null-terminated string
 * to the UART.
 *
 * arguments:
 *   str - a pointer to the beginning of the
 *         string to be printed.
 *
 * returns:
 *   nothing
 *
 * changes:
 *   the state of the uart transmit buffer will
 *   be changed by this function.
 *
 * NOTE: uart_init() should be called this function
 *   is invoked for the first time or unpredictable
 *   UART behavior may result.
 */
void writestr(char * str)
{
    unsigned int i;

    /* loop for each character in the string */
    for (i=0; str[i]!=0;i++) {
        /* output the character to the UART */
        uart_writechar(str[i]);
    }
}

/************************************************************
* STUDENT CODE BELOW THIS POINT
*************************************************************/

/* Student-provided function comments go here */
void writehex8(unsigned char num)
{
    /* student-provided implementatino code goes here */
    char leftMost4Bits = (num & 0xF0) >> 4;
    char rightMost4Bits = num & 0x0F;

    int nums[2];
    nums[0] = leftMost4Bits;
    nums[1] = rightMost4Bits;

    //loop over the 4 msbs and 4 lsbs, using a switch statment to output
    for(int i = 0; i < 2; i++){
        switch(nums[i]){
        case 0:
            writestr("0");
            break;
        case 1:
            writestr("1");
            break;
        case 2:
            writestr("2");
            break;
        case 3:
            writestr("3");
            break;
        case 4:
            writestr("4");
            break;
        case 5:
            writestr("5");
            break;
        case 6:
            writestr("6");
            break;
        case 7:
            writestr("7");
            break;
        case 8:
            writestr("8");
            break;
        case 9:
            writestr("9");
            break;
        case 10:
            writestr("A");
            break;
        case 11:
            writestr("B");
            break;
        case 12:
            writestr("C");
            break;
        case 13:
            writestr("D");
            break;
        case 14:
            writestr("E");
            break;
        case 15:
            writestr("F");
            break;
        }
    }
}

/* Student-provided function comments go here */
void writehex16(unsigned int num)
{
    /* student-provided implementatino code goes here */
    writehex8(num >> 8);
    writehex8(num & 0x00FF);
}

/* Student-provided function comments go here */
void blink_led(char *msg)
{
    /* student-provided implementatino code goes here */
        while(*msg != '\0'){
        switch(*msg){
        case '-':
            PORTB |= 0x02; // output high on PB1 (LED on)
            delay(750);
            PORTB &= 0xFD; // output low on PB1 (LED off)
            delay(100);
            break;
        case '.':
            PORTB |= 0x02; // output high on PB1 (LED on)
            delay(250);
            PORTB &= 0xFD; // output low on PB1 (LED off)
            delay(100);
            break;
        case ' ':
            PORTB &= 0xFD; // output low on PB1 (LED off)
            delay(1000);
            break;
        }

        msg++;
    }
}
