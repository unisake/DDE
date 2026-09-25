#include "wayland.h"
#include "wpe.h"

int main(int argc, char *argv[]) {
	//ログの初期化、引数はデバッグモード
	wlr_log_init(WLR_DEBUG, NULL);
	//オプションコマンドを格納するstr
	char *startup_cmd = NULL;

	//オプションの文字列を走査
	int c;
	while ((c = getopt(argc, argv, "s:h")) != -1) {
		switch (c) {//オプション文字がsか確認
		case 's':
			startup_cmd = optarg;
			break;
		default://違ったらエラー処理
			printf("Usage: %s [-s startup command]\n", argv[0]);
			return 0;
		}
	}
	if (optind < argc) {//オプションidが違ったらエラー
		printf("Usage: %s [-s startup command]\n", argv[0]);
		return 0;
	}

	struct wayland_server *server = create_server();//ソケット構造体を空に

    if(!init_server(server)){
		printf("\nfailed initraze\n");
        return 1;
    }
	
	if (TRUE) {
		if (fork() == 0) {
			execl("/bin/sh", "/bin/sh", "-c", "foot", (void *)NULL);
		}
		if (fork() == 0) {
			execl("/bin/sh", "/bin/sh", "-c", "kitty", (void *)NULL);
		}
	}

	server_run(server);

	server_destroy(server);
	return 0;
}