#ifndef _Module2Program_H
#define _Module2Program_H

/** 
* Description: Loads student and course information from an external text file
*              to execute operations with the relevant data via text menus.
*
* Completion time: 13 hours
* 
* @author Wihebrink, Acuna
* @version 8/24/2021 
*
*/

////////////////////////////////////////////////////////////////////////////////
// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
// MACROS: CONSTANTS
#define MAX_STUDENT_NAME_LENGTH 20
#define MAX_COURSE_NAME_LENGTH 10
#define MAX_TEACHER_NAME_LENGTH 20
#define MAX_COMMENT_LENGTH 20
#define MAX_ASSIGN_NAME_LENGTH 20
#define MAX_FILENAME_LENGTH 30

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

typedef enum AcademicLevel {
  Freshman = 1,
  Sophomore = 2,
  Junior = 3,
  Senior = 4    
} AcademicLevel;

typedef struct ScoreStruct {
  int studentID;
  int assignID;
  float score;
  char* comment;
} ScoreStruct;

typedef struct Assign {
  int ID;
  char* name;
} Assign;

typedef struct Student {
  int ID;
  char* name;
  AcademicLevel level;
} Student;

typedef struct Course {
  int number;
  char* name;
  char* teacher;
  int numAssigns;
  Assign* assigns;
  ScoreStruct** scores;  
} Course;

////////////////////////////////////////////////////////////////////////////////
//GLOBAL VARIABLES

//place to store student information
Student* students = NULL;
//place to store course information
Course* courses = NULL; 
int numCourses, numStudents;

////////////////////////////////////////////////////////////////////////////////
//FORWARD DECLARATIONS

// the following should be used to read student/course data in from the file 
void readFile(char* filename);
void readString(FILE* file, char** dst, int max_length);
Student* readStudents(FILE* file);
Course* readCourses(FILE* file);
Assign* readAssigns(FILE* file, int numAssigns);
ScoreStruct** readScores(FILE* file, int numAssigns);

// the following should be used to free all heap data allocated during the programs runtime
// and handle dangling pointers
void terminate();
void studentsDestructor();
void coursesDestructor();
void assignsDestructor(Assign** assigns, int numAssign);
void scoresDestructor(ScoreStruct*** scores, int numAssigns);

// the following should be used to cleanly print the data used in the program 
void printStudents();
void printAssigns(Assign* assigns, int numAssigns);
void printGrades(ScoreStruct** scores, int numAssigns);
void printCourse(Course course);

// the following are mostly complete functions that define and 
// control the CLI menu associated with the program
void mainMenu();
void mainMenuBranch(int option);
void subMenu(Course course);
void subMenuBranch(int option, Course course);

// these are the 'special' functions that you are being asked to implement
void studentMenu(Course course);
void getStudentScores(Course course, int studentNo);
void assignmentMenu(Course course);
void getAssignmentScore(Course course, int assignmentNo);

// this is an optional function that parses and executes instructions defined in an input file
void processInstructions(char* iFile);

// this is a utility function to be called when input filenames are invalid
void printUsage();

/////////////////////////////////////////////////////////////////////////////////
//IMPLEMENTATION

/**
* Reads text from external file and loads that data into the program
*/
void readFile(char* filename){
  FILE* file = fopen(filename, "r");
  fscanf(file, "%d", &numStudents);
  students = readStudents(file);
  fscanf(file, "%d\n", &numCourses);
  courses = readCourses(file);
  fclose(file);
}

/**
*  Reads a string with a specified maximum length from a file
*/
void readString(FILE* file, char** dst, int max_length){
  char buffer[max_length];
  fgets(buffer, max_length, file);
  int length = strlen(buffer);
  if (buffer[length-1] == '\n'){
    buffer[length-1] = 0;
  }  
  char* string = (char*) malloc(sizeof(char)*length);
  strcpy(string, buffer);
  *dst = string;
}

/**
* Reads student data from file
*/
Student* readStudents(FILE* file){
  Student* students = (Student*) malloc(sizeof(Student)*numStudents);
  int i;
  for(i = 0; i < numStudents; i++){
    fscanf(file, "%d\n", &students[i].ID);
    readString(file, &students[i].name, MAX_STUDENT_NAME_LENGTH);
	int level;
	fscanf(file, "%d\n", &level);
	students[i].level = level;
  }
  return students;
}

