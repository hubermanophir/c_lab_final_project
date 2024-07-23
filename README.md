# C Lab Final

This project was written in c its pupose is to "demo" part of code compilation, the part of taking text in this example its an imaginary assebmly files with its own set of rules set by the course.


# The structure
The project is devided to 4 sections

## Preprocessor
The preprocessor purpose is to spread the macros defined in the .as file, and to make sure there are no syntax errors withing the macros definition/implementation

## Front
The front side is code that takes each line of "assembly" code and tranforms its to easy to use struct which is the `Object_Line` 
Here we check for syntax errors and logic errors within each line, meaning for each instuction line has its own possible operands: Some have different source, and target operands, some dont have either.
and for derective lines we check for valid data input

## Middle
The middle part is doing two passes on the file and converts each line to the easy to use object we defined in the front
In the first pass we check if there are any syntax/logic errors within the line and we build our Symbols table.
This table contains each and every label definition in the file:
`MAIN:   add r3, LIST`
`.extern LIST`
Here we also check for logic errors regarding symbol definition, meaning an extern label cannot be defined in this file ...
Here we also fill the `data_image`

The second pass uses the syntax table we built on the first pass to make sure in each place we use a label as an operand we can have its exact location in memory and we fill the `code_image`

## File assembler
This part takes the `data_image` and `code_image` along with the `IC` and `DC` from the middle part and create 3 files:
1. .obj file - binary code converted to octa 5 base for each line of code and each operand
2. .ext file - file contaning all the external files with their names and addresses in memory which have been used
3. .ent file - contains all the .entry  labels and the memory place they were defined at


