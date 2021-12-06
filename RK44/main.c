#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define BUF_SIZE 1024

enum err_e
{
	ok,
	input_err,
	file_err,
	key_err,
};

struct student
{
	char lastname[255];
	int age;
	struct list grades;
};

struct student student_read(FILE *f, int *ec)
{
	struct student self = { 0 };
	
	if (fscanf(f, "%255s %d", self.lastname, &self.age) != 2)
		*ec = input_err;

	self.grades = list_new(sizeof(int));
	
	int grade = 0;
	while (fscanf(f, "%d", &grade) == 1)
	{
		list_add(&self.grades, &grade);
		if (grade < 0)
			*ec = input_err;
	}
	return self;
}

void student_print(struct student *self)
{
	printf("%s %d", self->lastname, self->age);
	struct list grades = self->grades;
	int grade = 0;
	do
	{
		list_head(&grades, &grade);
		printf("%d", grade);
	}
	while (list_next(&grades)); // iterates as well
	printf("\n");
}

void student_destructor(void *ptr)
{
	struct student *self = (struct student *)ptr;
	list_delete(&(self->grades));
}

int all_grades_greater_eq(struct list grades, int target)
{
	int grade = 0;
	int flag = 1;
	do
	{
		list_head(&grades, &grade);
		if (grade < target)
			flag = 0;
	} while (flag && list_next(&grades));
	return flag;
}

int main(int argc, char **argv)
{
	FILE *f = fopen(argv[2], "r");
	int ec = ok;
	if (argc != 2 && argc != 3)
		ec = key_err;
	if (f == NULL)
	{
		printf("File not found \n");
		ec = file_err;
		return ec;
	}

	// reading
	struct list students = list_new(sizeof(struct student));

	students.item_destructor = student_destructor;

	while (!feof(f) && !ec)
	{
		struct student to_add = student_read(f, &ec);
		list_add(&students, &to_add);
	}

	if (!ec)
	{
		// printing
		struct list print_iterator = students;
		struct student s;
		do
		{
			list_head(&print_iterator, &s);
			student_print(&s);
		}	
		while (list_next(&print_iterator));
	}

	if (!ec)
	{
		// now delete students
		list_delete(&students);
		// note: item destuctor is called for list
	}
	fclose(f);

	if (ec == input_err)
		printf("file not valid\n");
	if (ec == key_err)
		printf("key err\n");
	return 0;
}
