#!/usr/bin/env python3

import subprocess


Commit_msg = [
    "add：",     # 新規（ファイル）機能追加
    "fix：",     # バグ修正
    "hotfix：",  # クリティカルなバグ修正
    "update：",  # 機能修正（バグではない）
    "remove：",  # 削除（ファイル）
    "change：",  # 仕様変更
    "clean：",   # 整理（リファクタリング等）
    "disable：", # 無効化（コメントアウト等）
    "upgrade：", # バージョンアップ
    "revert：",  # 変更取り消し
]

Type = 0

Add_Path = """
./src/main
./README.md
./project.py
""".strip().splitlines()

Commit_msg[Type] += """
改行付きの
コミットメッセージ
です
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