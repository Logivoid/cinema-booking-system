#include <stdio.h>
#include <string.h>

const int MAX_ITEMS = 100;
const int SEAT_COUNT = 100;


struct Movie {
	char name[50];
	char genre[50];
	int duration;
	double rating;
	double amount;
};

struct Snack {
	char name[50];
	int amount;
	double price;
};

struct Ticket {
	char movieName[50];
	int seatNumber;
	double amount;
};


void displayMenu() {
	printf("\n-------------------------\n");
	printf("|\tMenu\t\t|\n");
	printf("|0. Display menu (Again)|\n");
	printf("|1. Book a ticket\t|\n");
	printf("|2. Cancel a ticket\t|\n");
	printf("|3. Add a new movie\t|\n");
	printf("|4. Remove a movie\t|\n");
	printf("|5. Display all movies\t|\n");
	printf("|6. Buy snacks\t\t|\n");
	printf("|7. Display all snacks\t|\n");
	printf("|8. Display all tickets\t|\n");
	printf("|9. Exit\t\t|\n");
	printf("-------------------------\n");
}

void displayMovie(Movie movie) {
	printf("Name: %s\n", movie.name);
	printf("Genre: %s\n", movie.genre);
	printf("Duration: %d\n", movie.duration);
	printf("Rating: %.1f\n", movie.rating);
	printf("Amount: %.2f\n", movie.amount);
}

void displaySnack(Snack snack) {
	printf("Name: %s, Price: %.2f (%d Available)\n", snack.name, snack.price, snack.amount);
}

void displayTicket(Ticket ticket) {
	printf("Movie name: %s\n", ticket.movieName);
	printf("Seat number: %d\n", ticket.seatNumber);
	printf("Amount: %lf\n", ticket.amount);
}


void displayAvailableSeats(Ticket tickets[], int n, char movieName[]) {
	printf("Available seats:\n");
	for (int i = 0; i < SEAT_COUNT; i++) {
		bool isAvailable = true;
		for (int j = 0; j < n; j++) {
			if (tickets[j].seatNumber == i && strcmp(tickets[j].movieName, movieName) == 0) {
				isAvailable = false;
				break;
			}
		}
		if (isAvailable) {
			printf("%d\t", i);
		}
		else {
			printf("X\t");
		}
		if (i % 10 == 9) {
			printf("\n");
		}
	}
	printf("\n");
}



void displayAllMovies(Movie movies[], int n, Ticket tickets[], int k, bool show = false) {
	if (n == 0) {
		printf("No movies available!\n");
		return;
	}
	printf("Movies:\n");
	for (int i = 0; i < n; i++) {
		printf("%d)\n", i + 1);
		displayMovie(movies[i]);
		if (show)
		{
			displayAvailableSeats(tickets, k, movies[i].name);
		}
		printf("\n-------------------------\n");
	}
}

void displayAllSnacks(Snack snacks[], int n) {
	if (n == 0) {
		printf("No snacks available!\n");
		return;
	}
	printf("Snacks:\n");
	for (int i = 0; i < n; i++) {
		printf("%d) ", i + 1);
		displaySnack(snacks[i]);
	}
}

void displayAllTickets(Ticket tickets[], int n) {
	if (n == 0) {
		printf("No tickets available!\n");
		return;
	}
	printf("Tickets:\n");
	for (int i = 0; i < n; i++) {
		printf("%d)\n", i + 1);
		displayTicket(tickets[i]);
	}
}



void bookTicket(Ticket tickets[], int& n, Movie movies[], int& m) {
	if (m == 0) {
		printf("No movies available!\n");
		return;
	}
	if (n >= MAX_ITEMS) {
		printf("Ticket capacity reached!\n");
		return;
	}
	int movieNumber;
	displayAllMovies(movies, m, tickets, n);
	printf("Enter movie number: ");
	scanf_s("%d", &movieNumber);
	if (movieNumber < 1 || movieNumber >= m + 1) {
		printf("Invalid movie number!\n");
		return;
	}
	displayMovie(movies[movieNumber - 1]);
	displayAvailableSeats(tickets, n, movies[movieNumber - 1].name);
	int seatNumber;
	printf("Enter seat number: ");
	scanf_s("%d", &seatNumber);
	if (seatNumber < 0 || seatNumber >= SEAT_COUNT) {
		printf("Invalid seat number!\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		if (tickets[i].seatNumber == seatNumber && strcmp(tickets[i].movieName, movies[movieNumber - 1].name) == 0) {
			printf("Seat already booked!\n");
			return;
		}
	}
	Ticket ticket;
	ticket.seatNumber = seatNumber;
	ticket.amount = movies[movieNumber - 1].amount;
	strcpy_s(ticket.movieName, movies[movieNumber - 1].name);
	tickets[n] = ticket;
	n++;
	printf("Booked successfully!\n");
}


void cancelTicket(Movie movies[], int& n, Ticket tickets[], int& t) {
	if (t == 0) {
		printf("No tickets available!\n");
		return;
	}
	displayAllMovies(movies, n, tickets, t);
	int movieNumber;
	printf("Enter movie number: ");
	scanf_s("%d", &movieNumber);
	if (movieNumber < 1 || movieNumber >= n + 1) {
		printf("Invalid movie number!\n");
		return;
	}
	displayMovie(movies[movieNumber - 1]);
	int seatNumber;
	bool found = false;
	printf("Enter seat number: ");
	scanf_s("%d", &seatNumber);
	if (seatNumber < 0 || seatNumber >= SEAT_COUNT) {
		printf("Invalid seat number!\n");
		return;
	}
	for (int i = 0; i < t; i++) {
		if (tickets[i].seatNumber == seatNumber && strcmp(tickets[i].movieName, movies[movieNumber - 1].name) == 0) {
			for (int j = i; j < t - 1; j++) {
				tickets[j] = tickets[j + 1];
			}
			t--;
			i--;
			found = true;
		}
	}
	if (found) {
		printf("Cancelled successfully!\n");
	}
	else {
		printf("Ticket not found!\n");
	}
}


