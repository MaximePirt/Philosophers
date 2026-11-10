# Philosophers

Projet de l'école 42 (Cercle 3) : implémentation du problème des philosophes
mangeurs (*Dining Philosophers Problem*) en C, avec des threads et des mutex
POSIX.

## Le sujet

Un nombre donné de philosophes sont assis à une table ronde. Chaque
philosophe alterne entre trois états : manger, dormir et penser. Pour manger,
il doit prendre la fourchette à sa gauche et celle à sa droite (une seule
fourchette par voisin), mais meurt s'il ne mange pas avant un délai donné.

Le programme simule ces philosophes en parallèle (un thread par philosophe)
et affiche l'état de chacun avec un timestamp en millisecondes, tout en
détectant si un philosophe meurt de faim.

## Compilation

```bash
cd philo
make
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : nombre de philosophes (et de fourchettes).
- `time_to_die` (ms) : délai sans manger au bout duquel un philosophe meurt.
- `time_to_eat` (ms) : durée d'un repas (bloque les deux fourchettes).
- `time_to_sleep` (ms) : durée de sommeil.
- `number_of_times_each_philosopher_must_eat` (optionnel) : le programme
  s'arrête dès que chaque philosophe a mangé ce nombre de fois.

Exemple :

```bash
./philo 5 800 200 200
```

## Fonctionnement

- Chaque philosophe tourne dans son propre thread (`pthread_create`).
- Les fourchettes sont des `pthread_mutex_t`, partagées entre deux
  philosophes voisins.
- Un thread de monitoring surveille en continu l'heure du dernier repas de
  chaque philosophe pour détecter la mort, et compte le nombre de repas pour
  arrêter la simulation quand tout le monde a assez mangé.
- Le parsing des arguments n'accepte que des entiers positifs tenant dans un
  `int`.

## Structure

```
philo/
├── main.c                 # point d'entrée, boucle de monitoring
├── parsing.c              # parsing et validation des arguments
├── init.c                 # initialisation des structures et mutex
├── thread.c               # routine exécutée par chaque philosophe
├── action.c               # manger / dormir / penser
├── lock_unlock_forks.c    # prise et relâche des fourchettes
├── number_lib.c           # utilitaires numériques (atol, etc.)
├── lib_func_recode.c      # réimplémentations de fonctions libc
└── philo.h                # structures et prototypes
```

Seule la partie obligatoire est implémentée (threads + mutex, pas de
processus/sémaphores).
