# ProjetTech

## Projet Technologique de vision 3D pour robots. Usage de stéréoscopie.
Version OpenCV utilisée : 2.4.13

## Tâches
Calcul de la carte de disparité
  * Détection points d'intérêt
  * Méthodes d'appariement
  * Calcul carte de disparité

La macro _NON_FREE__ se situe dans imageTools.h

Standard ISO C++11
https://isocpp.org/faq

-> carte de disparité

# Cahier des charges

## Besoins fonctionnels  (fonctionnalités)
- Identifier une pesonne
- Avancer, tourner, reculer
  - bouger
  - calculer une distance
- Suivre une personne
  - Reconnaitre un "Humain" (phase d'initialisation)
## Besoins non fonctionnels (qualités)
                                                                (partie a quantifié)
- Robot suffisament rapide pour suivre une personne (moteurs)   (8~9 km/h)
- Temps de calcul suffisament rapide pour suivre une personne 
  - Taux d'image par seconde                                    (?)
  - ROBUSTE
    - changements de luminosité + ombres                        (?)
    - changements de personnes                                  (nombre de pesonne/temps de passage)
    - changements d'environement                                (?)

# Simulation
- Vidéos pré-enregistrée.
- Simulation 3D.
  - Unity
  - PovRay
