#include <stdlib.h>
#include <stdio.h>

#include "argo.h"
#include "global.h"
#include "debug.h"

int argo_write_basic(); //prototype
int argo_write_array(); //prototypes
int argo_write_number(); //prototype
int argo_write_string(); //prototype
int argo_write_object(); //prototype
int pretty_print(); //prototype
int exponentcalc(); //prototype
int argo_read_basic(); //prototype
int argo_read_array(); //prototype

int exponentcalc(int i,int variable2){ 
    int calculatingsum;
    calculatingsum = 0;
    int expon = 1;
    if(i == 0){
        calculatingsum = 1;
        calculatingsum = calculatingsum * variable2;
        return calculatingsum;
    }else{
    calculatingsum = 1;
    calculatingsum = calculatingsum * variable2;

    for (int j=0; j < i; j++){
        expon = expon * 16;

    }
    calculatingsum = calculatingsum * expon;

    return calculatingsum;
    }
}

int inttohex(int *ptr,FILE *f){ //receives a file to output too and a char ptr
  int number = *ptr;
  int flag = 1; //own flag
  int counter = 0; //counts how many already fputc
  int maxnumber = 4;

  putc(ARGO_BSLASH,f); //writes the / before
  putc(ARGO_U,f); //writes the u after

  int number2 = number; //number2 just used for computing the # of 0s
  while(number2 != 0){
      counter = counter + 1;
      number2 = number2 / 16;
  }

   counter = maxnumber - counter; //counter should be the amount of 0s needed to be putc in 
   for(int i = 0; i < counter; i++){
      fputc('0',f);
   }

  while(number != 0){ 
    if (number > 15){
         number = number / 16; //do this only in the beginning if > 15
    }else{
        flag = 0;
    }

    int numbermodulus = number % 16;
    if(numbermodulus >= 0 && numbermodulus <= 9){
        fputc(numbermodulus,f);
    }

    if(numbermodulus >= 10 && numbermodulus <= 16){
        if(numbermodulus == 10){
            fputc('a',f);
        }

        if(numbermodulus == 11){
            fputc('b',f);
        }

        if(numbermodulus == 12){
            fputc('c',f);
        }

        if(numbermodulus == 13){
            fputc('d',f);
        }

        if(numbermodulus == 14){
            fputc('e',f);
        }

        if(numbermodulus == 15){
            fputc('f',f);
        }
    }
        if (flag == 0){
        number = number / 16; //else you do it at the end
      }
   }

   return 1;

 }

/**
 * @brief  Read JSON input from a specified input stream, parse it,
 * and return a data structure representing the corresponding value.
 * @details  This function reads a sequence of 8-bit bytes from
 * a specified input stream and attempts to parse it as a JSON value,
 * according to the JSON syntax standard.  If the input can be
 * successfully parsed, then a pointer to a data structure representing
 * the corresponding value is returned.  See the assignment handout for
 * information on the JSON syntax standard and how parsing can be
 * accomplished.  As discussed in the assignment handout, the returned
 * pointer must be to one of the elements of the argo_value_storage
 * array that is defined in the const.h header file.
 * In case of an error (these include failure of the input to conform
 * to the JSON standard, premature EOF on the input stream, as well as
 * other I/O errors), a one-line error message is output to standard error
 * and a NULL pointer value is returned.
 *
 * @param f  Input stream from which JSON is to be read.
 * @return  A valid pointer if the operation is completely successful,
 * NULL if there is any error.
 */
