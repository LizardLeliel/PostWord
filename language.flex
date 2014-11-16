%option noyywrap

INT        [0-9]
NDIGIT     [^0-9]

%%

{INT}+[ \t\n]                      {
	             	           pushInt(atoi(yytext));
		   	 	   printf("debugging, int");
		     	           }
{INT}+"."{INT}+[ \t\n]             {
				   pushFloat(atof(yytext));
				   printf("debugging, float");
				   }

"+"[ \t\n]			   {
				   stackAdd();
				   printf("Add");
				   }




"<<EOF>>"            	 return 0;

%%


