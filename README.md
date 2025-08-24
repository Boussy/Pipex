# pipex – Reproduction du piping en C

## 🚀 Introduction

`pipex` est un projet clé de l’école 42.
Le but est de **reproduire le comportement du shell avec des pipes** :

```bash
< infile cmd1 | cmd2 > outfile
```

En d’autres termes :

* Lire depuis un fichier (`infile`).
* Rediriger la sortie de la première commande vers l’entrée de la suivante via un **pipe**.
* Écrire le résultat final dans un fichier (`outfile`).

C’est une étape cruciale pour comprendre :

* La gestion des **processus** (`fork`).
* La redirection avec **descripteurs de fichiers** (`dup2`).
* L’exécution de commandes via **`execve`**.
* La manipulation des **pipes Unix**.

---

## 🛠️ Fonctionnalités

* Reproduction du piping simple avec deux commandes.
* Gestion des **fichiers d’entrée et de sortie**.
* Recherche du chemin des binaires via la variable d’environnement `PATH`.
* Gestion robuste des erreurs (fichiers inexistants, commande invalide, permissions…).
* Nettoyage mémoire pour éviter les fuites.

---

## 🤓 Structure du projet

* **`pipex.c`** → logique principale.
* **`child_process.c`** → création des processus enfants.
* **`exec_cmd.c`** → exécution d’une commande via `execve`.
* **`get_path.c`** → résolution du chemin d’un binaire.
* **`pipe_utils.c`** → création et fermeture des pipes.
* **`file_utils.c`** → ouverture et validation des fichiers.
* **`cleanup.c`** → libération mémoire & gestion d’erreurs.
* **`utils.c` / `ft_split.c`** → fonctions utilitaires.

---

## 🥸 Subtilités & enjeux du projet

### 🔹 Gestion des processus

* Utilisation de `fork()` pour créer deux processus enfants.
* Chaque enfant exécute une commande avec **`execve`**.

### 🔹 Descripteurs de fichiers

* Redirection avec `dup2()` :

  * `dup2(fd_in, STDIN_FILENO)` pour l’entrée.
  * `dup2(fd_out, STDOUT_FILENO)` pour la sortie.

### 🔹 Pipes

* Créés avec `pipe(fd)`.
* `fd[0]` → lecture, `fd[1]` → écriture.
* Nécessité de **fermer correctement** les descripteurs inutiles pour éviter les blocages.

### 🔹 PATH & exécution

* Parsing de la variable d’environnement `PATH`.
* Vérification de l’accessibilité des binaires avec `access()`.

### 🔹 Gestion des erreurs

* Fichiers inexistants.
* Commandes invalides.
* Permissions refusées.
* Nettoyage mémoire pour éviter les leaks.

---

## ⚡️ Conseils pour refaire le projet

1. Commence par maîtriser **`fork`, `dup2`, `execve`, `pipe`** indépendamment.
2. Implémente un exécutable minimal qui fait :

   * `cmd1 < infile`
   * puis `cmd2 > outfile`.
3. Ajoute la gestion du pipe (`cmd1 | cmd2`).
4. Teste des cas limites :

   * `infile` inexistant.
   * Commande introuvable.
   * Droits refusés.
5. Ajoute une gestion propre des erreurs et un **nettoyage mémoire**.

---

## 📖 Ressources utiles

* 📌 [man fork](https://man7.org/linux/man-pages/man2/fork.2.html)
* 📌 [man pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
* 📌 [man dup2](https://man7.org/linux/man-pages/man2/dup.2.html)
* 📌 [man execve](https://man7.org/linux/man-pages/man2/execve.2.html)
* 📌 [Beej’s Guide to Unix IPC](https://beej.us/guide/bgipc/html/)
* 📌 [42docs – Pipex tester](https://github.com/vfurmane/pipex-tester)

---

## 🎯 Objectif final

À la fin de `pipex`, tu sauras :

* Créer et gérer des **processus Unix**.
* Manipuler des **pipes et des redirections**.
* Implémenter un comportement de **shell simplifié**.
* Écrire un code robuste et **proprement architecturé**.

