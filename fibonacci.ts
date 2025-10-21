/**
 * Generates a Fibonacci sequence of a specified length.
 * 
 * The Fibonacci sequence is a series of numbers where each number is the sum
 * of the two preceding ones, starting from 0 and 1. The sequence begins:
 * 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
 * 
 * @param n - The number of Fibonacci numbers to generate. Must be a non-negative integer.
 * @returns An array containing the first n Fibonacci numbers.
 * @throws {Error} If n is negative or not an integer.
 * 
 * @example
 * // Generate the first 10 Fibonacci numbers
 * generateFibonacci(10);
 * // Returns: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]
 * 
 * @example
 * // Edge case: n = 0
 * generateFibonacci(0);
 * // Returns: []
 * 
 * @example
 * // Edge case: n = 1
 * generateFibonacci(1);
 * // Returns: [0]
 */
function generateFibonacci(n: number): number[] {
  // Validate that n is an integer
  if (!Number.isInteger(n)) {
    throw new Error('Input must be an integer');
  }

  // Validate that n is not negative
  if (n < 0) {
    throw new Error('Input must be a non-negative number');
  }

  // Handle edge case: n = 0
  if (n === 0) {
    return [];
  }

  // Handle edge case: n = 1
  if (n === 1) {
    return [0];
  }

  // Initialize the sequence with the first two Fibonacci numbers
  const fibonacci: number[] = [0, 1];

  // Generate the remaining Fibonacci numbers
  for (let i = 2; i < n; i++) {
    const nextNumber = fibonacci[i - 1] + fibonacci[i - 2];
    fibonacci.push(nextNumber);
  }

  return fibonacci;
}

// ============================================================================
// USAGE EXAMPLES
// ============================================================================

// Example 1: Basic usage - Generate the first 10 Fibonacci numbers
// console.log(generateFibonacci(10));
// Output: [0, 1, 1, 2, 3, 5, 8, 13, 21, 34]

// Example 2: Generate the first 5 Fibonacci numbers
// console.log(generateFibonacci(5));
// Output: [0, 1, 1, 2, 3]

// Example 3: Edge case - n = 0 (empty array)
// console.log(generateFibonacci(0));
// Output: []

// Example 4: Edge case - n = 1 (single element)
// console.log(generateFibonacci(1));
// Output: [0]

// Example 5: Edge case - n = 2 (two elements)
// console.log(generateFibonacci(2));
// Output: [0, 1]

// Example 6: Error case - Negative number (throws error)
// console.log(generateFibonacci(-5));
// Error: Input must be a non-negative number

// Example 7: Error case - Non-integer input (throws error)
// console.log(generateFibonacci(3.14));
// Error: Input must be an integer

// Example 8: Error case - Decimal number (throws error)
// console.log(generateFibonacci(7.5));
// Error: Input must be an integer

export { generateFibonacci };
