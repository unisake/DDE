#include "wayland.h"
#include "dde.h"

void server_set_surface(dde_server *server, surface *surface){
	memcpy(server->position, surface->position, sizeof server->position);
	memcpy(server->size, surface->size, sizeof server->size);
	
	if(fork() == 0){
		execl("/bin/sh", "/bin/sh", "-c", surface->cmd, (char *)NULL);
		perror("execl");
    	_exit(1);
	}
}

int main() {
	//ログの初期化、引数はデバッグモード
	wlr_log_init(WLR_DEBUG, NULL);

	dde_server *server = create_server();//ソケット構造体を空に

    if(!init_server(server)){
		printf("\nfailed initraze\n");
        return 1;
    }

	surface surface[] = {{
		.position = {50,50,},
		.size = {200,200},
		.cmd = "foot",
	}};

	server_set_surface(server, &surface[0]);
	
	server_run(server);

	server_destroy(server);
	return 0;
}