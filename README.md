# Supermarket Billing System (C++)

A high-performance, console-based application designed to manage product inventory and automate customer billing processes efficiently. This project demonstrates the practical application of Object-Oriented Programming (OOP) and persistent storage using C++ File Handling.

## 🚀 Features

### Administrator Module
- **Secure Access:** (Optional) Restricted access to inventory management.
- **Add Products:** Create new product entries with unique IDs, names, prices, and discounts.
- **Modify Inventory:** Update existing product details dynamically.
- **Remove Records:** Delete outdated or out-of-stock products from the database.

### Customer (Buyer) Module
- **Real-time Inventory:** View the current list of available products and prices.
- **Automated Billing:** Enter product codes and quantities to generate an instant receipt.
- **Discount Calculation:** Automatically applies percentage-based discounts to the final total.

## 🛠️ Tech Stack

- **Language:** C++
- **Paradigm:** Object-Oriented Programming (Classes & Objects)
- **File Handling:** `fstream` library for persistent data storage (`database.txt`)
- **Environment:** Developed using Dev-C++

## 📁 Project Structure

- `main.cpp`: The core source code containing the `Product` class and menu logic.
- `database.txt`: The local file where product data is stored (created automatically upon first run).
