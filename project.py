#!/usr/bin/env python3
import subprocess
Commit_msg = [
    "add：",      # 新規（ファイル）機能追加
    "fix：",      # 修正(誤字脱字・バグ諸々)
    "hotfix：",   # クリティカルなバグ修正
    "update：",   # 機能修正（バグではない）
    "remove：",   # 削除（ファイル）
    "change：",   # 仕様変更
    "refactor：", # 外から見た機能・挙動を変えずに、中身を整理する
    "disable：",  # 無効化（コメントアウト等）
    "upgrade：",  # バージョンアップ
    "revert：",   # 変更取り消し
    "docs：",     #ドキュメント・スクリプト等の修正
]

Type = 10

Add_Path = """
./README.md
./project.py
""".strip().splitlines()

Commit_msg[Type] += """
Gitツールの機能追加
READMEの軽微な誤字脱字
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