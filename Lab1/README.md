DESCRIPTION
This program is a simple math quiz game written in C. It asks the user 10 division questions and keeps track of how many answers are correct.

HOW IT WORKS
The program uses random numbers to create each question.

For every question (10 times total):
  It chooses two random numbers:
    x is between 1 and 12
    y is between 0 and 12
  It calculates z = x * y.
  It then asks the user: “z / x is equal to?”
    Since z = x * y, the correct answer is y.
  The user types their answer.
  If the answer matches y:
    The program prints “Correct” and increases the score.
  If the answer is wrong:
    The program prints “Incorrect” and shows the correct answer.

After 10 questions, the program prints the user’s total score.

HOW TO RUN
Save the program in a file, for example: lab.c

Compile the program (example using gcc):
  gcc quiz.c -o quiz

Run the program:
  ./quiz
