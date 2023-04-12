
%option noyywrap

%{ 
    #include<stdio.h>
%}

%%

if {return 300;}

else {return 301;}

then {return 302;}

throw {return 303;}

([1-9][0-9]*)|0 {return 304;}

0[0-7]* {return 304;}

0x[0-9a-fA-F]* {return 304;}

([0-9]+\.[0-9]*|\.[0-9]+)([eEdD][+|-]?[0-9]+)? {return 305;}

[A-Za-z"_"][A-Za-z"_"0-9]* {return 307;}

[" "|\t|\n|\r|\f] {/*rien*/} 

"//".*\n {/*rien*/}

"/""*"[[^*]*"*"+[^*/]]*[^*]*"*"+"/" {/*rien*/}

. {return -1; /* ret un jeton pour tout le reste */ }

%%


int main() {
    union{int i; char* s; float f}
    printf("Saisir un truc :");
    int j;
    char* i;
    while ((j=yylex())!=0){
    if (j==300){i="IF";}
    else if (j==301){i="ELSE";}
    else if (j==302){i="THEN";}
    else if (j==303){i="THROW";}
    else if (j==304){i="INT";}
    else if (j==307){i="ID";}
    else if (j==308){i="FLOAT";}
    printf("%i",j);
    printf("\nJeton : %s; de lexeme %s\n",i,yytext);}
}