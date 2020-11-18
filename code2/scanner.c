#include <ctype.h>
#include "buffer.h"
#include "scanner.h"
#include "diagnosis.h"
#include "convience.h"
int yylineno = 1;

/* ADD YOUR CODE HERE */

char next_char(){
    char c;
    while(is_whitespace(c = fgetc(yyin)))
        if(c=='\n')
            yylineno++;

    return c;
}

char non_filter_next_char(){
    char c;
    c = fgetc(yyin); 
    if(c=='\n')
        yylineno++;
    return c;
}


void scanID(){
    char c;   
} /* scan an IDENT or keywords */
int scanNUMBER(){
    char c;
    while (is_whitespace(c=nextchar()));
    while (between(c=next_char(),48,57)) // '0'<c<'9'
    {
        buffer_add(c);
    }
    if(c=='.'){
        while (between(c=next_char(),48,57)) // '0'<c<'9'
        {
            buffer_add(c);
        }
        return 1;
    }
    return 0;
}  /* scan an INTEGER (return 0) or REAL (return 1) */
void scanSTRING(){
    char c;
    while ((c=non_filter_next_char())!='"');
    while ((c=non_filter_next_char())!='"'){
        buffer_add(c);
    }
    buffer_add('"');
    
} /* scan a STRING */
void scanCHAR(){

}   /* scan a CHAR */