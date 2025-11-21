#include <Arduino.h>
#include <Servo.h>

Servo MonServo;
int PosServo;          // Variable de position du servo, de 0 à 180°
int Gauche;            // Variables de valeur des photoresistances
int Droite;
int entreePhotoGauche = A1; // Photorésistances sur A0 et A1
int entreePhotoDroite = A0;
int ponderation = 12;

void setup()
{
  Serial.begin(9600);   // Moniteur série
  MonServo.attach(11);  // Servo sur pin 11
}

void loop()
{
  Gauche = analogRead(entreePhotoGauche);
  Droite = analogRead(entreePhotoDroite);

  // Si la luminosité générale n'est pas suffisante on le replace à sa position de départ.
  // La nuit il sera en position pour le matin
  if ((Droite + Gauche) < 600)
  {
    if (PosServo > 1)
      PosServo = 1;
    MonServo.write(PosServo);
  }
  else
  {
    // Si la valeur de droite est plus haute on tourne vers la droite
    if (Droite > Gauche + ponderation)
    {
      if (PosServo < 179)
        PosServo++;
      MonServo.write(PosServo);
    }
    // Si c'est la valeur de gauche on tourne vers la gauche
    else if (Gauche > Droite + ponderation)
    {
      if (PosServo > 1)
        PosServo--;
      MonServo.write(PosServo);
    }
  }

  // Affichage sur Moniteur Série
  Serial.print("Gauche > ");
  Serial.print(Droite);
  Serial.print(" | ");
  Serial.print(Gauche);
  Serial.println(" < Droite");

  // On attend 150 ms avant la prochaine boucle
  delay(150);
}
