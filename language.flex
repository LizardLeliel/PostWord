%option noyywrap

DIGIT      [0-9]
NDIGIT     [^0-9]
WSPACE     [\n\t]


%%

{DIGIT}+             {
	             pushInt(atoi(yytext));
		     }
"<<EOF>>"            return;
{NDIGIT}+            printf("");

%%


