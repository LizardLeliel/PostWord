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
"!"[ \t\n]			{
				if (pop()) return -1;
				}
"?"[ \t\n]			{
				if (stackDup()) return -1;
				}
"<->"[ \t\n]			{
				if (stackSwap()) return -1;
				}
"<-"[ \t\n]			{
				if (stackLROT()) return -1;
				}
"->"[ \t\n]			{
				if (stackRROT()) return -1;
				}
"("        {
            register int c;

            for ( ; ; )
                {
                while ( (c = input()) != ')' &&
                        c != EOF )
                    ;    /* eat up text of comment */

                if ( c == ')' )
                    {
		    break;
  		    }
                if ( c == EOF )
                    {
                    printf("End of file while parsing comment");
		    return -1;
                    }
                }
            }
"<<EOF>>"            	 return 0;

%%


