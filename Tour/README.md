<DOCTYPE html>
  <head>
  </head>
  <body>
    <p>Ici se trouvent les fonctions utilisée au cours du tour, à savoir :</p>
    <ul>
      <li> prise : Applique les prises de pions </li>
      <li> checkTableau : Vérifie qu'un pion est pris pour une direction donnée et appelle prise dans ce cas.</li>
      <li> initTableau : Reset le tableau utilisé par checkTableau.</li>
      <li> prendPion : Note pour chaque direction le contenu de cases de façon utilisable pour checkTableau.</li>
      <li> aVoisins : Renvoit le nombre de voisins de la couleur adverse d'une case donnée.</li>
      <li> estInvalide : Vérifie qu'un coup n'est pas en dehors du plateau ni sur un pion existant et qu'un pion est pris par ce coup. Renvoit un code d'erreur ou 0 si tout s'est bien passé.</li>
      <li> coupIntellIA : détermine le meilleur coup a jouer et l'applique</li>
      <li> coupAleatIA : joue un coup au hasard dans le plateau</li>
      <li> saisieCoupJcJL : Réalise la saisie du mode joueur contre joueur local.</li>
      <li> saisieCoupJcIA : Réalise la saisie du mode joueur contre IA.</li>
      <li> saisieCoupJcJD : Réalise la saisie du mode joueur contre joueur distant.</li>
    </ul>
  </body>
</html>
