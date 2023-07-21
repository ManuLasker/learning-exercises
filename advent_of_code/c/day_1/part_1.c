#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

const char filename[] = "data.txt";

int char_to_double(char c){
    return (double) c-'0';
}

int string_to_int(char number[]) {
    int sum = 0;
    int N = strlen(number)-1;
    for(int i=0; i<N ;i++) {
        sum += (int) char_to_double(number[i])*pow(10, N-(i+1));
    }
    return sum;
}

int get_max_calories(const char filename[]){
    FILE *fptr; // Define file pointer
    fptr = fopen(filename, "r");
    char line[1024];
    int sum_calories = 0;
    int max_calories = INT_MIN;
    if (fptr != NULL){
        while(fgets(line, sizeof line, fptr)){
            if (strcmp(line, "\n") == 0){//strcmp return 0 if both strings are equal
                //enter if line is equal to newline
                //calculate max calories
                if (max_calories <= sum_calories){
                    max_calories = sum_calories;
                }
                sum_calories = 0;
            }else{
                //enter if line is different to newline
                sum_calories += string_to_int(line);
            }
        }
    }
    //close file
    fclose(fptr);
    return max_calories;
}

int main() {
    printf("reading file %s\n", filename);
    int max_calories = get_max_calories(filename);
    printf("max calories: %i\n", max_calories);
    return 0;
}
