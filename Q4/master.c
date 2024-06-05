#include <avr/io.h>
#include <util/delay.h>

#define SS_PIN   PB2
#define MOSI_PIN PB3
#define MISO_PIN PB4
#define SCK_PIN  PB5

#define ACK 0x79
#define NACK 0x1F

void SPI_MasterInit(void) {
    // Set MOSI, SCK, and SS as output, MISO as input
    DDRB = (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
    DDRB &= ~(1 << MISO_PIN);
    // Enable SPI, Set as Master, Set clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

uint8_t SPI_MasterTransfer(uint8_t data) {
    SPDR = data; // Start transmission
    while (!(SPSR & _BV(SPIF))); // Wait for transmission complete
    return SPDR; // Return received data
}

void setup() {
    SPI_MasterInit();
    DDRD = 0xFF; // Set PORTD as output for displaying results
}

void loop() {
    uint8_t x = 5; // Example number
    uint8_t y = 0; // Operation code for x+1

    PORTB &= ~(1 << SS_PIN); // Enable Slave
    SPI_MasterTransfer(x);
    SPI_MasterTransfer(y);

    uint8_t ack = SPI_MasterTransfer(0xFF); // Receive ACK/NACK
    uint8_t result = (ack == ACK) ? SPI_MasterTransfer(0xFF) : 0xFF; // Receive result if ACK

    PORTB |= (1 << SS_PIN); // Disable Slave

    PORTD = result; // Display result on PORTD

    _delay_ms(1000); // 1 second delay
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
