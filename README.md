# ♠️♦️ Rummy Card Game Simulation (C++)

This project is a simulation of the classic card game **Rummy** (also called "Score" game), built in **C++**.  
It features **human vs. computer** gameplay where the goal is to **minimize your hand value** by replacing high-value cards and strategically calling showdowns.

---

## 🎮 Game Rules

1. **Deck & Cards**
   - Standard 52-card shuffled deck.  
   - Suits: Hearts ♥, Diamonds ♦, Clubs ♣, Spades ♠.  
   - Card values:  
     - **Ace (Rank 1):** 1 point  
     - **Cards 2–8:** Face value  
     - **9, 10, Jack, Queen:** Face value  
     - **King:** 20 points  
     - **Joker:** 0 points  

2. **Game Flow**
   - Each player starts with **4 cards**.  
   - On their turn, players may **replace their highest-value card** with a new one from the deck.  
   - Players can call a **Showdown** to compare hand values:  
     - If the caller’s hand value is lower → caller scores **0**.  
     - Others add their hand value to their score.  
     - If the caller’s hand value is equal or higher → caller gets a **30-point penalty**.  
   - A player is eliminated once they reach the **target score**.  
   - The **last player remaining wins**.  

3. **Computer as a Player**
   - Decides moves based on its **hand value** and **random chance**.  
   - May replace high-value cards or call a showdown.  
   - Throws in **taunts** after its moves. 😏  

4. **End Game**
   - The player who reaches the target score first **loses**.  
   - Game exits with a **“You lost”** or **“You won”** message.  

---

## 🖥️ Code Structure

- **`Card`** → Represents a card (suit, rank, value).  
- **`Deck`** → Manages the 52-card deck (shuffle using Fisher–Yates).  
- **`Player`** → Stores up to 4 cards, calculates hand values, replaces cards.  
- **`GameManager`** → Controls turns, showdown logic, computer AI, and win/lose conditions.  

---

## ⚙️ Setup & Compilation Notes  

⚠️ **Important:** This game may not run smoothly on the default settings of Dev-C++ 5 or VS Code.  

### For Dev-C++ 5
1. Go to **Compiler Options**.  
2. Open the **Settings** tab.  
3. Go to **Code Generation**.  
4. Under **Language standard (-std)** → Select **ISO C++11**.  
5. Press **OK** and recompile.  

### For VS Code
- Some users may face compilation errors.  
- Make sure you are compiling with:  
  ```bash
  g++ -std=c++11 rummy.cpp -o rummy
  ./rummy