void addMovie(Movie movies[], int& n) {
	if (n >= MAX_ITEMS) {
		printf("Movie capacity reached!\n");
		return;
	}
	Movie movie;
	printf("Enter movie name: ");
	scanf_s("%s", &movie.name, 50);
	printf("Enter genre: ");
	scanf_s("%s", &movie.genre, 50);
	printf("Enter duration (minutes): ");
	scanf_s("%d", &movie.duration);
	if (movie.duration < 0 || movie.duration > 500000) {
		printf("Invalid duration!\n");
		return;
	}
	printf("Enter rating (0.0 <-> 5.0): ");
	scanf_s("%lf", &movie.rating);
	if (movie.rating < 0.0 || movie.rating > 5.0) {
		printf("Invalid rating!\n");
		return;
	}
	printf("Enter amount (0 <-> 500,000): ");
	scanf_s("%lf", &movie.amount);

	if (movie.amount < 0.0 || movie.amount > 500000) {
		printf("Invalid amount!\n");
		return;
	}
	movies[n] = movie;
	n++;
	printf("Added successfully!\n");
}

void cancelMovieTickets(Ticket tickets[], int& n, char movieName[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(tickets[i].movieName, movieName) == 0) {
			for (int j = i; j < n - 1; j++) {
				tickets[j] = tickets[j + 1];
			}
			n--;
			i--;
		}
	}
}



void removeMovie(Ticket tickets[], int& t, Movie movies[], int& n) {
	if (n == 0) {
		printf("No movies available!\n");
		return;
	}
	displayAllMovies(movies, n, tickets, t);
	int movieNumber;
	printf("Enter movie number: ");
	scanf_s("%d", &movieNumber);
	if (movieNumber < 1 || movieNumber >= n + 1) {
		printf("Invalid movie number!\n");
		return;
	}
	displayMovie(movies[movieNumber - 1]);
	cancelMovieTickets(tickets, t, movies[movieNumber - 1].name);
	for (int i = movieNumber - 1; i < n - 1; i++) {

		movies[i] = movies[i + 1];
	}
	n--;
	printf("Removed successfully!\n");

}


void buySnack(Snack snacks[], int& n, Movie movies[], int& m, Ticket tickets[], int& k) {
	if (m == 0) {
		printf("No movies available!\n");
		return;
	}

	if (k == 0) {
		printf("No tickets available!\n");
		return;
	}
	if (n == 0) {
		printf("No snacks available!\n");
		return;
	}
	else {
		displayAllSnacks(snacks, n);
	}

	int movieNumber, seatNumber;
	bool found = false;
	displayAllMovies(movies, m, tickets, k);
	printf("Enter movie number: ");
	scanf_s("%d", &movieNumber);
	if (movieNumber < 1 || movieNumber >= m + 1) {
		printf("Invalid movie number!\n");
		return;
	}
	displayMovie(movies[movieNumber - 1]);
	printf("Enter seat number: ");
	scanf_s("%d", &seatNumber);
	if (seatNumber < 0 || seatNumber >= SEAT_COUNT) {
		printf("Invalid seat number!\n");
		return;
	}
	for (int i = 0; i < k; i++) {
		if (tickets[i].seatNumber == seatNumber && strcmp(tickets[i].movieName, movies[movieNumber - 1].name) == 0) {
			found = true;
			int snackNumber;
			printf("Enter snack number: ");
			scanf_s("%d", &snackNumber);
			if (snackNumber < 1 || snackNumber >= n + 1) {
				printf("Invalid snack number!\n");
				return;
			}
			displaySnack(snacks[snackNumber - 1]);
			int amount;
			printf("Enter amount: ");
			scanf_s("%d", &amount);
			if (amount <= 0 || amount > snacks[snackNumber - 1].amount) {
				printf("Invalid amount!\n");
				return;
			}
			tickets[i].amount += amount * snacks[snackNumber - 1].price;
			snacks[snackNumber - 1].amount -= amount;
			printf("Bought successfully!\n");
		}
	}
	if (!found) {
		printf("Ticket not found!\n");
	}
}


int main() {
	Movie movies[MAX_ITEMS];
	int n = 0;
	Snack snacks[MAX_ITEMS] = { {"Popcorn", 100, 5000}, {"Coca", 100, 15000}, {"Pepsi", 100, 12000}, {"Water", 100, 2500}, {"Hotdog", 100, 50000} };
	int m = 5;
	Ticket tickets[MAX_ITEMS];
	int k = 0;

	displayMenu();
	while (true) {
		int choice;
		printf("Enter your choice: ");
		scanf_s("%d", &choice);
		switch (choice) {
		case 0:
			displayMenu();
			break;
		case 1:
			bookTicket(tickets, k, movies, n);
			break;
		case 2:
			cancelTicket(movies, n, tickets, k);
			break;
		case 3:
			addMovie(movies, n);
			break;
		case 4:
			removeMovie(tickets, k, movies, n);
			break;
		case 5:
			displayAllMovies(movies, n, tickets, k, true);
			break;
		case 6:
			buySnack(snacks, m, movies, n, tickets, k);
			break;
		case 7:
			displayAllSnacks(snacks, m);
			break;
		case 8:
			displayAllTickets(tickets, k);
			break;
		case 9:
			return 0;
		default:
			printf("Invalid choice!\n");
		}

		printf("-----------New Choice-----------\n");

	}
	return 0;
}
