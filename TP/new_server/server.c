#include "challengesHandler.h"
#include "clientConnection.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 23423
#define HASH_BUFFER 40
#define STRING_BUFFER 1024

int main() {
  char stringBuffer[STRING_BUFFER];
  uint8_t challengeIndex = 0;
  int clientFD;

  clientFD = serve(PORT);
  while (1) {
    system("clear");
    if(challengeIndex == 11){
      t_challengeADT challenge = getChallenge(challengeIndex);
      printf("%s\n", getChallengeDescription(challenge));
      exit(0);
    }
    printf("------------- DESAFIO -------------\n");
    t_challengeADT challenge = getChallenge(challengeIndex);
    printf("%s\n", getChallengeDescription(challenge));
    getChallengeFunction(challenge);
    puts("\n----- PREGUNTA PARA INVESTIGAR -----");
    printf("%s\n",getChallengeResearchQuestion(challenge));
    receive(clientFD, stringBuffer, STRING_BUFFER);  
    int c;
    if((c = isValidAnswer(challenge, stringBuffer)) == 0){
      puts("Respuesta correcta");
      challengeIndex++;
    }
    else {
      printf("Respuesta incorrecta: %s",stringBuffer);
    }
    sleep(1);
  }
  return 0;
}

