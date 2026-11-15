*This project has been created as part of the 42 curriculum by gaducurt.*

# Minitalk

**A small data exchange program using UNIX signals.**

## Description

Minitalk is a communication project developed as part of the 42 Common Core curriculum.

The goal is to implement a simple client-server communication system in C, using UNIX signals as the only communication mechanism.

The project consists of two programs:

- **Server:** Waits for incoming messages, receives data encoded as signals and displays the reconstructed string.
- **Client:** Sends a message to the server by transmitting signals to its process ID (PID).

Communication relies exclusively on `SIGUSR1` and `SIGUSR2`. Each character is encoded into bits and transmitted one bit at a time.

The server must be able to receive messages from multiple clients successively without being restarted.

This project provides practical experience with UNIX signals, process identification, bitwise operations and low-level inter-process communication.

## Features

- Client-server architecture.
- Communication exclusively through UNIX signals.
- Character encoding and decoding at the bit level.
- Use of `SIGUSR1` and `SIGUSR2` to transmit binary data.
- Server process identification through its PID.
- Support for multiple consecutive client messages.
- Signal handling and message reconstruction.
- Error handling for invalid arguments and process communication.

## How it works

Minitalk uses two UNIX signals to represent binary information:

| Signal | Meaning |
|---|---|
| `SIGUSR1` | Binary `0` |
| `SIGUSR2` | Binary `1` |

The client converts each character into its binary representation and sends its bits sequentially to the server.

The server receives the signals, reconstructs the binary data and converts it back into characters.

### Communication flow

```text
        CLIENT                         SERVER
          |                              |
          | ------ Message bits -------> |
          |                              |
          |       SIGUSR1 / SIGUSR2      |
          |                              |
          |                         Reconstruct bits
          |                              |
          |                         Rebuild characters
          |                              |
          |                         Display message
          |                              |
```

## Technical concepts

### UNIX signals

Signals provide a mechanism for notifying a process that an event has occurred.

This project uses:
- `SIGUSR1`
- `SIGUSR2`
- `signal()`
- `sigaction()`
- `kill()`

### Bitwise operations

Bitwise operations are used to extract individual bits from characters and reconstruct the original data on the server side.

This involves:
- Bit shifting (`<<`, `>>`).
- Bit masking (`&`).
- Binary representation of characters.
- Sequential data reconstruction.

### Process management

The client identifies the server using its Process ID (PID).

Relevant functions:
- `getpid()` — Retrieves the current process ID.
- `kill()` — Sends a signal to a specified process.

### Signal handling

The server registers signal handlers to process incoming bits and rebuild the transmitted message.

Careful signal handling is essential to avoid losing information and to ensure reliable communication.

## Instructions

### Requirements

- Unix-like operating system.
- C compiler (`cc`).
- `make`.

### Compilation

Clone the repository and compile both programs:

```bash
git clone https://github.com/tiegd/minitalk.git
cd minitalk
make
```

This generates the two executables:

- `server`
- `client`

### Execution

**1. Start the server**

```bash
./server
```

The server displays its PID:

```text
Server PID: 12345
```

**2. Send a message from the client**

Open another terminal and execute:

```bash
./client 12345 "Hello from Minitalk!"
```

Replace `12345` with the PID displayed by your server.

The server receives and displays the message.

### Makefile commands

```bash
make        # Compile client and server
make clean  # Remove object files
make fclean # Remove object files and executables
make re     # Recompile everything
```

## Resources

### Documentation

- [42 Minitalk Subject](https://cdn.intra.42.fr/pdf/pdf/222167/en.subject.pdf) — Official project requirements.
- [Linux Signals — signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html) — Overview of UNIX signals.
- [sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html) — Signal handling configuration.
- [kill(2)](https://man7.org/linux/man-pages/man2/kill.2.html) — Sending signals to processes.
- [getpid(2)](https://man7.org/linux/man-pages/man2/getpid.2.html) — Retrieving process identifiers.

### AI usage

AI tools were used as supplementary learning and documentation resources.

For this project, AI assistance was used to help structure and draft the README and clarify technical concepts related to UNIX signals and inter-process communication.

Technical information was reviewed against the official project requirements. The implementation and technical decisions remain the author's responsibility.

---

**42 Common Core — Minitalk**  
**Language:** C  
**Communication:** UNIX Signals (`SIGUSR1`, `SIGUSR2`)  
**Architecture:** Client / Server  
**Author:** [gaducurt](https://github.com/tiegd)
