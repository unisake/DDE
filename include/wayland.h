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

//構造体でサーバーのソケットを取得
struct wayland_server {
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
	enum wayland_cursor_mode cursor_mode;
	struct wayland_toplevel *grabbed_toplevel;
	double grab_x, grab_y;
	struct wlr_box grab_geobox;
	uint32_t resize_edges;

	struct wlr_session *session;  // wlr_output_layout の前あたり

	struct wlr_output_layout *output_layout;
	struct wl_list outputs;
	struct wl_listener new_output;
	int de_sock_fd; /* TODO: core.cに分離する DEソケットのfd */
};

//ソケットを構造体でもう一度まとめる

//アウトプットのソケット（よくわからない）
struct wayland_output {
	struct wl_list link;
	struct wayland_server *server;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
	struct wl_listener request_state;
	struct wl_listener destroy;
};

//トップレベルウィンドウのソケット
struct wayland_toplevel {
	struct wl_list link;
	struct wayland_server *server;
	struct wlr_xdg_toplevel *xdg_toplevel;
	struct wlr_scene_tree *scene_tree;
	struct wl_listener map;
	struct wl_listener unmap;
	struct wl_listener commit;
	struct wl_listener destroy;
	struct wl_listener request_move;
	struct wl_listener request_resize;
	struct wl_listener request_maximize;
	struct wl_listener request_fullscreen;
};

//ポップアップウィンドウのソケット
struct wayland_popup {
	struct wlr_xdg_popup *xdg_popup;
	struct wl_listener commit;
	struct wl_listener destroy;
};

//キーボードのソケット
struct wayland_keyboard {
	struct wl_list link;
	struct wayland_server *server;
	struct wlr_keyboard *wlr_keyboard;

	struct wl_listener modifiers;
	struct wl_listener key;
	struct wl_listener destroy;
};

// ================================
// 関数宣言
// ================================

bool init_server(struct wayland_server *server);

// フォーカス
void focus_toplevel(struct wayland_toplevel *toplevel);

// キーボード
void keyboard_handle_modifiers(
		struct wl_listener *listener, void *data);

bool handle_keybinding(
		struct wayland_server *server, xkb_keysym_t sym);

void keyboard_handle_key(
		struct wl_listener *listener, void *data);

void keyboard_handle_destroy(
		struct wl_listener *listener, void *data);

void server_new_keyboard(
		struct wayland_server *server,
		struct wlr_input_device *device);

// 入力デバイス
void server_new_pointer(
		struct wayland_server *server,
		struct wlr_input_device *device);

void server_new_input(
		struct wl_listener *listener, void *data);

// Seat
void seat_request_cursor(
		struct wl_listener *listener, void *data);

void seat_pointer_focus_change(
		struct wl_listener *listener, void *data);

void seat_request_set_selection(
		struct wl_listener *listener, void *data);

// デスクトップ・カーソル
struct wayland_toplevel *desktop_toplevel_at(
		struct wayland_server *server,
		double lx, double ly,
		struct wlr_surface **surface,
		double *sx, double *sy);

void reset_cursor_mode(
		struct wayland_server *server);

void process_cursor_move(
		struct wayland_server *server);

void process_cursor_resize(
		struct wayland_server *server);

void process_cursor_motion(
		struct wayland_server *server,
		uint32_t time);

// カーソルイベント
void server_cursor_motion(
		struct wl_listener *listener, void *data);

void server_cursor_motion_absolute(
		struct wl_listener *listener, void *data);

void server_cursor_button(
		struct wl_listener *listener, void *data);

void server_cursor_axis(
		struct wl_listener *listener, void *data);

void server_cursor_frame(
		struct wl_listener *listener, void *data);

// Output
void output_frame(
		struct wl_listener *listener, void *data);

void output_request_state(
		struct wl_listener *listener, void *data);

void output_destroy(
		struct wl_listener *listener, void *data);

void server_new_output(
		struct wl_listener *listener, void *data);

// XDG Toplevel
void xdg_toplevel_map(
		struct wl_listener *listener, void *data);

void xdg_toplevel_unmap(
		struct wl_listener *listener, void *data);

void xdg_toplevel_commit(
		struct wl_listener *listener, void *data);

void xdg_toplevel_destroy(
		struct wl_listener *listener, void *data);

void begin_interactive(
		struct wayland_toplevel *toplevel,
		enum wayland_cursor_mode mode,
		uint32_t edges);

void xdg_toplevel_request_move(
		struct wl_listener *listener, void *data);

void xdg_toplevel_request_resize(
		struct wl_listener *listener, void *data);

void xdg_toplevel_request_maximize(
		struct wl_listener *listener, void *data);

void xdg_toplevel_request_fullscreen(
		struct wl_listener *listener, void *data);

void server_new_xdg_toplevel(
		struct wl_listener *listener, void *data);

// XDG Popup
void xdg_popup_commit(
		struct wl_listener *listener, void *data);

void xdg_popup_destroy(
		struct wl_listener *listener, void *data);

void server_new_xdg_popup(
		struct wl_listener *listener, void *data);

#endif /*WAYLAND_H*/