#define _GNU_SOURCE		//strcasestr is a nonstandard GNU extension, 
//we need this line while serching for matching last name
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"
#define MAX_EMPLOYEES 100


//helper function to swap two employee records
void swap_employees(employee* a, employee* b) {
	employee temp;
	memcpy(&temp, a, sizeof(employee));
	memcpy(a, b, sizeof(employee));
	memcpy(b, &temp, sizeof(employee));
}

//sort_by_id function
void sort_by_id(dataBase_ptr db) {
	int i, j;


	for (i = 0; i < db->total - 1; i++) {
		for (j = 0; j < db->total - i - 1; j++) {
			//convert the ID strings to integers for comparison
			int id1 = atoi(db->emp[j].ID);
			int id2 = atoi(db->emp[j + 1].ID);

			//compare the IDs as integers and swap if necessary
			if (id1 > id2) {
				swap_employees(&db->emp[j], &db->emp[j + 1]);
			}
		}
	}
}

//helper function to compare two hire dates
int compare_hire_dates(const date* date1, const date* date2) {
	if (date1->year != date2->year) {
		return date1->year - date2->year;
	}
	if (date1->month != date2->month) {
		return date1->month - date2->month;
	}
	return date1->day - date2->day;
}

//sort_by_hire_date function
void sort_by_hire_date(dataBase_ptr db) {
	int i, j;

	for(i = 0; i < db->total - 1; i++) {
		for(j = 0; j < db->total - i -1; j++) {
			//compare hire dates and swap if necessary
			if (compare_hire_dates(&db->emp[j].hire_date, &db->emp[j+1].hire_date) > 0) {
			       //swap employees using helper function
			       swap_employees(&db->emp[j], &db->emp[j+1]);
			}
		}
	}
}

//display_all_employees function
void display_all_employees(dataBase_ptr db) {
       
	print_title();

	//loop through the employees
	for(int i = 0; i < db->total; i++) {
		char name[14];
		//combine first name and last name
		snprintf(name, sizeof(name), "%.13s", db->emp[i].first_name);
		strncat(name, " ", sizeof(name) - strlen(name) - 1);
		strncat(name, db->emp[i].last_name, sizeof(name) - strlen(name) - 1);

                //format email
		char formatted_email[13];
		snprintf(formatted_email, sizeof(formatted_email), "%s", db->emp[i].email);

		//format salary
		char formatted_salary[11];
		snprintf(formatted_salary, sizeof(formatted_salary), "$%9.2f", db->emp[i].salary);

		//format date
		char formatted_date[11];
		snprintf(formatted_date, sizeof(formatted_date), "%02d/%02d/%04d", db->emp[i].hire_date.month,db->emp[i].hire_date.day, db->emp[i].hire_date.year);

		printf("%-3d %-5s %-13s %-12s %-10s %-10s\n", i, db->emp[i].ID, name, formatted_email, formatted_salary, formatted_date);
	}
}

//display one employee helper function
void display_one_employee(dataBase_ptr db, int i) {
	//print_title();

	//check if the index is within the valid range
	if (i >= 0 && i < db->total) {
		
		//display the single employee's information
		char name[14];
		snprintf(name, sizeof(name), "%.13s", db->emp[i].first_name);
		strncat(name, " ", sizeof(name) - strlen(name) - 1);
		strncat(name, db->emp[i].last_name, sizeof(name) - strlen(name) - 1);

		char formatted_email[13];
		snprintf(formatted_email, sizeof(formatted_email), "%s", db->emp[i].email);

		char formatted_salary[11];
		snprintf(formatted_salary, sizeof(formatted_salary), "$%9.2f", db->emp[i].salary);

		char formatted_date[11];
		snprintf(formatted_date, sizeof(formatted_date), "%02d/%02d/%04d", db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);

		printf("%-3d %-5s %-13s %-12s %-10s %-10s\n", i, db->emp[i].ID, name, formatted_email, formatted_salary, formatted_date);
	}
	else {
		printf("invalid employee index provided.\n");
	}
}

//search_employee_by_id function
void search_employee_by_id(dataBase_ptr db) {
	char search_ID[idSIZE];
	printf("Enter the ID you are searching for \n");
	scanf("%s", search_ID);

	int found = 0; //flag to check if the ID is found

	print_title();
	
	for(int i = 0; i < db->total; i++) {
		//compare the entered ID with stored ID, disregarding the 0's
		const char *stored_ID = db->emp[i].ID;
		while(*stored_ID == '0') {
			stored_ID++; //skip leading zeroes
		}

		if(strcmp(stored_ID, search_ID) == 0) {
			//employee with matching ID found
			display_one_employee(db, i);
			found = 1;
			break;
			}
	}
	if (!found){
		printf("Employee with ID %s not found.\n", search_ID);
	}
}

