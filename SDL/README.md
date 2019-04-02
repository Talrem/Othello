<!DOCTYPE HTML>
<head></head>
<body>
   <h1>
      Ce dossier contient les définitions des fonctions SDL.
   </h1>
   <h2>
      SDL_Othello : Fonction permettant d'afficher de jouer au othello
   </h2>
      <h3>
         Liste des fonctions :
      </h3>
         <ul>
            <li> drawText : dessine la chaine donnée sur le renderer, a la position donnée, avec la taille et la couleur donnée.</li>
            <li> drawImage : affiche l'image sur le renderer, a une position donné, a partir de son chemin dans l'architecture.</li>
            <li> showWindow : Initialise la fenetre SDL.</li>
            <li> posClick : vérifie si le clic est dans la zone donnée.</li>
            <li> set_pixel : place un pixel.</li>
            <li> draw_circle : dessine un cercle en utilisant l'Algorithme de tracé d'arc de cercle de Bresenham.</li>
            <li> fill_circle : dessine un cercle plein.</li>
            <li> calculVarPlat : calcule les variables essentielle a l'affichage et utilisation du plateau.</li>
            <li> afficherPlateau : affiche le plateau de jeu, uniquement le quadrillage.</li>
            <li> afficherPion : affiche un pion au coordonées données, de la couleur donnée.</li>
            <li> afficherMatrice : affiche le contenu de la matrice (les pions) sur le plateau de jeu.</li>
            <li> placerPion : ajoute le pion dans la matrice, de la couleur du joueur donnée.</li>
            <li> coordCaseClic : calcul les coordonées de la case de la matrice corespondants a l'emplacement du clic.</li>
         </ul>
   <h2>
      SDLinclude : Contient des fonctions SDL de base, permet d'afficher et naviguer dans les menus
   </h2>
      <h3>
         Liste des fonctions :
      </h3>
         <ul>
            <li> ShowWindow : Créer la fenetre SDL
            <li> creerBoutons : créer un nombre donné de bouton de menu, puis les ranges dans un tableau. Les boutons crées sont placés les uns en dessous des autres</li>
            <li> getRes : Récupere la dimension actuelle de la fenetre, renvoie l'emplacement de cette résolution dans le tableau des résolutions disponible (la derniere case si la résolution n'est pas dans le tableau)</li>
            <li> initBoutonMenu4 : crée les boutons du menu4. Fonction séparé de creerBoutons car la disposition du menu 4 est différent des autres</li>
            <li> Fonctions "SDL_Menu" : Gèrent chacune le menu auquel elles correspondent</li>
            <li> Fonctions "SDL_AfficherMenu" : Affichent le menu auquels elles correspondent</li>
            <li> AfficherErreur : Affiche l'erreur de coup donné</li>
            <li> AfficheJoueurTour : Affiche le joueur actuel</li>
            <li> AfficherMenuPause : Affiche les boutons du menu de la pause en partie</li>
            <li> Fonctions "Jeu" : permettent de faire une partie</li>
         </ul>

</body>
