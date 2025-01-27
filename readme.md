# Projet Rodia

Rodia est un projet permettant de faire revivre les anciennes radios via retrofit grâce à une carte Arduino. Le projet a été démarré durant le COVID et est en stand-by depuis 2021.

## Fonctionnalités

- **Écoute de la radio** : Le projet utilise une carte Arduino pour capter les stations radio.
- **Changement de station** : Un encodeur rotatif permet de naviguer entre les différentes stations radio disponibles.

À implémenter : Sauvegarde des stations préférées.

## Composants nécessaires

- Arduino Uno
- Module radio TEA5767
- Encodeur rotatif
- Haut-parleur ou casque audio
- Fils de connexion
- Alimentation pour l'Arduino

## Installation

1. **Télécharger le code** : Clonez ou téléchargez le dépôt contenant le fichier `main_rodia.ino`.
2. **Connecter les composants** : Suivez le schéma de câblage pour connecter le module radio et l'encodeur rotatif à l'Arduino.
3. **Téléverser le code** : Ouvrez le fichier `main_rodia.ino` dans l'IDE Arduino et téléversez-le sur votre carte Arduino.
4. **Tester** : Allumez l'Arduino et utilisez l'encodeur rotatif pour changer de station.

## Schéma de câblage

```plaintext
Arduino       Module Radio       Encodeur Rotatif
3.3V          VCC                VCC
GND           GND                GND
A4            SDIO                -
A5            SCLK                -
D2            -                  CLK
D3            -                  DT
D4            -                  SW
