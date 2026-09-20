# project(...)             ← 関数を呼ぶ
# inc = ...                ← 変数に値を代入
# executable(...)          ← 関数を呼ぶ
#        ↓
# 名前付き引数も使える
# include_directories : inc
# # 名前 : 値

project('dde', 'c', #'名前', '使う言語'
    version: '0.1.0', #'バージョン'
    default_options: ['c_std=c23'] #'コンパイラ指定'
)

#各ライブラリの依存関係取得
wlroots = dependency('wlroots-0.21') 
wayland_server = dependency('wayland-server')
xkbcommon = dependency('xkbcommon')
wpe_dep = dependency('wpe-webkit-2.0')

#インクルードの捜索先ディレクトリを指定
#inc = include_directories('include')

#実際にビルド
#executable(名前,ソースファイル)

executable('dde', #出力される実行ファイルの名前
    sources: [ #配列でソース指定
        'src/main.c',
        'src/wayland.c',
        'src/wpe.c'
        ],
    dependencies: [ #さっき取得した依存関係
        wlroots,
        wayland_server,
        xkbcommon,
        wpe_dep,
    ],
    include_directories: 'include', #さっき宣言した捜索先
    c_args: [ #コンパイラに渡すopt引数
        '-DWLR_USE_UNSTABLE', #`#ifdef`が使える
        '-D_POSIX_C_SOURCE=200809L' #`#if`が使える
        ],
)

#ビルド
#rm -rf build ←クリーンしたいとき
#meson setup build #ビルド環境作る
#meson compile -C build #実際にコンパイラ突っ込む