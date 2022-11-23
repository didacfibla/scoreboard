#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

//pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2);

//bluetoth
SoftwareSerial BT(12,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
String readString;

int SPK = 4;

int btn_num_tiradores = 7;
int btn_start = 8; //parece que no va
int btn_reset = 6;
int btn_acierto = 9;
int btn_fallo = 5;
int btn_atras = 10;


void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  
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
  lcd.print("Hola Mundo");
  digitalWrite(SPK, HIGH);
  delay(300);
  digitalWrite(SPK, LOW);
}

void loop() {

  if (digitalRead(btn_atras) == LOW){
      Serial.println("Se ha pulsado el boton ATRAS");
      lcd.clear();
      lcd.print("Se ha pulsado el boton ATRAS");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }
  
  if (digitalRead(btn_num_tiradores) == LOW){
      Serial.println("Se ha pulsado el boton NUM_TIRADORES");
      lcd.clear();
      lcd.print("Se ha pulsado el boton NUM_TIRADORES");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }

  if (digitalRead(btn_start) == LOW){
      Serial.println("Se ha pulsado el boton START");
      lcd.clear();
      lcd.print("Se ha pulsado el boton START");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }

  if (digitalRead(btn_reset) == LOW){
      Serial.println("Se ha pulsado el boton RESET");
      lcd.clear();
      lcd.print("Se ha pulsado el boton RESET");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }

  if (digitalRead(btn_acierto) == LOW){
      Serial.println("Se ha pulsado el boton ACIERTO");
      lcd.clear();
      lcd.print("Se ha pulsado el boton ACIERTO");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }

  if (digitalRead(btn_fallo) == LOW){
      Serial.println("Se ha pulsado el boton FALLO");
      lcd.clear();
      lcd.print("Se ha pulsado el boton FALLO");
      digitalWrite(SPK, HIGH);
      delay(300);
      digitalWrite(SPK, LOW);
  }

  while (BT.available()) {
    delay(3);  
      char c = BT.read();
    readString += c; 
  }
  
  if (readString.length() >0) {
     lcd.clear();
      int i = 0;
     for(i=0; i<readString.length()-2;i+=1){
      lcd.print(readString[i]);
      Serial.print(readString[i]);
      }
     readString = "";
  }

}
