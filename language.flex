%option noyywrap

INT        [0-9]
NDIGIT     [^0-9]

%%

{INT}+[ \t\n]                   {
	             	        pushInt(atoi(yytext));
		     	        }
{INT}+"."{INT}+[ \t\n]          {
				pushFloat(atof(yytext));
				}

"+"[ \t\n]			{
				if (stackAdd()) return -1;
				}
"-"[ \t\n]			{
				if (stackSub()) return -1;
				}
"*"[ \t\n]			{
				if (stackMul()) return -1;
				}
"/"[ \t\n]			{
				if (stackDiv()) return -1;
				}

"<<EOF>>"            	 return 0;

%%


