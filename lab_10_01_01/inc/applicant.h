//
// Created by dev on 11/16/21.
//

#ifndef LAB_10_01_01_APPLICANT_H
#define LAB_10_01_01_APPLICANT_H
#define MAXNAME 60

typedef struct
{
	char name[60];
	float gpa;
} applicant_t;

applicant_t applicant_new(char *name, float gpa);

applicant_t applicant_read(int *ec);

void applicant_print(applicant_t *self);

#endif //LAB_10_01_01_APPLICANT_H
