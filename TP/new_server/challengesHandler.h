#ifndef _CHALLENGES_HANDLER_H
#define _CHALLENGES_HANDLER_H

#include <stdint.h>

#define CHALLENGES_LENGTH 12
#define RESEARCH_QUESTIONS_LENGTH (CHALLENGES_LENGTH - 1)
#define HASHES_LENGTH CHALLENGES_LENGTH
#define MAX_ANSWER_LENGTH 400

typedef struct t_challengeCDT *t_challengeADT;

const t_challengeADT getChallenge(uint8_t challenge);

const char *getChallengeDescription(t_challengeADT challenge);

const char *getChallengeResearchQuestion(t_challengeADT challenge);

void getChallengeFunction(t_challengeADT challenge);

int isValidAnswer(t_challengeADT challenge, const char *answer);

#endif
