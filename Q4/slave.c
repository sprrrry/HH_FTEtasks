#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define SS_PIN   PB2
#define MOSI_PIN PB3
#define MISO_PIN PB4
#define SCK_PIN  PB5

#define ACK 0x79
#define NACK 0x1F

void SPI_SlaveInit(void) {
    // Set MISO as output, MOSI, SCK, and SS as input
    DDRB = (1 << MISO_PIN);
    DDRB &= ~((1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN));
    // Enable SPI
    SPCR = (1 << SPE);
}

uint8_t SPI_SlaveTransfer(uint8_t data) {
    SPDR = data; // Load data into the buffer
    while (!(SPSR & _BV(SPIF))); // Wait until transmission complete
    return SPDR; // Return received data
}

uint8_t calculate(uint8_t x, uint8_t y) {
    switch (y) {
        case 0: return x + 1;
        case 1: return x - 1;
        case 2: return x * 2;
        case 3: return floor(x / 3);
        default: return 0xFF; // Invalid operation
    }
}

void setup() {
    SPI_SlaveInit();
    DDRD = 0xFF; // Set PORTD as output for displaying results
}

void loop() {
    uint8_t x = SPI_SlaveTransfer(0xFF); // Receive x from master
    uint8_t y = SPI_SlaveTransfer(0xFF); // Receive y from master
    uint8_t result = calculate(x, y);

    if (result != 0xFF) { // Valid result
        SPI_SlaveTransfer(ACK); // Send ACK
        SPI_SlaveTransfer(result); // Send result
    } else { // Invalid command
        SPI_SlaveTransfer(NACK); // Send NACK
    }

    PORTD = x; // Display received number on PORTD

    _delay_ms(1000); // 1 second delay
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
