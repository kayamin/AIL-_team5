# 貸出GPUマシンセットアップに関するメモ
## 概要
先端人工知能論2のグループワークのために貸し出されたGPU搭載デスクトップPCを、ニューラルネットの学習などに用いることができるようにセットアップした。
この作業は2017/12/14〜15にかけて行い、記録のためメモを残す。

## マシンスペック
|||
|:---|:---|
|名称|ZBOX-EN1070K|
|CPU|Intel Core i5-7500T (quad-core, 2.7 GHz, up to 3.3 GHz)|
|メモリ|16GB x 2|
|GPU|GeForce® GTX 1070 8GB GDDR5 256-bit|
|OS|Windows10

## 環境について
### python管理
pythonはpyenvでanaconda3-5.0.1を入れた。デフォルトだとpython3.6しか入らなかったのでanacondaの仮想環境で`py35`と言う名前でpython3.5も入れた。今は`py35`がglobal環境になっていて、各種ライブラリも`py35`にしか入れていない。  

### ssh接続
現在、無線でUTokyo-wifi

## 手順
実際に行った手順は大まかに言うと、
1. Ubuntu 16.04インストール
1. Ubuntu初期設定諸々
1. pyenv, anacondaのインストール
1. (tensorflow, chainerのインストール; コンフリクトしてあとでuninstallした)
1. 外部から接続できるように設定
1. CUDA toolkit, CUDA, cuDNNインストール
1. Openposeインストール
1. 諸々のtf, chainerなどのインストール

Openposeのインストール以外はほとんど以下のサイトの丸コピでできたので割愛  
https://qiita.com/jh3rox/items/20f04527f8084dddd57f


### 