//search_employee_by_last_name function
void search_employee_by_last_name(dataBase_ptr db) {
	char search_last_name[nameSIZE];
	printf("Enter the Last Name you are searching for \n");
	scanf("%s", search_last_name);

	int found = 0; //flag to check if any employee with the last name is found

	print_title();
	for (int i = 0; i < db->total; i++) {
		if (strcasestr(db->emp[i].last_name, search_last_name) != NULL) {
			//Employee with last name containing substring found
			if (!found) {
				found = 1;
			}
			display_one_employee(db, i);
		}
	}
	if (!found){
		printf("No employees found with last name containing %s.\n", search_last_name);
	}
}

//delete_employee_by_id function
void delete_employee_by_id(dataBase_ptr db) {
	char employee_id[idSIZE];
	printf("Enter the ID you are searching for \n");
	scanf("%s", employee_id);

	int found = 0;

	//find the employee by ID
	for (int i = 0; i < db->total; i++) {
		//compare the entered ID with stored ID, disregarding the 0s
		const char *stored_ID = db->emp[i].ID;
		while(*stored_ID == '0') {
			stored_ID++;
		}

		if(strcmp(stored_ID, employee_id) == 0) {
			//dipslay the employee that is to be deleted
			printf("The following employee is deleted: \n");
			print_title();
			display_one_employee(db, i);

			//employee with matching ID found, remove them by shifting the array
			for (int j = i; j < db->total - 1; j++) {
				db->emp[j] = db->emp[j + 1];
			}
			db->total--; //reduce the total count of employees
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Employee with ID %s not found.\n", employee_id);
	}
}


void create_record (char* ID, char* first_name, char* last_name, char* email, double salary, date hire_date, dataBase_ptr db)// specify parameters. Clues are in the initalize function.
{
  //define function. Clues are in the initalize function
  //do not forget to increase total number of employees in the database
  
  //check if the database is full
  if (db->total >= MAX_EMPLOYEES) {
	  printf("Database is full.\n");
	  return;
  }

  //create a new employee record
  employee new_employee;
  strcpy(new_employee.ID, ID);
  strcpy(new_employee.first_name, first_name);
  strcpy(new_employee.last_name, last_name);
  strcpy(new_employee.email, email);
  new_employee.salary = salary;
  new_employee.hire_date = hire_date;

  //add the new employee to the database
  db->emp[db->total] = new_employee; //assign the new employee record to the database
  db->total++; //increment the count of total employees
}


void print_title ()// you can keep this fuction or remove if needed
{
  printf ("No. ID    Name          Email        Salary     Hire Date\n");
  printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}


//fix save function. Save array into file: database_updated in the same format with the 
//database file.
void save (dataBase_ptr db)// this function is for saving the database into a text file
{
  FILE *dbfu;
  dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
  if (dbfu == NULL)
  {
    printf ("File cannot be created");
    return;
  }
  for (int i = 0; i < db->total; i++)
  {
      fprintf (dbfu, "%s %s %s %s %.2f %d/%d/%04d\n",
	      //add format specifiers here, db->emp[i].ID,
	      //add other members);
	      db->emp[i].ID,
	      db->emp[i].first_name,
	      db->emp[i].last_name,
	      db->emp[i].email,
	      db->emp[i].salary,
	      db->emp[i].hire_date.month,
	      db->emp[i].hire_date.day,
	      db->emp[i].hire_date.year);

  }

  fclose (dbfu);//close file after writing
  return;

}

//deallocate_database function
void deallocate_database(dataBase_ptr db){
	if (db != NULL) {
		//free the employees array
		free(db->emp);
		db->emp = NULL;

		//free the database structure
		free(db);
		db = NULL;
	}
}

void display_menu (struct DataBase *db)
{
  int input = 0;
  while (input != 8)
  {
    puts
      ("\n**************************************************************");
    printf
      (  "********** Employee Database - Total Employees: %03d **********\n", db->total
      );//you need to fix this line so that total employees in the database is printed
    puts
      ("**************************************************************\n");
    puts ("Choose one of the menu options below:");
    puts ("1. Sort by ID");
    puts ("2. Sort by Hire Date");
    puts ("3. Display all employees");
    puts ("4. Search employees by ID");
    puts ("5. Search employees by Last Name");
    puts ("6. Delete employee by ID");
    puts ("7. Save");
    puts ("8. Exit");

    scanf ("%d", &input);

    switch (input) {
      case 1:
	//call the function you defined for sorting by ID
	sort_by_id(db);
	break;
      case 2:
        //call the function you defined for sorting by Hire Date
	sort_by_hire_date(db);
        break;
      case 3:
        //call the function you defined for displaying employees
	display_all_employees(db);
        break;
      case 4:
        //call the function you defined for searching employees by ID
	search_employee_by_id(db);
        break;
      case 5:
        //call the function you defined for searching employees by Last Name
	search_employee_by_last_name(db);
        break;
      case 6:
        //call the function you defined for deleting employee by ID
	delete_employee_by_id(db);
        break;
      case 7:
        save (db);
        break;
      case 8:
        //free all allocated memory
	deallocate_database(db);
        printf("Bye!\n");
        break;

    }
  }
}
