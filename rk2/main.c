#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 255
#define MAX_SURNAME 255
#define MAX_GROUP_NAME 255
#define MAX_SUB_NAME 255
#define N_GRADES 5
#define BUF_LEN 1024
#define MAX_STUDENTS 10

typedef struct 
{
	char name[MAX_NAME];
	char surname[MAX_SURNAME];
	char group[MAX_GROUP_NAME];
	char sub_names[N_GRADES][MAX_SUB_NAME];
	int grades[N_GRADES];
} student_t;

void read_name(char *str, student_t *s)
{
	int tag_len = sizeof("<name>") / sizeof(char) - 1;
	char *name_start = strstr(str, "<name>");
	char *name_end = strstr(name_start, "</name>");
	memcpy(s->name, name_start+tag_len, name_end-name_start - tag_len);
}

void read_surname(char *str, student_t *s)
{
	int tag_len = sizeof("<surname>") / sizeof(char) - 1;
	char *name_start = strstr(str, "<surname>");
	char *name_end = strstr(name_start, "</surname>");
	memcpy(s->surname, name_start+tag_len, name_end-name_start - tag_len);
}

void read_group(char *str, student_t *s)
{
	int tag_len = sizeof("group=\"") / sizeof(char) - 1;
	char *tag_start = strstr(str, "group=\"");
	char *tag_end = strstr(tag_start+tag_len+1, "\"");
	memcpy(s->group, tag_start+tag_len, tag_end-tag_start - tag_len);
}

void read_one_mark(char *str, int *mark)
{
	char mark_buf[8];
	int tag_len = sizeof(">") / sizeof(char) - 1;
	char *tag_start = strstr(str, ">");
	char *tag_end = strstr(tag_start, "</mark>");
	memcpy(mark_buf, tag_start+tag_len, tag_end-tag_start - tag_len);
	*mark = atoi(mark_buf);
}
void read_subject_name(char *str, char *subj)
{
	int tag_len = sizeof("subject=\"") / sizeof(char) - 1;
	char *tag_start = strstr(str, "subject=\"");
	char *tag_end = strstr(tag_start+tag_len+1, "\"");
	memcpy(subj, tag_start+tag_len, tag_end-tag_start - tag_len);
}

void read_grades(char *str, FILE *in, student_t *s)
{
	int cur_grade = 0;
	while (!strstr(str, "</marks>"))
	{
		if (strstr(str, "<mark "))
		{
			read_one_mark(str, &s->grades[cur_grade]);
			read_subject_name(str, s->sub_names[cur_grade]);
			cur_grade++;
		}
		fgets(str, BUF_LEN, in);
	}
}

void serialize_student(student_t *s, FILE *out)
{

	fprintf(out, "%s\n", s->group);
	fprintf(out, "%s\n", s->name);
	fprintf(out, "%s\n", s->surname);
	for (int i = 0; i < N_GRADES; i++)
		fprintf(out, "%s %d\n", s->sub_names[i], s->grades[i]);
	fprintf(out, "\n");
}

student_t read_student(FILE *in, char *buf, int *flag)
{
	student_t res = { 0 };
	int ended = 0;
	int read_something = 0;
	while (!ended)
	{
		if (strstr(buf, "<name>"))
		{
			read_name(buf, &res);
			read_something = 1;
		}
		if (strstr(buf, "<surname>"))
		{
			read_surname(buf, &res);
			read_something = 1;
		}
		if (strstr(buf, "<student "))
		{
			read_group(buf, &res);
			read_something = 1;
		}
		if (strstr(buf, "<marks>"))
		{
			read_grades(buf, in, &res);
			read_something = 1;
		}
		if (strstr(buf, "/student"))
			ended = 1;
		fgets(buf, BUF_LEN, in);
	}	
	if (read_something)
		*flag = 1;
	return res;
}

int read_students(FILE *in, student_t *out_buf)
{
	char buf[BUF_LEN];
	int students_started = 0;
	int ended = 0;
	int flag = 0;
	int n = 0;
	student_t s = { 0 };
	fgets(buf, BUF_LEN, in);
	while (!ended)
	{
		flag = 0;
		if (strstr(buf, "<students>") != NULL)
		{
			students_started = 1;
		}
		if (strstr(buf, "</students>"))
			ended = 1;
		if (students_started && !ended)
		{
			s = read_student(in, buf, &flag);
			if (flag)
				out_buf[n++] = s;
		}
	}
	return n;
}

int main(int argc, char **argv)
{	
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");
	
	student_t students[MAX_STUDENTS];
	int n = read_students(in, students);
	printf("%d\n", n);
	for (int i = 0; i < n; i++)
		serialize_student(&students[i], out);
	
	fclose(in);
	fclose(out);
}


