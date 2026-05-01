# Disneyland Visitor App (C++)

Simple C++ console app for tracking number of visitors and revenue per day.

## What it does

- Stores data for multiple days
- Adds new days (auto expands array when full)
- Deletes first X days (with error check)
- Calculates total visitors between two days
- Finds 2 days with the lowest revenue
- Prints all data

## Sectors

### Interactive
- Only total visitors
- Everyone pays same ticket price

### Exhibition
- Tracks:
  - adults
  - school kids (half price)
  - kids under 7 (free)
- Revenue depends on visitor type

## Notes

- Uses templates (`Aplikacija<T>`)
- Dynamic memory (`new/delete`)
- Tested in `main()` with 5+ days for both sectors
