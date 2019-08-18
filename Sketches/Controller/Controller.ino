#define ROWS 4
#define COLS 8

uint8_t data[ ROWS * 8 ][ COLS ];


// Pin connected to ST_CP of 74HC595
int latchPinRow = 3;
// Pin connected to SH_CP of 74HC595
int clockPinRow = 4;
// Pin connected to DS of 74HC595
int dataPinRow = 5;

// Pin connected to ST_CP of 74HC595
int latchPinCol = 8;
// Pin connected to SH_CP of 74HC595
int clockPinCol = 12;
// Pin connected to DS of 74HC595
int dataPinCol = 11;


void setup() {
    // Setup columns
    pinMode(clockPinCol, OUTPUT);
    pinMode(dataPinCol,  OUTPUT);
    pinMode(latchPinCol, OUTPUT);

    // Setup rows
    pinMode(clockPinRow, OUTPUT);
    pinMode(dataPinRow,  OUTPUT);
    pinMode(latchPinRow, OUTPUT);

    // Set to a known state
    digitalWrite(dataPinCol,  LOW);
    digitalWrite(clockPinCol, LOW);
    digitalWrite(dataPinRow,  LOW);
    digitalWrite(clockPinRow, LOW);
}

void loop(void) {
    // Set first bit in rows
    // Set data pin
    digitalWrite(dataPinRow,  HIGH);
    // Clock transition
    digitalWrite(clockPinRow, HIGH);
    digitalWrite(clockPinRow, LOW);
    // Set data pin back to low
    digitalWrite(dataPinRow,  LOW);

    // Loop through every row
    for (int i = 0; i < ROWS * 8; i++) {
        // Set all values for columns
        for (int j = 0; j < COLS) {
            // Loop through all 8-bits in each column data value
            for (int k = 0; k < 8; k++) {
                // Set data pin
                digitalWrite(dataPinCol,  ((data[i][j] >> k) & 0x01));
                // Clock transition
                digitalWrite(clockPinCol, HIGH);
                digitalWrite(clockPinCol, LOW);
            }
        }

        // Set next row
        // Set data pin back to low
        digitalWrite(dataPinRow,  LOW);
        // Clock transition
        digitalWrite(clockPinRow, HIGH);
        digitalWrite(clockPinRow, LOW);
    }
}
