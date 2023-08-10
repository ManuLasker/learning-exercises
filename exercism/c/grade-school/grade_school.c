#include "grade_school.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_roster(roster_t* roster){
    roster->count = 0;
    student_t* students = (student_t*)
        malloc(sizeof(student_t) * MAX_STUDENTS);
    // reinitilize the memory
    memcpy(roster->students, students, sizeof(student_t)*MAX_STUDENTS);
    free(students);
}

void debug_students(roster_t* roster){
    printf("count: %zu\n", roster->count);
    for (size_t i = 0; i < roster->count; i++){
        printf("name: %s, grade: %d\n", roster->students[i].name,
                roster->students[i].grade);
    }
}

int add_student(roster_t* roster, char *name, uint8_t grade){
    if (roster->count == MAX_STUDENTS)
        return 0;

    student_t student = {.grade =  grade, .name =  ""};

    strcpy(student.name, name);

    if (roster->count == 0)
        roster->students[0] = student;

    for (size_t i = 0; i < roster->count; i++){
        if (strcmp(roster->students[i].name, name) == 0){
            return 0;
        }

        student_t temp = roster->students[i];

        if (student.grade < temp.grade){
            roster->students[i] = student;
            student = temp;
        }else if (student.grade == temp.grade){
            // compare strings to sort by Name
            if (strcmp(student.name, temp.name) < 0){
                roster->students[i] = student;
                student = temp;
            }
        }

        // When sorted I need to put back the last element into the list
        // this is saved in student as a temp
        if (i == roster->count - 1){
            roster->students[i+1] = student;
        }
    }

    roster->count += 1;
    return 1;
}

roster_t get_grade(roster_t* roster, uint8_t expected_grade){
    roster_t roster_result;
    init_roster(&roster_result);

    if (roster->count == 0)
        return roster_result;

    for (size_t i=0; i<roster->count; i++) {
        student_t c_student = roster->students[i];

        if (c_student.grade == expected_grade){
            add_student(&roster_result, c_student.name, c_student.grade);
        }
    }
    return roster_result;
}
