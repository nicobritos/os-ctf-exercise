#ifndef _STRING_HELPER_H
#define _STRING_HELPER_H
#include <stdint.h>

#define RESEARCH_QUESTIONS_LENGTH (MENUS_LENGTH - 1)
#define HASHES_LENGTH MENUS_LENGTH
#define MAX_ANSWER_LENGTH 400
#define MENUS_LENGTH 12

const char *getChallenge(uint8_t challenge);

const char *getResearchQuestion(uint8_t challenge);

const char *getAnswerHash(uint8_t challenge);

void hash(char *out, char *in);

#endif
