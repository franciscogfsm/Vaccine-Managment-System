# Vaccine Management System (IAED 2024/2025) 💉🗓️
This project is a vaccine management system developed for the IAED course during the 2024/2025 academic year.

# Overview

This system allows managing vaccine batches and tracking inoculations to users. Features include:
Adding new vaccine batches with expiration dates and available doses
Applying vaccine doses to users
Removing vaccine batches or vaccine applications
Listing vaccines and applications
Simulating the passing of time
All interaction happens through command-line commands.

## Features 🚀
Unique vaccine batch identification with validation
Expiration dates and dose availability management
Support for user names with spaces (quoted or unquoted)
Efficient memory management without global variables
Bilingual error messages: English (default) and Portuguese (with 'pt' argument)

# Commands 📋
```
q : Quit the program

c : Add a new vaccine batch

l : List vaccines (all or filtered by name)

a : Apply a vaccine dose to a user

r : Remove vaccine batch availability

d : Delete vaccine application records

u : List vaccine applications

t : Advance the simulated date
```
# Usage 💻
Compile with:
```
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```
## Run with:
```
./proj
```
For Portuguese messages:
```
./proj pt
```
Enter commands as per the project instructions.

# Notes 📝
Initial system date: 01-01-2025

Supports up to 1000 vaccine batches

Handles large inputs with dynamic memory management and very fast lookups
