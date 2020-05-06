#include "OneButton.h"
#include "DYPlayerArduino.h"

class Buttons {

// Initialise the player, it defaults to using Serial.
        DY::Player player;

// Alternatively initialise on another serial port.
// DY::Player player(&Serial1); // FO R Arduino mini

#define OUT_PIN_3 3
#define OUT_PIN_4 4
#define OUT_PIN_5 5
#define OUT_PIN_6 6
#define OUT_PIN_7 7
#define OUT_PIN_8 8
#define OUT_PIN_9 9

        OneButton whiteButton(10, true);
        OneButton violetButton(15, true);
        OneButton blueButton(14, true);
        OneButton greenButton(16, true);
        OneButton yellowButton(A3, true);
        OneButton orangeButton(A1, true);
        OneButton redButton(A2, true);
        OneButton pinkButton(A0, true);


        void onWhiteButtonClick()
        {
                player.playSpecified(1);
                Serial.println("Play 1.");
        }

        void onVioletButtonClick()
        {
                player.playSpecified(2);
                Serial.println("Play 2.");
        }

        void onBlueButtonClick()
        {
                digitalWrite(OUT_PIN_3, !digitalRead(OUT_PIN_3));
                Serial.println("Turn on led on pin 3");
        }

        void onGreenButtonClick()
        {
                digitalWrite(OUT_PIN_4, !digitalRead(OUT_PIN_4));
                Serial.println("Turn on led on pin 4");
        }

        void onYellowButtonClick()
        {
                digitalWrite(OUT_PIN_5, !digitalRead(OUT_PIN_5));
                Serial.println("Turn on led on pin 5");
        }

        void onOrgangeButtonClick()
        {
                player.playSpecified(3);
                Serial.println("Play 3.");
        }

        void onRedButtonClick()
        {
                player.playSpecified(4);
                Serial.println("Play 4.");
        }

        void onPinkButtonClick()
        {
                player.playSpecified(5);
                Serial.println("Play 5.");

        }


        void tlacitkaSetup() {

                player.begin();
                player.setVolume(15); // 50% Volume
                // Pick one of these..
                // player.setCycleMode(DY::PlayMode::SEQUENCE); // Play all and stop.
                //  player.setCycleMode(DY::PlayMode::REPEAT); // Play all and repeat.
                //  player.play();

                pinMode(OUT_PIN_3, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_4, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_5, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_6, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_7, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_8, OUTPUT); // sets the digital pin as output
                pinMode(OUT_PIN_9, OUTPUT); // sets the digital pin as output

                whiteButton.attachClick(onWhiteButtonClick);
                violetButton.attachClick(onVioletButtonClick);
                blueButton.attachClick(onBlueButtonClick);
                greenButton.attachClick(onGreenButtonClick);
                yellowButton.attachClick(onYellowButtonClick);
                orangeButton.attachClick(onOrgangeButtonClick);
                redButton.attachClick(onRedButtonClick);
                pinkButton.attachClick(onPinkButtonClick);
        }

        void tlacitkaLoop() {

                whiteButton.tick();
                violetButton.tick();
                blueButton.tick();
                greenButton.tick();
                yellowButton.tick();
                orangeButton.tick();
                redButton.tick();
                pinkButton.tick();

        }
}
