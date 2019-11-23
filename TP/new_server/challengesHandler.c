#include "challengesHandler.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1

typedef unsigned long    undefined8;
typedef unsigned int    undefined4;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    byte;





#define HASH_COMMAND_LENGTH 80

typedef struct t_challengeCDT {
    const char *description;
    const char *research;
    const char *answer;
    void (*function)(void);
} t_challengeCDT;

void hash(char *out, const char *in);
void ebadf();
void mixed_fds();
void printPortrait();
void quine();
void gdbme();
int easter_egg();

static t_challengeCDT challenges[CHALLENGES_LENGTH] = {
    {
        "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
            "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n"
            "Además tendrán que investigar otras preguntas para responder durante la defensa.\n"
            "El desafío final consiste en crear un servidor que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta"
            "Además deberán implementar el cliente para comunicarse con este servidor.\n\n"
            "Deberán estar atentos a los desafíos ocultos.\n\n"
            "Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con \"entendido\\n\"",
        "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
        "eb112daf85b0e0fd7c662a23e53cd7b3",
        NULL
    },
    {
        "# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *",
        "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
        "5758b4bf840c5ace20d99eb532c71df7",
        NULL
    },
    {
        "https://vocaroo.com/i/s1lD9m8lGzei",
        "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
        "029f8eb213944c40683dbf63b10c529b",
        NULL
    },
    {
        "EBADF... abrilo y verás o redirijilo ;)",
        "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
        "4b686aae68f1cc95eea31b87c7939cb1",
        ebadf
    },
    {
        "respuesta = strings[217]",
        "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
        "4df7184afd235967b93670386783701d",
        NULL
    },
    {
        ".data .bss .comment ? .shstrtab .symtab .strtab",
        "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
        "1a48227f647065a628394511d8a3d76a",
        NULL
    },
    {
        "mixed fds",
        "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
        "495213ba05e806e698e596b9d826ae99",
        mixed_fds
    },
    {
        "Portrait",
        "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
        "ec5e1ae6629ce3c9cbc869e4fdec7814",
        printPortrait
    },
    {
        "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo",
        "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?",
        "97948f7a5ff8b7ff45ed8a9388f1b396",
        NULL
    },
    {
        "quine",
        "¿Cuáles son las características del protocolo SCTP?",
        "062bca7bb736a217a853f7a6ad9821aa",
        quine
    },
    {
        "b gdbme y encontrá el valor mágico",
        "¿Qué es un RFC?",
        "469ce529bbe8586e554e11a297a83241",
        gdbme
    },
    {
        "Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto",
        NULL,
        NULL,
        NULL
    }
};


const t_challengeADT getChallenge(uint8_t challenge) {
    if (challenge > CHALLENGES_LENGTH) return NULL;
    return challenges + challenge;
}

const char *getChallengeDescription(t_challengeADT challenge) {
    if (challenge == NULL) return NULL;
    return challenge->description;
}

const char *getChallengeResearchQuestion(t_challengeADT challenge) {
    if (challenge == NULL) return NULL;
    return challenge->research;
}

void getChallengeFunction(t_challengeADT challenge){
    if(challenge->function != NULL){
        (challenge->function)();
    }
}

uint8_t isValidAnswer(t_challengeADT challenge, const char *answer) {
    if (challenge == NULL) return 0;
    char buffer[HASH_COMMAND_LENGTH];
    hash(buffer, answer);
    return strcmp(buffer, challenge->answer);
}

void hash(char *out, const char *in) {
  char buffer [MAX_ANSWER_LENGTH + HASH_COMMAND_LENGTH];
  FILE *popenFile;
  
  snprintf(buffer, HASH_COMMAND_LENGTH, "echo -n \"%s\" | md5sum | cut -d \' \' -f 1", in);
  popenFile = popen(buffer, "r");
  if (popenFile == NULL) {
    perror("popen error on hash");
    exit(1);
  }

  fgets(out, HASH_COMMAND_LENGTH, popenFile);
  out[32] = 0;
  return;
}

void ebadf(){
  char *answer;
  
  answer = "la respuesta a este acertijo es pistolero";
  write(5,answer,strlen(answer));
  return;
}

void printPortrait(void)

