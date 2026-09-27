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

typedef struct{
	struct wl_display *wl_display;
	struct wlr_backend *backend;
	struct wlr_renderer *renderer;
	struct wlr_allocator *allocator;
	struct wlr_scene *scene;
	struct wlr_scene_output_layout *scene_layout;

	struct wlr_xdg_shell *xdg_shell;
	struct wl_listener new_xdg_toplevel;
	struct wl_listener new_xdg_popup;
	struct wl_list toplevels;

	struct wlr_cursor *cursor;
	struct wlr_xcursor_manager *cursor_mgr;
	struct wl_listener cursor_motion;
	struct wl_listener cursor_motion_absolute;
	struct wl_listener cursor_button;
	struct wl_listener cursor_axis;
	struct wl_listener cursor_frame;

	struct wlr_seat *seat;
	struct wl_listener new_input;
	struct wl_listener request_cursor;
	struct wl_listener pointer_focus_change;
	struct wl_listener request_set_selection;
	struct wl_list keyboards;

	struct wlr_session *session;  // wlr_output_layout の前あたり

	struct wlr_output_layout *output_layout;
	struct wl_list outputs;
	struct wl_listener new_output;
	int de_sock_fd;

	const char *wl_socket;

	int position[2];
    int size[2];
}dde_server;

dde_server *create_server(void);

bool init_server(dde_server *server);

void server_run(dde_server *server);

void server_destroy(dde_server *server);

#endif /*WAYLAND_H*/