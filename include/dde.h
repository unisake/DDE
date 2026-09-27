#define SETTING_DATATYPE void //一旦コレで...
#define DDE SETTING_DATATYPE dde_server_settings(void) //データ宣言っぽく見せたいのであえて隠す
#define SERVER_SETTINGS return (SETTING_DATATYPE) //型を突っ込む
typedef void (*event)();

typedef struct{
    void *data;
    event *event;
} dde;

typedef struct{
    int position[2];
    int size[2];
    char *cmd;
} surface;


typedef struct{
    event new_surface;
    event delete_suface;
    surface *surface;
} client;

SETTING_DATATYPE dde_server_settings(void);
