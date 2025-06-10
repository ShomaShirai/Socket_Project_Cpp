# ソケット通信を使ったプログラムのC++画像取得部分

このプログラムは、OpenCV を用いてカメラ映像を取得し、ZeroMQ の PUB ソケットを通じて JPEG 形式でエンコードした画像を送信するアプリケーションです。

## 特徴

- OpenCV を使用してリアルタイムでカメラフレームを取得
- JPEG 形式でフレームをエンコード
- ZeroMQ を使ったソケット通信で画像データを送信（Publisher として動作）

## 使用技術

- C++
- OpenCV
- ZeroMQ（ソケット通信）

## 必要環境

- C++17 以降対応のコンパイラ（例: g++）
- OpenCV（バージョン4系推奨）
- ZeroMQ (`libzmq` および `cppzmq`)

## ビルド方法

以下のように CMake または手動でビルドできます。

### 手動ビルドの例（g++）

```bash
g++ -std=c++17 -o camera_publisher main.cpp `pkg-config --cflags --libs opencv4` -lzmq