/**
* Reads course data from file
*/
Course* readCourses(FILE* file){
  Course* courses = (Course*) malloc(sizeof(Course)*numCourses);
  int i;
  for(i = 0; i < numCourses; i++){
    fscanf(file, "%d\n", &courses[i].number);
    readString(file, &courses[i].name, MAX_COURSE_NAME_LENGTH);
    readString(file, &courses[i].teacher, MAX_TEACHER_NAME_LENGTH);
    fscanf(file, "%d\n", &courses[i].numAssigns);
    courses[i].assigns = readAssigns(file, courses[i].numAssigns);
    courses[i].scores = readScores(file, courses[i].numAssigns);    
  }
  return courses;
}

/**
* Reads assignment data from file
*/
Assign* readAssigns(FILE* file, int numAssigns){
  Assign* assigns = (Assign*) malloc(sizeof(Assign)*numAssigns);
  int i;
  for(i = 0; i < numAssigns; i++){
    fscanf(file, "%d\n", &assigns[i].ID);
    readString(file, &assigns[i].name, MAX_ASSIGN_NAME_LENGTH);
  }
  return assigns; 
}

/**
* Reads scores data from file
*/
ScoreStruct** readScores(FILE* file, int numAssigns){
  ScoreStruct** scores = (ScoreStruct**) malloc(sizeof(ScoreStruct*) * numStudents);
  int i;
  for(i = 0; i < numStudents; i++){
    scores[i] = (ScoreStruct*) malloc(sizeof(ScoreStruct) * numAssigns);
  }
  int j;
  
  for(j = 0; j < numAssigns * numStudents; j++){
    int studentID, assignID;

    fscanf(file, "%d\n%d\n", &assignID, &studentID);
    scores[studentID-1][assignID-1].studentID = studentID;
    scores[studentID-1][assignID-1].assignID = assignID;
    fscanf(file, "%f\n", &scores[studentID-1][assignID-1].score);
    readString(file, &scores[studentID-1][assignID-1].comment, MAX_COMMENT_LENGTH);
  }
  return scores;  
}

/**
* Returns a string specifying a student's Academic level
*/
char* getLevelString(AcademicLevel level){
  switch(level){
    case Freshman: 
	return "Freshman";
    case Sophomore:
	return "Sophomore";
    case Junior:
	return "Junior";
    case Senior:
	return "Senior";
  }
}

/**
* Displays a main menu that allows a user to select a course of choice to interact with
*/
void mainMenu(){
  int input_buffer;
  printf("Course Searcher");  
  do {
    printf("\n-----------------------------------\n");
    printf("Course Options");
    printf("\n-----------------------------------\n");

    int i;
	
    for(i = 0; i < numCourses; i++){
      printf("   %d %s\n", courses[i].number, courses[i].name);
    }
    printf("   0 REPEAT OPTIONS\n");
    printf("  -1 TERMINATE PROGRAM\n");
    printf("Please enter your choice ---> ");
    scanf(" %d", &input_buffer);
    mainMenuBranch(input_buffer);
  } while (1);
}

/**
* Manages main menu choices
*/
void mainMenuBranch(int option){
  if (option < -1 || option > numCourses){
    printf("Invalid input. Please try again...\n");
 
    while(option < -1 || option > numCourses){
      printf("Please enter a valid option ---> ");
      scanf(" %d", &option);
    }
  }
  if(option == -1){
    printf("Terminating program...\n");
    terminate();
  } else if (option == 0) {
      printf("Repeating options...\n");
  } else {
      Course course = courses[option - 1];
      printf("Course with name %s selected.\n", course.name);
      subMenu(course);
  }
}

/**
* Displays sub menu that allows users to select how they want to interact with course
*/ 

void subMenu(Course course){
  int input_buffer;
  do {
    printf("\n-----------------------------------\n");
    printf("Menu Options");
    printf("\n-----------------------------------\n");
    printf("   1 Get a student's final grades in the course\n");
    printf("   2 Get the average grade of an assignment in the course\n");
    printf("   3 Print all course data\n");
    printf("   0 REPEAT OPTIONS\n");
    printf("  -1 RETURN TO PREVIOUS MENU\n");
    printf("  -2 TERMINATE PROGRAM\n");	
    printf("Please enter your choice ---> ");
    scanf(" %d", &input_buffer);
    subMenuBranch(input_buffer, course);
  } while (input_buffer != -1);
}

/**
* Manages sub menu choices
*/
void subMenuBranch(int option, Course course){
  if (option < -2 || option > 3){
    printf("Invalid input. Please try again...\n");
    while(option < -2 || option > 3){
      printf("Please enter a valid option ---> ");
      scanf(" %d", &option);
    }
  }
  if(option == -2){
    printf("Terminating program...\n");
    terminate();
  } else if (option == -1){
      printf("Returning to previous menu...\n");
  } else if (option == 0){
      printf("Repeating options...\n");
  } else if (option == 1){
      studentMenu(course);
  } else if (option == 2){
      assignmentMenu(course);
  } else if (option == 3){
      printCourse(course);
  } 
}

