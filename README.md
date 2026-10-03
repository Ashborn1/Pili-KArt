# 🛒 Pili KArt

![Status](https://img.shields.io/badge/Status-Completed-success)
![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![License](https://img.shields.io/badge/License-MIT-yellow)

A fully functional **console-based e-commerce simulation** with a built-in **virtual ATM system**, written entirely in C. Built as a final project for a Computer Science course, Pili KArt simulates a complete digital shopping experience with multiple stores, currency conversion, discounts, cart management, and a persistent ATM banking system using file handling.

---

## 📖 Overview

**Pili KArt** ("Pili" = choose, "KArt" = cart) is a terminal-based shopping simulator inspired by the Filipino culture of *tingi* (buying in small quantities) and *sari-sari* stores. The program walks the user through a full e-commerce lifecycle — from signing up, selecting a currency, funding a wallet, browsing virtual shops, managing a cart, applying discounts, and even using a virtual ATM for top-ups.

The project demonstrates core **C programming concepts** including:
- Structures and file handling (binary I/O)
- Input validation and error handling
- Multi-dimensional arrays
- Modular functions and program organization
- Terminal UI design with ANSI color codes
- Currency conversion logic

---

## 🏪 The Four Stores

Each store has a culturally inspired Filipino name:

| Store | Category | Inspiration |
| :--- | :--- | :--- |
| 📱 **APOLLO** | Technologies | Named after the Apollo missions — the Lunar Roving Vehicle was allegedly designed by **Eduardo San Juan**, a Filipino NASA engineer. |
| 👗 **HABI** | Fashion | Tagalog for "weave" — reflecting the Philippine weaving tradition. |
| 🏠 **NIPA** | Home Appliances | Derived from the **Bahay Kubo** (Nipa Hut), the traditional Filipino home. |
| 🍲 **PASO** | Food Essentials | Another term for "banga" (a clay pot), representing **Calamba**. |

---

## ✨ Features

### 👤 User System
- **Sign-Up Validation** — Ensures names contain only letters and spaces, ages are realistic (1–120), and PWD status is clearly declared.
- **Age & PWD Tracking** — Used later for automatic discount calculations.

### 💱 Multi-Currency Support
- Choose between **PHP 🇵🇭**, **USD 🇺🇸**, **EUR 🇪🇺**, or **JPY 🇯🇵**.
- All prices are stored in PHP internally and converted in real-time using fixed exchange rates.

### 🛍️ Shopping Cart
- Add items from any of the 4 stores into a unified cart.
- **Auto-Merge** — Buying the same item again updates the quantity instead of creating a duplicate entry.
- **Edit Cart** — Change quantities or remove items before checkout.
- **Real-Time Subtotal & Total** calculations per item and across the entire cart.

### 🎁 Automatic Discounts
Discounts are calculated based on multiple criteria, applied automatically at checkout:

| Condition | Discount |
| :--- | :--- |
| Senior (60+) **and** PWD | **15%** |
| Senior (60+) only | **10%** |
| Promo: Total ≥ ₱20,000 | **10%** |
| Promo: Total ≥ ₱15,000 | **7.5%** |
| Promo: Total ≥ ₱10,000 | **5%** |
| Promo: Total ≥ ₱5,000 | **2.5%** |
| PWD only | **5%** |

> The program intelligently detects overlapping discounts and applies only the highest applicable one, with a note when a discount is overridden.

### 🏧 Virtual ATM (Pili KAhera)
A fully persistent banking system stored in `atm_accounts.dat` using binary file I/O:

- **Create Account** — Name + 6-digit PIN + initial deposit.
- **Login** — Validates name and PIN against stored accounts.
- **Deposit** — Transfers money from the wallet into the ATM account (auto-converted to PHP).
- **Transfer to Wallet** — Moves ATM balance back into the shopping wallet.
- **Check Balance** — Displays balance in both PHP and the selected currency.
- **View All Accounts** — Lists every registered account and its balance.
- **Insufficient Funds Recovery** — If the wallet is short at checkout, the program offers to redirect the user to the ATM for a top-up.

### 🧾 Receipt Generation
- Displays current **date & time** using `time()` and `ctime()`.
- Itemizes every product with quantity and subtotal.
- Shows **initial total**, **discount applied**, **final total**, and **change**.
- Personalized thank-you message using the customer's name.

### 🎨 Terminal UI
- **ANSI color codes** for a clean, colorful interface.
- Structured **section headers**, **dividers**, and **box headers**.
- Emoji-enhanced labels for quick visual scanning.

---

## 🗂️ Project Structure
