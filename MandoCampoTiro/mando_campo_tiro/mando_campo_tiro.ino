#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

//pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2);

//bluetoth
SoftwareSerial BT(12,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
String readString;

int SPK = 3;
int btn_num_tiradores = 7;
int btn_start = 5;
int btn_reset = 6;
int btn_acierto =8 ;
int btn_fallo = 9;
int btn_atras = 10;

// variables globales
int NUM_TIRADORES = 1;
int NUM_PLATOS = 5;
int tirador = 1;
int plato = 1;
int mensaje_empezar = 0;

// estados
boolean ESTADO_SELECCION = true;
boolean ESTADO_EMPEZAR = false;
boolean ESTADO_FINALIZADO = false;

//puntuacion
int puntos[6][25] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    ,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    ,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    ,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    ,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    ,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
                    };

void setup() {
  Serial.begin(9600);
  pinMode(SPK, OUTPUT);
  pinMode(btn_num_tiradores, INPUT_PULLUP);
  pinMode(btn_start, INPUT_PULLUP);
  pinMode(btn_reset, INPUT_PULLUP);
  pinMode(btn_acierto, INPUT_PULLUP);
  pinMode(btn_fallo, INPUT_PULLUP);
  pinMode(btn_atras, INPUT_PULLUP);
  
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(0,0);
  lcd.print("  CLUB DE TIRO  ");
  lcd.setCursor(0,1);
  lcd.print("  LES PEDRERES  ");
  digitalWrite(SPK, HIGH);
  delay(300);
  digitalWrite(SPK, LOW);

  // Damos 3 segundos de delay y empezamos
  delay(2000);
  lcd.clear();
  lcd.print("Num. tiradores:");
  lcd.setCursor(0,1);
  lcd.print(NUM_TIRADORES);
}

void loop() {

  // seleccion del numero de tiradores
  if (ESTADO_SELECCION == true){
    
    if (digitalRead(btn_num_tiradores) == LOW) {
      NUM_TIRADORES += 1;

      if (NUM_TIRADORES == 7){NUM_TIRADORES=1;}
      
      lcd.setCursor(0,1);
      lcd.print(NUM_TIRADORES);
      digitalWrite(SPK, HIGH);
      delay(100);
      digitalWrite(SPK, LOW);
      delay(300);
    }

    if (digitalRead(btn_start) == LOW) {
      delay(300);
      ESTADO_SELECCION = false;
      ESTADO_EMPEZAR = true;
    }


  }

  // empezamos la partida
  if (ESTADO_EMPEZAR == true){

    digitalWrite(SPK, HIGH);
    delay(1200);
    digitalWrite(SPK, LOW);
    
    for (plato=1; plato<=NUM_PLATOS; plato++){
      for(tirador=1; tirador<=NUM_TIRADORES; tirador++){
          lcd.clear();
          lcd.print("Tirador: " + String(tirador) + "/" + String(NUM_TIRADORES));
          lcd.setCursor(0,1);
          lcd.print("Plato: " + String(plato) + "/" + String(NUM_PLATOS));
          
          Serial.print("Tirador: ");
          Serial.print(tirador);
          Serial.print(" Plato: ");
          Serial.println(plato);
          
          while(1){
            //esperamos a que se pulse ACIERTO o FALLO
            if (digitalRead(btn_acierto) == LOW || digitalRead(btn_fallo) == LOW) {
              lcd.clear();
              lcd.print("  Siguiente ... ");
              digitalWrite(SPK, HIGH);
              delay(100);
              digitalWrite(SPK, LOW);
              delay(1200);
              break;
            }
            delay(50);
          }//fin while
          
        }
    }
    ESTADO_FINALIZADO = true;
    ESTADO_EMPEZAR = false;
  }

  if (ESTADO_FINALIZADO == true){
    lcd.clear();
    lcd.print("Serie finalizada");
    lcd.setCursor(0,1);
    lcd.print(" Presiona reset ");
    
    digitalWrite(SPK, HIGH);
    delay(1200);
    digitalWrite(SPK, LOW);
   

    
    while(1){
      //esperamos a que se pulse RESET
      if (digitalRead(btn_reset) == LOW) {
        
        ESTADO_FINALIZADO = false;
        ESTADO_SELECCION = true;
        NUM_TIRADORES = 1;

        lcd.clear();
        lcd.print("Num. tiradores:");
        lcd.setCursor(0,1);
        lcd.print(NUM_TIRADORES);
        
        delay(1000);
        break;
      }
      delay(50);
   }//fin while 
 }
 
  // ...
}
