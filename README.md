# 🔐 VESPER-SEC-01: Cryptographic Benchmarking Under Emulation

**Author:** Rutvika Mahadev Ashtekar  
**Programme:** VISVAMBHARA Weeks 4–12  
**Domain:** 🛡️ Cybersecurity (Option A)  
**Project:** 🐝 Nano-Bee Secure Communications  
**Week 4 Status:** ✅ **COMPLETE**

---

## 🎯 What's This Project About?

The **Nano-Bee** is a tiny autonomous swarm robot that needs to talk securely with a control system. Problem? It's got almost no compute power, limited RAM, and a small battery.

This project answers one question:
> **Which encryption algorithms can actually run on Nano-Bee without killing its battery?**

I'm testing **4 different encryption methods** to see which ones fit:

| Encryption | Type | Purpose |
|-----------|------|---------|
| 🔐 **Ascon v1.2** | Lightweight | Made for IoT & tiny devices |
| 🔐 **ChaCha20-Poly1305** | Symmetric | Fast & proven |
| 🔐 **Kyber-512** | Post-Quantum | Future-proof security |
| 🔐 **SPHINCS+** | Post-Quantum | Quantum-safe signatures |

**Tool:** Renode (a simulator that acts like real hardware)  
**Measurement:** How fast? How much RAM? How much power?  
**Result:** Feasible ✅ or Not Feasible ❌

---

## 📊 Quick Facts

| 📌 Detail | 📌 Value |
|-----------|---------|
| 🎯 Target Hardware | STM32F407 (ARM Cortex-M4 @ 168 MHz) |
| 💻 Compute Available | 18 MHz (out of 168 MHz) |
| 💾 RAM Available | 50 KB (out of 192 KB) |
| 🔋 Power Available | ~14.1 mW peak |
| 🖥️ Emulator Used | Renode (cycle-accurate) |
| 🔧 Build Tool | Arm GNU Toolchain |
| 📚 References | 18 academic papers |
| ✅ Test Location | Local laptop only (safe!) |

---

## 📁 What's In This Repository

This is what I **actually have** right now (Week 4):

```
VESPER-SEC-01/
│
├─ 📄 README.md                          ← You are here
│
├─ 📂 proposal/                          ← Week 4 work
│  ├─ VESPER-SEC-01-Proposal.docx       ✅ 7-page proposal
│  ├─ VESPER-SEC-01-Proposal.pdf        ✅ PDF version
│  └─ references.bib                    ✅ 18 citations
│
├─ 📂 verification/                      ← Proof it works
│  └─ 📂 screenshots/                    ✅ Evidence photos
│     ├─ gcc_version.png
│     ├─ qemu_version.png
│     ├─ renode_version.png
│     ├─ renode_execution_proof.png
│     └─ renode_cycle_verification.png
│
├─ 💻 cycle_test.c                       ← Test code
└─ 💻 cycle_test.elf                     ← Compiled binary

---

## ✅ What's Finished (Week 4)

### 📝 Proposal Document

✅ **7 pages** with everything:
- 📌 Problem statement (why this matters)
- 📚 18 academic papers reviewed
- 🔍 Detailed methodology (how I'll measure)
- 🎯 Success criteria (what counts as feasible)
- ⚠️ Risk assessment (what could go wrong)

### 🔧 Toolchain Installed

| Tool | Version | Status |
|------|---------|--------|
| 🔨 Arm GNU Toolchain | v12.2.1 | ✅ Working |
| 🖥️ QEMU | v11.1.0 | ✅ Working |
| 📡 Renode | v1.14+ | ✅ Working |

### 🧪 Tests Passed

| Test | Result | Details |
|------|--------|---------|
| 🔌 Functional Test | ✅ PASS | STM32F4 firmware loaded & executed |
| 📊 Cycle Accuracy | ✅ PASS | 1,000 NOPs → 1,003 cycles (0.3% error) |
| ⚙️ Tolerance | ✅ PASS | Within ≤5% requirement |

**Proof:** Screenshots in `verification/screenshots/` 📸

---

## 🚀 How to Use This Repo

### Step 1️⃣: Clone It

```bash
git clone https://github.com/rutvikaashtekar1607/VESPER-SEC-01.git
cd VESPER-SEC-01
```

### Step 2️⃣: Check Tools Are Installed

```bash
arm-none-eabi-gcc --version
qemu-system-arm --version
renode --version
```

Should show:
```
arm-none-eabi-gcc (GNU Arm Embedded Toolchain 12.2.1)...
QEMU emulator version 11.1.0...
Renode 1.14...
```

### Step 3️⃣: View Evidence

All verification screenshots:
```
verification/screenshots/
  ├─ gcc_version.png
  ├─ qemu_version.png
  ├─ renode_version.png
  ├─ renode_execution_proof.png
  └─ renode_cycle_verification.png
