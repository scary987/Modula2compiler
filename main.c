#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#define MAXLENGTH 100

char *yytext;
void yyerror(char *msg){
    printf("%s\n",msg);
    exit(EXIT_FAILURE);
}


int is_delimiter(char* word, int length){
    if(length<2||length==8||length>11)
        return 0;
    if(
        strncmp(word,"BY",length)==0||
        strncmp(word,"DO",length)==0||
        strncmp(word,"IF",length)==0||
        strncmp(word,"IN",length)==0||
        strncmp(word,"TO",length)==0||
        strncmp(word,"OF",length)==0||
        strncmp(word,"AND",length)==0||
        strncmp(word,"DIV",length)==0||
        strncmp(word,"END",length)==0||
        strncmp(word,"FOR",length)==0||
        strncmp(word,"MOD",length)==0||
        strncmp(word,"NOT",length)==0||
        strncmp(word,"REM",length)==0||
        strncmp(word,"SET",length)==0||
        strncmp(word,"VAR",length)==0||
        strncmp(word,"CASE",length)==0||
        strncmp(word,"EXIT",length)==0||
        strncmp(word,"FROM",length)==0||
        strncmp(word,"LOOP",length)==0||
        strncmp(word,"THEN",length)==0||
        strncmp(word,"TYPE",length)==0||
        strncmp(word,"WITH",length)==0||
        strncmp(word,"ARRAY",length)==0||
        strncmp(word,"BEGIN",length)==0||
        strncmp(word,"CONST",length)==0||
        strncmp(word,"ELSIF",length)==0||
        strncmp(word,"RETRY",length)==0||
        strncmp(word,"UNTIL",length)==0||
        strncmp(word,"WHILE",length)==0||
        strncmp(word,"EXCEPT",length)==0||
        strncmp(word,"IMPORT",length)==0||
        strncmp(word,"EXPORT",length)==0||
        strncmp(word,"MODULE",length)==0||
        strncmp(word,"RECORD",length)==0||
        strncmp(word,"REPEAT",length)==0||
        strncmp(word,"RETURN",length)==0||
        strncmp(word,"FINALLY",length)==0||
        strncmp(word,"FORWARD",length)==0||
        strncmp(word,"POINTER",length)==0||
        strncmp(word,"PACKEDSET",length)==0||
        strncmp(word,"QUALIFIED",length)==0||
        strncmp(word,"DEFINITION",length)==0||
        strncmp(word,"IMPLEMENTATION",length)==0) 
            return 1;
    return 0;
}

int is_identifier(char* word, int length){
    if (length<2||length>16)
        return 0;
    if(
        strncmp(word,"IM",length)==0||
        strncmp(word,"RE",length)==0||
        strncmp(word,"VAL",length)==0||
        strncmp(word,"ABS",length)==0||
        strncmp(word,"CAP",length)==0||
        strncmp(word,"CHR",length)==0||
        strncmp(word,"INC",length)==0||
        strncmp(word,"INT",length)==0||
        strncmp(word,"MAX",length)==0||
        strncmp(word,"MIN",length)==0||
        strncmp(word,"NEW",length)==0||
        strncmp(word,"NIL",length)==0||
        strncmp(word,"ODD",length)==0||
        strncmp(word,"ORD",length)==0||
        strncmp(word,"CHAR",length)==0||
        strncmp(word,"EXCL",length)==0||
        strncmp(word,"HALT",length)==0||
        strncmp(word,"HIGH",length)==0||
        strncmp(word,"INCL",length)==0||
        strncmp(word,"PROC",length)==0||
        strncmp(word,"REAL",length)==0||
        strncmp(word,"SIZE",length)==0||
        strncmp(word,"TRUE",length)==0||
        strncmp(word,"FALSE",length)==0||
        strncmp(word,"FLOAT",length)==0||
        strncmp(word,"TRUNC",length)==0||
        strncmp(word,"BITSET",length)==0||
        strncmp(word,"LENGTH",length)==0||
        strncmp(word,"LFLOAT",length)==0||
        strncmp(word,"BOOLEAN",length)==0||
        strncmp(word,"COMPLEX",length)==0||
        strncmp(word,"DISPOSE",length)==0||
        strncmp(word,"INTEGER",length)==0||
        strncmp(word,"CARDINAL",length)==0||
        strncmp(word,"CMPLXDEC",length)==0||
        strncmp(word,"LONGREAL",length)==0||
        strncmp(word,"PROTECTION",length)==0||
        strncmp(word,"LONGCOMPLEX",length)==0||
        strncmp(word,"INTERRUPTIBLE",length)==0||
        strncmp(word,"UNINTERRUPTIBLE",length)==0
    )return 1;

    return 0;
}

