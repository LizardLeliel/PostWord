Postword
========

Postword is a intrepreted, stack-oriented language, inspired by Forth. It aims to make stack-oriented programming simple and natural, and it is my Volta Megathon entry

What does a stack oriented language?
------------------------------------

Most languagees have you create variables, assign values, and with
them, use functions, operators, branching and looping to manipulate the data, and have an output.

Postword does most of that; however, instead of creating variables, data is stored on the stack. You push data by typing a literal:

1 55 72 "Hello World" 3.342 5

After this, your stack will look like: <br>
\[1, 55, 72, "Hello World", 3.342 5\] <br>

And once you have data on the stack, you use operations which pop the data, and push results. Here is what addition, then printing looks like:

27 33 + print

And if this doesn't make sense, just remember, its about pushing data to the stack, and using it. This is what the stack looks like over time: 

\[27\]
\[27, 33\]
\[60\]
\[\]  (This what the stack looks like after its printed!)

Simple, isn't it? And with this, you can add (+), subtract (-),
multiply (*), divide (/), boolean NOT (!!), boolean AND (&&), boolean OR (||), and all the comparison operators (==, !=, <=, >=, <, >).

How do I manage memory then?
----------------------------

But as you can see, how do keep a variable on the stack, push more data, but then get it back? Does everything I need to use only be at the top of the stack? What id I want to remember which values I'm adding?!?

These are all valid questions! Postword won't have variables for awhile, however stack-oriented languages discourages variables. But they do have tools for manipulating memory, and that would be manipulating the stack itself, and these are all done with operators, just as arthemetic and boolean operators. 

Assuming you have a stack of: <br>
\[1, 4, 7, 6\]

And the operators you have are: <br>
?   (duplicate the top of the stack -- \[1, 4, 7, 6, 6\]) <br>
!   (pop the top of the stack -- \[1, 4, 7\]) <br>
\>>> (rotate the stack one to the right -- \[6, 1, 4, 7\]) <br>
\<<< (rotate the stack one to the left -- \[4, 7, 6, 1\]) <br>
^   (swap the top two items -- \[4, 7, 1, 6\]) <br>

With these, you can move things arround, and recover them back when you need them. Suppose this quick fibonacci code:

1 1        \[1, 1\]
  ? >>> +  \[1, 1, 1\] \[1, 1, 1\] \[1, 2\]
  ? >>> +  \[1, 2, 2\] \[2, 1, 2\] \[2, 3\]
  ? >>> +  \[2, 3, 3\] \[3, 2, 3\] \[3, 5\]
  ? >>> +  \[3, 5, 5\] \[5, 3, 5\] \[5, 8\]
print      (Prints: 8)

And, as shown above, combining this way of doing arthmetic as well as doing stack operations, some problems become much simplier to do! Stacks are used in every day life, and using a stack-oriented language will let you look at it in a different light!

More to come!
-------------








