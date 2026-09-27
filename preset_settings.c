#include "dde.h"

void funcA();

void funcB();

//mainでサーバーが出来たあとに呼ばれる関数(実質的な本処理)
DDE{
    client client = {
        .new_surface = funcA,
        .delete_suface = funcB,
        .surface = (surface[]){
            {
                .position = {0,0},
                .size = {0,0},
                .cmd = "foot"
            },
            {
                .position = {100, 100},
                .size = {640, 480},
                .cmd = "firefox"
            },
        },
    };
}
