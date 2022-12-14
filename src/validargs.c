#include <stdlib.h>

#include "argo.h"
#include "global.h"
#include "debug.h"

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the various options that were specified will be
 * encoded in the global variable 'global_options', where it will be
 * accessible elsewhere in the program.  For details of the required
 * encoding, see the assignment handout.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * @modifies global variable "global_options" to contain an encoded representation
 * of the selected program options.
 */

//Function for comparing Strings
int stringCompare(char* string1 , char* string2 ){ //both get passed down as a array of characters so we compare here 
//returns an int type
//const means that the variable is only a read only value
    int checkervar = 0;
    while((*string2 != '\0') && (*string1 != '\0')){ //compares until both of their characters reach the end
    //because they are null terminating
        if(*string1 == *string2){ //checking the addresses there
            checkervar = 1; //if addresses = then do this
        }
        else{
          checkervar = 0;
          break; //breaks out of the loop whenever checkervar = 0;
        }
        string1 = (string1 + 1); //moves the address to the next character
        string2 = (string2 + 1); //moves the address to the next character
      }

    if(checkervar == 1){
       return 1; //if the strings are equal
    }else
       return 0; //if strings are not equal
    }
    
  //Function for checking if a String is an Int or Empty
  int StringtoInt(char* Pointer){
    int var = 0;

    int checkerval2 = 0;
    while((*Pointer != '\0')){
      if(*Pointer >= '0' && *Pointer <= '9'){
        checkerval2 = 1;
      }else{
        checkerval2 = 0;
        break; //breaks out of the loop
      }
      var = var * 10 + *Pointer - '0'; //gets the String to an int
      //the *10 shifts the var to the left so it can keep adding digits to the right
      Pointer = Pointer + 1; //moves the address by 1
    }
    //or if the Pointer is empty which is legal

    if (checkerval2 == 1){
      return var; //If it is an integer or legal
    }else{
      return -1; //If its not an integer
    }
  }

int validargs(int argc, char **argv) {
  //argv has arguements in argv[0] and argv[1]
  // TO BE IMPLEMENTED
  //check for -h, -c, and -v first
  //<----- Area for the flag starts here ----->
  int check1 = 1;
  int check2 = 1;
  int check3 = 1;
  int check4 = 1;
  int check5 = 1;

  // <----- Ends Here the Check flags ----->

  // <-------- Variables (Starts here) ---------->
  int i = 1;
  int numofargs = 1;
  //char *Pstring1 = *(argv+i);
  char *Pstring2 = "-h";
  char *Pstring3 = "-c";
  char *Pstring4 = "-v";
  char *Pstring5 = "-p";
  
   // <-------- Variables (Ends here) ---------->
  // <------- Conditions start here to check ---------->

  //Check 1 : 
  if (argc <= 1){ //Conditon for when there are 1 or less than 1 arguements, it gives an error
    return -1;
  }
  
  //
  for(i=1; i < argc; i++){ //initial check for if -h, -c, -v are the first arguement
    
    char *Pstring1 = *(argv+i);
    if (check1 == 1){
      if ((stringCompare(Pstring1,Pstring2) == 0) && (stringCompare(Pstring1,Pstring3) == 0) && (stringCompare(Pstring1,Pstring4) == 0)){
        return -1; //returns an error and terminates
      }  
    }
    check1 = 0; //if this gets back the first test so then it doesn't repeat the test
   
  //Check 2 : 
    if ((stringCompare(Pstring1,Pstring2) == 1)){ //if -h flag is provided
      if(check2 == 0){
        return -1; //exits with fail because -h can't be in later flags
      }
        global_options = global_options + HELP_OPTION; //Exit success
        return 0; //exits with success
      }
    check2 = 0; //gets set because -h can't be in later flags

  //Check 3 :
    if ((stringCompare(Pstring1,Pstring4) == 1)){ //if -v flag is provided
      if(check3 == 0){
        return -1;
      }
      numofargs = numofargs + 1; //counter
      global_options = global_options + VALIDATE_OPTION; //Exit success
      if(numofargs == argc){
          return 0;
      }
    }
    check3 = 0;

  //Check 4 :
    if ((stringCompare(Pstring1,Pstring3) == 1)){ //if -c flag is provided
      if(check4 == 0){
        return -1;
      }
      global_options = global_options + CANONICALIZE_OPTION; //Exit success
      numofargs = numofargs + 1;
      if(numofargs == argc){
          return 0;
      }
    }
    check4 = 0;

  //Check 5 : 
    if ((stringCompare(Pstring1,Pstring5) == 1)){ //if -p flag is provided
      if(check5 == 0){
        return -1;
      }
      global_options = global_options + PRETTY_PRINT_OPTION; //Exit success

      check5 = 0;

      char *TempPtr = *(argv + i - 1);
      if ((stringCompare(Pstring3, TempPtr) == 1)){//if -c is the previous flag
      }else{
        return -1;
      }
      char *TemptPtr2 = *(argv + i + 1); //checks the thing after it is a number
      numofargs = numofargs + 1;
      if(numofargs == argc){
        global_options = global_options + 4;
        return 0;
      }
      numofargs = numofargs + 1;
      if(numofargs == argc){
        if(StringtoInt(TemptPtr2) != -1){ //if its a number its chill
          global_options = global_options + StringtoInt(TemptPtr2);
          return 0;
        } else{
          return -1; //if its not a number error
          }
      }else{
        if(StringtoInt(TemptPtr2) != -1){
          global_options = global_options + StringtoInt(TemptPtr2);
          i++;
        }
      }
  
  // <------- Conditions end here to check ---------->
   }
  
}
  global_options = 0;
  return -1;

}