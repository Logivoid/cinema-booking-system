# Cinema Booking System

A menu-driven C++ console application for basic cinema management. It supports
adding and removing movies, booking and cancelling seats, purchasing snacks,
and displaying the current movies, tickets, seats, and snack inventory.

## Features

- Manage a list of movies
- Book one of 100 seats for a movie
- Cancel existing tickets
- Purchase snacks against a booked ticket
- Track snack inventory and ticket totals during the session

## Build and run

1. Open `Project1.sln` in Visual Studio 2022.
2. Select a Debug or Release configuration.
3. Build and run `Project1`.

The project is intended for Windows because it uses Visual Studio's `scanf_s`
and `strcpy_s` input functions.

The project uses the Visual Studio 2022 C++ toolset (`v143`). All application
data is stored in memory and is reset when the program exits.

Movie names and genres are entered as single words because the current console
input format uses whitespace-delimited values.

Durations are entered in minutes, ratings must be between 0 and 5, and prices
must be between 0 and 500,000.

## Typical workflow

1. Add a movie with its duration, rating, and ticket price.
2. Book a seat for the movie and note the seat number.
3. Optionally buy snacks for the booked ticket.
4. Use the display options to review movies, snacks, or tickets.

Seat numbers run from 0 through 99. Snack quantities cannot exceed the
remaining inventory.