//int argo_lines_read; 
//int argo_chars_read; reset to 0 after each line


 ARGO_VALUE *argo_read_value(FILE *f) { //interally has argo_read_basic

     char variable = fgetc(f);

      if(variable == ARGO_QUOTE){
          argo_read_string(&((argo_value_storage + argo_next_value)->content.string),f);
          argo_next_value = argo_next_value + 1;
      }

      if(variable == ARGO_T){ //for basic True read_basic
          variable = fgetc(f);
          if(variable == ARGO_R){
             variable = fgetc(f);
             if(variable == ARGO_U){
                variable = fgetc(f);
                if(variable == ARGO_E){
                    //set it to something like below
                     (argo_value_storage + argo_next_value) -> content.basic = ARGO_TRUE;
                    argo_next_value = argo_next_value + 1;

                 }
                 else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
            }


      if(variable == ARGO_F){ //for basic False read_basic
          variable = fgetc(f);
          if(variable == 'a'){
             variable = fgetc(f);
             if(variable == 'l'){
                variable = fgetc(f);
                if(variable == 's'){
                    variable = fgetc(f);
                    if(variable == ARGO_E){
                        //set it to something like below
                        (argo_value_storage + argo_next_value) -> content.basic = ARGO_FALSE;
                        argo_next_value = argo_next_value + 1;

                    }
                else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                     return NULL;
                 }
            }


      if(variable == ARGO_N){ //for basic Null read_basic
          variable = fgetc(f);
          if(variable == ARGO_U){
             variable = fgetc(f);
             if(variable == 'l'){
                variable = fgetc(f);
                if(variable == 'l'){
                        //set it to something like below
                    (argo_value_storage + argo_next_value) -> content.basic = ARGO_NULL;
                    argo_next_value = argo_next_value + 1;

                 }
                 else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
                 } else{
                    fprintf(stderr, "invalid basic");
                    return NULL;

                 }
         } 

      if(argo_is_digit(variable) || variable == ARGO_MINUS){ //whens its a digit between 0 - 9 and -
          variable = ungetc(variable, f);
          argo_read_number(&((argo_value_storage + argo_next_value)->content.number),f);
          argo_next_value = argo_next_value + 1;
       } 

    return NULL;
    // TO BE IMPLEMENTED.

}


/**
 * @brief  Read JSON input from a specified input stream, attempt to
 * parse it as a JSON string literal, and return a data structure
 * representing the corresponding string.
 * @details  This function reads a sequence of 8-bit bytes from
 * a specified input stream and attempts to parse it as a JSON string
 * literal, according to the JSON syntax standard.  If the input can be
 * successfully parsed, then a pointer to a data structure representing
 * the corresponding value is returned.
 * In case of an error (these include failure of the input to conform
 * to the JSON standard, premature EOF on the input stream, as well as
 * other I/O errors), a one-line error message is output to standard error
 * and a NULL pointer value is returned.
 *
 * @param f  Input stream from which JSON is to be read.
 * @return  Zero if the operation is completely successful,
 * nonzero if there is any error.
 */
int argo_read_string(ARGO_STRING *s, FILE *f) { //should work 
   char variable = fgetc(f);
    
   s-> capacity = 0;
   s-> content = 0;
   s-> length = 0;


  while(variable != ARGO_QUOTE){
    if(variable == EOF){
        fprintf(stderr,"then it does not terminate"); //non terminating error
        return -1;
    }
    char variable2 = 0;
    int sum2;

    argo_chars_read = argo_chars_read + 1; //1 more char read

    if(variable == ARGO_BSLASH){
        variable2 = fgetc(f); //gets the next 
        argo_chars_read = argo_chars_read + 1; //1 more char read

        switch (variable2){

        case ARGO_BSLASH: //Escape character 
            argo_append_char(s, ARGO_BSLASH); //stores it
            //action you do if this case
            break;
        
        case ARGO_QUOTE: //quotes character 
            argo_append_char(s, ARGO_BSLASH); //stores it
            //action you do if this case
            break;
        
        case ARGO_B: // \b
            argo_append_char(s, ARGO_BS); //stores it
            //action you do if this case

            break;
        
        case ARGO_F: // \f
            argo_append_char(s, ARGO_FF); //stores it

            break;
        
        case ARGO_N: // \n
            argo_append_char(s, ARGO_LF); //stores it
            //action you do if this case

            break;
        
        case ARGO_R: // \r
            argo_append_char(s, ARGO_CR); //stores it
            //action you do if this case

            break;

        case ARGO_T: // \t
            argo_append_char(s, ARGO_HT); //stores it
            //action you do if this case
            break;

        case ARGO_U: // \u
            sum2 = 0;
            for(int i=3; i >= 0; i--){ //checks it while adding in one go
                variable2 = fgetc(f);

                if(variable2 >='0' && variable2 <='9'){
                    variable2 = (int)variable2 - 48;
                    sum2 = sum2 + exponentcalc(i,variable2);

                    continue;
                }

                if((variable2 == 'a') || (variable2 == 'A')){
                    int a = 10;
                    sum2 = sum2 + exponentcalc(i,a);                   
                    continue;

                }

                if(variable2 == ('b' || 'B')){
                    int b = 11; 
                    sum2 = sum2 + exponentcalc(i,b);
                    continue;
                    
                }               
            
                if(variable2 == ('c' || 'C')){
                    int c = 12;
                    sum2 = sum2 + exponentcalc(i,c);
                    continue;
                    
                }
                if(variable2 == ('d' || 'D')){
                    int d = 13;
                    sum2 = sum2 + exponentcalc(i,d);
                    continue;
                    
                }

                if(variable2 == ('e' || 'E')){
                    int e = 14;
                    sum2 = sum2 + exponentcalc(i,e);
                    continue;
                    
                }

                if(variable2 == ('f' || 'F')){
                    int f = 15;
                    sum2 = sum2 + exponentcalc(i,f);
                    continue;
                    
                }

                else{
                    fprintf(stderr, "after u checking error");
                    return -1; // when error 

                }
            
            }
            argo_append_char(s, sum2); //st
            break;
        }
      variable = fgetc(f);
        continue;   
     }

     else {
        argo_append_char(s, variable); //stores it
        continue;

     }
  }

    return 0;
    // TO BE IMPLEMENTED.
}

/**
 * @brief  Read JSON input from a specified input stream, attempt to
 * parse it as a JSON number, and return a data structure representing
 * the corresponding number.
 * @details  This function reads a sequence of 8-bit bytes from
 * a specified input stream and attempts to parse it as a JSON numeric
 * literal, according to the JSON syntax standard.  If the input can be
 * successfully parsed, then a pointer to a data structure representing
 * the corresponding value is returned.  The returned value must contain
 * (1) a string consisting of the actual sequence of characters read from
 * the input stream; (2) a floating point representation of the corresponding
 * value; and (3) an integer representation of the corresponding value,
 * in case the input literal did not contain any fraction or exponent parts.
 * In case of an error (these include failure of the input to conform
 * to the JSON standard, premature EOF on the input stream, as well as
 * other I/O errors), a one-line error message is output to standard error
 * and a NULL pointer value is returned.
 *
 * @param f  Input stream from which JSON is to be read.
 * @return  Zero if the operation is completely successful,
 * nonzero if there is any error.
 */

int argo_read_number(ARGO_NUMBER *n, FILE *f) {
    // TO BE IMPLEMENTED.
    char variable = getc(f); //gets the first number
    int flag = 0;

    if(variable == ARGO_MINUS){
        flag = 10;
        argo_append_char(&(n->string_value), variable); //appends the - char
        variable = getc(f); //goes to next 
    }

    int sumofint = 0;
    variable = ungetc(variable,f);
    argo_append_char(&(n->string_value), variable); //appends the char

    while(variable != ARGO_E || variable != ARGO_PERIOD){ //for integers basically
        
        variable = getc(f); //gets the first number
        argo_append_char(&(n->string_value), variable); //appends the ints

        if((variable == ARGO_E) || variable == ARGO_PERIOD){
            break;
        }

        if((variable != ARGO_E) && (variable != ARGO_PERIOD)){
            if((variable < '0') || (variable > '9')){
                 n -> int_value = variable;
                 if (flag == 10){
                     sumofint = sumofint * -1;
                     n ->int_value = sumofint;
                     n->valid_int = 2;
                     return 0; //exits here for negative
                  }
                 n ->int_value = sumofint;
                 //1 exit
                 return 0;
            }
        }

        sumofint = (sumofint * 10) + (variable - 48); //adding it up for the int first
        //argo_append_char(n->string_value.content, variable); //appends the char
    }

    double sumfordecimal = 0;
    double counter = 0;
    double power = 1;
    double counterforaftere = 0;
    double power3 = 1;

    if(variable == ARGO_PERIOD){ //conditions for . basically
        variable = getc(f);
        argo_append_char(&(n->string_value), variable); //appends the .

        if(!(argo_is_digit(variable))){
            fprintf(stderr,"nothing after .");
            return -1;   
        }

        double sumfinaldec = 0;
     //continue writing code for this float stuff
        while(argo_is_digit(variable)){
            sumfordecimal = (sumfordecimal * 10) + (variable - 48); //prints the sum of everything after the decimal point
            variable = getc(f);
            argo_append_char(&(n->string_value), variable); //appends the decimal chars
            counter = counter + 1;
            if(variable == ARGO_E){
                break;
            }
        }
            if((variable != ARGO_PLUS && (variable != ARGO_MINUS) && (variable != ARGO_E))){

                for(int i=0; i < counter; i++){
                    power = power * 10;
                }
                sumfinaldec = sumofint + (sumfordecimal / power); //this for decimal such as 526.2562 
                if (flag == 10){
                    sumfinaldec = sumfinaldec * -1;
                     n ->float_value = sumfinaldec;
                     n->valid_float = 2;
                     return 0; //exits here for negative decimal
                  }
                   n ->float_value = sumfinaldec;
                    n->valid_float = 2;

                return 0;
            }

            if((variable == ARGO_PLUS) || (variable == ARGO_MINUS) || (variable
             == ARGO_E)){ //51415.53e12 for working on this
                //exits as a decimal
                for(int i=0; i < counter; i++){
                    power = power * 10;
                }
                double sumfinaldec = sumofint + (sumfordecimal / power); //this for decimal such as 526.2562 

                if(variable == ARGO_E){ //calculating for this case
                    variable = getc(f);
                    
                  if((variable != ARGO_PLUS) && (variable != ARGO_MINUS)){
                
                    if(!(argo_is_digit(variable))){
                        fprintf(stderr,"nothing after e+ or e-");
                        return -1;
                    }
                    variable = ungetc(variable, f);

                    while(argo_is_digit(variable)){

                        variable = getc(f);
                        argo_append_char(&(n->string_value), variable); //appends the decimal chars

                     if (!argo_is_digit(variable)){
                            break;
                        }
                        counterforaftere = (10*counterforaftere) + (variable-48);
          
                    } 
                        for(int i=0; i < counterforaftere; i++){
                            power3 = power3 * 10;
                        }
                        
                        double finalvalue = power3 * sumfinaldec;
                          if (flag == 10){
                            finalvalue = finalvalue * -1;
                            n->float_value = finalvalue;
                            n->valid_float = 2;

                            return 0; //exits here for negative 515.25e5
                       }
                         n->float_value = finalvalue;
                        n->valid_float = 2;

                        return 0; //1 exit
                        //here it should work with no + - but you have . and e 
                      }

                    if((variable == ARGO_PLUS) || (variable == ARGO_MINUS)){
                        
                        if(variable == ARGO_PLUS){
                            variable = getc(f);
                            argo_append_char(&(n->string_value), variable); //appends the +
                        if(!(argo_is_digit(variable))){
                            fprintf(stderr,"nothing after e+ or e-");
                            return -1;
                        }
                        variable = ungetc(variable, f);

                        while(argo_is_digit(variable)){
                            variable = getc(f);
                            argo_append_char(&(n->string_value), variable); //appends the characters after

                            if (!argo_is_digit(variable)){
                                    break;
                            }
                                counterforaftere = (10*counterforaftere) + (variable-48);
          
                        }        
                            for(int i=0; i < counterforaftere; i++){
                                power3 = power3 * 10;
                            }

                            double finalvalue = power3 * sumfinaldec;
                            if (flag == 10){
                                finalvalue = finalvalue * -1;
                                n->float_value = finalvalue;
                                 n->valid_float = 2;

                                return 0; //exits here for negative 25e5
                       }
                            n->float_value = finalvalue;
                            n->valid_float = 2;

                                return 0; //1 exit
                        //here it should work with no + - but you have . and e 
                      }
                
                        if(variable == ARGO_MINUS){

                            variable = getc(f);
                            argo_append_char(&(n->string_value), variable); //appends the -
                            if(!(argo_is_digit(variable))){
                                fprintf(stderr,"nothing after e+ or e-");
                                return -1;
                            }
                            variable = ungetc(variable, f);

                            while(argo_is_digit(variable)){

                                variable = getc(f);
                                argo_append_char(&(n->string_value), variable); //appends the char

                            if (!argo_is_digit(variable)){
                                    break;
                                }
                                counterforaftere = (10*counterforaftere) + (variable-48);
          
                            }        
                                for(int i=0; i < counterforaftere; i++){
                                    power3 = power3 * 10;
                                }

                                double finalvalue = sumfinaldec / power3;
                                if (flag == 10){
                                    finalvalue = finalvalue * -1;
                                    n->float_value = finalvalue;
                                    n->valid_float = 2;

                                    return 0; //exits here for negative 25e5
                        }
                                n->float_value = finalvalue;
                                n->valid_float = 2;

                                    return 0; //1 exit
                        //here it should work with no + - but you have . and e 
                                    }
                                }

                            }

                    }
               }

    double sumfinal = sumofint + (sumfordecimal / power);

    double sum3 = 0;
    double power2 = 1;

    if(variable == ARGO_E){ //conditions for e technically also a float
        argo_append_char(&(n->string_value), variable); //appends the e

        variable = getc(f); //0.525e

        if(!(argo_is_digit(variable)) && (variable == !(ARGO_PLUS)) && (variable == !(ARGO_MINUS))){ //if its not a digit , + , or - error
            fprintf(stderr,"nothing after e");
            return -1;
        } 

          if((variable != ARGO_PLUS) && (variable != ARGO_MINUS)){
              if(!(argo_is_digit(variable))){
                    fprintf(stderr,"nothing after e+ or e-");
                    return -1;
              }else{
                variable = ungetc(variable,f);
                while(argo_is_digit(variable)){

                    variable = getc(f);
                    argo_append_char(&(n->string_value), variable); //appends the nums

                    if(!argo_is_digit(variable)){
                        break;
                    }
                    counterforaftere = (10*counterforaftere) + (variable-48);
          
                }        
                    for(int i=0; i < counterforaftere; i++){
                        power2 = power2 * 10;
                     }   
     
                     double finalvalue = power2 * sumfinal;
                     if (flag == 10){
                            finalvalue = finalvalue * -1;
                            n->float_value = finalvalue;
                             n->valid_float = 2;

                            return 0; //exits here for negative 25e5
                       }

                        n->float_value = finalvalue;
                        n->valid_float = 2;

                     return 0; //should end here
                        //here it should work with no + - but you have . and e 

              }   
          }

          if(variable == ARGO_PLUS || variable == ARGO_MINUS){
             argo_append_char(&(n->string_value), variable); //appends the + or -

            if(variable == ARGO_PLUS){
                variable = getc(f);
                if(!(argo_is_digit(variable))){
                    fprintf(stderr,"nothing after e+ or e-");
                    return -1;
                }
                variable = ungetc(variable, f);

                 while(argo_is_digit(variable)){

                    variable = getc(f);
                    argo_append_char(&(n->string_value), variable); //appends the nums

                    if(!argo_is_digit(variable)){
                        break;
                    }
                    counterforaftere = (10*counterforaftere) + (variable-48);
          
                  }        
                    for(int i=0; i < counterforaftere; i++){
                        power2 = power2 * 10;
                     }   
                     double finalvalue = power2 * sumfinal;
                     if (flag == 10){
                            finalvalue = finalvalue * -1;
                            n->float_value = finalvalue;
                             n->valid_float = 2;

                            return 0; //exits here for negative 25e5
                       }
                        n->float_value = finalvalue;
                        n->valid_float = 2;

                     return 0; //should end here
                        //here it should work with no + - but you have . and e 
                   }
                
            if(variable == ARGO_MINUS){
               variable = getc(f);
                if(!(argo_is_digit(variable))){
                    fprintf(stderr,"nothing after e+ or e-");
                    return -1;
                }
                variable = ungetc(variable,f);

                while(argo_is_digit(variable)){

                    variable = getc(f);
                    argo_append_char(&(n->string_value), variable); //appends the nums

                    if(!argo_is_digit(variable)){
                        break;
                    }
                    counterforaftere = (10*counterforaftere) + (variable-48);
          
                    }        
                for(int i=0; i < counterforaftere; i++){
                    power2 = power2 * 10;
                    }   

                  double finalvalue = sumfinal / power2;
                    if (flag == 10){
                            finalvalue = finalvalue * -1;
                        n->float_value = finalvalue;
                            return 0; //exits here for negative 25e5
                       }
                      n->float_value = finalvalue;
                      n->valid_float = 2; //setting the float to valid according to the struct

                    return 0; //should end here
                        //here it should work with no + - but you have . and e 

                }

            }

        }   
    return 0;
}

/**
 * @brief  Write canonical JSON representing a specified value to
 * a specified output stream.
 * @details  Write canonical JSON representing a specified value
 * to specified output stream.  See the assignment document for a
 * detailed discussion of the data structure and what is meant by
 * canonical JSON.
 *
 * @param v  Data structure representing a value.
 * @param f  Output stream to which JSON is to be written.
 * @return  Zero if the operation is completely successful,
 * nonzero if there is any error.
 */

 int argo_write_value(ARGO_VALUE *v, FILE *f) { //Combines all the other helpers to Write
     // TO BE IMPLEMENTED.

     if (v ->type == ARGO_STRING_TYPE){
         argo_write_string(&v->content.string, f);
             //Passing on content.string
             //& gives u address
     }

     if (v ->type == ARGO_BASIC_TYPE){
         argo_write_basic(&v->content.basic,f);
          //Passing on content.basic
          //& gives u address
     }

     if (v ->type == ARGO_NUMBER_TYPE){
         argo_write_number(&v->content.number,f);
         //Passing on content.number
          //& gives u address
     }

     if (v ->type == ARGO_ARRAY_TYPE){
         indent_level = indent_level + 1; 
         argo_write_array(&v->content.array,f);
         //Passing on content.array
          //& gives u address
     }


     if (v ->type == ARGO_OBJECT_TYPE){
         indent_level = indent_level + 1; 
         argo_write_object(&v->content.object,f);
         //Passing on content.object
          //& gives u address
     }


     return 0;
 }

/**
 * @brief  Write canonical JSON representing a specified string
 * to a specified output stream.
 * @details  Write canonical JSON representing a specified string
 * to specified output stream.  See the assignment document for a
 * detailed discussion of the data structure and what is meant by
 * canonical JSON.  The argument string may contain any sequence of
 * Unicode code points and the output is a JSON string literal,
 * represented using only 8-bit bytes.  Therefore, any Unicode code
 * with a value greater than or equal to U+00FF cannot appear directly
 * in the output and must be represented by an escape sequence.
 * There are other requirements on the use of escape sequences;
 * see the assignment handout for details.
 *
 * @param v  Data structure representing a string (a sequence of
 * Unicode code points).
 * @param f  Output stream to which JSON is to be written.
 * @return  Zero if the operation is completely successful,
 * nonzero if there is any error.
 */
int argo_write_string(ARGO_STRING *s, FILE *f) {
    int length = s->length;
    int i = 0; //iterator
    fputc(ARGO_QUOTE,f);

    for(i=0; i < length; i++){
        int *ptr = (s->content + i);
        switch (*ptr){
        case ARGO_SPACE: //space Character
            fputc(ARGO_SPACE,f);
            break;
        
        case ARGO_BSLASH: //Escape character 
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_BSLASH,f);
            break;
        
        case ARGO_QUOTE: //quotes character 
            fputc(ARGO_BSLASH,f); //slash
            fputc(ARGO_QUOTE,f); //quote
            break;
        
        case ARGO_BS: // \b
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_B,f);
            break;
        
        case ARGO_FF: // \f
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_F,f);
            break;
        
        case ARGO_LF: // \n
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_N,f);
            break;
        
        case ARGO_CR: // \r
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_R,f);
            break;

        case ARGO_HT: // \t
            fputc(ARGO_BSLASH,f);
            fputc(ARGO_T,f);
            break;

        default:
            if ((*ptr < 32) || (*ptr > 255)){
                inttohex(ptr,f); //if its in the range then you convert into to hex and display it 
                //you pass in the addres as ptr
            }
            else{
                fputc(*ptr,f);
            }
            break;
     }
  }
    fputc(ARGO_QUOTE,f);
    return 0;
}

