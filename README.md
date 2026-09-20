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

※TTYから起動する！.

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
        "id":str,//ウィンドウid(アドレスポインタの予定)
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
