# Temperature Forecast Checker

## Overview
A TypeScript program that checks and analyzes temperature forecasts for the next 10 days, providing detailed reports and insights.

## Features

### Core Functionality
- **10-Day Forecast Generation**: Simulates temperature data for the next 10 days
- **Comprehensive Analysis**: Calculates statistics including average, max, and min temperatures
- **Detailed Reporting**: Provides formatted output with daily forecasts and summary statistics
- **Intelligent Insights**: Offers weather recommendations based on temperature patterns
- **Flexible Filtering**: Supports filtering days by temperature criteria

### Data Structure
The program uses TypeScript interfaces to ensure type safety:
- `DayForecast`: Contains day number, date, temperature, and weather condition
- `ForecastReport`: Aggregates all forecast data with statistical analysis

## Usage

### Running the Program
```bash
# Using ts-node
ts-node temperature-forecast.ts

# Or compile and run
tsc temperature-forecast.ts
node temperature-forecast.js
```

### Example Output
```
=== 10-DAY TEMPERATURE FORECAST REPORT ===

Daily Forecasts:
------------------------------------------------------------
Day | Date       | Temperature | Condition
------------------------------------------------------------
  1 | 2024-01-15 |    24°C     | Sunny
  2 | 2024-01-16 |    26°C     | Partly Cloudy
  3 | 2024-01-17 |    27°C     | Clear
...

Summary Statistics:
  Average Temperature: 24.5°C
  Highest Temperature: 29°C (Day 5)
  Lowest Temperature:  19°C (Day 9)
  Temperature Range:   10°C

Insights:
  ✓  Pleasant temperature range expected.
  ⚠️  Significant temperature variations expected.
```

## Functions

### `generateForecast()`
Generates simulated temperature forecast data for 10 days. In a production environment, this would be replaced with actual API calls to a weather service.

### `analyzeForecast(forecasts: DayForecast[])`
Analyzes forecast data to calculate:
- Average temperature across all days
- Maximum and minimum temperatures
- Days with extreme temperatures

### `displayForecastReport(report: ForecastReport)`
Formats and displays the forecast report with:
- Daily breakdown of temperatures
- Summary statistics
- Actionable insights and recommendations

### `checkTemperatureCriteria(forecasts, minTemp?, maxTemp?)`
Filters days based on temperature thresholds, useful for finding:
- Hot days (e.g., above 25°C)
- Cold days (e.g., below 20°C)
- Days within a specific temperature range

## Implementation Details

### Temperature Generation
The program uses a combination of:
- Sinusoidal function for natural temperature variations
- Random noise for realistic day-to-day fluctuations
- Base temperature of 20°C with ±8°C variations

### Weather Conditions
Random selection from: Sunny, Partly Cloudy, Cloudy, Rainy, Clear

## Future Enhancements
- Integration with real weather APIs (e.g., OpenWeatherMap, Weather.gov)
- Support for multiple locations
- Historical data comparison
- Precipitation and humidity tracking
- Graphical visualization of temperature trends
- Alert system for extreme weather conditions

## Type Safety
All functions are fully typed using TypeScript interfaces, ensuring compile-time type checking and better IDE support.

## Export
The program exports all major functions and interfaces for use in other modules or for unit testing purposes.