/**
 * @brief  Write canonical JSON representing a specified number
 * to a specified output stream.
 * @details  Write canonical JSON representing a specified number
 * to specified output stream.  See the assignment document for a
 * detailed discussion of the data structure and what is meant by
 * canonical JSON.  The argument number may contain representations
 * of the number as any or all of: string conforming to the
 * specification for a JSON number (but not necessarily canonical),
 * integer value, or floating point value.  This function should
 * be able to work properly regardless of which subset of these
 * representations is present.
 *
 * @param v  Data structure representing a number.
 * @param f  Output stream to which JSON is to be written.
 * @return  Zero if the operation is completely successful,
 * nonzero if there is any error.
 */
int argo_write_number(ARGO_NUMBER *n, FILE *f) {

    if(n -> valid_int){ //put it in the array first
    //use remainder % 10 to read it backward
        int count = 0;
        int i = 0;
        long value = (n->int_value); //the full value

        if (value < 0){ //for negative inputs
            value = value * -1;
        }

        for (i=0; i < ARGO_MAX_DIGITS; i++){
            int partofvalue = value%10; //gets the last value

            int converting = partofvalue + ARGO_DIGIT0;
            *(argo_digits + i) = converting; //placing it in the array
            value = value / 10;

            if(value == 0){
                break; //breaks out of the for statement
            }
            count = count + 1;

        }

        for (i=count; i >= 0; i--){
            putc(*(argo_digits + i), f); //puts it in console in a backward fashion

      }
        return 0;

    }
    else if(n -> valid_float){ //precedence comes next
        double floatvalue = n ->float_value; //already reads it with the 0s
        int counter = 0;
        int signflag = 0;

         if(floatvalue < 0){
            floatvalue = floatvalue * -1;
            signflag = 1; //sets a signflag so u can set sign later works like normal
         }
         if(floatvalue == 0){
            fputc(ARGO_DIGIT0,f);
            fputc(ARGO_PERIOD,f);
            fputc(ARGO_DIGIT0,f);
            return 0;
         }

          if(floatvalue >= 1){
        
            while (floatvalue >= 1){
                floatvalue = floatvalue / 10;
                counter = counter + 1;
            }

            double temp = 0;
            int newcounter = 18;

            if(signflag == 1){
                newcounter = newcounter - 1; //decreases iteration by 1 so basically 1 less 0
                fputc(ARGO_MINUS,f); //puts the - sign
            }
            long temp2 = 0;
            fputc(ARGO_DIGIT0,f);
            fputc(ARGO_PERIOD,f);

            while(newcounter > 1){
                floatvalue = floatvalue * 10;
                temp = floatvalue;
                temp2 = (long)temp;
                temp2 = temp2 % 10;
                int convert = temp2 + ARGO_DIGIT0;
                fputc(convert,f);
                newcounter = newcounter - 1;
            }
            fputc(ARGO_E,f);
            counter = counter;
            int quickconvert = counter + ARGO_DIGIT0;
            fputc(quickconvert,f);

          }else if(floatvalue < 1){ //so negative e comes here at the end
                
                floatvalue = floatvalue * 10;

                while (floatvalue <= 1){
                    floatvalue = floatvalue * 10;
                    counter = counter + 1;
                }

                if(counter == 0){
                    fputc(ARGO_DIGIT0,f);
                    fputc(ARGO_PERIOD,f);
                    double temp = 0;
                    long temp2 = 0;
                    floatvalue = floatvalue / 10;
                    int newcounter = ARGO_PRECISION;
                    while(newcounter > 1){
                        floatvalue = floatvalue * 10;
                        temp = floatvalue;
                        temp2 = (long)temp;
                        temp2 = temp2 % 10;
                        int convert = temp2 + ARGO_DIGIT0;
                        putc(convert,f);
                        newcounter = newcounter - 1;

                 }

                    return 0; 
                }

                double temp = 0;
                int newcounter = 17;
                long temp2 = 0;

                if(signflag == 1){
                    newcounter = newcounter - 1; //decreases iteration by 1 so basically 1 less 0
                    fputc(ARGO_MINUS,f); //puts the - sign
                    }
                fputc(ARGO_DIGIT0,f);
                fputc(ARGO_PERIOD,f);
                floatvalue = floatvalue / 10; //so then the next part could work properly

                while(newcounter > 1){
                    floatvalue = floatvalue * 10;
                    temp = floatvalue;
                    temp2 = (long)temp;
                    temp2 = temp2 % 10;
                    int convert = temp2 + ARGO_DIGIT0;
                    putc(convert,f);
                    newcounter = newcounter - 1;

                 }
                 
                fputc(ARGO_E,f);
                fputc(ARGO_MINUS,f);
                int quickconvert = counter + ARGO_DIGIT0;
                fputc(quickconvert,f);
          }
        return 0;
    }  //Conversions for numbers ends here

    else if(n -> valid_string){
        argo_write_string(&(n->string_value),f); //send the address to handle valid_string
    }
    return 0;

    // TO BE IMPLEMENTED.
 } 

