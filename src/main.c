#include <stdio.h>
#include <stdlib.h>

#include "argo.h"
#include "global.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char **argv)
{

    if(validargs(argc, argv))
        USAGE(*argv, EXIT_FAILURE);
    if(global_options == HELP_OPTION)
        USAGE(*argv, EXIT_SUCCESS);

    if(global_options == VALIDATE_OPTION){
        if(argo_read_value(stdin)){
            return EXIT_SUCCESS;
        }else{
            return EXIT_FAILURE;
        }
    }

    if(global_options >= CANONICALIZE_OPTION){
        ///argo_write_value(argo_read_value(stdin),stdout);
        ARGO_VALUE* ptr = argo_read_value(stdin);
        if(ptr == NULL){
            return EXIT_FAILURE;
        }else{
            if(argo_write_value(ptr,stdout) == 0){
                return EXIT_SUCCESS;
            }else{
                return EXIT_FAILURE;
            }
        }
    }
    
    //if(global_options == CANONICALIZE_OPTION)
        //argo_read_value is the data structure and stdout is the file that it writes too

    // TO BE IMPLEMENTED
    return EXIT_FAILURE;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
