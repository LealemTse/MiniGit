# MiniGit

MiniGit is a minimal, C++-based version control system inspired by Git.
## Features

- `init` – initialize a new MiniGit repository
- `add` – stage files for the next commit
- `commit` – snapshot changes with a message and author
- Persists staged files between runs (like Git's index)

---
##  Requirements

- A terminal or shell (Linux/macOS or Git Bash on Windows)
- g++ or clang++

---

## 🛠️ How to Compile

Use `g++` to compile on any platform run:

```bash
g++ -std=c++17 main.cpp Repository.cpp -o MiniGit
```
For windows user it will creat an .exe file but for linux /MacOs use it will make the main file excutable. 
To creates a hidden .minigit/ folder for tracking changes:
```bash
./MiniGit init
```
To add the file in to the minigit:
```bash
./MiniGit add <filename>
```
To commit what you made:
```bash
./MiniGit commit -m "your commit message"
```
When doing this it will ask for who made the commit as:
```bash
Enter author name:
```
you simply have enter your name:
##Example
```bash
g++ -std=c++17 main.cpp Repository.cpp -o MiniGit
./MiniGit init
./MiniGit add hello.txt
./MiniGit commit -m "Add hello.txt"

```
To Remove the init file run the following:

###For linux/MacOS
```bash
rm -rf .minigit
```

###For windows
```bash
rmdir /s /q .minigit
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
