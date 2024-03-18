#include <SD.h>

#define DO4 262
#define RE4 294
#define MI4 330
#define FA4 349
#define SOL4 392
#define LA4 440
#define SI4 493
#define DO5 524

#define RE5 588
#define MI5 660
#define FA5 699
#define SOL5 784
#define LA5 880
#define SI5 988

#define DO4_DIEZ_RE4_BEMOL 277
#define RE4_DIEZ_MI4_BEMOL 311
#define MI4_DIEZ_FA4 349
#define FA4_DIEZ_SOL4_BEMOL 370
#define SOL4_DIEZ_LA4_BEMOL 415
#define LA4_DIEZ_SI4_BEMOL 466
#define SI4_DIEZ_DO5 524

#define DO5_DIEZ_RE5_BEMOL 554
#define RE5_DIEZ_MI5_BEMOL 622
#define MI5_DIEZ_FA5 699
#define FA5_DIEZ_SOL5_BEMOL 740
#define SOL5_DIEZ_LA5_BEMOL 831
#define LA5_DIEZ_SI5_BEMOL 932
#define SI5_DIEZ_DO6 1047


#define BUZZER 10
#define CS 4
#define DURATA A1

#define DO4_BUTON A0
#define RE4_BUTON 9
#define MI4_BUTON 8
#define FA4_BUTON 7
#define SOL4_BUTON 6
#define LA4_BUTON 5
#define SI4_BUTON A4
#define DO5_BUTON 3

#define OCTAVA_BUTON 2
#define SEMITON_BUTON A5
#define CITIRE_MICROSD_BUTON A3

int g_ok = 0;
int g_okOctava = 0;
int g_okSemiton = 0;
unsigned long durata;

File g_f;

void setup()
{
  pinMode(DO4_BUTON, INPUT_PULLUP);
  digitalWrite(DO4_BUTON, HIGH);
  pinMode(RE4_BUTON, INPUT_PULLUP);
  digitalWrite(RE4_BUTON, HIGH);
  pinMode(MI4_BUTON, INPUT_PULLUP);
  digitalWrite(MI4_BUTON, HIGH);
  pinMode(FA4_BUTON, INPUT_PULLUP);
  digitalWrite(FA4_BUTON, HIGH);
  pinMode(SOL4_BUTON, INPUT_PULLUP);
  digitalWrite(SOL4_BUTON, HIGH);
  pinMode(LA4_BUTON, INPUT_PULLUP);
  digitalWrite(LA4_BUTON, HIGH);
  pinMode(SI4_BUTON, INPUT_PULLUP);
  digitalWrite(SI4_BUTON, HIGH);
  pinMode(DO5_BUTON, INPUT_PULLUP);
  digitalWrite(DO5_BUTON, HIGH);
  
  pinMode(OCTAVA_BUTON, INPUT_PULLUP);
  digitalWrite(OCTAVA_BUTON, HIGH);

  pinMode(SEMITON_BUTON, INPUT_PULLUP);
  digitalWrite(SEMITON_BUTON, HIGH);

  pinMode(CITIRE_MICROSD_BUTON, INPUT_PULLUP);
  digitalWrite(CITIRE_MICROSD_BUTON, HIGH);
  
  Serial.begin(9600);

  if (!SD.begin(CS)) 
  {
    Serial.println("Eroare initializare MicroSD");
    return;
  }

  g_f = SD.open("fisier.txt", FILE_WRITE);
  g_f.close();
}

void MYMICROSD_WriteSong(int note, unsigned long durata) {
  if (SD.exists("fisier.txt")) 
  {
    g_f = SD.open("fisier.txt", FILE_WRITE);

    if (g_f) 
    {
      g_f.println(String(note) + " " + String(durata) + " " + String(millis()));
      g_f.close();
    } 
    else 
    {
      Serial.println("Eroare scriere in fisier");
    }
  } 
  else 
  {
    Serial.println("Eroare gasire fisier");
  }
}

