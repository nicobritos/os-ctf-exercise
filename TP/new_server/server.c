#include "challengesHandler.h"
#include "clientConnection.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define PORT 23423
#define HASH_BUFFER 40
#define STRING_BUFFER 1024

int main() {
  char stringBuffer[STRING_BUFFER];
  char hashBuffer[HASH_BUFFER];
  int hashCompareResult;
  uint8_t challengeIndex = 0;
  int clientFD;

  clientFD = serve(PORT);
  while (1) {
    system("clear");
    // // exitInMenu11(challenge, stringBuffer);
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
      printf("\nRespuesta incorrecta: %s",stringBuffer);
    }
    sleep(1);
  }
  return 0;
}

