import sys
from math import factorial

def erlang_c(A, N):
    numerator = (A ** N / factorial(N)) * (N / (N - A))
    denominator = sum([(A ** i / factorial(i)) for i in range(N)]) + numerator
    P_w = numerator / denominator
    return P_w

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python erlangc.py var1 var2")
        sys.exit(1)

    try:
        A = float(sys.argv[1]) # Número promedio de llegadas por unidad de tiempo
        N = int(sys.argv[2]) # Número de servidores
    except ValueError:
        print("Invalid arguments. var1 must be a float and var2 must be an integer.")
        sys.exit(1)

    print(f"A = {A}")
    print(f"N = {N}")
    P_w = erlang_c(A, N)
    print(f"P_w = {P_w}")