int argo_write_basic(ARGO_BASIC *s, FILE *f){
    if(*s == ARGO_NULL){
        fputs(ARGO_NULL_TOKEN,f);
    }

    if(*s == ARGO_TRUE){
        fputs(ARGO_TRUE_TOKEN,f);
    }

    if(*s == ARGO_FALSE){
        fputs(ARGO_FALSE_TOKEN,f);
    }
    return 0;
}

int argo_write_object(ARGO_OBJECT *s, FILE *f){

     ARGO_VALUE *ptr = (s->member_list); //this creates a pointer to the struct
     //this is the head of the structure     
     ARGO_VALUE *ptr2 = (s->member_list->next); //creates a pointer to the next after head
     putc(ARGO_LBRACE,f);
          
     if(global_options > CANONICALIZE_OPTION){
        putc('\n',f);
        pretty_print(f);   
     }

     while(ptr != ptr2){ //when the addresses are = then the circular linked list would be done
        argo_write_string(&(*ptr2).name, f); //call the argo string method, pass the values of the pointer name in
        
        putc(ARGO_COLON,f);
        putc(ARGO_SPACE,f); //1 space

        argo_write_value(ptr2,f); //.next goes to the next element
        ptr2 = ptr2->next; //changes the pointer to next

        if(ptr == ptr2){
            break;
        }else{
            putc(ARGO_COMMA,f);
                 
            if(global_options > CANONICALIZE_OPTION){
                putc('\n',f);
                pretty_print(f);   
     }  
        }    

     }

    indent_level = indent_level - 1;
         
     if(global_options > CANONICALIZE_OPTION){
        putc('\n',f);
        pretty_print(f);   
     }

    if(global_options > CANONICALIZE_OPTION){
        putc(ARGO_RBRACE,f);
        if(indent_level == 0){
            putc('\n',f);
        }
    }

     return 1;
   
}
 //When its a object type you call argo_value again