```

---

## 🔒 Test Environment (Important!)

**Where does testing happen?**

| ✅ YES | ❌ NO |
|--------|-------|
| 💻 Renode emulation on my laptop | 🖥️ Physical hardware |
| 📡 STM32F4 simulator model | 🌐 External networks |
| 🔒 Isolated & safe | 📱 Third-party systems |
| 👤 Just me, local machine | 🤝 Other people's devices |

**All work is 100% isolated & safe.**

---

## 🎯 The 9-Week Plan

| Week | 🎯 Goal | Status |
|------|---------|--------|
| **4** | ✍️ Proposal + Toolchain | ✅ Done |
| **5** | 🔬 Validate measurements | ⏳ Now |
| **6** | 📊 First benchmarks | ⏳ Next |
| **7** | 🔐 More algorithms | ⏳ Planned |
| **8** | ✔️ Cross-check results | ⏳ Planned |
| **9** | 🔄 Share with other team | ⏳ Planned |
| **10** | 🧪 Stress test | ⏳ Planned |
| **11** | 📄 Write full report | ⏳ Planned |
| **12** | 🎤 Present & defend | ⏳ Planned |

---

## 💰 Budget Numbers (My Assumptions)

**These are MY assumptions based on STM32F4 datasheet:**

| 📌 Resource | 📌 Total | 📌 Available for Crypto | 📌 Reserved |
|-----------|---------|------------------------|-----------|
| 💻 Compute | 168 MHz | 18 MHz | 150 MHz |
| 💾 RAM | 192 KB | 50 KB | 142 KB |
| 🔋 Power | ~100 mW | ~14.1 mW | ~86 mW |

**How I calculated power:**
- Datasheet says: 238 µA per MHz at 3.3V
- My allocation: 18 MHz × 238 µA = 4,284 µA = 4.284 mA
- Power: 4.284 mA × 3.3V = **14.1 mW**

**⚠️ These could change** if the project gets an official Nano-Bee spec.

---

## 📚 References

All **18 papers** are in:
```
proposal/references.bib
```

**Top papers I'm using:**

| 📖 Paper | 📖 Why It Matters |
|----------|-----------------|
| 🔐 Ascon | NIST standard for lightweight encryption |
| 🔐 Heinz 2021 | Kyber-512 on Cortex-M4 (my benchmark!) |
| 🔐 RFC 8439 | ChaCha20-Poly1305 official standard |
| 📖 Yiu 2013 | ARM Cortex-M4 instruction manual |
| 🔐 Bos et al. 2018 | Kyber design & how it works |

---

## 📊 What I'm Measuring

For **each encryption algorithm**, I measure:

| 📏 Metric | 📏 What It Means |
|----------|-----------------|
| **Cycles/byte** | CPU cycles needed to encrypt 1 byte of data |
| **Peak RAM** | Maximum memory used during operation (KB) |
| **Code size** | How big the compiled program is (KB) |
| **Energy/op** | Power consumed per operation (µJ) |

Then I check: **Does it fit in the 18 MHz / 50 KB / 14.1 mW budget?**

Result: ✅ **FEASIBLE** or ❌ **NOT FEASIBLE**

---

## 🚨 What I'm NOT Claiming Yet

| ❌ NOT Done | ⏳ When Done |
|-----------|-----------|
| Actual crypto benchmark numbers | Week 6+ |
| Kyber-512 validation | Week 5 |
| Secure boot integration | Week 9 |
| Stress testing | Week 10 |
| Final 25-page report | Week 11 |

**I'm being honest about this.** No fake numbers. No pretending things are done when they're not.

---

## 📞 Contact Info

| 📱 Contact | 🔗 Link |
|-----------|--------|
| 👤 **GitHub** | [rutvikaashtekar1607](https://github.com/rutvikaashtekar1607) |
| 💼 **LinkedIn** | [Rutvika Ashtekar](https://www.linkedin.com/in/rutvikaashtekar07/) |
| 🏫 **Programme** | VISVAMBHARA (VESPER Cybersecurity) |

---

## 📈 Progress Tracking

### ✅ Week 4 Complete

- ✅ Installed 3 tools (GCC, QEMU, Renode)
- ✅ Verified tools with real firmware
- ✅ Passed cycle-accuracy sanity check
- ✅ Wrote 7-page proposal
- ✅ Collected 18 academic references
- ✅ Created evidence screenshots
- ✅ Set up GitHub repo
- ✅ Created this README

---

## 📌 Notes for Group Members

If you're reviewing this:

| 📍 Question | 📍 Answer |
|-----------|----------|
| Where's the proposal? | `proposal/VESPER-SEC-01-Proposal.docx` |
| Where's the evidence? | `verification/screenshots/` |
| Are budget numbers real? | Stated honestly (my assumptions, not official) |
| Any fake benchmarks? | ❌ No - none claimed yet |
| Why no results yet? | Week 6 is when benchmarking happens |
| Questions? | Check the proposal - all details there |

---

## 🎉 Summary

| 🎯 What | 📊 Status |
|--------|----------|
| **Proposal** | ✅ Complete (7 pages) |
| **Tools Installed** | ✅ Complete (3/3) |
| **Toolchain Verified** | ✅ Complete (screenshots) |
| **Cycle Test** | ✅ Passed (0.3% error) |
| **Documentation** | ✅ Complete (honest & clear) |
| **Ready for Week 5** | ✅ YES |

---

**Last Updated:** 🗓️ September 2026 (Week 4)  

**Happy reviewing!**
