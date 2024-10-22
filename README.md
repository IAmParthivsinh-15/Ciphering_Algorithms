# 🔐 Cyber Security Ciphers in React

Welcome to the **Cyber Security Ciphers** project! This React and TypeScript-based project showcases implementations of various classical ciphers, bringing the fascinating world of cryptography to life. Whether you're a student, professional, or just curious, these components will help you understand and visualize how different encryption techniques work right in your browser.

## 🚀 Getting Started

Follow these steps to set up the project on your local machine:

### Prerequisites

Ensure you have the following installed:

- **Node.js** (version 14 or later)
- **npm** or **yarn**

### Installation Steps

1. **Clone the Repository:**

   Begin by cloning the repository to your local machine:

   ```bash
   git clone https://github.com/IAmParthivsinh-15/Ciphering_Algorithms.git
   cd nextjs
Install Dependencies:

Next, install all the necessary dependencies:

bash
Copy code
npm install
# or
yarn install
Start the Development Server:

Now, you're ready to start the development server:

bash
Copy code
npm run dev
# or
yarn dev
Your application will be up and running at http://localhost:3000. Open this URL in your browser to start exploring the ciphers!

# 🔑 Cipher Implementations

Explore a variety of classical ciphers, each implemented as a React component in the `pages` directory. Here's a quick overview:

- **AFFINE CIPHER (affine.tsx)**: A monoalphabetic substitution cipher where each letter is mapped to its numeric equivalent, encrypted using a mathematical function, and converted back to a letter.
- **COLUMNAR TRANSPOSITION CIPHER (columnar.tsx)**: Rearranges plaintext into a grid and reads it off in columns for secure messages.
- **FEISTEL CIPHER (feistel.tsx)**: A basic Feistel structure, a building block for many modern encryption algorithms.
- **MONOALPHABETIC SUBSTITUTION CIPHER (mono.tsx, monoalphabetic.tsx)**: A substitution cipher where each letter of the plaintext is replaced with a fixed letter of the alphabet.
- **PLAYFAIR CIPHER (playfair.tsx)**: A digraph substitution cipher that encrypts pairs of letters.
- **RAIL FENCE CIPHER (railfence.tsx)**: A simple transposition cipher that jumbles the order of letters by writing them in a zigzag pattern.
- **SHIFT CIPHER (shift.tsx)**: The classic Caesar cipher, which shifts the letters of the alphabet by a fixed number.
- **VIGENÈRE CIPHER (vigener.tsx)**: A polyalphabetic substitution cipher using a keyword to make encryption harder to crack than simple substitution.

🎨 **Visualization & Interaction**

Each cipher comes with interactive components that allow you to:

- **Encrypt and Decrypt**: See the process in action by entering your text and key.
- **Visualize the Process**: Understand how each step transforms the plaintext into ciphertext and vice versa.
- **Experiment with Variations**: Modify keys and inputs to see how changes affect the output.

## C++ Cipher Implementations

In addition to the React implementations, this project also includes C++ implementations of various ciphers. Here are the available files:

- **DES (des.cpp)**: Implementation of the Data Encryption Standard (DES) algorithm.
- **AFFINE & FEISTEL CIPHERS (affine_feistel.cpp)**: Combined implementation of the Affine cipher and the Feistel structure.
- **RAIL FENCE & COLUMNAR TRANSPOSITION CIPHERS (railfence_columnar.cpp)**: Implementation of both the Rail Fence and Columnar Transposition ciphers.
- **RSA (rsa.cpp)**: Implementation of the RSA encryption algorithm.
- **SHIFT, MONOALPHABETIC, VIGENÈRE, AND PLAYFAIR CIPHERS (shift_monoalphabetic_vigenere_playfair.cpp)**: Combined implementation of the Shift cipher, Monoalphabetic cipher, Vigenère cipher, and Playfair cipher.

🤝 **Contributing**

If you would like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request. Contributions are welcome!


Screenshots :


![image](https://github.com/user-attachments/assets/47456fb3-7b70-429f-b678-04f55f5e1454)

Shift Cipher :
![image](https://github.com/user-attachments/assets/fc08135c-581f-4704-8372-99f8077afeb7)

Columnar Cipher :
![image](https://github.com/user-attachments/assets/d671bbb1-bca2-4e9f-b6eb-df0544e9451b)

PlayFair Cipher :
![image](https://github.com/user-attachments/assets/edeba00a-8d27-4ce8-98a3-104f3839cb91)

