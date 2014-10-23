#include <avr/pgmspace.h>

#define MAX_ARRAY_LENGTH 32

prog_int coordinatesTable[3][39] PROGMEM = {
  1000,3300,'a',
  3300,2600,'b',
  4800,2400,'c',
  6800,1900,'d',
  8700,1800,'e',
  10300,1800,'f',
  12000,1800,'g',
  14100,1800,'h',
  15800,1800,'i',
  17300,1800,'j',
  19200,2000,'k',
  20500,2500,'l',
  22800,3000,'m',
  1300,4900,'n',
  3100,4300,'o',
  4800,3900,'p',
  6500,3600,'q',
  8600,3400,'r',
  10300,3200,'s',
  12000,3200,'t',
  13800,3200,'u',
  15700,3200,'v',
  17800,3200,'w',
  19500,4000,'x',
  21400,4200,'y',
  22800,5000,'z',
  0,0,'0',
  0,0,'1',
  0,0,'2',
  0,0,'3',
  0,0,'4',
  0,0,'5',
  0,0,'6',
  0,0,'8',
  0,0,'9',
  0,0,'+',//YES
  0,0,'-',//NO
  0,0,'!'//GOODBYE
};
  
int findSymbolInTable(char symbol){
  int tableIndex;
  
  for(tableIndex = 0; tableIndex <= 39; tableIndex++){
    if(symbol == coordinatesTable[2][tableIndex]){
      return tableIndex; //Return the table location
    }
  }
     return -1; //if we got to the point
                // we didn't find our value in the table 
}

void moveToSymbol(char character){
  int tableLocation = findSymbolInTable(character);
  
  //xAxisLocation = coordinatesTable[0][tableIndex];
  //yAxisLocation = coordinatesTable[1][tableIndex];
  
  //MoveMotors?
  
  return;
}

void ouijaDelay(void){
  //Delay to make it spoooooooky
  //Standard Delay until we can make it more spooky
   delay(200); 
}

void ouijaPrint(char* charArray){
  int i;
  for(i = 0; i <= MAX_ARRAY_LENGTH; i++){
    Serial.print(charArray[i]); //Debug the array as we move
    if(charArray[i] != 0){
      ouijaDelay();
      moveToSymbol(charArray[i]);
      ouijaDelay();            
    } //Only move if there if valid data, if not let the loop run out.
  }
  return;
}
