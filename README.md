# 📦 HuffCompress
## A Lossless File Compression Tool using Huffman Encoding (C++)

### 🚀 Overview

**HuffCompress** is a **lossless text file compression tool** implemented in C++, based on the Huffman Encoding algorithm.
It efficiently reduces file size by assigning shorter binary codes to frequently occurring characters, achieving 30–40% compression on average without any loss of data.

This project demonstrates:


- Strong understanding of **data structures**

- **Greedy algorithms**

- **File I/O**

- **Bit-level manipulation**

- **Real-world compression techniques**

### 💡 Why HuffCompress?

Imagine needing to upload or share a large text file but having limited bandwidth or storage.
HuffCompress helps by significantly reducing file size while preserving original data — making it ideal for:

- Cloud uploads

- File sharing

- Storage optimization

- Learning compression internals

### 🧠 About the Algorithm (Huffman Encoding)

Huffman Coding is an optimal prefix-free binary encoding algorithm, developed by David A. Huffman (1952).

How it works:

1. Count character frequencies from the input file

2. Build a min-heap (priority queue) using frequencies

3. Construct a Huffman Tree

4. Generate prefix-free binary codes

5. Encode the file using these codes

6. Store metadata to enable accurate decompression

Key Properties:

- ✅ Lossless compression

- ✅ Prefix-free codes (no ambiguity)

- ✅ Fast decoding

- ✅ Used in ZIP, PNG, and network protocols

### ✨ Features

- 🔒 **Lossless Compression**

- 🔄 **Accurate Decompression**

- 🌳 **Huffman Tree Construction**

- 📊 **Frequency-Based Encoding**

- 🧵 **Bit Packing & Unpacking**

- 🗂️ **Binary File Handling**

- 💻 Written in **Modern C++**


## Project Structure
```

HuffCompress/
│
├── main.cpp          # Entry point
├── compressor.cpp    # Compression logic
├── decompressor.cpp  # Decompression logic
├── huffman.cpp       # Huffman tree & encoding
├── huffman.h         # Declarations
├── input.txt         # Sample input file
├── output.huff       # Compressed output
├── README.md         # Documentation
└── LICENSE           # MIT License

```
### 🛠️ Getting Started
**🔧 Prerequisites**

- C++ Compiler (g++)

- Git

### 📥 Clone the Repository
```
git clone https://github.com/Amankumarsingh23/HuffCompress.git
cd HuffCompress
```
### 🧱 Compile
Linux / macOS
```
g++ main.cpp -o huffcompress
```

Windows (MinGW)
```
g++ main.cpp -o huffcompress.exe
```
### ▶️ Run
```
./huffcompress
```
### 🔄 Compression Workflow

1. Read input text file

2. Generate frequency map

3. Build Huffman Tree

4. Generate binary codes

5. Compress data with bit packing

6. Save metadata for decompression


### 📉 Merits

- ✔️ Efficient lossless compression

- ✔️ Widely used industry-standard algorithm

- ✔️ Simple and fast decoding

- ✔️ Great educational value

### ⚠️ Limitations

- ❌ Compression overhead for very small files

- ❌ Limited improvement for uniform ASCII text

- ❌ Not ideal for real-time streaming scenarios

### 📚 References

- GeeksForGeeks – Huffman Coding

- Programiz – Huffman Algorithm

- CodeReview StackExchange

### 🧑‍💻 Author

**Aman Singh**

- 🎓 IIT Kanpur

- 💡 Competitive Programmer

- 🧠 Interested in Systems, Algorithms & Optimization

### 📄 License

This project is licensed under the MIT License.
See the LICENSE file for details.


