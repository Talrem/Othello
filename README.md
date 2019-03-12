<DOCTYPE html>
  <head>
  </head>
  <body>
    <h1>Othello</h1>
    <h2>Projet de L2 avec David MERLAT, Nathan MANSON et Samuel DURAN</h2>
    <h3>"-" -> à faire et "*" -> fait</h3>
    <h2>- LE JEU :</h2>
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
    </ul>
    <h3>* COUP VALIDE :</h3>
    <ul>
      <li>* dans le plateau</li>
      <li>* coup dans une case vide</li>
      <li>* au moins un pion de l'adversaire est retourné</li>
    </ul>
    <h3>- INTERFACE GRAPHIQUE</h3>
    <ul>
      <li>- SDL2</li>
    </ul>
    <h3>- JEU EN RESEAU</h3>
    <ul>
      <li>- Socketv</li>
    </ul>
    <h3>- JEU CONTRE L'ORDINATEUR</h3>
    <ul>
      <li>- arbre de points</li>
      <li>- si égalité de gain potentiel : coup aléatoire</li>
    </ul>
  </body>
</html>