int is_space(char c){
    if (c ==' '||c=='\t'||c=='\r'||c=='\v'||c=='\f')
        return 1;
    return 0;
}
int is_newline(char c){
    if (c=='\n')
        return 1;
    return 0;
}

int between(int a, int b, int c){
    if (b<=a && a<=c)
        return 1;
    return 0;
}
int is_operator(char* word, int length){
    char fc = word[0];
    if(length>2)
        return 0;

    if (length==1){
        if (
        fc==':'||
        fc==';'||
        fc=='.'||
        fc==','||

        fc=='='||
        fc=='+'||
        fc=='-'||
        fc=='*'||
        fc=='/'||
        fc=='&'||
        fc=='<'||
        fc=='>'||

        fc=='{'||
        fc=='}'||
        fc=='('||
        fc==')'||
        fc=='['||
        fc==']'||

        fc=='#'||
        fc=='|'||
        fc=='~'||
        fc=='^'
        )
            return 1;
        }
        if (length==2){
            if(fc!=':'&&fc!='<'&&fc!='>')
                return 0;
            if (
                strncmp(word,":=",2)==0||
                strncmp(word,"<>",2)==0||
                strncmp(word,"<=",2)==0||
                strncmp(word,">=",2)==0
            ) return 1;

            else
                return 0;
        }
    return 0;
}

int is_number(char* word, int length){ //returns 1 for int, 2 for float, 3 for improper number 
    if(!between(word[0],48,57))
        return 0;
    if(length>1&&word[0]=='0')
        return 3;
    for(size_t i = 1;i<length;i++){
        if(!between(word[i],48,57))
            continue;
        if(word[i]==46){
            int j =i+1;
            for(;j<length;j++){
            if(!between(word[j],48,57))
                continue;
            else
            {
                return 3;
            }
            }
        
        return 2;
        }
    }
    return 1;
}



int main(int argc, char const *argv[])
{   
    FILE *file;
    FILE *out;
    int yycounter=0;
    char c;
    int midword=0;

    if(argc>3){
        yyerror("error: wrong number of parameters");
    }
    if (argc>1){
        file = fopen(argv[1],"r");
        if (file!=NULL){
            //redirect to stdin if given
            freopen(argv[1],"r",stdin);
            }
        else
        {
            yyerror("error: cannot open file for reading");
        }
        
        
    }
    if (argc>2){
        out = fopen(argv[2],"w");
        if(out==NULL){
            yyerror("error: cannot open file for writing");
            exit(EXIT_FAILURE                    &&!is_identifier(yytext,yycounter));
            }
        else
        {   
            //redirect from stdout to file
            freopen(argv[2],"w",stdout);
        }
        
    }

    yytext = (char *) malloc(MAXLENGTH* sizeof(char));

    do
    {   
        if(yytext==NULL){
            yytext = (char *) malloc(MAXLENGTH * sizeof(char));
            printf("%s",yytext);
        }
        c = fgetc(stdin);
        if(c==EOF){
            if(yytext!=NULL)
                free(yytext);
            break;
            }
        if(is_newline(c)){
            if(midword){
                if(
                    !is_operator(yytext,yycounter)
                    &&!is_number(yytext,yycounter)
                    &&!is_delimiter(yytext,yycounter)
                    &&!is_identifier(yytext,yycounter)
                    )   printf("%s\n",yytext);
                if(yytext!=NULL)
                    free(yytext);
                yycounter=0;

                yytext = (char *) malloc(MAXLENGTH * sizeof(char));
            }
            midword = 0;
            continue;
        }
        if(is_space(c)){
            if(midword||c=='\n'){
                    if(
                        !is_operator(yytext,yycounter)
                        &&!is_number(yytext,yycounter)
                        &&!is_delimiter(yytext,yycounter)
                        &&!is_identifier(yytext,yycounter)
                        )   printf("%s\n",yytext);
                yycounter=0;
                free(yytext);
                yytext = (char *) malloc(MAXLENGTH * sizeof(char));

            }
            midword=0;
            continue;
        }
        if(c=='.') //very special case, will probably adjust right here for floats
            continue; //the check for numbers will only return 1 for ints or 0,3 
        if(c==';'){
            midword=0;
            if(yytext){                           
                if(
                    !is_operator(yytext,yycounter)
                    &&!is_number(yytext,yycounter)
                    &&!is_delimiter(yytext,yycounter)
                    &&!is_identifier(yytext,yycounter)
                    ) printf("%s\n",yytext);
            }
            free(yytext);
            yycounter=0;
            yytext = (char *) malloc(MAXLENGTH * sizeof(char));
            continue;

        }
   
        else{
            //maybe check for single-digit operators here
            yytext[yycounter]=c;
            yycounter++;
            midword=1;
        }
        
    } while (1);
    //fclose(file); //causes an intern bug, eof cant be reached

    return 0;
}
