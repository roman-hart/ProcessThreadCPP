<h1 align="center">C++ Threads vs Processes</h1>
<p align="center"><i>Does square matrix multiplication using .txt files for i/o</i></p>
<p align="center"><i>For education purposes. Developed as a laboratory project for <a href="http://www.univ.kiev.ua/en">Taras Shevchenko National University of Kyiv</a></i></p>
<br>

# Requires

OS-specific library: <unistd.h> and <sys/wait.h> for POSIX systems. For Windows: replace it wih <process.h> and <windows.h>, than replace fork(), wait(), gettpid() with CreateProcess(), WaitForSingleObject(), GetCurrentProcessId().

Standart libraries: time.h (has relative accuracy), fstream, string, thread.


# Usage

Change general variables <i>N, S, CYCLES</i> to test a particular configuraiton. Compile the program and run `main.exe` file. <br>
Program output will be saved to `output.txt` file. <br>

# Results, ms for each cycle (CYCLES = 100)

Thread approach:

S             | 2 | 3 | 4
------------- | ----- | ----|----
Thread approach       | 0.91ms | 1.00ms | 1.29ms
Process approach      | 0.22ms | 0.30ms | 0.32ms
