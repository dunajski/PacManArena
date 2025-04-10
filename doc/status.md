## Current Project Status

W tym momencie istnieje podstawowa struktura projektu Pac-Man Arena w C++ z użyciem biblioteki SFML. Aplikacja została podzielona na dwie części:
1. **Serwer** (klasa `Server`) – nasłuchuje na porcie i przyjmuje połączenia klientów, przechowując ich gniazda w wektorze. W aktualnej implementacji serwer potrafi tylko wysłać/odebrać proste komunikaty, nie ma jeszcze rozbudowanej synchronizacji rozgrywki.
2. **Klient** (klasa `Client`) – łączy się z serwerem, po czym uruchamia okno SFML i startuje jednosesyjną rozgrywkę z Pac-Manem w trybie lokalnym (single-player). Pac-Man, duchy i kropki są renderowane, a gracz może poruszać się klawiszami strzałek.

### Co działa
- Mapa planszy Pac-Mana jest zainicjalizowana w klasie `Game::initialize_map()`.
- Obiekty takie jak Pac-Man (`Pacman`), duch (`Ghost`), zwykła kropka (`Dot`) i kropka mocy (`PowerDot`) są tworzone i umieszczane w `std::vector<std::unique_ptr<GameEntity>>`.
- Klasa `Drawer` rysuje ściany (mapę) i wszystkie utworzone encje.
- Pac-Man może się poruszać w czterech kierunkach zgodnie z układem ścieżek w mapie (ściana jest wartością `1`, a Pac-Man nie może w nią wejść).

### Czego brakuje
1. **Integracja sieciowa** – choć serwer i klient mają proste łączenie się, nie ma jeszcze:
    - Synchronizacji stanu gry między wieloma klientami.
    - Obsługi lobby (potwierdzanie gotowości, czekanie na czterech graczy).
    - Wiele instancji planszy (po jednej dla każdego gracza) nie jest jeszcze zaimplementowane.
2. **Kolizje i punktacja** – obecnie Pac-Man nie „zjada” kropek, nie ma liczenia punktów, nie ma odejmowania żyć w przypadku kontaktu z duchem.
3. **Menu i ekrany** – w kodzie nie ma jeszcze klas zarządzających menu głównym, ekranem pomocy ani wynikami końcowymi (tylko prosta pętla SFML w `Client::run_game()`).
4. **Zaawansowany ruch duchów** – w planach była losowość lub A*, ale w aktualnym stanie duch ma jedynie kształt graficzny, nie porusza się.
5. **Obsługa wyjścia z gry** – obecnie można wyjść z okna SFML (krzyżyk okna), ale nie ma osobnego przycisku „Opuść grę” w trakcie rozgrywki.

### Plany rozwoju
- Dodać obsługę kolizji i rejestrowanie zjedzonych kropek oraz punktów (np. w metodzie `Game::update()` reagować na pozycję Pac-Mana i usuwać kropki z wektora `game_entities`).
- Zaimplementować synchronizację stanu na serwerze (utrzymywanie np. listy `Game` lub wspólnej mapy) i wysyłanie jej do wszystkich klientów.
- Rozwinąć logikę menu i lobby, by klienci faktycznie czekali na siebie, a serwer przydzielał sloty.
- Poprawić poruszanie się duchów (dodać `Ghost::update()` z losowym lub inteligentniejszym wyborem trasy).

