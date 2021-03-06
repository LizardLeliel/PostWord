Postword
========

Postword is a intrepreted, type-checked, stack-oriented language; inspired by Forth. It aims to make stack-oriented programming simple and natural, and it is a Hackathon competition entrance (Volta Megathon 2014). It was written with intentions to learn and to have some fun; and a more complete (and cleaner) version of the project is planned to take over from this.

What is a stack-oriented language?
----------------------------------

Most languagees have you create variables, assign values, and with
them, use functions, operators, branching and looping to manipulate the data, and have an output.

Postword does most of that; however, instead of creating variables, data is stored on the stack. You push data by typing a literal:

1 55 72 "Hello World" 3.342 5

After this, your stack will look like: <br>
\[1, 55, 72, "Hello World", 3.342, 5\] <br>

And once you have data on the stack, you use operations which pop the data, and push results. Here is what addition, then printing looks like:

27 33 + print

And if this doesn't make sense, just remember, its about pushing data to the stack, and using it. This is what the stack looks like over time: 

\[27\] <br>
\[27, 33\] <br>
\[60\] <br> 
\[\]  (This what the stack looks like after its printed!)

Simple, isn't it? And with this, you can add (+), subtract (-),
multiply (*), divide (/), boolean NOT (!!), boolean AND (&&), boolean OR (||), and all the comparison operators (==, !=, <=, >=, <, >). A full detailed list of what operators it supports at the bottom

How do I keep track of values then?!?
-------------------------------------

But as you can see, how do keep a variable on the stack, push more data, but then get it back? Does everything I need to use only be at the top of the stack? What id I want to remember which values I'm adding?!?

These are all valid questions! Postword won't have variables for awhile, however stack-oriented languages discourages variables. But they do have tools for manipulating memory, and that would be manipulating the stack itself, and these are all done with operators, just as arthemetic and boolean operators. 

Assuming you have a stack of: <br>
\[1, 4, 7, 6\]

Then these are the operators, and what they do to the above stack: <br>
?   (duplicate the top of the stack -- \[1, 4, 7, 6, 6\]) <br>
!   (pop the top of the stack -- \[1, 4, 7\]) <br>
-> (rotate the stack one to the right -- \[6, 1, 4, 7\]) <br>
<\- (rotate the stack one to the left -- \[4, 7, 6, 1\]) <br>
\<\->   (swap the top two items -- \[4, 7, 1, 6\]) <br>

With these, you can move things arround, and recover them back when you need them. Suppose this quick fibonacci code:

1 1        ( \[1, 1\] ) <br>
  ? -> +  ( \[1, 1, 1\] \[1, 1, 1\] \[1, 2\] ) <br>
  ? -> +  ( \[1, 2, 2\] \[2, 1, 2\] \[2, 3\] ) <br>
  ? -> +  ( \[2, 3, 3\] \[3, 2, 3\] \[3, 5\] ) <br>
  ? -> +  ( \[3, 5, 5\] \[5, 3, 5\] \[5, 8\] )<br>
print      (Prints: 8)

And, as shown above, combining this way of doing arthmetic as well as doing stack operations, some problems become much simplier to do! Stacks are used in every day life, and using a stack-oriented language will let you look at it in a different light!

Documentation
-------------

This section describes what you can do!

Supported data types:

Integers (pushed by a whole value; no decimal places, including .0) <br>
Doubles  (pushed by having a number with a decimal place and a number on both sides) <br>
Booleans (pushed by true or false; they will be outputted as "ture or false") <br>
Strings  (pushed by typing in a series of letters delimited by quote marks: no escape characters, no implicit line continuation (or explicit, for that matter <br>

Output: <br>

print  (prints value) <br>
prints (prints value with a following space) <br>
puts   (prints value with a following newline) <br>

Arthmetic operators: <br> 
\+ Addition (n1 n2 -- n1+n2) <br>
\- Subtraction (n1 n2 -- n2-n1) (Note: this is a little different from most other implementations of stack langauges as of this update) <br>
\* Multiplication (n1 n2 -- n1*n2) <br>
/ Division (n1 n2 -- n2/n1) (Note: As subtraction, this isn't the usual (n1 n2 -- n1/n2) implementation) <br>
% Modulus  (d1 d2 -- d2%d1) (Note: same as above)

Stack operators: <br>
? dupplication (n -- n n) <br>
! pop/drop     (n1 n2 -- n1) <br>
<\- left rot   (nf n(f-1) .... n3 n2 n1 -- n(f01) .... n3 n2 n1 nf) <br>
-\> right rot  (nf n(f-1) .... n3 n2 n1 -- n1 nf n(f-1) .... n3 n2) <br>
<\-> swap      (n1 n2 -- n2 n1) <br>

Boolean operators: <br>
&& Boolean AND (b1 b2 -- b1&&b2) <br>
!! Boolean NOT (b1 -- !b1) <br>
|| Boolean OR  (b1 b2 -- b1||b2) <br>

Comparison operators: <br>
<\ Less then       (n1 n2 -- n2 <\  n1) <br>
<= Less then or eq (n1 n2 -- n2 <\= 21) <br>
\> More then       (n1 n2 -- n2 >  n1) <br>
=> More then or eq (n1 n2 -- n2 => n2) <br>
== Equal to       (n1 n2 -- n1 == n2) <br>
!= Not equal to    (n1 n2 -- n1 != n2) <br>

Note: ANYTHING (pushing a data type, output keyword, operators) must be followed by atleast one white space





