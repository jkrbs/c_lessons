# Task 12
## Calulator Game

Write a little game that asks the user to add two numbers and gives
him 1 second to respond. When he responded in time, print a congratulation message. If the second has passed and he hasn't responded,
tell the user that he didn't make it and exit.

### Example Runs:
* Success:
```
$ ./calc_game
What is 3 + 7? You have one Second!
10
Success!
```

* Wrong Answer:
```
$ ./calc_game
What is 5 + 2? You have one Second!
12
Wrong answer!
```


* Too slow:
```
$ ./calc_game
What is 5 + 2? You have one Second!
Too slow!
```

### Some Functions you might need

* You can get a number between 1 and 100 using rand() % 100  
  (rand is declared in <stdlib.h>)

* You can wait for one second with sleep(1)
  (sleep is declared in <unistd.h>)

### Hints

* The input handling should be on a separate thread from the waiting,
  since scanf will blocks until the user entered something

### For Experts
* Allow multiple runs of the game without restarting the program,
so the user will get a new question after the first one 
(regardless of whether he failed or not).
If you want also count the Users Score.
