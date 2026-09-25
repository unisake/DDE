#!/usr/bin/env python3
import subprocess
Commit_msg = [
    "add：",      # 0.新規（ファイル）機能追加
    "fix：",      # 1.修正(誤字脱字・バグ諸々)
    "hotfix：",   # 2.クリティカルなバグ修正
    "update：",   # 3.機能修正（バグではない）
    "remove：",   # 4.削除（ファイル）
    "change：",   # 5.仕様変更
    "refactor：", # 6.外から見た機能・挙動を変えずに、中身を整理する
    "disable：",  # 7.無効化（コメントアウト等）
    "upgrade：",  # 8.バージョンアップ
    "revert：",   # 9.変更取り消し
    "docs：",     # 10.ドキュメント・スクリプト等の修正
]

Type = 6

Add_Path = """
./src/main.c
./include/wayland.h
./src/wayland.c
./project.py
""".strip().splitlines()

Commit_msg[Type] += """
APIをライブラリ側に押し込んでmainを薄くした
"""

print(Commit_msg[Type])

if input("push? [y/n] ") == "y":

    subprocess.run(
        ["git", "add", *Add_Path],
        check=True
    )

    subprocess.run(
        ["git", "commit", "-m", Commit_msg[Type]],
        check=True
    )

    subprocess.run(
        ["git", "push"],
        check=True
    )