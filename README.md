# test-bms

A TypeScript project demonstrating Fibonacci sequence generation with comprehensive documentation and development environment configuration.

## 📋 Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [Files Documentation](#files-documentation)
  - [fibonacci.ts](#fibonaccits)
  - [.devfile.yaml](#devfileyaml)
- [Usage Examples](#usage-examples)
- [Development](#development)
- [Testing](#testing)
- [Additional Documentation](#additional-documentation)
- [Contributing](#contributing)
- [License](#license)

## 🔍 Overview

This repository contains a well-documented TypeScript implementation of a Fibonacci sequence generator. The project is configured with a development environment using Eclipse Che/OpenShift Dev Spaces through a `.devfile.yaml` configuration file.

The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones, starting from 0 and 1: `0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...`

## 📁 Repository Structure

```
test-bms/
├── .devfile.yaml          # Development environment configuration
├── fibonacci.ts           # TypeScript Fibonacci sequence generator
├── README.md             # This file - comprehensive project documentation
└── docs/                 # Detailed documentation directory
    ├── FIBONACCI.md      # Detailed fibonacci.ts documentation
    └── DEVFILE.md        # Detailed .devfile.yaml documentation
```

## ✨ Features

- **Fibonacci Generator**: Efficient algorithm to generate Fibonacci sequences of any length
- **Type Safety**: Full TypeScript implementation with proper type annotations
- **Input Validation**: Comprehensive error handling for invalid inputs
- **Edge Case Handling**: Proper handling of edge cases (n=0, n=1, negative numbers, non-integers)
- **Documentation**: Extensive JSDoc comments and usage examples
- **Development Environment**: Pre-configured devfile for consistent development setup
- **Build Automation**: Automated TypeScript compilation and type checking

## 🔧 Prerequisites

### For Local Development
- Node.js 18 or higher
- npm or yarn package manager
- TypeScript compiler

### For Devfile-based Development
- Eclipse Che, OpenShift Dev Spaces, or any devfile-compatible environment
- No local setup required - the devfile handles all dependencies

## 🚀 Quick Start

### Method 1: Local Development

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd test-bms
   ```

2. **Install TypeScript (if not already installed)**
   ```bash
   npm install -g typescript
   ```

3. **Compile the TypeScript code**
   ```bash
   tsc fibonacci.ts
   ```

4. **Use the function in your project**
   ```typescript
   import { generateFibonacci } from './fibonacci';
   
   const sequence = generateFibonacci(10);
   console.log(sequence);  // [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
   ```

### Method 2: Using Devfile

1. **Open in a devfile-compatible environment**
   - Eclipse Che
   - OpenShift Dev Spaces
   - Or any devfile 2.2.0 compatible IDE

2. **The environment will automatically**:
   - Set up Node.js 18 container
   - Install system dependencies (git, findutils, grep, curl, wget)
   - Install TypeScript globally
   - Configure the workspace

3. **Build the project**
   ```bash
   # Runs automatically, but you can manually trigger:
   tsc fibonacci.ts
   ```

4. **Type check**
   ```bash
   tsc --noEmit fibonacci.ts
   ```

## 📚 Files Documentation

### fibonacci.ts

**Purpose**: Implements a Fibonacci sequence generator function with comprehensive error handling and validation.

**Key Features**:
- Generates Fibonacci sequences of specified length
- Input validation (ensures non-negative integers)
- Optimized iterative algorithm (O(n) time complexity, O(n) space complexity)
- Comprehensive JSDoc documentation
- Multiple usage examples in comments

**Function Signature**:
```typescript
function generateFibonacci(n: number): number[]
```

**Parameters**:
- `n` (number): The number of Fibonacci numbers to generate. Must be a non-negative integer.

**Returns**:
- `number[]`: An array containing the first n Fibonacci numbers.

**Throws**:
- `Error`: If n is negative or not an integer.

**Examples**:
```typescript
generateFibonacci(10);  // [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
generateFibonacci(0);   // []
generateFibonacci(1);   // [0]
generateFibonacci(-5);  // Error: Input must be a non-negative number
generateFibonacci(3.5); // Error: Input must be an integer
```

**Edge Cases Handled**:
- `n = 0`: Returns empty array
- `n = 1`: Returns `[0]`
- `n = 2`: Returns `[0, 1]`
- Negative numbers: Throws error
- Non-integer inputs: Throws error

**Algorithm Details**:
- Uses iterative approach (not recursive) for better performance
- Initializes array with first two Fibonacci numbers `[0, 1]`
- Iteratively calculates each subsequent number as sum of previous two
- Time Complexity: O(n)
- Space Complexity: O(n)

For detailed documentation, see [docs/FIBONACCI.md](docs/FIBONACCI.md)

### .devfile.yaml

**Purpose**: Defines the development environment configuration for Eclipse Che/OpenShift Dev Spaces.

**Devfile Version**: 2.2.0

**Components**:
- **nodejs**: Node.js 18 container with 1Gi memory limit
  - Source mapping: `/ramdisk/app/test-bms`
  - Pre-configured for TypeScript development

**Commands Defined**:

1. **install-system-deps** (build):
   - Installs system dependencies: git, findutils, grep, curl, wget
   - Runs automatically on `postStart`

2. **install** (build, default):
   - Installs TypeScript globally via npm
   - Runs automatically on `postStart`

3. **build**:
   - Compiles fibonacci.ts to JavaScript
   - Command: `tsc fibonacci.ts`

4. **type-check** (test, default):
   - Performs TypeScript type checking without emitting files
   - Command: `tsc --noEmit fibonacci.ts`

**Events**:
- **postStart**: Automatically runs `install-system-deps` and `install` when workspace starts

**Use Cases**:
- Consistent development environment across team members
- Zero-setup development in cloud IDEs
- Automated dependency installation
- Standardized build and test commands

For detailed documentation, see [docs/DEVFILE.md](docs/DEVFILE.md)

## 💡 Usage Examples

### Basic Usage

```typescript
import { generateFibonacci } from './fibonacci';

// Generate first 10 Fibonacci numbers
const fibonacci = generateFibonacci(10);
console.log(fibonacci);
// Output: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

// Generate first 5 Fibonacci numbers
const shortSequence = generateFibonacci(5);
console.log(shortSequence);
// Output: [0, 1, 1, 2, 3]
```

### Edge Cases

```typescript
// Empty sequence
const empty = generateFibonacci(0);
console.log(empty);  // []

// Single element
const single = generateFibonacci(1);
console.log(single);  // [0]

// Two elements
const pair = generateFibonacci(2);
console.log(pair);  // [0, 1]
```

### Error Handling

```typescript
try {
  // This will throw an error
  generateFibonacci(-5);
} catch (error) {
  console.error(error.message);  // "Input must be a non-negative number"
}

try {
  // This will also throw an error
  generateFibonacci(3.14);
} catch (error) {
  console.error(error.message);  // "Input must be an integer"
}
```

### Advanced Usage

```typescript
// Calculate sum of first n Fibonacci numbers
function sumFibonacci(n: number): number {
  const sequence = generateFibonacci(n);
  return sequence.reduce((sum, num) => sum + num, 0);
}

console.log(sumFibonacci(10));  // 88

// Find Fibonacci numbers less than a maximum value
function fibonacciLessThan(max: number): number[] {
  let n = 1;
  let sequence = generateFibonacci(n);
  
  while (sequence.length === 0 || sequence[sequence.length - 1] < max) {
    n++;
    sequence = generateFibonacci(n);
  }
  
  return sequence.filter(num => num < max);
}

console.log(fibonacciLessThan(100));
// [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
```

## 🛠️ Development

### Building the Project

```bash
# Compile TypeScript to JavaScript
tsc fibonacci.ts

# This generates fibonacci.js
```

### Type Checking

```bash
# Type check without generating JavaScript
tsc --noEmit fibonacci.ts
```

### Using in Your Project

```typescript
// Import the function
import { generateFibonacci } from './fibonacci';

// Or require in CommonJS
const { generateFibonacci } = require('./fibonacci');
```

### Development Environment Commands

When using the devfile environment, you can run:

```bash
# Install dependencies (runs automatically)
npm install -g typescript

# Build the project
tsc fibonacci.ts

# Type check
tsc --noEmit fibonacci.ts
```

## 🧪 Testing

The code includes comprehensive input validation and error handling. Here are test scenarios:

### Valid Inputs
- ✅ `n = 0`: Returns empty array
- ✅ `n = 1`: Returns `[0]`
- ✅ `n = 2`: Returns `[0, 1]`
- ✅ `n = 10`: Returns first 10 Fibonacci numbers
- ✅ Large `n`: Handles large sequences efficiently

### Invalid Inputs
- ❌ Negative numbers: Throws "Input must be a non-negative number"
- ❌ Non-integers: Throws "Input must be an integer"
- ❌ NaN: Throws "Input must be an integer"
- ❌ Infinity: Throws "Input must be an integer"

### Running Tests Manually

```typescript
// Test suite (you can add to a test file)
const tests = [
  { input: 0, expected: [] },
  { input: 1, expected: [0] },
  { input: 2, expected: [0, 1] },
  { input: 5, expected: [0, 1, 1, 2, 3] },
  { input: 10, expected: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34] }
];

tests.forEach(test => {
  const result = generateFibonacci(test.input);
  const passed = JSON.stringify(result) === JSON.stringify(test.expected);
  console.log(`Test n=${test.input}: ${passed ? 'PASS' : 'FAIL'}`);
});
```

## 📖 Additional Documentation

For more detailed information about specific files, please refer to:

- **[docs/FIBONACCI.md](docs/FIBONACCI.md)** - In-depth documentation for fibonacci.ts including:
  - Algorithm explanation
  - Performance analysis
  - Advanced usage patterns
  - Mathematical background
  
- **[docs/DEVFILE.md](docs/DEVFILE.md)** - Complete devfile.yaml reference including:
  - Devfile specification details
  - Component configuration
  - Command customization
  - Troubleshooting guide

## 🤝 Contributing

Contributions are welcome! Here are some ways you can contribute:

1. **Report bugs**: Open an issue describing the bug and how to reproduce it
2. **Suggest enhancements**: Open an issue with your feature request
3. **Submit pull requests**: Fork the repo, make your changes, and submit a PR

### Development Guidelines

- Maintain TypeScript type safety
- Add JSDoc comments for new functions
- Include usage examples
- Handle edge cases and errors appropriately
- Update documentation when adding features

## 📄 License

[Add your license information here]

---

## 🔗 Quick Links

- [Fibonacci Sequence (Wikipedia)](https://en.wikipedia.org/wiki/Fibonacci_number)
- [TypeScript Documentation](https://www.typescriptlang.org/docs/)
- [Devfile Specification](https://devfile.io/)
- [Eclipse Che](https://www.eclipse.org/che/)

---

**Note**: This project is designed for both local development and cloud-based development environments. Choose the method that best suits your workflow!
