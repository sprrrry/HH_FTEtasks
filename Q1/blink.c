#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5

void setup() {
    DDRB |= (1 << LED_PIN); // Set LED_PIN as output
}

void loop() {
    PORTB ^= (1 << LED_PIN); // Toggle LED_PIN
    _delay_ms(1000); // 1 second delay
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
