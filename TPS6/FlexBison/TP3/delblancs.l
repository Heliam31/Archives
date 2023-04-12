%option noyywrap

%{ 
    #include<stdio.h>
%}

%%
^[\t ]*\n {}
^[\t ]+ {}
[\t ]+$ {}
[\t ]+ {int c;
		if((c=input())!=EOF && c!=0){
			//printf("<CHAR %c (%d)>", c, c)
			unput(c);
			putchar('_');
			}
		}
%%

int main(){
    int i;
    while((i=yylex()));
}