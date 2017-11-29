OpenPose による腕立て伏せ画像の解析
============================

## directories, files

### 腕立て伏せ画像(2017年11月21日撮影)

- `pict_push-ups/`	オリジナル画像の置き場
- `pict_push-ups/0_up/`	腕を伸ばしている状態の画像
- `pict_push-ups/1_down/`	腕を曲げている状態の画像
- `pict_push-ups/Z_estimate-error/`	openposeが姿勢推定に失敗した画像など訓練データから除くべき画像

- `pict_push-ups_COCO-pose/`
`pict_push-ups`以下の画像に対する、OpenPose による PoseKeyPoints(特徴点) の
**出力結果(関節の座標)** の置き場。
**COCO Model** を利用。  
`0_up.csv` や `1_down.csv` など、`pict_push-ups/` の下にある
ディレクトリ名のcsvファイル が、そのディレクトリにある画像の
特徴点の出力結果。

- `pict_push-ups_COCO-pict/`
`pict_push-ups`以下の画像に対する、
OpenPose による PoseKeyPoints(特徴点) の **出力画像** の置き場。**COCO Model** を利用。  
たとえば、`pict_push-ups/0_up/` にある画像の特徴点の出力画像は
`pict_push-ups_COCO/0_up/`


### 横から撮影した腕立て伏せ画像(2017年11月28日撮影)
- `pict_push-ups-from-side/`	オリジナル画像
- `pict_push-ups-from-side_COCO-pose/`	`pict_push-ups-from-side/`以下の画像に対する出力結果の置き場
- `pict_push-ups-from-side_COCO-pict/`	`pict_push-ups-from-side/`以下の画像に対する出力画像の置き場



### 腕立て伏せ動画(2017年11月21日撮影)

- `movie_push-ups/`	オリジナル動画の置き場
- `animation_push-ups/`	`movie_push-ups/` にある動画の各フレームから作成した静止画像の置き場
- `animation_push-ups_COCO-pose/`	`animation_push-ups/`以下の画像に対する出力結果の置き場
- `animation_push-ups_COCO-pict/`	`animation_push-ups/`以下の画像に対する出力画像の置き場


### 横から撮影した腕立て伏せ動画(2017年11月28日撮影)
- `movie_push-ups-from-side/`	お察し
- `animation_push-ups-from-side/`	お察し
- `animation_push-ups-from-side_COCO-pose/`	お察し
- `animation_push-ups-from-side_COCO-pict/`	お察し




## output format

### `*_push-ups_COCO-pose/` などにある特徴点の出力結果のフォーマット
各行は、1つの画像に対する出力。
18個の特徴点の `(x,y,score)` が並び、最後にファイル名がある。すなわち、以下の55列のデータ：
```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

- `(x0, y0, score0)` は、検出した **鼻** の`(x座標, y座標, score)`
- `(x1, y1, score1)` は、検出した **首** の`(x座標, y座標, score)`
- …
- `score` は、0以上1以下の実数値で、1が自信あり、0が自信なし。

ただし、1個の特徴点も得られなかった場合は、ファイル名のみの1列のデータになる：
```
filename
```




鼻、首、以降の特徴点の並びは
[openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
参照。


## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita の日本語解説](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
