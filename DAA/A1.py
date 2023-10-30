def recursive_fibo(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return recursive_fibo(n - 1) + recursive_fibo(n - 2)

def iterative_fibo(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    fibo1 = 0
    fibo2 = 1
    for i in range(2, n + 1):
        fibo3 = fibo1 + fibo2
        fibo1 = fibo2
        fibo2 = fibo3
    return fibo3

def main():
    flag = 1
    while flag == 1:
        print("Choose a method to calculate Fibonacci:")
        print("1. Recursive")
        print("2. Iterative")
        choice = int(input())
        
        if choice == 1:
            n = int(input("Enter the value of n: "))
            result = recursive_fibo(n)
            print(f"Fibonacci({n}) = {result}")
        elif choice == 2:
            n = int(input("Enter the value of n: "))
            result = iterative_fibo(n)
            print(f"Fibonacci({n}) = {result}")
        else:
            print("Invalid choice.")
        flag = int(input("Do you want to continue? (1/0): "))

if __name__ == "__main__":
    main()
