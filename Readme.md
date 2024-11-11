# Game Boy Emulator

## Description
Un émulateur Game Boy en C qui reproduit le CPU, la mémoire, les graphismes, et le son pour exécuter des jeux Game Boy (.gb) sur mac arm.

## Fonctionnalités
- **CPU Sharp LR35902** : Simulation du jeu d'instructions.
- **Graphismes** : Affichage 160x144 avec gestion des sprites et arrière-plans.
- **Audio** : Émulation des 4 canaux sonores.
- **Chargement de ROM** : Prise en charge des fichiers `.gb`.
- **Contrôles** : Support complet des boutons de la Game Boy.

## Prérequis
- **C** (GCC)
- **SDL2** : `brew install sdl2`

## Compilation et Exécution
```bash
make
./GameBoy path/to/rom.gb
```

## Commandes
| Touche  | Action      |
|---------|-------------|
| A       | Bouton A    |
| B       | Bouton B    |
| Flèches | Direction   |
| Start   | Start       |
| Select  | Select      |
| Échap   | Quitter     |


Important References :

- https://gbdev.io/pandocs/
- https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
- https://archive.org/details/GameBoyProgManVer1.1/page/n85/mode/2up
