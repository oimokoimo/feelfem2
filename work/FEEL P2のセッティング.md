# HOWTO: Build & Run FEEL P2 on WSL (Ubuntu)

このドキュメントでは、WSL2上のUbuntu環境で **FEEL P2 (1993-1997)** をビルドし、実行するための手順を解説します。

> [!CAUTION]
> **重要: OSバージョンの制限**
> Ubuntu 24.04以降では、依存パッケージである `gcl` (GNU Common Lisp) が公式リポジトリから削除されたため、動作しません。**Ubuntu 22.04 LTS** 以前を使用してください。

---

## 1. 動作環境 (Prerequisites)

* **Windows 10 / 11 + WSL2**
* **OS:** Ubuntu 22.04 LTS (推奨) / 20.04 LTS
* **X11環境:** * **Windows 11:** 標準の WSLg で動作します。
    * **Windows 10:** VcXsrv や X410 などの外部Xサーバーを起動してください。

---

## 2. 依存パッケージのインストール

ビルドに必要なツール、パーサジェネレータ、および X11 関連の開発用ヘッダーをインストールします。

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  gfortran \
  gcl \
  flex bison \
  libfl-dev \
  libx11-dev \
  libxt-dev \
  libxext-dev \
  libxmu-dev \
  libxpm-dev


カテゴリ,パッケージ名,用途
Build Tools,"build-essential, gfortran","gcc, g++, make, Fortranコンパイラ"
Parser,"flex, bison, libfl-dev",字句解析・構文解析器の生成 (-lfl を含む)
Lisp,gcl,システムのコアとなる GNU Common Lisp
GUI/X11,libx11-dev ～ libxpm-dev,可視化およびGUIコンポーネント (Xt/Xpm等)

3. ビルド手順 (Build)
FEEL P2は、専用のビルドスクリプトを実行することで、自動的にバイナリとライブラリが配置されるよう設計されています。

ソースディレクトリへ移動

Bash
cd ~/feelfem2/work/feelp2-wsl/src.inria98.web/
ビルドスクリプトの実行

Bash
./build.sh
実行が完了すると、~/bin に実行ファイルが、~/lib にライブラリファイルが自動的に設定されます。

4. 実行方法 (Run)
X11の接続確認
実行前に、GUIが表示できる状態か確認します。

Bash
echo $DISPLAY
# :0 または localhost:0 と表示されればOK
FEEL P2の起動
~/bin にパスが通っているか確認し、inputファイルを指定して実行します。

Bash
~/bin/feelp2 -bamg [pdeファイル (feelfem2/samplesP2にFEEL P2用のものがあります]
正しく設定されていれば、Fortran 77プログラムとデータファイルが生成されます。

makeで実行ファイルfeelgoを作成し、./feelgoで実行してみてください。

5. トラブルシューティング
X11/Intrinsic.h: No such file or directory

libxt-dev がインストールされているか確認してください。

cannot find -lfl

libfl-dev が必要です。これは flex のライブラリです。

X Window が表示されない

Windows 11の場合: WSLgが有効であることを確認。

Windows 10の場合: Xサーバーを起動し、アクセス許可設定（Access Control）を確認してください。

6. Philosophy
FEEL P2は、ソースコードからビルドすることを前提に設計された、非常にコンパクトで堅牢な FEM DSL（ドメイン特化言語） システムです。
flex、bison、make、そして X11 という伝統的なUnixスタックが揃っていれば、30年近い時を経てもなお、現代の最新環境でそのパワーを発揮することができます。
