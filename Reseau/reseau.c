#include "./reseau.h"

SOCKET serveur (SOCKET sock){

  SOCKADDR_IN sin;
  socklen_t recsize = sizeof(sin);
  // Socket et contexte d'adressage du client
  SOCKET csock;
  SOCKADDR_IN csin;
  socklen_t crecsize = sizeof(csin);
  // Vérifie si les étapes du protocoles TCP IP sont fait
  int sock_err;
  // Création d'une socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  // Adresse IP du serveur
  printf("Veuillez saisir l'adresse IP du serveur: ");
  int adresse_ip_len = 255;
  char * adresse_ip;
  adresse_ip = (char *) malloc(adresse_ip_len);
  fgets(adresse_ip,adresse_ip_len,stdin);
  // Si la socket est valide
  if(sock != INVALID_SOCKET){
      printf("Ouverture de la socket %d en mode TCP/IP\n", sock);
      // Configuration
      sin.sin_addr.s_addr = inet_addr(adresse_ip);
      free(adresse_ip);
      sin.sin_family = AF_INET;
      sin.sin_port = htons(PORT);
      sock_err = bind(sock, (SOCKADDR*)&sin, recsize);
      // Verifie si l'opération de liaison fonctionne
      if(sock_err != SOCKET_ERROR){
          // Démarrage du listage (mode server)
          sock_err = listen(sock, 5);
          printf("Listage du port %d...\n", PORT);
          // Vérifie si le port est occupé
          if(sock_err != SOCKET_ERROR){
              //Attente pendant laquelle le client se connecte
              printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
              csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
              printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
              return csock;
          }
          else perror("Listen");
      }else perror("Bind");
  }else perror("Socket");
}

SOCKET client (SOCKET sock) {

  // Adresse IP du serveur
  printf("Veuillez saisir l'adresse IP du serveur: ");
  int adresse_ip_len = 255;
  char * adresse_ip;
  adresse_ip = (char *) malloc(adresse_ip_len);
  fgets(adresse_ip,adresse_ip_len,stdin);
  // Création de la socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  // Configuration de la connexion
  SOCKADDR_IN sin;
  sin.sin_addr.s_addr = inet_addr(adresse_ip);
  free(adresse_ip);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  // Si le client arrive à se connecter et si l'on a réussi à se connecter
  if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR){
      printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
      return sock;
  } else perror("Connection");
}

void deconnexion (SOCKET sock){
  printf("Fermeture de la socket Client et Serveur\n");
  closesocket(sock);
}
