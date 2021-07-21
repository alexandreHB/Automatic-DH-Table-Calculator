# **Automatic DH Table Calculator**

_ENGLISH READ-ME BELOW THE FRENCH ONE :)_

---

# **READ-ME FRANCAIS :**

## **Description du projet :**

Ce projet est un calculateur de Tableau de DH (Denavit-Hartenberg)
pour la commande de bras articulés type série. 

Il prend pour l'instant en charge la gestion de liaisons pivots et liaisons glissières.
D'autre de liaisons mécaniques peuvent être implémentée si elles deviennent suffisament répandues et utilisées. 

_Coucou les sphères dentées et les futures bras avec des liaisons rotules que Sam a montré sur discord :)_


---
## **Principe de fonctionnement :** 

[Video d'utilisation](lien de la video)

1. Créer des solides representés par des liaisons pivots et glissières dans le but de faire un semblant de schéma cinématique.

2. Orienter les axes X et Z des solides crées en suivant les conventions de DH.

    Règles de la convention de Denavit-Hartenberg : 
* axe **zi** orienté vers l'axe de la liaison i
* axe **xi** doit être orthogonal à **zi** et à **zi-1**
* axe **xi** doit si possible être orienté vers le prochain solide  

3. Appuyer sur le bouton _GO_ pour afficher sur le terminal le tableau de DH correspondant au schéma cinematique du robot.


---
## **Lancer le programme :**

_Pour compiler : **make**_

_Pour lancer l'application : **./exec**_

_Pour supprimer les fichiers.o : **make clean**_



---
## **Hypothèse faites :**

* Le solide **S0**  n'est jamais au même endroit que la base
Cela ne change rien au calcul pour le tableau de DH.

    _Car la transformation homogène de la base au solide 0 est constante_

    _Mais pour un vrai robot, il ne faut pas oublier d'ajouter la transformation T_base->S0 dans le produit final de matrice pour le modèle géométrique direct_

* il ne peut y avoir d'offset de distance **di** ET **ai** en même temps pour un solide.

    _s'il y a un offset de distance, c'est soit l'un l'autre, soit aucun des deux_

* Les case **di** pour un solide en translation auront toujours _li = 0_ 

    _La case la plus générique qui soit est _Qi + li_ mais dans ce code, je n'ai pas pris en charge le cas où il y a un offset de distance dans selon l'axe de la translation._


---
## **Fonctionalités / Mécanique d'interaction :** 

* Création de solide avec boutons.
* Déplacement d'un solide en le maintenant.
* Suppression d'un solide en le deplacant dans la poubelle.
* Changement texture d'un solide pour changer de point de vue **: appuyer sur _C_**
* Rotation de la texture d'un solide **: appuyer sur E_ et _R_**
* Rotation de l'axe **x** **: appuyer sur _Q_ et _S_**
* Rotation de l'axe **z** **: appuyer sur _A_ et _Z_**
* Remplissage du tableau de DH du robot dessiné **: en cliquant sur _GO_**


---
##  **À venir :** 

* calcul de matrice de transformation homogène en expression litéral
* Implementaton d'une deuxème couche graphique en 3D avec OpenGL

_Plus de details dans TODO.txt_


---
## **Possibilité de contribuer !**

La version 2D est fonctionnel, mais rien n'est parfait et il y a surement dec choses à améliorer dans ce projet ! 

Comme par exemple : 

*   rajoutter un commentaire à un endroit si vous estimez que cela   facilite la comphréension du code
*  corriger une faute d'orthographe
* corriger une mauvaise traduction 
* faire des test uniatires _hmm hmm..._
* réduire un peu les fuites mémoires 

    _Bien qu'a priori, elles sont proportionnelles aux nombre de solides crées, or le nombre de solide crées lors de l'utilisation de l'application ne dépasse que rarement 6..., sauf si l'on décide de faire plusieurs schéma cinématique de suite_

---





# **ENGLISH READ-ME :**

## **Description of the projet :**

This project is an automatic DH Table calculator (Denavit-Hartenberg) for serie type articulated arms.

The code handle pivotal and slinding links. Other mechanicals links can be implemeted in the future if they become enough wildly used and mainstream.

_High spherical gears and futur articulated arms with rotoidal links :)_

---
## **Functionning principle :** 

[Video d'utilisation](lien de la video)

1. Create solids represented by pivotal or sliding links in order to draw a kind of kinematic scheme.

2. Oriente x ad z axis of the solids  previously created by following the rules of the DH convention : 

    Rules of the Denavit-Hartenberg convention
* **zi** axis oriented into axis of the link/solid i
* **xi-1** axis must be orthogonal to **zi** and **xi-1**
* **xi** should be oriented toward the next solid

3. click on the _GO_ button to print the DH table on the terminal corresponding to the kinematoc scheme you have drawn.

---
## **Hypothesis made :**

* Le solide **S0** est n'est pas au même endroit que la base
Cela ne change rien au calcul pour le tableau de DH.
(Car la transformation homogène de la base au solide 0 est constante)
Mais Pour un vrai robot, il ne faut pas oublier d'ajouter la transformation T_base->S0 dans le produit final d

* The **S0** solid is dissociated of the base. It means that **S0** is never at the same pose that the base. It doesn't change anything for the filling of the table.

    _Because the homogeneous transformation from the base to S0 T_base->S0 is constant._

    _But for a real robot, you need to take care of that for your final matrix product for the direct geometrical model_

 * There cannot be an offset of distance **di** AND **ai** at the same time for one solid.

    _it is wether **di**, either **ai** or neither_

* **di** cases for one solid in translation will always be _li = 0_

    _The more generic case is Qi + li , but in this code, I didn't handle the case where there is a an offset in distance along the axis of the translation._


---
## **Lanch the program :**

_To compile : **make**_

_To lanch the application : **./exec**_

_To remove files.o : **make clean**_


---
## **Fonctionality / Interactivity mechanics :** 

* Creation of solids with buttons.
* Moving a solid by holding it.
* Deletion of a solid by moving it into the garbage.
* Changement of texture of a solid for changing point of view. **: press _C_**
* Rotate the texture of a solid **: press _E_ and _R_**
* Rotate **x** axis **: press _Q_ and _S_**
* Rotate **z** axis **:press _A_ and _Z_**
* Remplissage du tableau de DH du robot dessiné **: by clickin on _GO_**



---
##  **Coming next :** 

* Calcul of homogeneous transformation matrix of each line of the table with literal expressions
* Implementation of graphism in 3D with OpenGL

_More details in TODO.txt_



---
## **Possibility to contribute !**

The 2D version of the application is fonctionnal, but nothing is perfect and there must be somthing to enhance in this project ! 

For exemple : 

* add a comment where it allows to better understand the code
* correct a spelling mistake
* correct a wrong translation
* doing unity test _hmm hmm..._
* minimise memory leaks

    _In first sight, leaks are proportional to the number of solid created since the launch of the application. But the number of solid created doesn't often exceed 6..., only if the user decide to make several kinematic scheme in a row_
---

