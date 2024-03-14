#ifndef CABLE_H // Directive de préprocesseur pour éviter les inclusions multiples
#define CABLE_H

#include <Arduino.h> // Inclure la bibliothèque Arduino pour utiliser les fonctions Arduino

class Cable {
private:
    int inputPins[8];   // Broches d'entrée du câble
    int outputPins[8];  // Broches de sortie du câble
    uint8_t dataS;      // Données à envoyer
    uint8_t dataR;      // Données reçues

public:
    // Constructeur par défaut
    Cable();

    // Constructeur surchargé prenant les broches en entrée et en sortie
    Cable(int inputPins[], int outputPins[]);

    // Envoi des données sur les broches de sortie
    void envoi(uint8_t data);

    // Réception des données depuis les broches d'entrée
    void reception();

    // Vérifie si les données envoyées correspondent à celles reçues
    bool verifyCodes(uint8_t send, uint8_t receive);

    // Affiche les broches d'entrée
    void printInputPins();

    // Affiche les broches de sortie
    void printOutputPins();

    // Vérifie si le câble est fonctionnel
    void checkCable();