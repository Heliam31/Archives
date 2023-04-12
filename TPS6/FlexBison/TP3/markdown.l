%option noyywrap
%s DANSLISTE

%{ 
    #include<stdio.h>
    int niveau;
    int tab[10];
%}

%%
^\n[ \t]*[-*]{
    BEGIN(DANSLISTE);
    niveau=0:
    tab[niveau]=yyleng-2;
    puts("<ul><li>");
    }
<DANSLISTE>^[ \t]*[*-] {
    puts("</li>");
    int diff=(yyleng-1)-tab[niveau];
    if(diff==0||diff==1){
        puts("<li>");
    }
    else if(diff>=2){
        puts("<ul><li>");
        niveau++;
        tab[niveau]=yyleng-1;
    } else{
        do{
            puts("</ul>");
            niveau--;
        }while(niveau>0 && tab[niveau]>yyleng-1);
        puts("<li>");
    }
}

%%

int main(int nbarg, char** argv){
if(nbarg != 2){
        printf("fichier_in \n");
    }
    yyin = fopen(argv[1], "r");
    while(yylex()!=0);
}