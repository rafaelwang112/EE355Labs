import subprocess
import sys

def main():
    num = sys.argv[1]
    result = subprocess.run(["./output_dp.o", num], capture_output=True, text=True)
    output_lines = result.stdout.strip().split("\n")
    if output_lines[0] == "1":
        print(f"Congratulations! You have the Fibonacci {num}")
    else:
        next_fib = output_lines[1] 
        print(f"Sorry! {num} is not a Fibonacci number but the next Fibonacci number to it is {next_fib}")

if __name__ == "__main__":
    main()
