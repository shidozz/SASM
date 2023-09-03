# Documentation de l'assembleur sasm

## Sommaire

1. [Introduction](#1-introduction)
2. [Registres](#2-registres)
3. [Opcodes](#3-opcodes)
4. [Format du bytecode](#4-format-du-bytecode)
5. [Exemples de code](#5-exemples-de-code)

## 1. Introduction

`sasm` est un assembleur personnalisé qui compile vers un bytecode spécifique. Le bytecode résultant utilise des nombres entiers non signés de 32 bits (`uint32_t`) pour les opérations.

## 2. Registres

- **Registres 16 bits**: A0 à A9
- **Registres 32 bits**: B0 à B4

## 3. Opcodes

Les opcodes sont numérotés de 0 à 10 et ont les fonctions suivantes:

- **0: `global`**: Rend un label utilisable dans un autre langage.
- **1: `extern`**: Récupère une fonction, un label ou une variable d'un langage externe (comme le C).
- **2: `ret`**: Utilisé pour retourner d'une fonction.
- **3: `add`**: Ajoute un opérande A à un opérande B.
- **4: `rem`**: Retire un opérande A d'un opérande B.
- **5: `jii`**: Saute si inférieur (Jump If Inferior).
- **6: `jie`**: Saute si égal (Jump If Equal).
- **7: `jis`**: Saute si supérieur (Jump If Superior).
- **8: `jin`**: Saute si différent (Jump If Not Equal).
- **9: `set`**: Définit un opérande A à un opérande B.
- **10: `ver`**: Vérifie un opérande A avec un opérande B.

## 4. Format du bytecode

Chaque instruction est formatée comme suit:

```
[opcode] [opérande1] [opérande2] [indicateur de registre]
```

L'indicateur de registre est composé comme suit:
- **0**) Pas de registre utilisé.
- **1**) Le premier opérande est un registre (A0=0, B0=10).
- **2**) Le deuxième opérande est un registre (A0=0, B0=10).
- **3**) Les deux opérandes sont des registres (A0=0, B0=10).

## 5. Exemples de code

```asm
// Exemple d'utilisation de 'add'
3 5 12 1  // Ajoute la valeur 12 au registre A5
```

This project is licensed under the MIT License. See [LICENSE.md](../LICENSE.md) for details.