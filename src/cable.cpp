#include <Arduino.h>
#include "cable.h"

Cable::Cable() {
    // Implémentation du constructeur par défaut
}

Cable::Cable(int inputPins[], int outputPins[]) {
    // Implémentation du constructeur surchargé
    this->dataS = 0x00;
    this->dataR = 0x00;

    for (int i = 0; i < 8; i++) {
        this->inputPins[i] = inputPins[i];
        this->outputPins[i] = outputPins[i];
    }

    // Configuration des pins
    for (int i = 0; i < 8; i++) {
        pinMode(this->inputPins[i], INPUT);
        pinMode(this->outputPins[i], OUTPUT);
    }
}

void Cable::envoi(uint8_t data) {
    // Implémentation de la fonction envoi
    this->dataS = data;

    for (int i = 0; i < 8; i++) {
        if (this->dataS & (1 << i)) {
            Serial.print("Le bit ");
            Serial.print(i);
            Serial.print(" est à 1 Broch output ");
            Serial.println(this->outputPins[i]);
            digitalWrite(this->outputPins[i], HIGH);
        } else {
            Serial.print("Le bit ");
            Serial.print(i);
            Serial.print(" est à 0 Broch output ");
            Serial.println(this->outputPins[i]);
            digitalWrite(this->outputPins[i], LOW);
        }
    }

    Serial.print("Data envoyé : ");
    Serial.println(this->dataS, HEX);
}

void Cable::reception() {
    // Implémentation de la fonction reception
    for (int i = 0; i < 8; i++) {
        if (digitalRead(this->inputPins[i]) == HIGH) {
            Serial.print("Le bit ");
            Serial.print(i);
            Serial.print(" est HIGH Broch input ");
            Serial.println(this->inputPins[i]);
            this->dataR |= 1 << i;
        } else {
            Serial.print("Le bit ");
            Serial.print(i);
            Serial.print(" est LOW Broch input ");
            Serial.println(this->inputPins[i]);
            this->dataR &= ~(1 << i);
        }
    }

    Serial.print("Data reçu : ");
    Serial.println(dataR, HEX);
}

bool Cable::verifyCodes(uint8_t send, uint8_t receive) {
    // Implémentation de la fonction verifyCodes
    this->dataS = send;

    this->envoi(this->dataS);
    this->reception();

    return (receive == this->dataR);
}

void Cable::printInputPins() {
    // Implémentation de la fonction printInputPins
    for (int i = 0; i < 8; i++) {
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(this->inputPins[i]);
    }
}

void Cable::printOutputPins() {
    // Implémentation de la fonction printOutputPins
    for (int i = 0; i < 8; i++) {
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(this->outputPins[i]);
    }
}

void Cable::checkCable() {
    // Implémentation de la fonction checkCable
    if (this->verifyCodes(0xFF, 0xFF)) {
        Serial.println("Le câble est fonctionnel");
    } else {
        Serial.println("Le câble n'est pas fonctionnel");
    }
}

void Cable::checkCableType() {
    // Implémentation de la fonction checkCableType
    bool croise = true;
    uint8_t CodeSend[] = {0x01, 0x02, 0x08, 0x10, 0x04, 0x20, 0x40, 0x80};
    uint8_t CodeReci[] = {0x04, 0x20, 0x08, 0x10, 0x01, 0x02, 0x40, 0x80};

    for (uint8_t i = 0; i < sizeof(CodeReci) / sizeof(CodeReci[0]); i++) {
        Serial.println(i);
        if (!this->verifyCodes(CodeSend[i], CodeReci[i])) {
            croise = false;
            break;
        }
    }

    if (croise) {
        Serial.println("Le câble est croisé");
    } else {
        Serial.println("Le câble est droit");
    }
}


