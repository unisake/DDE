//wayland.h
#ifndef WAYLAND_H
#define WAYLAND_H

#include <assert.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/backend/session.h>
#include <wlr/backend/multi.h>
#include <wlr/render/allocator.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/types/wlr_keyboard.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_pointer.h>
#include <wlr/types/wlr_scene.h>
#include <wlr/types/wlr_seat.h>
#include <wlr/types/wlr_subcompositor.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/util/log.h>
#include <xkbcommon/xkbcommon.h>
//UNIXソケット用
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <string.h>

//カーソルのモードを列挙型で指定
enum wayland_cursor_mode {
	wayland_CURSOR_PASSTHROUGH,
	wayland_CURSOR_MOVE,
	wayland_CURSOR_RESIZE,
};

struct window {
	char *app_cmd;
	int x;
	int y;
	int w;
	int h;

};

struct wayland_server;

struct wayland_server *create_server(void);

bool init_server(struct wayland_server *server);

void server_run(struct wayland_server *server);

void server_destroy(struct wayland_server *server);

#endif /*WAYLAND_H*/