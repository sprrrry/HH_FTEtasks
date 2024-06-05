#include <avr/io.h>
#include <util/delay.h>

#define DISPLAY1 PB0
#define DISPLAY2 PB1
#define MULTIPLEX_DELAY 5 // Short delay for multiplexing
#define DISPLAY_DURATION 500 // Duration for displaying each Fibonacci number
#define MAX_FIB_INDEX 12 // Maximum index for Fibonacci sequence to avoid overflow

uint8_t segment_map[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

int fib_cache[MAX_FIB_INDEX + 1] = {0, 1}; // Cache for storing Fibonacci values

void setup() {
    DDRD = 0xFF; // Set PORTD as output for segment control
    DDRB = (1 << DISPLAY1) | (1 << DISPLAY2); // Set DISPLAY1 and DISPLAY2 pins as output
    for (uint8_t i = 2; i <= MAX_FIB_INDEX; i++) {
        fib_cache[i] = fib_cache[i-1] + fib_cache[i-2];
    }
}

void display_digit(uint8_t digit, uint8_t display) {
    PORTD = 0;
    if (display == 0) {
        PORTB |= (1 << DISPLAY2); // Activate display 1
        PORTB &= ~(1 << DISPLAY1); // Deactivate display 2
    } else {
        PORTB |= (1 << DISPLAY1); // Activate display 2
        PORTB &= ~(1 << DISPLAY2); // Deactivate display 1
    }
    PORTD = segment_map[digit]; // Send segment data to PORTD
    _delay_ms(MULTIPLEX_DELAY); // Brief delay for multiplexing
}

void display_number(int number) {
    for (int i = 0; i < DISPLAY_DURATION / (2 * MULTIPLEX_DELAY); i++) { // Ensure visible display through multiplexing
        display_digit(number % 10, 0); // Display ones place on display 1
        display_digit((number / 10) % 10, 1); // Display tens place on display 2
    }
}

void loop() {
    static uint8_t index = 0;
    int fib_number = fib_cache[index++];
    if (fib_number > 99) {
        index = 0; // Reset index to avoid overflow
    }
    else display_number(fib_number);
    _delay_ms(DISPLAY_DURATION); // Delay between updates
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}