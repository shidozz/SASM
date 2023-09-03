# Langage de programmation Sasm

## Introduction
Sasm (Shidozz Assembler) est un langage de programmation de bas niveau conçu pour la programmation système et l'accès de bas niveau aux ressources informatiques. Ce projet contient l'assembleur pour le langage Sasm.

## Fonctionnalités
1) Notation hexadécimale : `(0x000000) à (0xFFFFFF)`
2) Registres : `A0-A9`, `B0-B4`
3) Mots-clés : `ret`, `add`, `rem`, `set`, `jmp`, `ver`, `jie`, `jin`, `jis`, `jii`, `global`, `extern`

## Pour commencer
### Prérequis
```
Compilateur GCC
Make
```

## Compilation
### Pour compiler le compilateur Sasm :
```
make
```
Cela produira un exécutable nommé `sasm.exe`.

### Pour assembler et exécuter un programme Sasm :
```bash
./sasm.exe input.sasm -o output.bts
```

## Exemples
### Opération basique avec les registres :
```
global _start
    add A0 1
    ret
```

### Opérations de saut :
```
global _start
    add A0 5
    jmp A1
```

## Bytecode
Pour plus de détails sur le Bytecode, veuillez vous référer à la [documentation du Bytecode](docs/Bytecode.md).

## Documentation
Pour des spécifications détaillées du langage et des sujets avancés, veuillez vous référer au [Wiki](#) (à venir).

## Contribution
Les contributions sont les bienvenues ! Veuillez lire les directives de contribution avant de faire une PR.

## Licence
Ce projet est sous licence MIT. Voir [LICENSE.md](LICENSE.md) pour plus de détails.
