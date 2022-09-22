#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdbool.h>
#define PORT 5431
#define MAX_SOCKS 10
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MENSAJE_MAXIMO 1024

ssize_t readsocket(int s){

	char buf[MENSAJE_MAXIMO];
	ssize_t r;

	r = recv(s, buf, sizeof(buf) - 1, 0);
	if (r == -1)
		perror("recv");

	/* cierre de conexión o error */
	if (r == 0 || r == -1)
		return r;

	/* transforma a string de C */
	buf[r] = '\0';
	printf("[%d] < %s", s, buf);

	return r;
}

int main(int argc, char **argv)
{
	fd_set rdfs;
	struct sockaddr_in local;
    struct sockaddr_in remote;
	int first, max,newsocket, remotelen, sfd;
	int sockets[MAX_SOCKS];
	
	for ( int i = 0; i < MAX_SOCKS; i++){sockets[i] = 0;}
	
	/* crea socket */
    if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* configura dirección */
	local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;

	/* linkea socket con dirección */
    if (bind(sfd, (struct sockaddr *)&local, sizeof(local)) < 0) {
		perror("bind");
		exit(1);
	}

	/* setea socket a modo "listen"*/
	if (listen(sfd, 10) == -1) {
		perror("listen");
		exit(1);
	}

	/* atiende cliente */
	for (;;) {

		/* setea el fd_set de fd de lectura */
		FD_ZERO(&rdfs);
		FD_SET(sfd, &rdfs);
		max = sfd;
		first = 0;
		bool found = false;

		/* chequeo cuales hay que agregar */
		for(int i = 0; i < MAX_SOCKS;i++)
		{
			int s = sockets[i];
			if (s> 0)
				FD_SET(s,&rdfs);
			else if (s == 0 && !found){
				first = i;
				found = true;
			}

			if (s > max)
				max = s;
		}

		/* espera lectura, no escritura, no errores, no señales, sin
		 * timeout */
		if (pselect(max + 1, &rdfs, NULL, NULL, NULL, NULL) == -1) {
			perror("pselect");
			break;
		}

		/* checkea si hay nueva conexion*/
		if (FD_ISSET(sfd, &rdfs)) {
			remotelen = sizeof(remote);
			if ((newsocket = accept(sfd, (struct sockaddr *)&remote, (socklen_t *)&remotelen)) == -1) {
				perror("accept cfd0");
				exit(1);
			}

			sockets[first] = newsocket;
			char buf[6] = "hola\n";
			if (send(newsocket, buf, strlen(buf), 0) == -1) {
            	perror("enviando");
            	exit(1);
        	}
		}
		
		//Acá llegamos si no pasó nada con el server socket
		int m_size; //tamanio del mensaje recibido
        for ( int i = 0; i < MAX_SOCKS; i++){
        	if (FD_ISSET(sockets[i], &rdfs)) {
				if (readsocket(sockets[i]) == 0){
					close(sockets[i]);
                    sockets[i] = 0;
				}

			}
        }
	}

	/* cierra sockets */


	return 0;
}
