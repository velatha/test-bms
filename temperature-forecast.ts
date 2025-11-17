/**
 * Temperature Forecast Checker
 * 
 * This program checks the temperature forecast for the next 10 days
 * and reports the results with detailed analysis.
 */

interface DayForecast {
  day: number;
  date: string;
  temperature: number;
  condition: string;
}

interface ForecastReport {
  forecasts: DayForecast[];
  averageTemp: number;
  maxTemp: number;
  minTemp: number;
  hottestDay: number;
  coldestDay: number;
}

/**
 * Generates a temperature forecast for the next 10 days
 * In a real application, this would fetch data from a weather API
 */
function generateForecast(): DayForecast[] {
  const forecasts: DayForecast[] = [];
  const conditions = ['Sunny', 'Partly Cloudy', 'Cloudy', 'Rainy', 'Clear'];
  const baseDate = new Date();
  
  for (let i = 1; i <= 10; i++) {
    const forecastDate = new Date(baseDate);
    forecastDate.setDate(baseDate.getDate() + i);
    
    // Generate realistic temperature variations (between 15°C and 30°C)
    const temperature = Math.round(20 + Math.sin(i * 0.5) * 8 + Math.random() * 4);
    const condition = conditions[Math.floor(Math.random() * conditions.length)];
    
    forecasts.push({
      day: i,
      date: forecastDate.toISOString().split('T')[0],
      temperature,
      condition
    });
  }
  
  return forecasts;
}

/**
 * Analyzes the forecast data and generates a comprehensive report
 */
function analyzeForecast(forecasts: DayForecast[]): ForecastReport {
  const temperatures = forecasts.map(f => f.temperature);
  const averageTemp = temperatures.reduce((sum, temp) => sum + temp, 0) / temperatures.length;
  const maxTemp = Math.max(...temperatures);
  const minTemp = Math.min(...temperatures);
  
  const hottestDay = forecasts.find(f => f.temperature === maxTemp)?.day || 0;
  const coldestDay = forecasts.find(f => f.temperature === minTemp)?.day || 0;
  
  return {
    forecasts,
    averageTemp: Math.round(averageTemp * 10) / 10,
    maxTemp,
    minTemp,
    hottestDay,
    coldestDay
  };
}

/**
 * Formats and displays the forecast report
 */
function displayForecastReport(report: ForecastReport): void {
  console.log('\n=== 10-DAY TEMPERATURE FORECAST REPORT ===\n');
  
  console.log('Daily Forecasts:');
  console.log('-'.repeat(60));
  console.log('Day | Date       | Temperature | Condition');
  console.log('-'.repeat(60));
  
  report.forecasts.forEach(forecast => {
    console.log(
      `${forecast.day.toString().padStart(3)} | ` +
      `${forecast.date} | ` +
      `${forecast.temperature.toString().padStart(5)}°C     | ` +
      `${forecast.condition}`
    );
  });
  
  console.log('-'.repeat(60));
  console.log('\nSummary Statistics:');
  console.log(`  Average Temperature: ${report.averageTemp}°C`);
  console.log(`  Highest Temperature: ${report.maxTemp}°C (Day ${report.hottestDay})`);
  console.log(`  Lowest Temperature:  ${report.minTemp}°C (Day ${report.coldestDay})`);
  console.log(`  Temperature Range:   ${report.maxTemp - report.minTemp}°C`);
  
  // Additional insights
  console.log('\nInsights:');
  if (report.averageTemp > 25) {
    console.log('  ⚠️  Expect warm weather overall - stay hydrated!');
  } else if (report.averageTemp < 18) {
    console.log('  ❄️  Expect cool weather overall - dress warmly!');
  } else {
    console.log('  ✓  Pleasant temperature range expected.');
  }
  
  const tempRange = report.maxTemp - report.minTemp;
  if (tempRange > 10) {
    console.log('  ⚠️  Significant temperature variations expected.');
  } else {
    console.log('  ✓  Stable temperature conditions expected.');
  }
  
  console.log('\n' + '='.repeat(60) + '\n');
}

/**
 * Checks if a specific day meets certain temperature criteria
 */
function checkTemperatureCriteria(
  forecasts: DayForecast[],
  minTemp?: number,
  maxTemp?: number
): DayForecast[] {
  return forecasts.filter(forecast => {
    const meetsMin = minTemp === undefined || forecast.temperature >= minTemp;
    const meetsMax = maxTemp === undefined || forecast.temperature <= maxTemp;
    return meetsMin && meetsMax;
  });
}

/**
 * Main function to run the temperature forecast checker
 */
function main(): void {
  console.log('Starting Temperature Forecast Checker...\n');
  
  // Generate forecast data
  const forecasts = generateForecast();
  
  // Analyze the forecast
  const report = analyzeForecast(forecasts);
  
  // Display the complete report
  displayForecastReport(report);
  
  // Additional analysis: Find days with temperature above 25°C
  const warmDays = checkTemperatureCriteria(forecasts, 25);
  if (warmDays.length > 0) {
    console.log(`Found ${warmDays.length} warm day(s) (≥25°C):`);
    warmDays.forEach(day => {
      console.log(`  - Day ${day.day} (${day.date}): ${day.temperature}°C`);
    });
    console.log();
  }
  
  // Additional analysis: Find days with temperature below 20°C
  const coolDays = checkTemperatureCriteria(forecasts, undefined, 20);
  if (coolDays.length > 0) {
    console.log(`Found ${coolDays.length} cool day(s) (≤20°C):`);
    coolDays.forEach(day => {
      console.log(`  - Day ${day.day} (${day.date}): ${day.temperature}°C`);
    });
    console.log();
  }
  
  console.log('Temperature forecast check completed successfully! ✓');
}

// Run the program
if (require.main === module) {
  main();
}

// Export functions for testing
export {
  generateForecast,
  analyzeForecast,
  displayForecastReport,
  checkTemperatureCriteria,
  DayForecast,
  ForecastReport
};
