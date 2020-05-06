#include <EC11.hpp>

class Display {

private:

EC11 encoder;

int ENCODER_PIN_A;
int ENCODER_PIN_B;
int ST_CP;          // RCLK
int SH_CP;          // SCLK
int DS;             // DIO

const int minvalue = 897;
const int maxvalue = 1059;

int value      = 897;
int displayval = 897;

// Table to convert a hex digit into the matching 7-seg display segments
int hexDigitValue[10] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };


public:
 Display(int st_cp, int sh_cp, int ds, int encoder_pin_a, int encoder_pin_b) {
           ST_CP = st_cp;
           SH_CP = sh_cp;
           DS = ds;
           ENCODER_PIN_A = encoder_pin_a;
           ENCODER_PIN_B = encoder_pin_b;
 }

 void pinDidChange() {
   encoder.checkPins(digitalRead(ENCODER_PIN_A), digitalRead(ENCODER_PIN_B));
 }

void setup()
{
        Serial.begin(9600);
        Serial.println("EC11 Test");

        // Set Arduino pins as outputs
        pinMode(ST_CP, OUTPUT);
        pinMode(SH_CP, OUTPUT);
        pinMode(DS,    OUTPUT);

        pinMode(ENCODER_PIN_A, INPUT_PULLUP);
        pinMode(ENCODER_PIN_B, INPUT_PULLUP);

        attachInterrupt(0, pinDidChange, CHANGE);
        attachInterrupt(1, pinDidChange, CHANGE);
}



/* Set display digit to a hexadecimal value '0'..'9','A'..'F'
 *
 *    row = row number of digit to light up 0..3 where 3 is most significant (leftmost) display digit
 *    dgit = value 0 to 15
 *    decimalPoint = true/false : whether to light thde decimal point or not
 */
void setDigit(unsigned int row, unsigned int digit, boolean decimalPoint)
{
        unsigned int rowSelector;
        unsigned int data;

        rowSelector = bit(3-row)<<4;
        data =  ~hexDigitValue[ digit & 0xF ];
        if(decimalPoint)
                data &= 0xFE;

        // First 8 data bits all the way into the second 74HC595
        shiftOut(DS, SH_CP, LSBFIRST, data );

        // Now shift 4 row bits into the first 74HC595 and latch
        digitalWrite(ST_CP, LOW);
        shiftOut(DS, SH_CP, LSBFIRST, rowSelector );
        digitalWrite(ST_CP, HIGH);

}


/* Displays a number as a 4-digit decimal number on the display
 *   Note this is multiplexed, so you need to keep calling it
 *   or you'll end up with just one digit lit.
 */


void displayNumber(unsigned int number){
        static bool showDecimal = false;

        for(unsigned int i=0; i<4; i++) {

                if(i==1) {
                        showDecimal = true;
                }else {
                        showDecimal = false;
                }

                setDigit(i, number % 10, showDecimal);         // display righmost 4 bits (1 digit)
                number = number / 10;         // roll on to the next digit
                delay(1);
        }
}



void loop()
{
        EC11Event e;

        if (encoder.read(&e)) {
                if (e.type == EC11Event::StepCW) {
                        value += e.count;
                        if(value > maxvalue) {
                                value = minvalue;
                        }
                } else {
                        value -= e.count;
                        if(value < minvalue) {
                                value = maxvalue;
                        }
                }

                displayval = value % 10000;

        }

        displayNumber(displayval);
}
};
