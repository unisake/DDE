project('dde', 'c', #'名前', '使う言語'
    version: '0.1.0', #'バージョン'
    default_options: ['c_std=c23'] #'コンパイラ指定'
)

#各ライブラリの依存関係取得
wlroots = dependency('wlroots-0.21') 
wayland_server = dependency('wayland-server')
xkbcommon = dependency('xkbcommon')

#インクルードの捜索先ディレクトリを指定
inc = include_directories('include')

#実際にビルド
#executable(名前,ソースファイル)

executable('dde.o', #出力される実行ファイルの名前
    sources: [ #配列でソース指定
        'src/main.c',
        'src/wayland.c',
        ],
    dependencies: [ #さっき取得した依存関係
        wlroots,
        wayland_server,
        xkbcommon,
    ],
    include_directories: 'include', #さっき宣言した捜索先
    c_args: [ #コンパイラに渡すopt引数
        '-DWLR_USE_UNSTABLE', #`#ifdef`が使える
        '-D_POSIX_C_SOURCE=200809L' #`#if`が使える
        ],
)