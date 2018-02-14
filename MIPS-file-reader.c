
    William Dahl
    wd347166
    Areeb Khan
    Friday 1:40 */

#include <stdio.h> #include <string.h> #include <stdlib.h>

/* Structure to hold the indentifier. */

struct Identifier { char label[11]; // Holds the label. char ref[1000]; // Holds the lines that the label is refernced in. };

/* Prototypes for the search and check functions */

void search(FILE*, struct Identifier[], int); int check(char*, struct Identifier[], int);

/*

    This is a C program whose input is
    a MIPS Assembly Language (MAL) program and
    whose output is a list of labels of the MAL program used as variables,
    a list of labels of the MAL program used for the flow control,
    or both.
    It is assumed that the input arguments to the program will be:
    -v, to produce only a list of labels of the MAL source program
    used as vairables in the specified output file.
    -f, to produce only a list of of labels of the MAL program
    used for flow control in the sepcified output file.
    -b, to produce both a list of labels of the MAL source program
    used as variables and used for flow control in the specified output file.
    The input MAL file.
    The specified output file. */

int main(int argc, char argv[]) { / Prototypes for the functions v, f, and b */

void v(FILE*, FILE*); void f(FILE*, FILE*); void b(FILE*, FILE*);

/* Checks if there are the right number of arguments when the program is called. */ if(argc != 4) { fprintf(stderr, "Not the correct number of inputs given when running p4.c.\n"); // Prints a message to stderr exit(1); // Ends the program } else { FILE *finp; // Creates a file pointer that points to the input file. FILE *fout; // Creats a file pointer that points to the output file.

  /* Checks that the input file can be opened for reading */
  if((finp = fopen(argv[2], "r")) == NULL)
{
  fprintf(stderr, "Error opening %s.\n", argv[2]); // Prints error meassage to stderr.
  exit(1); // Ends the program
}

  /* checks if the output file can be opened for writing. */
  if((fout = fopen(argv[3], "w")) == NULL)
{
  fprintf(stderr, "Error opening %s.\n", argv[3]); // Prints error message to stderr
  exit(1); // Ends the program.
}

  /* Checks for the flag given in the program call */
  if(strcmp(argv[1], "-v") == 0)
{
  v(finp, fout); // Calls v
}

  else if(strcmp(argv[1], "-f") == 0)
{ 
  f(finp, fout); // Calls f
}

  else if(strcmp(argv[1], "-b") == 0)
{
  b(finp, fout); // Calls b
}

  /* an incrorect flag was given in the program call. */
  else
{
  fprintf(stderr, "Invlaid input for flag.\n"); // Prints an error meassage to stderr.
  exit(1); // Ends the program
}

  /* checks that the input fiel can be closed */
  if(fclose(finp) == EOF)
{
  fprintf(stderr, "Error in closeing %s.\n", argv[2]); // Prints an error message to stderr
}

  /* Checks that the outputfile can be closed */
  if(fclose(fout) == EOF)
{
  fprintf(stderr, "Error in closing %s.\n", argv[3]); // prints an error message to stderr
}

}

return 0; // returns 0 upon compltion of the program }

/*

    Function to print the variables ID used in the MAL file
    and the lines in whcih they are refrenced in.
    First parameter is a file pointer to the inputfile.
    Second paramter is the file pointer to the output file.
    The function does not return anything. */

void v(FILE *finp, FILE fout) { / Creates a Identifier array called var */

struct Identifier var[100];

char line[81]; // Holds the current line of the file char variable[11]; // Holds the label with in the line char *hold; // Holds the pointer to the first occurence of a ':' in line int position; // Holds the postion of the first occurence of a ':' in line int index = 0; // Index of the identifier array int i = 0; // Second index for the array for printing int a; // Counter for itializing variable to empty on every new pass

/* Reads through the inout file / while(fgets(line, 81, finp)) { / checks if ".text" is in the current line of the input file. */ if(strstr(line, ".text")) { break; // Breaks out of the loop }

  /* Checks if a ':' is in the current line of the input file */
  if(strchr(line, ':'))
{
  hold = strchr(line, ':'); // Points hold to the first occurence of the ':' in the line
  position = (int)(hold - line); // Gets the posotion of the ':' in the line
  
  /* Makes vairable empty */
  for(a = 0; a <= 11; a++)
    {
      variable[a] = '\0'; // Sets the char at a in variable to the NULL character
    }

  strncpy(variable, line, position); // copies the first 'postion' characters in lin into variable.
  
  /* Ckecks if the variable is already in the identifier array */
  if(check(variable, var, index))
    {
      continue; // Exits the if statemnt and goes back into the loop.
    }

  strcpy(var[index].label, variable); // copies variable into the label filed of var
  search(finp, var, index); // Calls the search function 
  rewind(finp); // Points the file pointer of the input file back to the begining.
  index++; // Incremntes i by one
}
}

/* Prints the variable id and its references to the output file */ while(i < index) { fprintf(fout, "Variable ID -%s-\n%s\n", var[i].label, var[i].ref); i++; } }

/*

    Function to print the variable ID in the MAL file
    that have to do with flow control.
    First parameter is the file pointer to the input file
    Second paramter is the file pointer to the output file
    The function returns nothing. */

void f(FILE *finp, FILE *fout) { rewind(finp); // Rewinds the file pointer to point to the begingin of the input file struct Identifier var[100]; // Creates a Identifier array

char line[81]; // holds the current line char variable[11]; // holds the label char *hold; // holls the pointer to the irst apperance of ':' in the line size_t position; // Position of the the ':' in the line int count = 0; // count for the lines to read through before starting int index = 0; // index of var int start; // line to start int i = 0; // second index for printing int a; // counter for intializing variable

/* reads throught the inpit file / while(fgets(line, 81, finp)) { count++; / Checks if ".text" is in the current line. */ if(strstr(line, ".text")) { start = count; // sets start to count; } }

rewind(finp); // rewinds the file pointer count = 0; // sets count back to zero

/* reads through the file */ while(fgets(line, 81, finp)) { count++;

  /* checks if count is greater than start */
  if(count > start)
{
  /* checks for the ':' in the line */
  if(strchr(line, ':'))
    {
      /* intialzes variable. */
      for(a = 0; a <= 11; a++)
	{
	  variable[a] = '\0';
	}

      hold = strchr(line, ':'); // Sets hold to point tot he first occurence of ':'
      position = (int)(hold - line); // intializes the postion of the ':'
      strncpy(variable, line, position); // copies the label into varibale form line
      strcpy(var[index].label, variable); // copies variable into the label field of var at index
      index++;
    }
}
}

/* Prints the flow control varibale to the output file. */ while(i < index) { fprintf(fout, "Flow Control ID -%s-\n", var[i].label); i++; } }

/*

    Function to print both data varibales
    and flow control varibale to the output file.
    First paramter in the pointer to the input file
    Second paramter is the pointer to the output file.
    The function returns nothing */

void b(FILE finp, FILE fout) { v(finp, fout); // calls v f(finp, fout); // calls f }

/*

    Function to search for all the points that the label is referced.
    First paramter is the file pointer to the input file
    Second paramter is the Identifier array var
    Third paramter is the current index
    The function returns nothing. */

void search(FILE *finp, struct Identifier var[], int index) { char line[81]; // Holds the current line in the file char ref[1000] = {'\0'}; // Holds the lines the label is refrenced in char *hold; // Holds the pointer to the ':' int position; // Holds the position of the ':' char variable[11]; // Holds the label int a; // counter for intializing variable

/* reades through the file / while(fgets(line, 81, finp)) { / checks if line has a ':' in it */ if(strchr(line, ':')) { hold = strchr(line, ':'); // sets hold to oint to the ':' position = (int)(hold - line); // sets the position of the ':'

  /* intializes varaible */
  for(a = 0; a <= 11; a++)
    {
      variable[a] = '\0';
    }

  strncpy(variable, line, position); // copies line into varaible

  /* Checks if the label is with in the variable */
  if(strstr(variable, var[index].label))
    {
      continue; // exits out back to the loop
    }
}

  /* checks if the line containes the lable */
  if(strstr(line, var[index].label))
{
  strcat(ref, line); // Concatenates the line to the other lines where it is refernced
}
}

strcpy(var[index].ref, ref); // copies ref into the ref field in var }

/*

    Function to check if the label is already with in the identifier array var
    First parameter is the variable to be checked for
    Second paramter is the Identifter array var.
    Third Paramter is the index
    The function retuns an integer:
    A 0 if the variable is already with in var
    A 1 if the variable is not found in var */

int check(char *variable, struct Identifier var[], int index) { int i = 0; // index to go go through the var entries

/* goes through the var entries / while(i < index) { / Checks if the variable in within var at i */ if(strcmp(variable, var[i].label) != 0) { i++; // Incremnates i by one } else { return 1; // returns 1 if the variable is found to be in var } }

return 0; // returns 0 if not found in var }
