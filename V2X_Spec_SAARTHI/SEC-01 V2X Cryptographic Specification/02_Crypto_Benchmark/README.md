# SEC-01 V2X Cryptographic Benchmark

## Purpose

This benchmark supports the SEC-01 V2X Cryptographic Specification and the assigned task to benchmark AES-GCM against ECC.

## Benchmark Scope

The benchmark will compare:

* AES-GCM for authenticated encryption
* ECC for public-key cryptographic operations

## Required Measurements

The benchmark will record:

* Execution cycles
* Execution time
* Cycles per byte where applicable
* Peak RAM usage
* Code size
* Estimated energy
* Functional correctness

## Target Environment

* Target: ARM Cortex-M4
* Emulation: Renode
* Toolchain: Arm GNU Toolchain
* No physical hardware is used for the benchmark.

## Validation Status

Crypto-specific cycle measurements must be validated before final performance or feasibility claims are made.

## Important Configuration Note

The SAARTHI task specifies ECC but does not specify the exact ECC operation, curve, or key size. These parameters must be defined before the ECC benchmark is finalized.

No final ECC performance result will be claimed until the configuration is explicitly defined.
