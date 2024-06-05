#include <avr/io.h>
#include <util/delay.h>

#define MAX_INDEX 12 // Maximum Fibonacci index to fit in 8-bit
#define DELAY_MS 1000 // 1 second delay

// Lookup table for storing the first 13 Fibonacci numbers
uint8_t fib_cache[MAX_INDEX + 1] = {0, 1};

void setup() {
    DDRD = 0xFF; // Set all PORTD pins as output for LED array
    // Initialize the lookup table with Fibonacci numbers
    for (uint8_t i = 2; i <= MAX_INDEX; i++) {
        fib_cache[i] = fib_cache[i-1] + fib_cache[i-2];
    }
}

void loop() {
    static uint8_t index = 0;
    PORTD = fib_cache[index++]; // Display Fibonacci number on LED array
    if (index > MAX_INDEX) index = 0; // Reset index to avoid overflow
    _delay_ms(DELAY_MS); // 1 second delay
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
