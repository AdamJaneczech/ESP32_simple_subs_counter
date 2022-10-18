#include <NetworkManager.hpp>
#include <SPIFFS.h>

const char* readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
  }
  char * fileContentBuffer = new char[64];
  int msg_len = 0;
  Serial.println("− read from file:");
  while(file.available()){
    fileContentBuffer[msg_len] = file.read();
    msg_len++;
  }
  char * fileContent = new char[msg_len];
  for(uint8_t length = 0; length < msg_len; length++){
    fileContent[length] = fileContentBuffer[length];
    //Serial.write(fileContent[length]);
  }
  Serial.println(strlen(fileContent));
  delete fileContentBuffer;
  return fileContent;
  delete fileContent;
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } 
  else {
    Serial.println("- write failed");
  }
  file.close();
}