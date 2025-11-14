# fibonacci.ts - Detailed Documentation

## 📋 Table of Contents

- [Overview](#overview)
- [Function Reference](#function-reference)
- [Algorithm Explanation](#algorithm-explanation)
- [Mathematical Background](#mathematical-background)
- [Implementation Details](#implementation-details)
- [Performance Analysis](#performance-analysis)
- [Error Handling](#error-handling)
- [Usage Patterns](#usage-patterns)
- [Edge Cases](#edge-cases)
- [Testing](#testing)
- [Optimization Considerations](#optimization-considerations)
- [Alternatives and Variations](#alternatives-and-variations)
- [Real-World Applications](#real-world-applications)

## 🔍 Overview

The `fibonacci.ts` file contains a TypeScript implementation of a Fibonacci sequence generator. The implementation is designed with a focus on:

- **Type Safety**: Full TypeScript type annotations
- **Robustness**: Comprehensive input validation
- **Performance**: Iterative O(n) algorithm
- **Maintainability**: Clear code structure and extensive documentation
- **Usability**: Easy-to-use API with detailed examples

## 📖 Function Reference

### generateFibonacci

```typescript
function generateFibonacci(n: number): number[]
```

Generates a Fibonacci sequence of a specified length.

#### Parameters

| Parameter | Type | Description | Constraints |
|-----------|------|-------------|-------------|
| `n` | `number` | The number of Fibonacci numbers to generate | Must be a non-negative integer |

#### Returns

- **Type**: `number[]`
- **Description**: An array containing the first n Fibonacci numbers
- **Example return values**:
  - `n=0`: `[]`
  - `n=1`: `[0]`
  - `n=5`: `[0, 1, 1, 2, 3]`
  - `n=10`: `[0, 1, 1, 2, 3, 5, 8, 13, 21, 34]`

#### Throws

| Error Type | Condition | Message |
|------------|-----------|---------|
| `Error` | `n` is not an integer | "Input must be an integer" |
| `Error` | `n` is negative | "Input must be a non-negative number" |

#### Examples

```typescript
// Basic usage
const result = generateFibonacci(10);
console.log(result);
// Output: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

// Edge case: empty sequence
const empty = generateFibonacci(0);
console.log(empty);
// Output: []

// Edge case: single element
const single = generateFibonacci(1);
console.log(single);
// Output: [0]

// Error handling
try {
  generateFibonacci(-5);
} catch (error) {
  console.error(error.message);
  // Output: "Input must be a non-negative number"
}
```

## 🧮 Algorithm Explanation

### Step-by-Step Process

1. **Input Validation**:
   ```typescript
   if (!Number.isInteger(n)) {
     throw new Error('Input must be an integer');
   }
   if (n < 0) {
     throw new Error('Input must be a non-negative number');
   }
   ```
   - Checks if input is an integer using `Number.isInteger()`
   - Validates that input is non-negative

2. **Edge Case Handling**:
   ```typescript
   if (n === 0) return [];
   if (n === 1) return [0];
   ```
   - Returns empty array for n=0
   - Returns single-element array for n=1

3. **Sequence Initialization**:
   ```typescript
   const fibonacci: number[] = [0, 1];
   ```
   - Starts with the first two Fibonacci numbers

4. **Iterative Generation**:
   ```typescript
   for (let i = 2; i < n; i++) {
     const nextNumber = fibonacci[i - 1] + fibonacci[i - 2];
     fibonacci.push(nextNumber);
   }
   ```
   - Loops from index 2 to n-1
   - Each iteration calculates next number as sum of previous two
   - Appends to the result array

5. **Return Result**:
   ```typescript
   return fibonacci;
   ```
   - Returns the complete sequence

### Visual Algorithm Flow

```
Input: n = 7

Step 1: Validate input
  ✓ Is integer? Yes
  ✓ Is non-negative? Yes

Step 2: Check edge cases
  ✗ n === 0? No
  ✗ n === 1? No
  → Continue to step 3

Step 3: Initialize
  fibonacci = [0, 1]

Step 4: Iterate (i = 2 to 6)
  i=2: fibonacci[1] + fibonacci[0] = 1 + 0 = 1  → [0, 1, 1]
  i=3: fibonacci[2] + fibonacci[1] = 1 + 1 = 2  → [0, 1, 1, 2]
  i=4: fibonacci[3] + fibonacci[2] = 2 + 1 = 3  → [0, 1, 1, 2, 3]
  i=5: fibonacci[4] + fibonacci[3] = 3 + 2 = 5  → [0, 1, 1, 2, 3, 5]
  i=6: fibonacci[5] + fibonacci[4] = 5 + 3 = 8  → [0, 1, 1, 2, 3, 5, 8]

Step 5: Return
  Output: [0, 1, 1, 2, 3, 5, 8]
```

## 📐 Mathematical Background

### Fibonacci Sequence Definition

The Fibonacci sequence is defined mathematically as:

```
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)  for n ≥ 2
```

### Properties

1. **Golden Ratio**: As n approaches infinity, the ratio F(n+1)/F(n) approaches φ (phi), the golden ratio:
   ```
   φ = (1 + √5) / 2 ≈ 1.618033988749...
   ```

2. **Binet's Formula**: The nth Fibonacci number can be calculated directly:
   ```
   F(n) = (φⁿ - ψⁿ) / √5
   where φ = (1 + √5) / 2 and ψ = (1 - √5) / 2
   ```

3. **Sum Property**:
   ```
   Sum of first n Fibonacci numbers = F(n+2) - 1
   ```

4. **Even Numbers**: Every third Fibonacci number is even

5. **GCD Property**: gcd(F(m), F(n)) = F(gcd(m, n))

### Sequence Examples

```
n=15: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377]
n=20: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181]
```

## 🔧 Implementation Details

### Why Iterative Instead of Recursive?

**Recursive Approach** (NOT used):
```typescript
// ❌ Not recommended for large n
function fibonacciRecursive(n: number): number {
  if (n <= 1) return n;
  return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}
```

**Problems with recursion**:
- Time complexity: O(2ⁿ) - exponential!
- Space complexity: O(n) due to call stack
- Stack overflow for large n
- Recalculates same values multiple times

**Iterative Approach** (USED):
```typescript
// ✅ Efficient and recommended
function generateFibonacci(n: number): number[] {
  // ... validation ...
  const fibonacci: number[] = [0, 1];
  for (let i = 2; i < n; i++) {
    fibonacci.push(fibonacci[i - 1] + fibonacci[i - 2]);
  }
  return fibonacci;
}
```

**Advantages**:
- Time complexity: O(n) - linear
- Space complexity: O(n) - only for result array
- No stack overflow risk
- Better performance
- Simpler to understand

### Type Safety Features

```typescript
// TypeScript ensures type correctness
function generateFibonacci(n: number): number[] {
  // TypeScript compiler checks:
  // ✓ Parameter n must be a number
  // ✓ Return value must be an array of numbers
  // ✓ All array operations are type-safe
}

// Usage
const result: number[] = generateFibonacci(10);  // ✓ Type-safe
// const wrong: string[] = generateFibonacci(10);  // ✗ Compile error
```

### Input Validation Strategy

```typescript
// 1. Check integer constraint
if (!Number.isInteger(n)) {
  throw new Error('Input must be an integer');
}
// Catches: 3.5, 2.7, NaN, Infinity, -Infinity

// 2. Check non-negative constraint
if (n < 0) {
  throw new Error('Input must be a non-negative number');
}
// Catches: -1, -5, -100

// 3. Edge cases handled separately for clarity
if (n === 0) return [];
if (n === 1) return [0];
```

## 📊 Performance Analysis

### Time Complexity

- **Best Case**: O(1) - when n=0 or n=1 (edge cases)
- **Average Case**: O(n) - iterates n-2 times
- **Worst Case**: O(n) - linear time

### Space Complexity

- **Result Array**: O(n) - stores n numbers
- **Auxiliary Space**: O(1) - only uses constant extra variables
- **Total**: O(n)

### Performance Benchmarks

Approximate execution times (may vary by system):

| n | Time | Output Size |
|---|------|-------------|
| 10 | < 1ms | 10 numbers |
| 100 | < 1ms | 100 numbers |
| 1,000 | ~1ms | 1,000 numbers |
| 10,000 | ~10ms | 10,000 numbers |
| 100,000 | ~100ms | 100,000 numbers |

**Note**: For very large n (> 1000), the numbers will exceed JavaScript's safe integer range (2⁵³ - 1).

### Memory Usage

Each number in JavaScript is stored as a 64-bit floating-point:
- Memory per number: 8 bytes
- For n=1000: ~8KB
- For n=10000: ~80KB
- For n=100000: ~800KB

## ⚠️ Error Handling

### Error Types and Scenarios

#### 1. Non-Integer Input

```typescript
// Float numbers
generateFibonacci(3.5);   // Error: Input must be an integer
generateFibonacci(10.1);  // Error: Input must be an integer

// Special values
generateFibonacci(NaN);      // Error: Input must be an integer
generateFibonacci(Infinity); // Error: Input must be an integer
```

#### 2. Negative Input

```typescript
generateFibonacci(-1);   // Error: Input must be a non-negative number
generateFibonacci(-10);  // Error: Input must be a non-negative number
```

#### 3. Proper Error Handling Pattern

```typescript
function safeGenerateFibonacci(n: number): number[] | null {
  try {
    return generateFibonacci(n);
  } catch (error) {
    console.error(`Failed to generate Fibonacci sequence: ${error.message}`);
    return null;
  }
}

// Usage
const result = safeGenerateFibonacci(10);
if (result !== null) {
  console.log('Success:', result);
} else {
  console.log('Failed to generate sequence');
}
```

## 💡 Usage Patterns

### Pattern 1: Basic Generation

```typescript
const sequence = generateFibonacci(10);
console.log(sequence);
```

### Pattern 2: Finding Specific Fibonacci Number

```typescript
function getNthFibonacci(n: number): number {
  if (n === 0) return 0;
  const sequence = generateFibonacci(n + 1);
  return sequence[n];
}

console.log(getNthFibonacci(10));  // 55
```

### Pattern 3: Sum of Fibonacci Numbers

```typescript
function sumFibonacci(n: number): number {
  return generateFibonacci(n).reduce((sum, num) => sum + num, 0);
}

console.log(sumFibonacci(10));  // 88
```

### Pattern 4: Fibonacci Numbers Less Than X

```typescript
function fibonacciLessThan(max: number): number[] {
  if (max <= 0) return [];
  if (max === 1) return [0];
  
  const result: number[] = [0, 1];
  let a = 0, b = 1;
  
  while (a + b < max) {
    const next = a + b;
    result.push(next);
    a = b;
    b = next;
  }
  
  return result;
}

console.log(fibonacciLessThan(100));
// [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]
```

### Pattern 5: Even Fibonacci Numbers

```typescript
function evenFibonacci(n: number): number[] {
  return generateFibonacci(n).filter(num => num % 2 === 0);
}

console.log(evenFibonacci(15));  // [0, 2, 8, 34, 144]
```

### Pattern 6: Fibonacci Ratios (Golden Ratio Convergence)

```typescript
function fibonacciRatios(n: number): number[] {
  const sequence = generateFibonacci(n);
  const ratios: number[] = [];
  
  for (let i = 1; i < sequence.length; i++) {
    if (sequence[i - 1] !== 0) {
      ratios.push(sequence[i] / sequence[i - 1]);
    }
  }
  
  return ratios;
}

console.log(fibonacciRatios(10));
// Ratios converge to golden ratio φ ≈ 1.618
```

## 🎯 Edge Cases

### Comprehensive Edge Case Testing

```typescript
// Edge Case 1: n = 0 (empty sequence)
console.log(generateFibonacci(0));  // []

// Edge Case 2: n = 1 (single element)
console.log(generateFibonacci(1));  // [0]

// Edge Case 3: n = 2 (two elements)
console.log(generateFibonacci(2));  // [0, 1]

// Edge Case 4: n = 3 (first non-trivial case)
console.log(generateFibonacci(3));  // [0, 1, 1]

// Edge Case 5: Large n (performance test)
console.log(generateFibonacci(100).length);  // 100

// Error Case 1: Negative number
try { generateFibonacci(-1); } catch (e) { console.log(e.message); }

// Error Case 2: Float number
try { generateFibonacci(5.5); } catch (e) { console.log(e.message); }

// Error Case 3: NaN
try { generateFibonacci(NaN); } catch (e) { console.log(e.message); }

// Error Case 4: Infinity
try { generateFibonacci(Infinity); } catch (e) { console.log(e.message); }
```

## 🧪 Testing

### Unit Test Suite

```typescript
interface TestCase {
  input: number;
  expected: number[] | Error;
  description: string;
}

const testCases: TestCase[] = [
  {
    input: 0,
    expected: [],
    description: 'Empty sequence for n=0'
  },
  {
    input: 1,
    expected: [0],
    description: 'Single element for n=1'
  },
  {
    input: 2,
    expected: [0, 1],
    description: 'Two elements for n=2'
  },
  {
    input: 5,
    expected: [0, 1, 1, 2, 3],
    description: 'First 5 Fibonacci numbers'
  },
  {
    input: 10,
    expected: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34],
    description: 'First 10 Fibonacci numbers'
  }
];

// Run tests
function runTests() {
  let passed = 0;
  let failed = 0;
  
  testCases.forEach(test => {
    try {
      const result = generateFibonacci(test.input);
      const isEqual = JSON.stringify(result) === JSON.stringify(test.expected);
      
      if (isEqual) {
        console.log(`✓ PASS: ${test.description}`);
        passed++;
      } else {
        console.log(`✗ FAIL: ${test.description}`);
        console.log(`  Expected: ${JSON.stringify(test.expected)}`);
        console.log(`  Got: ${JSON.stringify(result)}`);
        failed++;
      }
    } catch (error) {
      console.log(`✗ ERROR: ${test.description}`);
      console.log(`  ${error.message}`);
      failed++;
    }
  });
  
  console.log(`\nResults: ${passed} passed, ${failed} failed`);
}

// Error test cases
const errorCases = [
  { input: -1, errorMessage: 'Input must be a non-negative number' },
  { input: -10, errorMessage: 'Input must be a non-negative number' },
  { input: 3.5, errorMessage: 'Input must be an integer' },
  { input: NaN, errorMessage: 'Input must be an integer' },
  { input: Infinity, errorMessage: 'Input must be an integer' }
];

function runErrorTests() {
  let passed = 0;
  let failed = 0;
  
  errorCases.forEach(test => {
    try {
      generateFibonacci(test.input);
      console.log(`✗ FAIL: Should throw error for ${test.input}`);
      failed++;
    } catch (error) {
      if (error.message === test.errorMessage) {
        console.log(`✓ PASS: Correctly throws error for ${test.input}`);
        passed++;
      } else {
        console.log(`✗ FAIL: Wrong error message for ${test.input}`);
        console.log(`  Expected: ${test.errorMessage}`);
        console.log(`  Got: ${error.message}`);
        failed++;
      }
    }
  });
  
  console.log(`\nError Tests: ${passed} passed, ${failed} failed`);
}
```

## 🚀 Optimization Considerations

### Current Implementation Strengths

1. **Linear Time Complexity**: O(n) is optimal for generating all n numbers
2. **Simple and Readable**: Easy to understand and maintain
3. **Type-Safe**: TypeScript provides compile-time guarantees
4. **Comprehensive Validation**: Catches all invalid inputs

### Potential Optimizations

#### 1. For Generating Single Fibonacci Number

If you only need the nth Fibonacci number (not the sequence):

```typescript
function nthFibonacci(n: number): number {
  if (n === 0) return 0;
  if (n === 1) return 1;
  
  let a = 0, b = 1;
  for (let i = 2; i <= n; i++) {
    [a, b] = [b, a + b];
  }
  return b;
}
// Space complexity: O(1) instead of O(n)
```

#### 2. Using BigInt for Large Numbers

For sequences beyond JavaScript's safe integer range:

```typescript
function generateFibonacciBigInt(n: number): bigint[] {
  if (n === 0) return [];
  if (n === 1) return [0n];
  
  const fibonacci: bigint[] = [0n, 1n];
  for (let i = 2; i < n; i++) {
    fibonacci.push(fibonacci[i - 1] + fibonacci[i - 2]);
  }
  return fibonacci;
}

// Can handle much larger numbers
console.log(generateFibonacciBigInt(100)[99]);
// 218922995834555169026n
```

#### 3. Memoization for Repeated Calls

If generating sequences repeatedly:

```typescript
class FibonacciGenerator {
  private cache: number[] = [0, 1];
  
  generate(n: number): number[] {
    if (n <= this.cache.length) {
      return this.cache.slice(0, n);
    }
    
    for (let i = this.cache.length; i < n; i++) {
      this.cache.push(this.cache[i - 1] + this.cache[i - 2]);
    }
    
    return this.cache.slice(0, n);
  }
}

// Reuses previously calculated values
const generator = new FibonacciGenerator();
console.log(generator.generate(10));  // Calculates 0-9
console.log(generator.generate(15));  // Only calculates 10-14
```

## 🔄 Alternatives and Variations

### 1. Generator Function

```typescript
function* fibonacciGenerator(): Generator<number> {
  let a = 0, b = 1;
  yield a;
  yield b;
  
  while (true) {
    [a, b] = [b, a + b];
    yield b;
  }
}

// Usage
const gen = fibonacciGenerator();
console.log(gen.next().value);  // 0
console.log(gen.next().value);  // 1
console.log(gen.next().value);  // 1
console.log(gen.next().value);  // 2
```

### 2. Matrix Exponentiation (O(log n) for nth number)

```typescript
function fibonacciMatrix(n: number): number {
  if (n === 0) return 0;
  if (n === 1) return 1;
  
  function matrixMultiply(a: number[][], b: number[][]): number[][] {
    return [
      [a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]],
      [a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]]
    ];
  }
  
  function matrixPower(matrix: number[][], n: number): number[][] {
    if (n === 1) return matrix;
    if (n % 2 === 0) {
      const half = matrixPower(matrix, n / 2);
      return matrixMultiply(half, half);
    }
    return matrixMultiply(matrix, matrixPower(matrix, n - 1));
  }
  
  const result = matrixPower([[1, 1], [1, 0]], n);
  return result[0][1];
}
```

### 3. Closed-Form Formula (Binet's Formula)

```typescript
function fibonacciBinet(n: number): number {
  const phi = (1 + Math.sqrt(5)) / 2;
  const psi = (1 - Math.sqrt(5)) / 2;
  return Math.round((Math.pow(phi, n) - Math.pow(psi, n)) / Math.sqrt(5));
}
// Note: Less accurate for large n due to floating-point precision
```

## 🌍 Real-World Applications

### 1. Algorithm Analysis

Fibonacci numbers appear in the analysis of various algorithms, especially those involving recursive decomposition.

### 2. Nature and Biology

- Flower petals often follow Fibonacci numbers
- Spiral patterns in shells and galaxies
- Branching in trees
- Arrangement of leaves on a stem

### 3. Financial Markets

- Fibonacci retracements in technical analysis
- Trading strategies based on golden ratio

### 4. Computer Science

- Fibonacci heap data structure
- Analysis of Euclidean algorithm
- Optimal caching strategies

### 5. Art and Architecture

- Golden ratio in design
- Proportions in Renaissance art
- Modern architectural design

### 6. Data Structure Testing

- Fibonacci numbers used to test sorting algorithms
- Worst-case scenarios for certain data structures

---

## 📝 Summary

The `fibonacci.ts` file provides a robust, efficient, and well-documented implementation of a Fibonacci sequence generator. Key takeaways:

- ✅ **Efficient**: O(n) time complexity
- ✅ **Type-Safe**: Full TypeScript support
- ✅ **Robust**: Comprehensive error handling
- ✅ **Well-Documented**: Extensive JSDoc and examples
- ✅ **Tested**: Handles all edge cases
- ✅ **Maintainable**: Clear, readable code

For the main project documentation, see [README.md](../README.md).
