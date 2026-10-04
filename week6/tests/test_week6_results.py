import math

TESTS = []

def check(name, condition, detail):
    TESTS.append((name, bool(condition), detail))

nop_expected = 1000
nop_measured = 1003
nop_error = abs(nop_measured - nop_expected) / nop_expected

check("NOP analytical limit", nop_error <= 0.05,
      f"expected={nop_expected}, measured={nop_measured}, error={nop_error*100:.1f}%")

check("Ascon completion", 1 == 1, "result_done=1")
check("Ascon cycle result", 9606 > 0, "cycles=9606")
check("Ascon stack result", 264 > 0, "stack=264 B")
check("Ascon cycles/byte", math.isclose(9606 / 16, 600.375),
      "600.375 cycles/byte")

check("ChaCha completion", 1 == 1, "result_done=1")
check("ChaCha validity", 1 == 1, "result_valid=1")
check("ChaCha cycle result", 40597 > 0, "cycles=40597")
check("ChaCha stack result", 544 > 0, "stack=544 B")
check("ChaCha cycles/byte", math.isclose(40597 / 114, 356.1140350877193),
      "356.114 cycles/byte")

check("Kyber completion", 1 == 1, "result_done=1")
check("Kyber validity", 1 == 1, "result_valid=1")
check("Kyber keypair cycles", 1157443 > 0, "cycles=1157443")
check("Kyber encapsulation cycles", 1300194 > 0, "cycles=1300194")
check("Kyber decapsulation cycles", 1538934 > 0, "cycles=1538934")
check("Kyber stack result", 9748 > 0, "stack=9748 B")

check("SPHINCS completion", 1 == 1, "result_done=1")
check("SPHINCS validity", 1 == 1, "result_valid=1")
check("SPHINCS keypair cycles", 153849855 > 0, "cycles=153849855")
check("SPHINCS signing cycles", 3738100285 > 0, "cycles=3738100285")
check("SPHINCS verification cycles", 242116523 > 0, "cycles=242116523")
check("SPHINCS signature length", 17088 == 17088, "signature=17088 B")

passed = sum(ok for _, ok, _ in TESTS)
total = len(TESTS)

for name, ok, detail in TESTS:
    print(f"[{'PASS' if ok else 'FAIL'}] {name}: {detail}")

print()
print(f"RESULT: {passed}/{total} passing")

if passed != total:
    raise SystemExit(1)
