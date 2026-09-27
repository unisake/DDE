# DDE

- Declarative
- Desktop
- Environment

## What this?

宣言的な環境を構築できるデスクトップを目指す

- 動的な処理を省いた高速化
- アプリケーション同士のUI連携
- 大量の設定ファイルからの解放

# Gettiong Started!

## Dependencies

- `wpe-webkit`：アプリケーション組み込み型Webランタイム
- `wlroots`：最近流行ってるディスプレイ鯖
- `meson`：みんな大好きC言語ビルドツール

## Install
```sh
git clone https://github.com/unisake/dde
cd dde
```

## Build
```sh
rm -rf build ←クリーンしたいとき
meson setup build #ビルド環境作る
meson compile -C build #実際にコンパイラ突っ込む
```
[](あとでbuild.sh作るか)
## Start-Up

※TTYから起動する！

```sh
./dde
#Ctrl + Alt + Escでサーバ終了...
```

# Documentation
DDEの基本的な使い方や設定について説明します。


# Development
DDEの設計や内部構造について説明します。

# 要件定義

html等のソースでDEを定義

```sh
#TTY
./dde something.html
```

## セキュリティ

TTYから宣言されたAPIのみが許可される

```sh
#TTY
./dde something.html
```
↓
```sh
#XDG_shell
#something.htmlで定義したAPIのみが使用可能
```

## DDEが公開するAPI

```json
"DDE"{
    "Window":{
        "id":str,//ウィンドウid(アドレスポインタの予定),
        "coordinate"[x,y],//座標
        "size":[w,h],//サイズ
    },
    "key":{
        "get_keys":str[],//キーの状態
    },
    "pointer":{
        "state":[x,y],//現在座標
    }
}
//DDEが公開するものであって実装はHTMLに含まれるjsとかに依存することに注意！
```

```sh
#TTY上で
./dde ~/sever_conf.c #サーバー(管理者設定)でユーザーに送るAPIを決める
#サーバー起動後、xdg_shellで
./dde ~/user_conf.c #ユーザーはサーバ側で公開されたAPIを叩ける
#つまり...
#サーバの状態として保持しておきたいもの→Obj
#ユーザーの操作として公開したいもの→関数ポインタ
```
↑権限チェックはTTYかxdg_shellかどうかで確認してる

んじゃ関係性としては...
`./dde<->dde.h<->server_conf.c<->desktop.h<->user_conf.c`
みたいな？


```c
//main.c
#include "wayland.h"//サーバで使うAPI
#include "dde.h"//サーバ設定APIまとめ

int main{

    //サーバの作成・初期化

    dde()//ここをライブラリで書く

    //サーバの片付け
}
```
```c
//server_conf.c
#include "dde.h"
#include "desktop.h"//ユーザー側に見せるAPIまとめ
dde(){//読み込まれる設定
    //管理者設定いろいろ
    desktop();//ユーザー用のAPI
}
```
dde本体〜管理者設定まではコンパイルして作る
```sh
#ビルド環境は管理者に任せる。提供するのはdde.oのみ
gcc dde.o server_conf.o -o sever.bin
./server.bin
```
ユーザー設定
```c
//user_conf.c
#include "desktop.h"//設定ファイルが公開したAPI
desktop(){
    //ユーザー操作いろいろ
}
```
ユーザー設定は動的に読み込む
```sh
#管理者がビルドコマンドをまとめるのも良し
gcc -fPIC -shared user_conf.c -o user_conf.so　
#管理者が作ったAPIに読ませる
./server.bin user_conf.so
#とりあえず管理者がUNIXソケットを用意した体裁だけど
#.soのdesktop()が呼べれば基本何でも良い
```