{
  printf(
        "                                  _______                                                                 _,,ad8888888888bba,_                                                        ,ad88888I888888888888888ba,                                                  ,88888888I88888888888888888888a,                                             ,d888888888I8888888888888888888888b,                                          d88888PP\"\"\"\" \"\"YY88888888888888888888b,                                      ,d88\"'__,,--------,,,,.;ZZZY8888888888888,                                    ,8IIl'\"                ;;l\"ZZZIII8888888888,                                  ,I88l;'                  ;lZZZZZ888III8888888,                               ,II88Zl;.                  ;llZZZZZ888888I888888,                             ,II888Zl;.                .;;;;;lllZZZ888888I8888b                            ,II8888Z;;                 `;;;;;''llZZ8888888I8888,                           II88888Z;'                        .;lZZZ8888888I888b                           II88888Z; _,aaa,      .,aaaaa,__.l;llZZZ88888888I888                           II88888IZZZZZZZZZ,  .ZZZZZZZZZZZZZZ;llZZ88888888I888,                          II88888IZZ<'(@@>Z|  |ZZZ<'(@@>ZZZZ;;llZZ888888888I88I                         ,II88888;   `\"\"\" ;|  |ZZ; `\"\"\"     ;;llZ8888888888I888                         II888888l            `;;          .;llZZ8888888888I888,                       ,II888888Z;           ;;;        .;;llZZZ8888888888I888I                       III888888Zl;    ..,   `;;       ,;;lllZZZ88888888888I888                       II88888888Z;;...;(_    _)      ,;;;llZZZZ88888888888I888,                      II88888888Zl;;;;;' `--'Z;.   .,;;;;llZZZZ88888888888I888b                      ]I888888888Z;;;;'   \";llllll;..;;;lllZZZZ88888888888I8888,                     II888888888Zl.;;\"Y88bd888P\";;,..;lllZZZZZ88888888888I8888I                     II8888888888Zl;.; `\"PPP\";;;,..;lllZZZZZZZ88888888888I88888                     II888888888888Zl;;. `;;;l;;;;lllZZZZZZZZW88888888888I88888                     `II8888888888888Zl;.    ,;;lllZZZZZZZZWMZ88888888888I88888                      II8888888888888888ZbaalllZZZZZZZZZWWMZZZ8888888888I888888,                     `II88888888888888888b\"WWZZZZZWWWMMZZZZZZI888888888I888888b                      `II88888888888888888;ZZMMMMMMZZZZZZZZllI888888888I8888888                       `II8888888888888888 `;lZZZZZZZZZZZlllll888888888I8888888,                       II8888888888888888, `;lllZZZZllllll;;.Y88888888I8888888b,                     ,II8888888888888888b   .;;lllllll;;;.;..88888888I88888888b,                    II888888888888888PZI;.  .`;;;.;;;..; ...88888888I8888888888,                   II888888888888PZ;;';;.   ;. .;.  .;. .. Y8888888I88888888888b,                ,II888888888PZ;;'                        `8888888I8888888888888b,              II888888888'                              888888I8888888888888888b            ,II888888888                              ,888888I88888888888888888           ,d88888888888                              d888888I8888888888ZZZZZZZ        ,ad888888888888I                              8888888I8888ZZZZZZZZZZZZZ      ,d888888888888888'                              888888IZZZZZZZZZZZZZZZZZZ    ,d888888888888P'8P'                               Y888ZZZZZZZZZZZZZZZZZZZZZ   ,8888888888888,  \"                                 ,ZZZZZZZZZZZZZZZZZZZZZZZZ  d888888888888888,                                ,ZZZZZZZZZZZZZZZZZZZZZZZZZZZ  888888888888888888a,      _                    ,ZZZZZZZZZZZZZZZZZZZZ888888888  888888888888888888888ba,_d'                  ,ZZZZZZZZZZZZZZZZZ88888888888888  8888888888888888888888888888bbbaaa,,,______,ZZZZZZZZZZZZZZZ888888888888888888  88888888888888888888888888888888888888888ZZZZZZZZZZZZZZZ888888888888888888888  8888888888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888  888888888888888888888888888888888888888ZZZZZZZZZZZZZZ888888888888888888888888  8888888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888  88888888888888888888888888888888888ZZZZZZZZZZZZZZ8888888888888888888888888888  8888888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888888  88888888888888888888888888888888ZZZZZZZZZZZZZZ8888888888888888888888888888888  8888888888888888888888888888888ZZZZZZZZZZZZZZ88888888888888888888888888888888"
        );
  return;
}

void gdbme(void){
    if (TRUE) {
        puts("try again");
    }
    else {
        char *answer = "gdb es la hostia";
        printf("%s",answer);
    }
    return;
}

void quine(void){
    int gccReturnValue;
    gccReturnValue = system("gcc quine.c -o quine");
    if (gccReturnValue == 0) {
        char * entryMessage = "¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde:\n";
        printf("%s",entryMessage);
        uint diff = system("./quine | diff - quine.c");
        if (diff == 0) {
            char * answer = "¡Genial! la respuesta a este acertijo es abalastro\n";
            printf("%s",answer);
        }
        else {
            printf("diff returned: %lu\n",(ulong)diff);
        }
    }
}

void mixed_fds(void)
{
  int randChar;
  int index;

  char *answer = "la respuesta a este acertijo es indeterminado";
  srand(time(NULL));
  
  index = 0;
  setvbuf(stdout,NULL,2,0);
  setvbuf(stderr,NULL,2,0);
  while (answer[index] != 0) {
    int rands = rand();
    if ((rands % 100) < 76) {
      randChar = rand();
      fprintf(stderr, "%c", (int)(char)((char)randChar + (char)(randChar / 0x1a) * -0x1a + 'a'));
    }
    else {
      fprintf(stdout, "%c", answer[index]);
      index++;
    }
  }
  return;
}

int easter_egg(){
    return 0;
}
