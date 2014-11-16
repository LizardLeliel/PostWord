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
"true"[ \t\n]			{
				if (pushTrue()) return -1;
				}
"false"[ \t\n]			{
				if (pushFalse()) return -1;
				}
"!!"[ \t\n]			{
				if (stackNot()) return -1;
				}
"&&"[ \t\n]			{
				if (stackAnd()) return -1;
				}
"||"[ \t\n]			{
				if (stackOr()) return -1;
				}
"<"[ \t\n]			{
				if (stackLessThen()) return -1;
				}
"<="[ \t\n]			{
				if (stackLessEq()) return -1;
				}
">"[ \t\n]			{
				if (stackMoreThen()) return -1;
				}
">="[ \t\n]			{
				if (stackMoreEq()) return -1;
				}
"=="[ \t\n]			{
				if (stackEqual()) return -1;
				}
"!="[ \t\n]			{
				if (stackInequal()) return -1;
				}
"print"[ \t\n]			{
				if (printTop()) return -1;
				}
"prints"[ \t\n]			{
				if (printsTop()) return -1;
				}
"puts"[ \t\n]			{
				if (putsTop()) return -1;
				}
"???"[ \t\n]			{
				if (pushStackLength()) return -1;
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


