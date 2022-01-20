# PARSER TEST
Parser test project written in ansi-c.
The project has a total of 656 lines. Header files are included.

* [About The Project](#about-the-project)
* [Purpose Of Project](#purpose-of-project)
* [Features](#features)
* [Build](#build)
* [Guide](#guide)
* [Bugs](#bugs)


# About The Project
While thinking about programming languages, I began to wonder how parsers work. When I started to research this subject, I had already started to prepare the project while I was thinking if I could prepare a project that would not be too complicated. As a result of my researches, many questions remained in my mind and while I was lost in my thoughts, for a moment "Can I do such a project without using any algorithms or knowledge?" I thought. Afterwards, I liked this idea, so now I could write my own programming language with my own algorithms and rules I would set myself. This is how I started doing this project. I have to admit that this was the project where I developed myself the most. In the first stages of the project, I encountered a lot of problems because I did not know about some subjects such as memory management. I decided to share it on Reddit and shared it immediately. Some of the feedback said that either my own algorithms and rules are silly or that it could be a good project so I can improve myself. I was so excited and made some decisions and plans and made a todo list showing my goals and mistakes. Thus, I started to constantly improve the project and myself. Sometimes I was able to finish the project even though my visas and some university problems came in between. I am proud of the project I have done because I have improved myself both in the C programming language and in compilers. Now I can better understand the working logic of programming languages. In fact, when I looked at the python repository, I was very interested in some of the things they did, because they did almost what I did, or even better. If I want to continue developing this project someday, I will definitely look at other algorithms and information, and even look at languages ​​such as python and lua and develop my project. The best experience I got from this project was that I didn't have to look at other projects or information resources to achieve anything, so I can do well on my own, of course, how successful it can be is a relative thing. Thank you for looking at my project.

# Purpose Of Project
The aim of this project is to understand how parsers in compilers work and to make this project a programming language with the algorithms and rules I have made. In other words, no compiler or parser-related resources were used in this project. Every algorithm or working logic in the project is entirely my own. The purpose of my saying this is that if you are looking for a professional project, this project is not for you, it is more of a trial project.

# Features
* CLI
* Print
* Loop statement
* If statement
* Variables
* Basic calculator
* Comment lines
* File parser (Like python or lua does)

# Build
### Required tools:
* ` gcc ` or ` minigw `
* ` make `

### Building:
* ` cd parser-test/ ` to enter the project folder.
* ` make ` to compile the project.
* ` make clean ` to delete compiled files.


# Guide
### CLI (Command Line Interface)
Execute the compiled file with no argument. Then just write what you want in command line.
- Variables not working.

### Print (Writing in terminal)
Print function need two quotation mark if you want to write a string.
- Example: ` print("foo") `

Printing a variable is simple just write a defined variable. Need '$' symbol before variable name.
- Example:
    ` $foo = "bar" `
    ` print($foo) `

Note: '\0' and '\n' allowed.

### Loop Statement
Loop section only has 'repeat()' function which means can only repeat with certain values.
- Example: ` repeat(12) {print("foo ")} `

### If Statement
If section can only use once in a file. And also part of if else true section doesn't work.
- Only works with variables.
- In comparing variables doesn't need quotation marks.
- Examples: ` $foo == "bar" `
    * ` if($foo == bar:) {print("bar ")} ` Result: bar 
    * ` if($foo == bar:) {print("bar "),print("false ");} ` Doesn't work!
    * ` if($foo == foo:) {print("bar "),print("false ");} ` Result: false 

### Variable
You need just defining a variable. You can use in 'print()', 'repeater()' and 'if()' functions.
- Example: ` $foo = "bar" `

### Basic Calculator
Basic calculator means can't calculate 2 digit numbers. And you can calculate only addition, subtraction, multiplication and division operations.
- Calculating section doesn't need 'print()' function. Because it print itself.
- If result is not digit in division section then result is 0.
- Example:
    * ` (+ 1 2) ` Result: 3
    * ` (- 2 1) ` Result: 1
    * ` (* 2 3) ` Result: 6
    * ` (/ 4 2) ` Result: 2
    * ` (/ 3 2) ` Result: 0
    * ` (+ 1 2 3) ` Result: 6
    * ` (+ 1 2 3 4) ` Result: 10

### Comment
Comment section is like python does. Comment symbol is '#'
- Example: ` print("foo") # This is comment line. `

### File Parser
File parser doesn't compile just executing a file like python or lua does.
- No need a file extension.
- Example:
    * ` acc.exe test/print `
    * ` ./acc demo/all_in_one`

### **Note: Parser may be sensitivity to the placement of spaces!**

# Bugs
* If else true statement not working.
* Can only use one if statement in files.
* If last line of file was not empty then last line doesn't work.
* In calculator section if didn't add space to last letter then last number doesn't calculating.
