#include <Gamer.h>
Gamer gamer;


int ballX,ballY; //ball location
int vectorX,vectorY; // direction for ball
unsigned long ballMoveTimer = 0;
int ballSpeed;//ms between ball moves

//paddle varibles
int paddleLocation;
int paddleSize = 3;
unsigned long paddleTimer = 0;

//level varibles
int level,bounces,bounceNumber;

boolean started = false;

void setup(){
  gamer.begin();
  
  reset();
  startAnimation();
  
}



void loop(){
  if( (millis() - paddleTimer) > 70){
    if(gamer.isHeld(LEFT) && paddleLocation > 0) paddleLocation--; 
    if(gamer.isHeld(RIGHT) && paddleLocation < (8-paddleSize)) paddleLocation++;
    drawPaddle(paddleLocation,paddleSize);
    paddleTimer = millis();
  }
  
  if( (millis() - ballMoveTimer) > ballSpeed){
    wallBounce();
    drawBall();
    ballMoveTimer = millis();
  }

}


void wallBounce(){
 
  if(ballX == 7) vectorX = -1; //right wall
  if(ballX == 0) vectorX = 1; //left wall
  if(ballY == 0) vectorY = 1;//top
  
  if(ballY == 6){
    if(ballX >= paddleLocation &&  ballX < (paddleLocation + paddleSize) ||//hit paddle
       ballX == (paddleLocation - 1) && vectorX == 1 ||
       ballX == (paddleLocation + paddleSize) && vectorX == -1){
        vectorY = -1;
        bounces++;
      
      if(bounces == bounceNumber){
        level++;
         switch (level) {
            case 1:
              ballSpeed = 260;
            break;
            case 2:
              ballSpeed = 220;
      
            break;
            case 3:
              paddleSize = 3;
              bounceNumber = 10;
            break;
            case 4: 
              ballSpeed = 180;
            
            break;
            case 5:
              ballSpeed = 140;
            break;
            case 6:
              paddleSize = 2;
              bounceNumber = 15;
            break;
            case 7:
              ballSpeed = 100;  
                
                
            break;
            case 8:           
              ballSpeed = 60;
             
            break;
     
            case 9:
              paddleSize = 1;
              bounceNumber = 20;             
            break;
           case 10:
              youWin();
             reset();
            break; 
              
         }
        //Level up
        levelUp();
        
        bounces = 0;
      
       }
      
    }
    else {
      gameOver();
      reset();}
  }
  
  
}



void drawBall() {
  
  //clear ball area
  for(int x = 0; x < 8;x++ ){
    for(int y = 0; y < 7;y++ ){
       gamer.display[x][y] = 0;
    }
  }

  
  //move ball
  ballX = ballX + vectorX;
  ballY = ballY + vectorY;
  
  //draw Ball
  gamer.display[ballX][ballY] = 1;
  gamer.updateDisplay();
}



void drawPaddle(int paddleLocation, int paddleSize){
  for(int x = 0; x < 8; x++){
    if(x >= paddleLocation &&  x < (paddleLocation + paddleSize)){
      gamer.display[x][7] = 1;
    }
    else gamer.display[x][7] = 0;
  }
  
  gamer.updateDisplay();
  
}


void reset(){

 for(int y = 0; y < 8; y++){
  for(int x = 0; x < 8; x++){
     gamer.display[x][y] = 1;
    }
    
    gamer.updateDisplay();
    delay(50);
 }
 
  ballX = random(1, 6);
  ballY = random(1, 2);
  
  vectorX = 1;
  
  if(random(0, 1) == 0) vectorY = -1;
  else vectorY = 1;
  
  ballSpeed = 300;
  paddleSize = 4;
  bounceNumber = 5;
}

void gameOver(){
  //clear ball area
  for(int x = 0; x < 8;x++ ){
    for(int y = 0; y < 7;y++ ){
       gamer.display[x][y] = 0;
    }
  }
  
  ballX = ballX + vectorX;
  ballY = ballY + vectorY;
  
  for(int i = 0; i < 8; i++){
    //draw Ball
    gamer.display[ballX][ballY] = 1;
    gamer.updateDisplay();
    delay(100);
    gamer.display[ballX][ballY] = 0;
    gamer.updateDisplay();
    delay(100);
  }
  
  youLose();
  
}

