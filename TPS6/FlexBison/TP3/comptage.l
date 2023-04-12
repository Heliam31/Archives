%{
	int nbcar = 0;
	int nbmot = 0;
	int nbligne = 0;
%}

%%
[^\n\t ]+ {nbmot++; nbcar+=yyleng;}
\n {nbcar++; nbligne++;}
. {nbcar++;}
%%

int main(int nbarg, char** argv){
	if(nbarg != 2){
		printf("fichier_in \n");
	}
	yyin = fopen(argv[1], "r");
	while(yylex()!=0);
	printf("nbcar: %i; nbmot: %i; nbligne: %i \n", nbcar, nbmot, nbligne);
}