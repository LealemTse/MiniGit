# MiniGit

MiniGit is a minimal, C++-based version control system inspired by Git.

## 🔧 Requirements

- C++17 or higher
- CMake (version 3.10 or above)
- A terminal or shell (Linux/macOS or Git Bash on Windows)
- g++ or clang++

---

## 🛠️ Build Instructions

### Step 1: Clone or open the project in CLion or your terminal.

### Step 2: Build using CMake (if not using CLion)

```bash
./cmake-build-debug/MiniGit init
```
### Then
```bash
./MiniGit init
```
### It should say this 
```bash
Initialized empty MiniGit repository in ./.minigit
```





# 🧩 MiniGit Project Board

## 📌 To Do
- [ ] **[Bitanya]** Set up `.minigit/` directory structure
- [ ] **[Bitanya]** Implement `add(filename)` function with file hashing
- [ ] **[Bitanya]** Implement `commit -m "message"` to save file snapshots
- [ ] **[Lealem]** Implement `log` command to show commit history
- [ ] **[Lealem]** Implement `branch <branch-name>` and store pointers
- [ ] **[Lealem]** Implement `checkout <branch>` or `<commit-hash>`
- [ ] **[Megdelawit]** Design and implement `merge <branch>` using 3-way merge
- [ ] **[Megdelawit]** Handle conflict detection and show conflict messages
- [ ] **[Megdelawit]** Implement command-line interface (parse input)
- [ ] Define and share core data structures (`Commit`, `Blob`, `HEAD`, etc.)
- [ ] Set up file I/O system and helpers (`FileManager` class/module)

## 🚧 In Progress
- [ ] Work on shared `MiniGit` class for managing commit DAG
- [ ] Begin building `.minigit/objects/` and blob storage logic

## 🔍 Code Review
- [ ] Review and test `add()` and `commit()` logic
- [ ] Review merge logic and ensure conflict messages display correctly
