OpenPose による腕立て伏せ画像の解析
============================

## ■ Directory Structure

### □ 第1レベル

撮影パターンごとのディレクトリ：

| Directory | Description |
| :-------- | :---------- | 
| `pict_push-ups/`            | 腕立て伏せ画像(2017年11月21日撮影) |
| `pict_push-ups-from-side/`  | 横から撮影した腕立て伏せ画像(2017年11月28日撮影) |
| `movie_push-ups/`           | 腕立て伏せ動画(2017年11月21日撮影) |
| `movie_push-ups-from-side/` | 横から撮影した腕立て伏せ動画(2017年11月28日撮影) |


### □ 第2レベル

画像種別/解析結果種別ごとのディレクトリ：

| Directory | Description |
| :-------- | :---------- | 
| `0.movie/`       | 撮影した動画、第1レベルのディレクトリが「動画」の場合のみ存在 |
| `1.pict/`        | 撮影した画像 or 動画の各フレームから作成した静止画像 |
| `2-1.COCO-pose/` | OpenPose(COCO Modelを利用)による特徴点の**出力結果(関節の座標)** |
| `2-2.COCO-pict/` | OpenPose(COCO Modelを利用)による特徴点の**出力画像** |


### □ 第3レベル

#### - 第1レベルのディレクトリが「画像」の場合

`1.pict/` および `2-2.COCO-pict/` 以下は
画像の内容ごとのディレクトリになる：

| Directory | Description |
| :-------- | :---------- | 
| `0_up/`             | 腕を伸ばしている状態の画像 |
| `1_down/`           | 腕を曲げている状態の画像 |
| `Z_estimate-error/` | OpenPoseが姿勢推定に失敗した画像など訓練データから除くべき画像 |


#### - 第1レベルのディレクトリが「動画」の場合

`1.pict/` および `2-2.COCO-pict/` 以下は
動画ファイルごとのディレクトリになり、
ディレクトリ名は動画ファイルから拡張子を除いたものとする：

| Directory | Description |
| :-------- | :---------- | 
| `aaaa/`   | `0.movie/aaaa.mp4`や`0.movie/aaaa.mov`などのいずれかから作成した静止画像 |
| `bbbb/`   | `0.movie/bbbb.mp4`や`0.movie/bbbb.mov`などのいずれかから作成した静止画像 |
|  ....     | .... |



## ■ OpenPose の出力結果(関節の座標)

`2-1.COCO-pose/` にあるOpenPose の出力結果(関節の座標)についてまとめる。


### □ ファイル

第2レベルの`1.pict/` の下にあるディレクトリ毎に、
出力結果をcsvファイルとして保存：

| FileName | Description |
| :-------- | :---------- | 
| `0_up.csv`   | `1.pict/0_up/` にある画像の特徴点の出力結果 |
| `1_down.csv` | `1.pict/1_down/` にある画像の特徴点の出力結果 |
|  ....     | .... |


### □ フォーマット

各行は、1つの画像に対する出力。
18個の特徴点の `(x,y,score)` が並び、最後にファイル名がある。すなわち、以下の55列のデータ：
```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

- `(x0, y0, score0)` は、検出した **鼻** の`(x座標, y座標, score)`
- `(x1, y1, score1)` は、検出した **首** の`(x座標, y座標, score)`
- `(x2, y2, score1)` は、検出した **右肩** の`(x座標, y座標, score)`
- …
- `score` は、0以上1以下の実数値で、1が自信あり、0が自信なし
- `score` が、0の場合は特徴点が検出されておらず、`x`, `y` ともに0になる

ただし、1個の特徴点も得られなかった場合は、ファイル名のみの1列のデータになる：
```
filename
```

鼻、首、右肩、以降の特徴点の並びは、以下の画像を参照：  
![COCO modelの特徴点の並び](https://github.com/CMU-Perceptual-Computing-Lab/openpose/raw/master/doc/media/keypoints_pose.png)



## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita の日本語解説](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
