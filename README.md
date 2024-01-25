# Minishell 42 Project

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## Introduction

Minishell is a fundamental project in the 42 school curriculum, designed to introduce students to the world of systems programming and command-line interfaces. In this project, we have are have created a simple shell that mimic the behavior of the bash shell using C programing language.

## Features

- *Command Execution:* Execute shell commands.
- *Pipelines:* Implementing simple command pipelines allows users to chain commands together, facilitating more complex operations.
- *Redirections:* Support input and output redirections.
- *Environment Variables:* Handle environment variables.
- *Built-in Commands:* Implement built-in shell commands like cd, echo, env, export, unset, exit and pwd.
- *Error Handling:* Provide meaningful error messages for user input.
- *Signal Handling:* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

  
## Getting Started

### Prerequisites

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/aandom/minishell.git
    

2. Navigate to the project directory:

    ```bash
    cd minishell
    

3. Build the project:

    ```bash
    make
    

## Usage

To run the Minishell, use the following command:

```bash
./minishell