int argo_write_array(ARGO_ARRAY *s, FILE *f){
    
     ARGO_VALUE *ptr = (s->element_list); //this creates a pointer to the struct
     //this is the head of the structure
     ARGO_VALUE *ptr2 = (s->element_list->next); //creates a pointer to the next after head
     int copyofglobal = global_options;
     int indent = copyofglobal - CANONICALIZE_OPTION - PRETTY_PRINT_OPTION; //contains the indent
     putc(ARGO_LBRACK,f);
     
     if(global_options > CANONICALIZE_OPTION){
        putc('\n',f);
        pretty_print(f);   
     }

     while(ptr != ptr2){ //when the addresses are = then the circular linked list would be done

        argo_write_value(ptr2,f); //.next goes to the next element

        ptr2 = ptr2->next; //changes the pointer to next 

        if(ptr == ptr2){
            break;
        }else{
            putc(ARGO_COMMA,f);
            if(global_options > CANONICALIZE_OPTION){
                putc('\n',f);
            pretty_print(f);   
          }
       
        }
     }
     
     indent_level = indent_level - 1;

    if(global_options > CANONICALIZE_OPTION){
         putc('\n',f);
          pretty_print(f);   
        }
     
     putc(ARGO_RBRACK,f);
     
     if(global_options > CANONICALIZE_OPTION){
        if(indent_level == 0){
            putc('\n',f);
        }
     }

    return 1; 
   
}

int pretty_print(FILE *f){
 
    int copyofglobal = global_options;
    int indent = copyofglobal - CANONICALIZE_OPTION - PRETTY_PRINT_OPTION; //contains the indent
   if (indent == 0){
        indent = 4; //set by default
    }  
    int spaces = indent * indent_level;
    for (int i=0; i < spaces; i++)
        putc(ARGO_SPACE,f);
    return 1;
}
