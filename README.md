<DOCTYPE html>
  <head>
  </head>
  <body>
    <h1>Othello</h1>
    <h3>Projet de L2 avec David MERLAT, Nathan MANSON et Samuel DURAN</h3>
    <h5>"-" -> à faire et "*" -> fait</h5>
    <h4>LE JEU :</h4>
    <ul>
      <li>* Plateau de 8 par 8</li>
      <li>* Chaque case est vide/blanche/noir</li>
      <li>* le noir joue en premier</li>
      <li>* coup en alternance entre les deux joueur</li>
      <li>- le tour passe si le joueur ne peux pas jouer</li>
      <li>* les cases du plateau doivent etre référencées par des coordoné type B5</li>
      <li>* la partie se termine quand :
        <ul>
          <li>* le plateau est plein</li>
          <li>* il n'y a plus de pions noirs sur le plateau</li>
          <li>* il n'y a plus de pions blancs sur le plateau</li>
        </ul>
      </li>
    </ul>
    <h4>COUP VALIDE :</h4>
    <ul>
      <li>*dans le plateau</li>
      <li>*coup dans une case vide</li>
      <li>-au moins un pion de l'adversaire est retourné</li>
    </ul>
    <h4>INTERFACE GRAPHIQUE</h4>
    <ul>
      <li>-SDL2</li>
    <ul>
    <h4>JEU EN RESEAU</h4>
    <ul>
      <li>-Socketv</li>
    </ul>
    <h4>JEU CONTRE L'ORDINATEUR</h4>
    <ul>
      <li>-arbre de points</li>
      <li>-si égalité de gain potentiel : coup aléatoire</li>
    </ul>
  </body>
</html>
