/*
 * File: types.h
 * Author: Profesores de PROG2
 */
#ifndef TYPES_H
#define TYPES_H
#define DEBUG() printf("%d	%s	\n", __LINE__, __FILE__)
#define MAXQUEUE 1024


typedef enum {
 ERROR = 0, OK = 1
} Status;
typedef enum {
 FALSE = 0, TRUE = 1
} Bool;

#endif /* TYPES_H */
