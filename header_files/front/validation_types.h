#ifndef VALIDATION_TYPES_H
#define VALIDATION_TYPES_H

typedef struct Operands {
  char *operand1;
  char *operand2;
  int amount;
} Operands;

/*
This means the possible addressing modes
Ex: mov source can be 0,1,2,3
    des can be 1,2,3
*/
typedef enum Valid_groups {
  ONE_GROUP,   /*1*/
  TWO_GROUP,   /*1,2*/
  THREE_GROUP, /*1,2,3*/
  FOUR_GROUP,  /*0,1,2,3*/
  NONE_GROUP   /*NONE*/
} Valid_groups;

#endif