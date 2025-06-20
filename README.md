# 🧩MiniGit

SECTION 4

Bitanya Damtew UGR/9112/16

Lealem Tsehay UGR/8061/16

Megdelawit Aynalem UGR/5929/16

Video Demo:
https://drive.google.com/file/d/1V8k-XjgHlu3a8gUs05cYC_9Wci0EI0_w/view?usp=sharing

the Video is in this zip file 

MiniGit is a minimal, C++-based version control system inspired by Git.
## Features

- `init` – initialize a new MiniGit repository
- `add` – stage files for the next commit
- `commit` – snapshot changes with a message and madeby
- `log` - see all the detail of the file commited
- `branch` - where one is working on and create a new branch to work on
- `checkout` - jump over to another branch and checkout or work there
- `merge` - merges branches together
- `diff` - shows the diffrenc between two files.

---
##  Requirements

- A terminal or shell (Linux/macOS or Git Bash on Windows)
- g++ or clang++

---

## 🛠️ How to Compile

Use `g++` to compile on any platform run:

```bash
g++ -std=c++17 main.cpp Repository.cpp log.cpp branch.cpp checkout.cpp merge.cpp -o MiniGit

```
For windows user it will creat an .exe file but for linux /MacOs use it will make the main file excutable. 
-When running the above command if you encunter any problem with your  C++ compiler plase follow this steps:

-Step: 1 Download and install MSYS2: https://www.msys2.org

-Step: 2 Open the MSYS2 MinGW 64-bit shell

-Step: 3 Run:
```bash
pacman -Syu  //This will update Your MSYS and follow the steps it shows you
pacman -S mingw-w64-x86_64-gcc
```
Then run this again:
```bash
g++ -std=c++17 main.cpp Repository.cpp log.cpp branch.cpp checkout.cpp merge.cpp -o MiniGit
```
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
To veiw logs 
```bash
./MiniGit log
```
To creat and check branches:
```bash
./MiniGit branch
```
This will show you all the branchs you have
```bash
./MiniGit branch <branch_name>
```
This one will create you a new branch

To move from one branch to onther or checkout anther branch
```bash
./MiniGit checkout
```
To merge branches:
```bash
./MiniGit merge <branch>
```
To see the diffrence:
```bash
./MiniGit diff <hash1> <hash2>
```

##Example
```bash
g++ -std=c++17 main.cpp Repository.cpp log.cpp branch.cpp checkout.cpp merge.cpp -o MiniGit
./MiniGit init
echo "Hello there this is MiniGit" >hello.txt
./MiniGit add hello.txt
./MiniGit commit -m "Add hello.txt"
./MiniGit log
./MiniGit branch
./MiniGit branch Feature1
./MiniGit checkout Feature1
echo "Hello there this is MiniGit, how are you?" >hello.txt
./MiniGit add hello.txt
./MiniGit commit -m "Add hello.txt"
./MiniGit checkout main
./MiniGit merge Feature1
./MiniGit diff 63dgv37 f8er320

```
To Remove the init file run the following:

-For linux/MacOS
```bash
rm -rf .minigit
```

-For windows
```bash
Remove-Item -Recurse -Force .minigit
```



# 🧩 MiniGit Project Board

## 📌 To Do
- [ ] **[Bitanya]** Set up `.minigit/` directory structure
- [ ] **[Bitanya]** Implement `add(filename)` function with file hashing
- [ ] **[Bitanya]** Implement `commit -m "message"` to save file snapshots
- [ ] **[Lealem]** Implement `log` command to show commit history
- [ ] **[Lealem]** Implement `branch` and store pointers
- [ ] **[Lealem]** Implement `checkout <branch>` 
- [ ] **[Megdelawit]** Design and implement `merge <branch>` using 3-way merge
- [ ] **[Megdelawit]** Handle conflict detection and show conflict messages
- [ ] **[Megdelawit]** Implement command-line interface (parse input)
