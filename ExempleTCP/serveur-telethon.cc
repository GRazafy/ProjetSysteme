#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

#include "make-sockaddr.h"
#include "EnvoiDon.h"

using namespace std;

int main(int argc,  char* argv[]) 
{
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " port" << std::endl;
    return EXIT_FAILURE;
  }
  
  auto adresse_locale = local_socket_address(SOCK_STREAM, argv[1]);
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  
  bind(fd, (sockaddr *) & adresse_locale, sizeof(adresse_locale));
  if(listen(fd,25)!=0)
  {
      std::cout<<"ERREUR LISTEN"<<std::endl;
      close(fd);
      return(EXIT_FAILURE);
  }
  else std::cout << "** Serveur Téléthon TCP port " << argv[1] << std::endl;

  int total = 0;
  while (true) {
    EnvoiDon m;
    auto sConnected=accept(fd,NULL,NULL);
    if (recv(sConnected, &m, sizeof m,0) == sizeof m) {
      unsigned int montant = m.montant();
      if (montant == 123456) { // code secret pour arrêter le serveur
	break;
      }
      total += montant;
      std::cout << "Merci à " << m.nom()
		<< " qui a envoyé " << montant << " €. "
		<< " total = " << total << " €"
        << std::endl;
    }
    //close(sConnected);
  }
  std::cout << "Et voila. Nous avons recueilli " << total << " €"
	    << std::endl;
}

