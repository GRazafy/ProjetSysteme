#include <iostream>
#include <cstring>
#include <unistd.h>

#include "make-sockaddr.h"
#include "EnvoiDon.h"

int main(int argc,  char* argv[]) 
{
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
	      << " serveur port nom montant" << std::endl;
    return EXIT_FAILURE;
  }
  auto adresse_serveur = remote_socket_address(argv[1], SOCK_STREAM, argv[2]);
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if(connect(fd,(sockaddr *) &adresse_serveur,sizeof(adresse_serveur))!=0)
  {
      std::cout<<"ERREUR CONNECT"<<std::endl;
      return(EXIT_FAILURE);
  }
  else std::cout<<"CONNECTION OK"<<std::endl;

  EnvoiDon m (argv[3], atoi(argv[4]));
  
  // on n'envoie qu'un message, le plus simple est d'utiliser sendto()

  int n = send(fd, &m, sizeof m,0);
  if (n == sizeof m) {
    std::cout << "C'est parti" << std::endl;
  } else {
    std::cout << "Problème d'envoi" << std::endl;
  }
  close (fd);
}

