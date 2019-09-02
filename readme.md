# minecraft_ground_generator
国土地理院の標高タイル画像を読み込み、マインクラフト統合版に標高を基にした地形を生成する関数群を有するパッケージを生成します。

## 現在の実装
現在の実装では引数で指定することなく、バージョンや名前の指定はできません。バージョンは0.0.1で名前はすべてgroundになります。

## 標高タイルの画像を入手
使用する画像は国土地理院の[地理院地図](https://maps.gsi.go.jp/)をスクショしカレントディレクトリーにimage.pngの名前で保存します。

[地理院地図](https://maps.gsi.go.jp/)は標高タイルのフィルターがかかったものを使用します。

[地理院地図](https://maps.gsi.go.jp/)のサイトに行き、
右上にある機能をクリックし、
ツールをクリックし、
外部タイル読込をクリックします。

URLのところに

https://cyberjapandata.gsi.go.jp/xyz/dem_png/{z}/{x}/{y}.png

を入力し、
上記の内容で読込開始をクリック

すると、海が赤く陸地が青の画像が生成されます。

海が赤くなっていない部分は、画像編集ソフトを用いて、塗りつぶします。

![日本](https://raw.githubusercontent.com/hikaright/minecraft_ground_generator/master/nippon.png)

こんな感じの画像になりますが、これをimage.pngでカレントディレクトリーに保存します。

## 実行
実行すると、func.mcpackが生成されます。Windows10のMinecraft BEではクリックでインポートされます。

## 関数の呼び出し
Minecraftで関数を呼び出すには、
```
/function 関数名
```
で実行できます。

生成された関数群は、
```
/function func0
/function func1
/function func2
...
```
のようにして実行されます。

## コンパイル
```
g++ main.cpp -luuid -std=c++11 -O2 `pkg-config opencv --cflags --libs` -w
```

(いろいろインストールして)ubuntuでコンパイルしているので他のOSでできるかはわかりません。
Linuxのコマンドを使うので、Windowsでは難しいです。

## ソフトウェアライセンス
[MIT License](https://github.com/hikaright/minecraft_ground_generator/blob/master/LICENSE)