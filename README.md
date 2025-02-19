# Hex Board Analysis Project

## Description

This project analyzes the state of a **Hex** board in **C++**, supporting board sizes from **1x1 to 11x11**. It provides functionality to evaluate given board states and determine statistics for the hex game state.

### Features:

- Determine board size
- Count placed pawns
- Validate board correctness
- Check if the game is over and which player won
- Verify if a board state is possible

---

## Input & Output

### Example Input:

```
          ---
       --< b >--
    --< r >-< b >--
 --< r >-< r >-< b >--
< b >-< b >-< r >-< b >
 --< r >-< b >-< b >--
    --< r >-< r >--
       --< r >--
          ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE
```

### Example Output:

```
4

16

YES

YES RED

NO
```

---

## Compilation & Execution

1. Compile with **g++**:
   ```bash
   g++ -o hex main.cpp
   ```
2. Run the program:
   ```bash
   ./hex < input.txt
   ```

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---