/**
* Engages the user to select an assignment to average grade's for.
*/
void assignmentMenu(Course course){
  printf("\nPlease choose from the following assignments: \n");
  printAssigns(course.assigns, course.numAssigns);
  printf("  0 RETURN TO PREVIOUS MENU\n");

  int assignID;

  printf("Please enter your choice ---> ");
  scanf(" %d", &assignID);

  while(assignID < 0 || assignID > course.numAssigns){
    scanf(" %d", &assignID);
  }
  if (assignID == 0){
    printf("Returning to previous menu...\n");
    return;
  } else {
      getAssignmentScore(course, assignID);
  }
} 


/**
* Displays the average score for the chosen assignment
*/
void getAssignmentScore(Course course, int assignID){	
  double total = 0, average = 0;
  int i;

  for(i = 0; i < numStudents; i++){
    total += course.scores[i][assignID-1].score;
  }

  average = total / numStudents;
  printf("\nThe average grade on %s was %.2f.\n", course.assigns[assignID-1].name, average);
}

/**
* Engages the user to select a student to get their scores for
*/
void studentMenu(Course course){
  printf("\nPlease choose from the following students: \n");
  printStudents();
  printf("  0 RETURN TO PREVIOUS MENU\n");

  int studentID;

  printf("Please enter your choice ---> ");
  scanf(" %d", &studentID);
  while(studentID < 0 || studentID > numStudents ){
    printf("Please enter a valid option ---> ");
    scanf(" %d", &studentID);
  }
  if (studentID == 0){
    printf("Returning to previous menu...\n");
    return;
  } else {
      getStudentScores(course, studentID);
  }
}

/**
* Displays a student grades in a course
*/
void getStudentScores(Course course, int studentID){
  double total = 0, average = 0;
  int i;

  printf("\n%s's assignment specific grades were: \n\n", students[studentID-1].name);
  printf("  %-16s%-16s%-16s\n", "Assign Name", "Score", "Comment");
  printf("-----------------------------------------------\n");

  for(i = 0; i < course.numAssigns; i++){
    total += course.scores[studentID - 1][i].score;
	printf("  %-16s%-16.2f%-16s\n", course.assigns[i].name, course.scores[studentID - 1][i].score, course.scores[studentID-1][i].comment); 
  }
  average = total / course.numAssigns;
  printf("\n%s's final grade was %.2f.\n", students[studentID -1].name, average);
}

/**
* Displays all data associated to a particular course
*/
void printCourse(Course course){
  printf("\nCourse ID: %d\n", course.number);
  printf("Course Name: %s\n", course.name);
  printf("Teacher: %s\n", course.teacher);
  printf("Assigns: \n");
  printAssigns(course.assigns, course.numAssigns);
  printf("Grade Data: \n");
  printGrades(course.scores, course.numAssigns);
}

/**
* Displays student data
*/
void printStudents(){
  int i;
  for(i = 0; i < numStudents; i++){
    printf("  %d %s (%s)\n", students[i].ID, students[i].name, getLevelString(students[i].level));     
  }
}

/**
* Displays assignment data
*/
void printAssigns(Assign* assigns, int numAssigns){
  int i;
  for(i = 0; i < numAssigns; i++){
    printf("  %d %s\n", assigns[i].ID, assigns[i].name);  
  } 
} 

/**
* Displays grade data
*/
void printGrades(ScoreStruct** scores, int numAssigns){
  int i, j;
  for(i = 0; i < numStudents; i++){
    for(j = 0; j < numAssigns; j++){
      printf("  %d %d %.02f %s\n", scores[i][j].studentID, scores[i][j].assignID, scores[i][j].score, scores[i][j].comment);
    }
  }
}

/**
* Displays basic usage instructions via command line to the user
*/
void print_usage(){
  printf("USAGE:\n./WihebrinkCourseReader -d <data_file_name(char*)> -c <instruction_file_name(char*)>\n");
  printf("-d refers to the required input data file containing student & course information; this must be a valid .txt file\n");
  printf("-i refers to the optionally supported 'instruction file' that provides directions for how the program should execute without CLI input; \n\t must be a valid .txt.file\n");
}

