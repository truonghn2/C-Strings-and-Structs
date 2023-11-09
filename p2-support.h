////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.h
// Description    : Header file for project2 
// Author         : ***Heather Truong***
// Date           : ***11/1/23***
// Notes          : ***Type bug fixes/other with dates for your records
//                  10/31 Fixed duplicate record of Chris Magenta, extra space in the database file
//                  10/31 Fixed format of output of salary 
//                  11/1  Fixed format of output for the save function
#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date// do not modify
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[6];
  //declare other members
  char first_name[10];
  char last_name[10];
  char email[20];
  double salary;
  date hire_date;

}employee, *employee_ptr;

typedef struct DataBase
{
  //a pointer to first element of empoloyee array
  employee* emp;
  //number of employees in database
  int total;
}*dataBase_ptr;

// Functional Prototypes

// Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (dataBase_ptr);

//Write formal comments for each function header. 
//In the same format with the initialize function

//Function	: create_record
//Description	: Adds a new employee record to the database
//Inputs	: employee ID, first name, last name, email, salary, hire date, a pointer to Database struct
//Outputs	: none
void create_record (char* ID, char* first_name, char* last_name, char* email, double salary, date hire_date, dataBase_ptr db);

//Function      : print_title
//Description   : Prints the formatted title for the employee database with column names
//Inputs        : none
//Outputs       : none
void print_title ();

//Function      : display_menu
//Description   : Displays the menu for the employee database with options
//                Options include displaying employees, searching employees, etc
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void display_menu (dataBase_ptr);

//Function      : swap_employees
//Description   : Helper function to swap two employee records
//Inputs        : two employee pointers (a and b)
//Outputs       : none
void swap_employees(employee* a, employee* b);

//Function      : sort_by_id
//Description   : Sorts employee records in the database by ID in ascending order
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void sort_by_id(dataBase_ptr db);

//Function      : compare_hire_dates
//Description   : Helper function to compare two hire dates
//Inputs        : pointers to two date structs (date1 and date2)
//Outputs       : integer indicating the comparison result
int compare_hire_dates(const date* date1, const date* date2);

//Function      : sort_by_hire_date
//Description   : Sorts employee records in the datbaase by hire date
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void sort_by_hire_date(dataBase_ptr db);

//Function      : display_all_employees
//Description   : Displays details of all employees in the database
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void display_all_employees(dataBase_ptr db);

//Function      : display_one_employee
//Description   : Displays details of a single employee from the database
//Inputs        : a poiunter to DataBase struct and index of the employee
//Outputs       : none
void display_one_employee(dataBase_ptr db, int i);

//Function      : search_employee_by_id
//Description   : Searches for an employee ID and displays the details if found
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void search_employee_by_id(dataBase_ptr db);

//Function      : search_employee_by_last_name
//Description   : Searches employee by last name and displays the details of matching employee
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void search_employee_by_last_name(dataBase_ptr db);

//Function      : delete_employee_by_id
//Description   : Deletes an employee by ID after displaying their details
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void delete_employee_by_id(dataBase_ptr db);

//Function      : save
//Description   : Saves the database to a file
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void save(dataBase_ptr);

//Function      : deallocate_database
//Description   : Deallocates memory used by the database and its components
//Inputs        : a pointer to DataBase struct
//Outputs       : none
void deallocate_database(dataBase_ptr db);


#endif //To prevent double inclusion of header
