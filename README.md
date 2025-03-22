# Pac-Man Arena

## Opis projektu
Pac-Man Arena to wieloosobowa gra online inspirowana klasycznym Pac-Manem. Gra umożliwia rozgrywkę dla czterech graczy w trybie survival, gdzie ostatni ocalały zostaje zwycięzcą.

## Funkcjonalności
- Gra wieloosobowa online dla 4 graczy
- Tryb survival – gra trwa do momentu, aż zostanie tylko jeden gracz
- Możliwość obserwowania rozgrywki po utracie wszystkich żyć
- System lobby do wyszukiwania graczy
- Interaktywne menu z możliwością wyjścia

## Technologie
- **Grafika:** SFML 3.0
- **Sieć:** SFML Network (opcjonalnie Asio Boost)
- **Obsługa wejścia:** SFML
- **Kompilator:** MinGW
- **Narzędzia developerskie:** Visual Studio Code / CLion, CMake, GitHub

## Struktura projektu
Projekt został podzielony na dwie główne aplikacje:
- **Aplikacja klienta** – obsługuje interakcję użytkownika, rysowanie gry i połączenie z serwerem
- **Aplikacja serwera** – zarządza stanem gry i synchronizuje rozgrywkę między graczami

## Uruchomienie
### Wymagania
- MinGW
- SFML 3.0
- CMake
- Opcjonalnie: CLion / Visual Studio Code

### Instalacja
1. Sklonuj repozytorium:
   ```sh
   git clone https://github.com/TwojeRepozytorium.git
   cd Pac-Man-Arena
   ```
2. Skonfiguruj projekt przy użyciu CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Uruchom serwer:
   ```sh
   ./server
   ```
4. Uruchom klienta:
   ```sh
   ./client
   ```

## Autor
Michał Dunajski – michal.dunajski.stud@pw.edu.pl