/**
* Frees up memory from student collection of data
*/ 
void studentsDestructor(){
  int i;
  for(i = 0; i < numStudents; i++){
    free(students[i].name);
  }
  free(students);
  students = NULL;
}

/**
* Frees up memory from course collection of data
*/
void coursesDestructor(){
  int i;
  for(i = 0; i < numCourses; i++){
    assignsDestructor(&courses[i].assigns, courses[i].numAssigns);
    scoresDestructor(&courses[i].scores, courses[i].numAssigns);
	free(courses[i].name);
	free(courses[i].teacher); 
  }
  free(courses);
  courses = NULL;
}

/**
* Frees up memory from an assignment collection of data
*/
void assignsDestructor(Assign** assigns, int numAssigns){
  int i;
  Assign* assignsArray = *assigns;
  for(i = 0; i < numAssigns; i++){
    free(assignsArray[i].name);
  }
  free(*assigns);
  *assigns = NULL;
}

/**
* Frees up memory from grade collection of data
*/
void scoresDestructor(ScoreStruct*** scores, int numAssigns){
    int i, j;
    ScoreStruct** scoresArray = *scores;
    
    for(i = 0; i < numStudents; i++){
      for(j = 0; j < numAssigns; j++){
        free(scoresArray[i][j].comment);
      }
      free(scoresArray[i]);
    }
    free(scoresArray);
    *scores = NULL;   
}

/**
* Frees data before program termination for no memory leaks.
*/
void terminate(){
  //FREE EVERYTHING HERE
  studentsDestructor();
  coursesDestructor();
  exit(0);
}

//////////////////////////////////////////////////////////////////////////
// EXTRA CREDIT

/**
* Parses and executes instructions defined in an instruction file
*/
void processInstructions(char* iFile){
  FILE* file = fopen(iFile, "r");
  int numInstructions;
  fscanf(file, "%d", &numInstructions);
  int i;
  for(i = 0; i < numInstructions; i++){
    int courseNum, studentNum, assignmentNum;
	fscanf(file, "%d %d %d", &courseNum, &studentNum, &assignmentNum);
	printf("\nProcessing instruction with courseNum %d, studentNum %d, and assignmentNum %d", courseNum, studentNum, assignmentNum);
    Course course = courses[courseNum - 1];
	if(studentNum && assignmentNum){
      printf("\nStudent with name %s received a %.02f on assignment %s\n", students[studentNum-1].name, course.scores[studentNum-1][assignmentNum-1].score, course.assigns[assignmentNum-1].name);
    } else if (studentNum && !assignmentNum){
      getStudentScores(course, studentNum);
    } else if (!studentNum && assignmentNum){
      getAssignmentScore(course, assignmentNum);
    } else {
      printCourse(course);
    }
  }
  fclose(file);
  printf("\nEnd of instructions reached. Terminating.\n");
  terminate();  
}

int main(int argc, char* argv[]){
  char* datafile;
  char* instructionfile;
  int opt;
  while((opt = getopt(argc, argv, ":d:i:")) != -1){
    switch(opt){
      case 'd':
        datafile = optarg;
        break;  
      case 'i':
        instructionfile = optarg;
        break;
      case ':':
	printf("option needs a value\n");
	break;
      case '?':
        printf("unknown option: %c\n", optopt);
        break;
    }
  }
  for (; optind < argc; optind++){
    printf("Given extra arguments: %s\n", argv[optind]);
  }  

  int dflen;
  if(datafile != NULL){
    dflen = strlen(datafile);
    if(dflen >= 5 && (strcmp(&datafile[dflen-4], ".txt") == 0)
        && (access(datafile, F_OK) != -1)){
      printf("Importing data from %s\n\n", datafile);
	  readFile(datafile);
    } else {
	  printf("Data file has an invalid name or does not exist.\n");
          print_usage();
	  exit(1);   
    }
  } else {
    printf("No data file name provided. This is a required field.\n");
    print_usage();
	exit(1);
  }

  int iflen;
  int ifval;
  if(instructionfile != NULL){
    iflen = strlen(instructionfile);
	if(iflen >= 5 && (strcmp(&instructionfile[iflen-4], ".txt") == 0)
		&& (access(instructionfile, F_OK) != -1)){
	  printf("Performing instructions defined in %s:\n", instructionfile);
	  //uncomment below if doing this optional part of the assignment
	  processInstructions(instructionfile);  	  
	} else {
      printf("Instruction file has an invalid name or does not exist.\n");
	  print_usage();
	  exit(1);
    }
  } else {
	printf("No instruction file provided. Using CLI:\n");
    mainMenu();
  }
  return 0;
}

#endif
