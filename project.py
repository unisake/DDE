#!/usr/bin/env python3
import subprocess

def commit_msg(prefix, text):
    return prefix + text

add = "add：" #------------- 新規（ファイル）機能追加
fix = "fix：" #------------- 修正（誤字脱字・バグ諸々）
hotfix = "hotfix：" #------- クリティカルなバグ修正
update = "update：" #------- 機能修正（バグではない）
remove = "remove：" #------- 削除（ファイル）
change = "change：" #------- 仕様変更
refactor = "refactor：" #--- 外から見た機能・挙動を変えずに、中身を整理する
disable = "disable：" #----- 無効化（コメントアウト等）
upgrade = "upgrade：" #----- バージョンアップ
revert = "revert：" #------- 変更取り消し
docs = "docs：" #----------- ドキュメント・スクリプト等の修正

msg = commit_msg(
    docs,
    """
    スクリプト、meson、READMEを微修正
    """
)

Add_Path = """
./README.md
./meson.build
""".strip().splitlines()

print(msg)

if input("push? [y/n] ") == "y":

    subprocess.run(
        ["git", "add", *Add_Path],
        check=True
    )

    subprocess.run(
        ["git", "add", "./project.py"],
        check=True
    )

    subprocess.run(
        ["git", "commit", "-m", msg],
        check=True
    )

    subprocess.run(
        ["git", "push"],
        check=True
    )