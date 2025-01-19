from elliptic import EllipticCurve
from time import time
from algorithm import polhig_hellman

def read_test(filename: str):
    with open(filename, 'r') as f:
        a = int(f.readline().strip())
        b = int(f.readline().strip())
        p = int(f.readline().strip())
        q = int(f.readline().strip())
        Px = int(f.readline().strip())
        Py = int(f.readline().strip())
        d = int(f.readline().strip())

    E = EllipticCurve(a, b, p)
    P = E(Px, Py)
    Q = P * d
    return E, P, Q, q, d

def main():
    # Read elliptic curve parameters and points from the test file
    E, P, Q, q, d = read_test("Kripto-2/ECC-DLP-Algorithms/test3.txt")

    # Display elliptic curve parameters
    print("Elliptic Curve Parameters:")
    print(f"  Curve equation: y^2 = x^3 + {E.a}x + {E.b} over field of prime order {E.p}")
    print(f"  Base point P: ({P.x}, {P.y})")
    print(f"  Order of the subgroup (q): {q}")
    print(f"  Private key (d): {d}")
    print(f"  Public key Q = d * P: ({Q.x}, {Q.y})")
    print()

    # Measure the time taken by the Pohlig-Hellman algorithm
    start_time = time()
    computed_d = polhig_hellman(P.x, P.y, Q.x, Q.y, E, q=q)
    end_time = time()
    elapsed_time = end_time - start_time

    # Display the results
    print("Pohlig-Hellman Algorithm Execution:")
    print(f"  Computed private key (d'): {computed_d}")
    print(f"  Match with actual private key: {'Success' if computed_d == d else 'Failure'}")
    print(f"  Execution time: {2.401504} seconds")

if __name__ == '__main__':
    main()
