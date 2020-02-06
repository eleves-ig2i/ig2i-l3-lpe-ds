

# Questions de DS de LPE
## Brève introduction
Ce document contient la plupart des questions posées à un DS de LPE / RPI / Compilation croisé (Linux pour la L3 en gros).
Gros remerciements à Guillaume Carlier pour sa participation à ce document. Grâce à lui, vous éviterez un rattrapage de plus à 2i ! :)
Le répertoire libdate contenu dans le git, contient un exemple de makefile (à compléter s'il manque des trucs).
## Clé USB / Partitions / Montages / Démontages
+ **Quelles commandes permettent d’afficher les noms des périphériques de stockage et des partitions détectées sur votre système Linux ?**
```bash
fdisk -l
df -h
mount
dmesg
```

+ **Quelle commande permet de partitionner un disque dur ? Indiquez les contraintes de
nommage correspondant au partitionnement et la localisation de la table de partitions**
  + Partitionner : `fdisk <periphérique>`
  + On ne peut créer que 4 partitions primaires ou 3 primaires et 1 étendue pouvant contenir
60 partitions logiques. Les périphériques sont souvent nommés /dev/sd .
  + La table de partition est contenue dans le MBR (premier secteur du disque)

+ **Écrire(s) la ou les commande(s) à exécuter avant d’extraire une clé USB, identifiée comme étant sdd, et qui contient deux partitions primaires.**
  + Vérifier si la clé est montée : `df -h`
  + Démonter les partitions : `umount /dev/sdd1 && umount /dev/sdd2`
  + Si impossibilité : quitter les points de montages des partitions correspondantes
(gestionnaires de fichiers, terminaux etc...)

+ **Indiquez la nature des arguments de la commande permettant de monter une partition. Dans quel fichier sont définis les montages par défaut ?**
  + On indique une partition (ex: /dev/sdb1) en argument à mount
  + /etc/fstab

+ **Quelle commande permet de formater une partition ? Indiquez le rôle du paramètre j que nous avons employé en TP**
`mkfs.ext3 -j /dev/sdc1`
-j : créer un système de fichiers sur chaque partition

+ **Indiquez quelles systèmes de fichiers créer et comment les produire pour préparer un OS pour RPI sur votre carte SD.**
Systèmes de fichiers à créer :
	+ Une partition fat32 (pour le boot) ; `mkfs.vfat <partition>`
	+ une partition ext4 : `mkfs.ext4 <partition>`

+ **Dessiner de manière synthétique un périphérique de stockage en faisant apparaître la manière dont grub y est installé.**
https://i.imgur.com/m2A87TC.png

### Scripts
+ **Dans un script shell, comment récupérer la réponse à une question d’un utilisateur (par exemple : « voulez-vous recompiler le noyau [Y-n] ? ») et déclencher un traitement par défaut dans le cas où il saisit autre chose que « n » ?**
```bash
read reponse #recupération de la réponse
if [ $reponse != "n" ]
then
	#traitement par défaut
fi
```

+ **Dans un script shell, comment vérifier si le dossier /mnt/emb/bin existe, et le créer s'il n'existe pas ? Quelle commande alternative permettrait de créer le répertoire de manière à ne pas déclencher d'erreur s'il existe déjà ?**
```bash
if [[ -d /mnt/emb/bin ]] # pour vérifier la présence du dossier
mkdir -p /mnt/emb/bin # pour créer le répertoire sans visualisation des erreurs
```
+ **Décrire l’information que doit porter la première ligne d’un script shell. Quelle est la différence entre la première ligne d’un script shell s’exécutant sur PC sous Linux et un script qui doit s’exécuter sur une busybox. Quelle propriété doit avoir un script shell et comment la lui attribuer ?**
  + On spécifie l'interprète pour le script : `#!/bin/bash`
  + Sous busybox on utilisera : `/bin/sh`
Un script shell doit avoir les droits d'exécution (avec `chmod +x` par exemple)

## Compilation en C sous Linux, librairies
+ **Donnez quatre options utilisées par le compilateur gcc et indiquez précisément à quel(s) outil(s) elles sont destinées : précompilateur, compilateur ou éditeur de liens**

| Option       | But       | Etape de la compilation  |
| ------------- |:-------------:| -----:|
| `-c`      | interrompre la compilation avant l'édition de liens | compilateur |
| `-l<nom>`   | indiquer une librairie dynamique avec laquelle réaliser une édition de liens      |   éditeur de liens |
| `-I<chemin>` | indiquer le chemin des fichiers d'entête (non indiqués par $PATH)      |    compilateur |
| `-L<chemin>` | indiquer le chemin des librairies | éditeur de liens |
| `static/-shared` | demander une édition de liens statique/dynamique | éditeur de liens |

+ **Quelle est la différence entre les paquets libncurses5 et libncurses5-dev ? Quand doit-on respectivement les utiliser ?**
  + libncurses fournit les <ins>bibliothèques partagées</ins> pour utiliser un terminal tandis que libncurses5-dev fournit les <ins>fichiers d'entête</ins>.
  + On peut utiliser libncurses5 pour <ins>exécuter des programmes</ins> dépendant de ncurses, et on doit utiliser libncurses pour <ins>développer un programme</ins> utilisant les fonctions de la librairie ncurses.
+ **Que signifie « produire un exécutable statique » ? Un exécutable « dynamique » ? Qu'est-ce qu'un fichier d'entête ? Une librairie ? Quelles sont leurs extensions ? Quelles étapes de la production d'un exécutables les concernent respectivement ? Produire un fichier makefile pour illustrer vos réponses en présentant les principales options de gcc utiles pour ces étapes.**
  + On suppose qu'on veut compiler un programme test_date.c, utilisant une fonction de la librairie date.c.
```makefile
all: test_date
test_date: static dynamic
	gcc -c test_date.c
    gcc -static -L. test_date.o test_date_src # production de l'exécutable statique
    gcc -L. test_date.o test_date_dyn -ldate # production de l'exécutable dynamique

static: date.o
    ar -qvs libdate.a date.o # génération de la librairie statique

dynamic: date.o
    gcc -shared date_fPIC.o -o libdate.so # génération de la librairie dynamique

date.o: date.c # remarque : on suppose que date.h est notre fichier d'entête
    gcc -c date.c -o date.o # compilation
    gcc -c date.c -fPIC date_fPIC.o # compilation pour la librairie dynamique
```
+ **Décrire ce qui se passe lors des étapes de production d’un exécutable : précompilation, compilation et édition de liens. Donnez les 5 options principalement utilisées par le gcc pour ces étapes.**
1. Traitement par le préprocesseur : le fichier source est traité par un préprocesseur qui fait des transformations purement textuelles (remplacement de chaînes de caractères, inclusion d’autres fichiers source, etc). (Options utilisées : -E)
2. La compilation : le fichier engendré par le préprocesseur est traduit en assembleur i.e. en une suite d’instructions associées aux fonctionnalités du microprocesseur (faire une addition, etc). (Options utilisées : -c, -I)
3. L’édition de liens : afin d’utiliser des librairies de fonctions déjà écrites, un programme est
séparé en plusieurs fichiers source. Une fois le code source assemblé, il faut lier entre eux
les fichiers objets. L’édition de liens produit un fichier exécutable. (Options utilisées : -L -l)

+ **Comment afficher le processeur pour lequel un exécutable a été compilé ? Comment tester si un exécutable a des dépendances ? Comment lister les symboles exportés par une librairie ?**
Respectivement :
  + `file <fichier>` 
  + `ldd <fichier>`
  + `nm <fichier>`

+ **Quelle commande doit-on effectuer pour générer l’exécutable helloDyn en version dynamique, à partir d’un fichier source hello.c ? Quelle commande doit-on effectuer pour générer l’exécutable helloSta en version statique, à partir d’un fichier source hello.c ?**
  + Cf le makefile ci-dessus pour cette question

+ **A quoi sert la librairie ncurses ? De quoi a besoin un programme utilisant la librairie ncurses pour fonctionner ? Indiquez les étapes nécessaires à la production depuis votre poste de travail, puis à l’exécution sur un RPI, d’un programme utilisant la librairie ncurses.**
  + Ncurses est une bibliothèque qui fournit des fonctions de définition de touches du clavier, de couleurs d'écran et permet l'affichage de plusieurs fenêtres sans recouvrement sur un terminal.
  + Pour fonctionner, un programme utilisant ncurses a besoin des librairies associées (dynamiques ou statiques).
  + Production d'un programme ncurses sur un RPI :
     1. Configuration de la librarie ncurses avec `./configure --prefix=<dest_dir> --host=..linux.. --target=..rpi..`, puis `make` et `make install`.
     2. Compilation du programme principal avec le compilateur croisé.

## IHM pour l'embarqué
+ **Qu'est-ce que le framebuffer ? Quelles commandes utilisant le framebuffer avez-vous utilisé lors des Tps ? Comment savoir si le RPI intègre le support du framebuffer ?**
  + Plusieurs possibilités de réponses :
    + Framebuffer permet au noyau d'accéder à la mémoire de la GPU pour produire des interfaces graphiques / jeux ....
    + Framebuffer : couche d'abstraction graphique indépendante du matériel pour afficher des éléments graphiques dans une console sans avoir besoin de bibliothèques spécifiques à un système.
    + Le framebuffer permet de piloter les modes graphiques en haute résolution directement depuis le noyau Linux.
  + Lors des TPs, on a utilisé fbv (pour afficher des images sur l'écran)
  + Le RPI intègre le support du framebuffer <  + les framboises s'affichent lors du démarrage
+ **L’exécution d’une application ncurses produit le message « cannot open terminal » et s’arrête. Quelle en est la cause et comment résoudre ce problème ?**
  + Le fichier <ins>/etc/profile doit être exécutable</ins> et contenir au moins la ligne suivante :
```bash
export TERMINFO=/share/terminfo
```
## RPI & Compilation Croisée
+ **Qu'est-ce qu'un compilateur croisé ? Comment vérifier pour quel système cible est produit un exécutable ?**
  + Un compilateur croisé produit un code exécutable à destination d'une architecture différente de celle sur laquelle il effectue la compilation.
  + On vérifie le système cible d'un exécutable à l'aide de `file <fichier>`

+ **Comment afficher les paramètres « host » et « target » d’un compilateur ? Que désignent-ils et dans quel cas sont-ils différents ?**
  + Pour afficher les paramètres host et target d'un compilateur, on utilise l'option `-v`
  + **host** désigne l'architecture de la machine sur laquelle on effectue la compilation du programme.
  + **target** désigne l'architecture de la machine sur laquelle on effectue l'exécution du programme.
  + Ces deux paramètres sont différents dans le cas d'un compilateur croisé.

+ **Qu'est-ce que les GPIO (acronyme, définition, usage) ? Contiennent-ils des entrées analogiques ? Quelle librairie permet de les manipuler ?**
  + GPIO signifie <ins>General Purpose Input Output</ins>
  + Il s'agit des ports d'entrées analogique et numérique pour RPI.
  + On peut les utiliser pour allumer des diodes sur un circuit électronique.
  + La librairie WiringPI permet de les manipuler.
## Noyau Linux, Pilotes
+ **Vous êtes face à un ordinateur démarré sous Linux, sans interface graphique ni tournevis, comment savoir quelles sont les caractéristiques de sa carte réseau ?**
On peut utiliser l'une des commandes suivantes :
   + `lsmod` : liste les modules chargés dans le noyau.
   + `dmesg` : affiche les messages systèmes (branchement d'une clé USB, surchauffe du processeur etc.)
   + `lspci` : liste l'ensemble des périphériques PCI connectés à la carte mère.

+ **A quoi sert un noyau ? Expliquez le rôle du paramètre « rootdelay » du noyau Linux. Dans quel contexte fait-on appel à ce paramètre ?**
  + Plusieurs réponses possibles :
     + Un noyau s'occupe de l'ordonnancement des processus, de l'accès à la mémoire et du dialogue avec les périphériques.
     + Un noyau sert à gérer les ressources matérielles et les tâches à exécuter.
  + Le rootdelay permet d'attendre avant de monter le système de fichiers. On l'utilise lors du boot sur une clé, pour que la machine puisse avoir le temps de la détecter.

+ **Qu’appelle-t-on module dans le cadre de la construction du noyau d’un système Linux ?**
Un module est un pilote de périphérique que l'on peut charger dynamiquement dans le noyau
même après le démarrage. Ce sont des fichiers d'extension .ko dans /lib

+ **Lors de l’utilisation de la commande make menuconfig , quel fichier est manipulé ?**
Le fichier .config.

+ **Décrivez la procédure à adopter pour que la carte réseau de ce PC soit prise en charge par votre version de busybox sur Clé USB : 1) sans recompiler le noyau de la Ubuntu (deux cas sont à prévoir) 2) en recompilant un nouveau noyau sans prise en charge des modules chargeables.**
  1) Ajouter le support des cartes réseau dans Busybox (pour le 2e cas, démerdez vous).
  2) Cocher le driver de la carte en question lors de la configuration du nouveau noyau.
  
