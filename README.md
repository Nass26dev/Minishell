# Minishell

Un shell minimaliste écrit en C, inspiré de `bash`. Projet de l'école 42.

Il lit une ligne de commande, la découpe en tokens, construit un AST, développe les
variables, puis exécute le tout avec gestion des pipes, des redirections et des
signaux.

## Compilation

```bash
make
```

Dépendances : `readline` (`libreadline-dev` sur Debian/Ubuntu).

Autres règles : `make clean`, `make fclean`, `make re`.

## Utilisation

```bash
./minishell
```

Un prompt `Minishell$` s'affiche et attend vos commandes.

```
Minishell$ ls -la | grep .c > out.txt
Minishell$ echo "$HOME" && pwd
Minishell$ cat << EOF
> ligne 1
> EOF
ligne 1
```

`Ctrl-D` ou `exit` pour quitter.

## Fonctionnalités

- Exécution de commandes via le `PATH` ou par chemin absolu/relatif
- Pipes `|` et opérateurs logiques `&&`, `||`
- Redirections `<`, `>`, `>>` et heredoc `<<`
- Guillemets simples `'` et doubles `"`
- Expansion des variables d'environnement `$VAR` et du code de retour `$?`
- Historique des commandes (readline)
- Signaux : `Ctrl-C`, `Ctrl-D`, `Ctrl-\` avec le comportement de bash

### Builtins

`cd`, `echo` (avec `-n`), `env`, `exit`, `export`, `pwd`, `unset`

## Tests

Le Makefile fournit des règles Valgrind, avec un fichier de suppression pour les
fuites internes de `readline` et `libtinfo` (qui ne sont pas imputables au shell) :

```bash
make valgrind        # leak-check complet
```

Le shell ne fuit pas : `definitely`, `indirectly`, `possibly lost` et
`still reachable` sont tous à 0, et les octets encore alloués à la sortie sont
entièrement couverts par les suppressions `readline` / `libtinfo`.

```
LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 0 bytes in 0 blocks
        suppressed: 232,829 bytes in 234 blocks
ERROR SUMMARY: 0 errors from 0 contexts
```

## Structure

```
include/    en-têtes
libft/      bibliothèque interne
src/
├── parsing/    lexer, parser (AST), expansion, heredoc
├── exec/       exécution, builtins, pipes, redirections, opérateurs
└── signals/    gestion des signaux
```

## Auteurs

nyousfi · eelissal
