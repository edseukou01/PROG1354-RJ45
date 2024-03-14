#include <Arduino.h> // Inclure la bibliothèque Arduino pour utiliser les fonctions Arduino
#include "cable.h"   // Inclure le fichier d'en-tête de la classe Cable

// Définir les broches d'entrée et de sortie du câble
int inputPins[] = {15, 2, 4, 5, 18, 19, 21, 22};
int outputPins[] = {13, 14, 27, 26, 25, 33, 32, 12};

void setup() {
  // Initialise la communication série pour le débogage
  Serial.begin(9600);
  
  // Crée une instance de la classe Cable avec les broches définies
  Cable cable(inputPins, outputPins);

  // Vérifie si le câble est un câble droit ou croisé
  cable.checkCableType();
}

void loop() {
  // rien ici
}