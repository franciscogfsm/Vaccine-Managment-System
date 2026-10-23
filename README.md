<div align="center">

# Vaccine Management System

Vaccine batches and inoculations, from the command line. IAED 2024/2025.

<img src="https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=black" alt="C">
<img src="https://img.shields.io/badge/Built_at-IST-009DE0?style=flat" alt="Built at">

</div>

<br>

A command-line system that manages vaccine batches and the doses given to each person. It was the
project for Introdução aos Algoritmos e Estruturas de Dados at Instituto Superior Técnico.

## What it does

- Adds vaccine batches with a unique batch id, an expiry date and a number of doses
- Applies a dose to a person from the batch with the earliest date
- Removes batches and deletes inoculation records
- Lists vaccines, filtered by name, and inoculations
- Moves the simulated date forward, so batches expire
- Accepts names with spaces, quoted or not
- Prints errors in English, or in Portuguese with the `pt` argument
- Uses no global variables

## Commands

| Command | Action |
|---|---|
| `c` | Add a vaccine batch |
| `l` | List vaccines, all or by name |
| `a` | Apply a dose to a person |
| `r` | Remove a batch's availability |
| `d` | Delete inoculation records |
| `u` | List inoculations |
| `t` | Advance the simulated date |
| `q` | Quit |

## Build and run

```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
./proj          # English messages
./proj pt       # Portuguese messages
```

The public tests are in `public-tests/`; run them with its `Makefile`.

## Layout

```
main.c                 entry point and command loop
commands.c             one handler per command
vaccine_table.c        vaccine hash table
lots_table.c           batches by id
aplications_table.c    inoculation records
functions.c            dates, parsing, validation
structs.h constants.h  shared types and limits
public-tests/          course test inputs and expected outputs
```
