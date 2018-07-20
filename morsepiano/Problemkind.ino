void setup () {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

int zustand = 1;
int unterzustand = 1;

void unterzustaende (int ein) {
    if (unterzustand == 1) {
      if (zustand == 1) {Serial.println("Uhrzeit");}
      else if (zustand == 2) {Serial.println("Schritte");}      
      else if (zustand == 3) {Serial.println("Herzfrequenz");}
      if (ein == 2) {
        unterzustand = 2;
      }
    } else if (unterzustand == 2) {
      if (zustand == 1) {Serial.println("Datum");}
      else if (zustand == 2) {Serial.println("Entfernung");}      
      else if (zustand == 3) {Serial.println("Kalorienverbrauch");}
      if (ein == 2) {
        unterzustand = 1;
      }
    } 
}

void loop () {
  long eingabe = Serial.parseInt();
  if (zustand == 1) {
    Serial.println("Zeit und Datum");
    if (eingabe == 1) {
       zustand = 2; 
       unterzustand = 1;
    }
    unterzustaende(eingabe);
    /*if (unterzustand == 1) {
      Serial.println("Uhrzeit");
      if (eingabe == 2) {
        unterzustand = 2;
      }
    } else if (unterzustand == 2) {
      Serial.println("Datum");
      if (eingabe == 2) {
        unterzustand = 1;
      }
    }*/ 
  }
  else if (zustand == 2) {
    Serial.println("Distanz");
    if (eingabe == 1) {
       zustand = 3; 
       unterzustand = 1;
    }
    unterzustaende();
    /*if (unterzustand == 1) {
      Serial.println("Schritte");
      if (eingabe == 2) {
        unterzustand = 2;
      }
    } else if (unterzustand == 2) {
      Serial.println("Entfernung");
      if (eingabe == 2) {
        unterzustand = 1;
      }
    }*/ 
  }
  else if (zustand == 3) {
    Serial.println("Koerper");
    if (eingabe == 1) {
       zustand = 1;
       unterzustand = 1;
    }
    unterzustaende();
    /*if (unterzustand == 1) {
      Serial.println("Herzfrequenz");
      if (eingabe == 2) {
        unterzustand = 2;
      }
    } else if (unterzustand == 2) {
      Serial.println("Kalorienverbrauch");
      if (eingabe == 2) {
        unterzustand = 1;
      }
    }*/ 
  }
}
