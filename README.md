<DOCTYPE html>
  <head>
  </head>
  <body>
    <h1>Othello</h1>
    <h2>Projet de L2 avec David MERLAT (Talrem), Nathan MANSON (Gaiall) et Samuel DURAN (Envyp)</h2>
    <h3>"-" -> à faire et "*" -> fait</h3>
    <h2>* LE JEU :</h2>
    <ul>
      <li>* Plateau de 8 par 8</li>
      <li>* Chaque case est vide/blanche/noir</li>
      <li>* le noir joue en premier</li>
      <li>* coup en alternance entre les deux joueur</li>
      <li>* le tour passe si le joueur ne peux pas jouer</li>
      <li>* les cases du plateau doivent etre référencées par des coordoné type B5</li>
      <li>* la partie se termine quand :
        <ul>
          <li>* le plateau est plein</li>
          <li>* il n'y a plus de pions noirs sur le plateau</li>
          <li>* il n'y a plus de pions blancs sur le plateau</li>
        </ul>
      </li>
      <li>* les pions sont retournés quand ils sont pris</li>
      <li>* On peut choisir de refaire une partie dans le même mode de jeu une fois la partie finie</li>
    </ul>
    <h3>* COUP VALIDE :</h3>
    <ul>
      <li>* dans le plateau</li>
      <li>* coup dans une case vide</li>
      <li>* la case est voisine à une case adverse</li>
      <li>* au moins un pion de l'adversaire est retourné</li>
    </ul>
    <h3>- INTERFACE GRAPHIQUE</h3>
    <ul>
      <li>- SDL2</li>
      <li>- Menus de sélection</li>
      <li>* saisie des coups</li>
      <li>* affichage du terminal et des scores</li>
    </ul>
    <h3>- JEU EN RESEAU</h3>
    <ul>
      <li>- Socketv</li>
      <li>- hébergement de partie</li>
      <li>- connection à une partie</li>
      <li>- échange des données de jeu</li>
    </ul>
    <h3>- JEU CONTRE L'ORDINATEUR</h3>
    <ul>
      <li>* l'IA a une couleur aléatoire</li>
      <li>* coup aléatoire tout les N tours en fonction de la difficulté</li>
      <li>- arbre de points</li>
      <li>- si égalité de gain potentiel : coup aléatoire</li>
      <li>* quand la partie est finie, si on choisit de rejouer, l'IA change de couleur</li>
    </ul>
  </body>
</html>