void loop()
{ 
  durata = analogRead(DURATA);
  
  if (digitalRead(OCTAVA_BUTON) == LOW && g_ok == 0) 
  {
    g_ok = 1;
    if (g_okOctava == 0) 
    {
      g_okOctava = 1;
    } 
    else 
    {
      g_okOctava = 0;
    }
    delay(1000);
  }
  g_ok = 0;

  if (digitalRead(SEMITON_BUTON) == LOW && g_ok == 0) 
  {
    g_ok = 1;
    if (g_okSemiton == 0) 
    {
      g_okSemiton = 1;
    } 
    else 
    {
      g_okSemiton = 0;
    }
    delay(1000);
  }
  g_ok = 0;
  
  if (digitalRead(DO4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, DO4, durata);
      MYMICROSD_WriteSong(DO4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, DO5, durata);
      MYMICROSD_WriteSong(DO5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, DO4_DIEZ_RE4_BEMOL, durata);
      MYMICROSD_WriteSong(DO4_DIEZ_RE4_BEMOL, durata);
    }
    else 
    {
      tone(BUZZER, DO5_DIEZ_RE5_BEMOL, durata);
      MYMICROSD_WriteSong(DO5_DIEZ_RE5_BEMOL, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(RE4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, RE4, durata);
      MYMICROSD_WriteSong(RE4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, RE5, durata); 
      MYMICROSD_WriteSong(RE5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, RE4_DIEZ_MI4_BEMOL, durata);
      MYMICROSD_WriteSong(RE4_DIEZ_MI4_BEMOL, durata);
    }
    else 
    {
      tone(BUZZER, RE5_DIEZ_MI5_BEMOL, durata);
      MYMICROSD_WriteSong(RE5_DIEZ_MI5_BEMOL, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(MI4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, MI4, durata);
      MYMICROSD_WriteSong(MI4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, MI5, durata);
      MYMICROSD_WriteSong(MI5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, MI4_DIEZ_FA4, durata);
      MYMICROSD_WriteSong(MI4_DIEZ_FA4, durata);
    }
    else 
    {
      tone(BUZZER, MI5_DIEZ_FA5, durata);
      MYMICROSD_WriteSong(MI5_DIEZ_FA5, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(FA4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, FA4, durata);
      MYMICROSD_WriteSong(FA4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, FA5, durata);
      MYMICROSD_WriteSong(FA5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, FA4_DIEZ_SOL4_BEMOL, durata);
      MYMICROSD_WriteSong(FA4_DIEZ_SOL4_BEMOL, durata);
    }
    else 
    {
      tone(BUZZER, FA5_DIEZ_SOL5_BEMOL, durata);
      MYMICROSD_WriteSong(FA5_DIEZ_SOL5_BEMOL, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(SOL4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, SOL4, durata);
      MYMICROSD_WriteSong(SOL4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, SOL5, durata);
      MYMICROSD_WriteSong(SOL5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, SOL4_DIEZ_LA4_BEMOL, durata);
      MYMICROSD_WriteSong(SOL4_DIEZ_LA4_BEMOL, durata);
    }
    else 
    {
      tone(BUZZER, SOL5_DIEZ_LA5_BEMOL, durata);
      MYMICROSD_WriteSong(SOL5_DIEZ_LA5_BEMOL, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(LA4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, LA4, durata);
      MYMICROSD_WriteSong(LA4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, LA5, durata);
      MYMICROSD_WriteSong(LA5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, LA4_DIEZ_SI4_BEMOL, durata);
      MYMICROSD_WriteSong(LA4_DIEZ_SI4_BEMOL, durata);
    }
    else 
    {
      tone(BUZZER, LA5_DIEZ_SI5_BEMOL, durata);
      MYMICROSD_WriteSong(LA5_DIEZ_SI5_BEMOL, durata);
    }
    delay(durata);
    g_ok = 0;
  }

  if (digitalRead(SI4_BUTON) == LOW && g_ok == 0)
  {
    g_ok = 1;
    if (durata == 0) 
    {
      durata = 10;
    }
    if (g_okOctava == 0 && g_okSemiton == 0) 
    {
      tone(BUZZER, SI4, durata);
      MYMICROSD_WriteSong(SI4, durata);
    }
    else if (g_okOctava == 1 && g_okSemiton == 0) 
    {
      tone(BUZZER, SI5, durata);
      MYMICROSD_WriteSong(SI5, durata);
    }
    else if (g_okOctava == 0 && g_okSemiton == 1) 
    {
      tone(BUZZER, SI4_DIEZ_DO5, durata);
      MYMICROSD_WriteSong(SI4_DIEZ_DO5, durata);
    }
    else 
    {
      tone(BUZZER, SI5_DIEZ_DO6, durata);
      MYMICROSD_WriteSong(SI5_DIEZ_DO6, durata);
    }
    delay(durata);
    g_ok = 0;
  }


  if (digitalRead(CITIRE_MICROSD_BUTON) == LOW && g_ok == 0) 
  {
    g_ok = 1;

    int notaParam, notaParam2;
    unsigned long durataParam, durataParam2;
    int delayParam, delayParam2;    

    g_f = SD.open("fisier.txt");
    if (g_f) 
    {
      String notaStr = "";
      String durataStr = "";
      String delayStr = "";
      char ch;
      int g_okLinie = 0;
      while (g_f.available()) 
      {
        ch = g_f.read();
        if (ch == '\n') 
        {
          notaParam = notaStr.toInt();
          durataParam = atol(durataStr.c_str());
          delayParam = delayStr.toInt();
          tone(BUZZER, notaParam, durataParam);
          notaStr = "";
          durataStr = "";
          delayStr = "";
          g_okLinie = 0;
          break;
        } 
        else if (ch == ' ' && g_okLinie == 0) 
        {
          g_okLinie = 1;
        } 
        else if (ch == ' ' && g_okLinie == 1) 
        {
          g_okLinie = 2;
        } 
        else if (g_okLinie == 0) 
        {
          notaStr += ch;
        } 
        else if (g_okLinie == 1) 
        {
          durataStr += ch;
        } 
        else 
        {
          delayStr += ch;
        }
      }

      while (g_f.available()) 
      {
        ch = g_f.read();
        if (ch == '\n') 
        {
          notaParam2 = notaStr.toInt();
          durataParam2 = atol(durataStr.c_str());
          delayParam2 = delayStr.toInt();
          notaStr = "";
          durataStr = "";
          delayStr = "";
          g_okLinie = 0;

          if (delayParam2 - delayParam < 0) 
          {
            delay(durataParam2);
          } 
          else 
          {
            delay(delayParam2 - delayParam);
          }
          
          tone(BUZZER, notaParam2, durataParam2);
      
          notaParam = notaParam2;
          durataParam = durataParam2;
          delayParam = delayParam2;
          
        } 
        else if (ch == ' ' && g_okLinie == 0) 
        {
          g_okLinie = 1;
        } 
        else if (ch == ' ' && g_okLinie == 1) 
        {
          g_okLinie = 2;
        } 
        else if (g_okLinie == 0) 
        {
          notaStr += ch;
        } 
        else if (g_okLinie == 1) 
        {
          durataStr += ch;
        } 
        else 
        {
          delayStr += ch;
        }
      }
      g_f.close();
      SD.remove("fisier.txt");
      g_f = SD.open("fisier.txt", FILE_WRITE);
      g_f.close();
    } 
    else 
    {
      Serial.println("Eroare citire MicroSD");
    }

    g_ok = 0;
  }
}