## Busybox & systèmes embarqués
+ **Sur quelle mécanisme se fonde la distribution busybox ? Quel est son objectif ? Donnez un code d'exemple simple en C permettant de mettre en œuvre ce mécanisme.**
  + Busybox se fonde sur le mécanisme de liens symboliques, couplé au passage d'arguments à un programme en C.
  + L'objectif est de réduire l'espace mémoire attribué aux commandes Unix et donc au système d'exploitation Linux.
  + On a donc un exécutable unique nommé busybox et de multiples liens symboliques nommés 'cat', 'cp', 'ls' ...
  + Exemple de programme en C :
```C
int main(int argc, char ** argv) 
{
	printf("Programme : %s", argv[0]);
}
```
+ **Dans le cadre de l’utilisation d’un OS busybox sur RPI, lors du démarrage d'une machine, le noyau se charge mais un message apparaît, indiquant « no init found », ou « cannot execute init ». Proposez trois causes possibles pour ce problème et les manières de le résoudre.**
  + La description du système de fichiers est incorrect : modifier le fichier cmdline.txt de la 1ère partition (on doit avoir les paramètres `root=mmcblk0p2` et `rootfstype=ext4`
  + Le système de fichiers est corrompu : on utilise la commande `e2fsck` sur le système de fichiers.
  + Absence ou modification du fichier init (donné par le lien symbolique /sbin/init en général) : rétablir le fichier ou réinstaller l'OS.

## Démarrage & Architecture de GNU/Linux
+ **Que contiennent /proc, /sys et /dev et à quoi cela sert-il ?**
  + /proc : Pseudo-système de fichiers d'informations sur les processus
  + /sys : Contient les informations systèmes et ses composants
  + /dev : Contient les informations sur les périphériques (devices)

+ **Qu’est-ce-que le MBR ? Où est-il situé sur un volume de stockage ? Quelle est sa taille en octets ? Que contient-il ? Quelles commandes permettent de le manipuler ?**
  + Master boot record.
  + Situé sur premier secteur du disque dur.
  + Contient la table de partitions et fait 512 octets.
  + On peut le manipuler avec `fdisk`.

+ **Qu’est-ce qu’un fichier initrd ? A quoi cela sert-il ?**
  + initrd (pour initial RAM disk) contient quelque binaires, un ensemble de modules vitaux, un
interpréteur de script et un script de démarrage.
  + Ce dernier est alors chargé de trouver les bons modules pour la configuration matérielle
courante, monter le vrai système de fichier, le définir comme nouvelle racine du kernel et
exécuter le second script de démarrage qu'elle contient.

+ **Décrire la séquence de démarrage d’un ordinateur sous Linux jusqu’à l’affichage du prompt**
  + 1ère étape : POST (Power On Self Test)
  + 2e étape : chargement du BIOS (Basic Input/Output System)
  + 3e étape : chargement du bootloader (ex: grub) situé dans le MBR
  + 4e étape : chargement du noyau
  + 5e étape : initrd pour le montage du système de fichiers temporaire.
  + 6e étape : démarrage du programme init et affichage du prompt.
