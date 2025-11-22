1. Load a random 5-letter word
## DONE

2. Read user guesses (up to 6 attempts)
Each guess must:
### DONE

3. Implement the comparison logic (core of Wordle)
For each letter:
• correct letter + correct position → green
• correct letter + wrong position → yellow
• letter not in the word → grey
Handle duplicates correctly.

4. Display feedback
Print the colored result for the guess in the console (or symbols if colors aren’t used).

5. Check win/lose conditions
• All letters correct → player wins
• 6 failed attempts → show the hidden word and finish

6. Game loop
Restart game if the player wants another round.