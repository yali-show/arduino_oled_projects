#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 

// constants asigment

#define OLED_RESET 13 
#define MAX_COULDOWN 2
#define MIN_COULDOWN 10
#define DINO_SIZE 10
#define DINO_ANIMATION 3
#define JUMP_PIN 2
#define DOWN_PIN 13
Adafruit_SSD1306 display(OLED_RESET);

typedef struct {
  bool in_jump=false;
  bool falling=false;
  bool dead=false;
  int score=0;
  int speed=4;
  int size=8;
  int pos[2] = {0, 32-size};
}Dino;

typedef struct {
  int speed;
  int pos[2];
}enemy;

typedef enemy Enemies[2]; // only 2 enemy object possile on the display


// variables asigment

const unsigned char running [] PROGMEM = {
	0x3c, 0x42, 0x95, 0x95, 0x95, 0x81, 0x42, 0x3c
};

const unsigned char jumping [] PROGMEM = {
	0x3c, 0x42, 0x95, 0x81, 0x81, 0x81, 0x42, 0x3c
};

const unsigned char falling [] PROGMEM = {
	0x3c, 0x42, 0x81, 0x81, 0x95, 0x81, 0x42, 0x3c
};


const unsigned char* dino_animation[DINO_ANIMATION] = {
	running,
	jumping,
	falling
};


Dino hero;

bool jump_state=false, down_state=false;

void setup() {
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 

  pinMode(JUMP_PIN, INPUT); 
  pinMode(DOWN_PIN, INPUT); 
  

}


void loop() {

  game(hero);
  buttons(hero);
  
}

// void score_update(){


// }

void buttons(Dino &dino){


   if (digitalRead(JUMP_PIN)){

    dino.in_jump = true;

  }

  if (digitalRead(DOWN_PIN)){

    if (dino.in_jump){

    dino.falling = true;

    }

  }
  display.display(); 
  delay(10);


}

void dino_change(Dino &dino){
 
  if (dino.in_jump){

      display.fillRect(dino.pos[0], dino.pos[1], dino.size, dino.size, BLACK);

      if (dino.falling){

        dino.pos[1] += dino.speed;
        display.drawBitmap(dino.pos[0], dino.pos[1], dino_animation[2], dino.size, dino.size, WHITE);

        if (dino.pos[1] >= 32-dino.size){
          
          dino.falling = false;
          dino.in_jump = false;

        }

      }else{
        
        dino.pos[1] -= dino.speed;
        display.drawBitmap(dino.pos[0], dino.pos[1], dino_animation[1], dino.size, dino.size, WHITE);

        if (dino.pos[1] <= 0){
          
          dino.falling = true;

        }

      }

  }else{

    display.drawBitmap(dino.pos[0], dino.pos[1], dino_animation[0], dino.size, dino.size, WHITE);

  }
  
  
    

}


void game(Dino &dino) { 
  // display.clearDisplay(); 
  // display.setTextSize(1); 
  // display.setTextColor(WHITE);
  // display.setCursor(35,10); 
  // display.println("TU");
  // display.writePixel(35, 10, BLACK);
  // display.drawRoundRect(dino.pos[0], dino.pos[1], dino.size, dino.size, dino.size, WHITE);
  // display.drawCircle(dino.pos[0]+dino.size/2, dino.pos[1]+dino.size/2, dino.size/2, WHITE);
  
  // display.setCursor(20,20); 
  dino_change(dino);
  
  display.display(); 
  delay(1);
}
