OpenPose output 腕立て伏せ
============================

## directories, files

### pict_push-ups_orig/
腕立て伏せの画像の置き場

#### pict_push-ups/0_up/
腕を伸ばしている状態の画像

#### pict_push-ups/1_down/
腕を曲げている状態の画像

### pose_push-ups_COCO/
**OpenPose** による PoseKeyPoints(特徴点) の出力結果の置き場。
**COCO Model** を利用。

`0_up.csv` や `1_down.csv` など、`pict_push-ups/` の下にある
ディレクトリ名のcsvファイル が、そのディレクトリにある画像の
特徴点の出力結果。


### pict_push-ups_COCO/
**OpenPose** による PoseKeyPoints(特徴点) の出力画像の置き場。
たとえば、`pict_push-ups/0_up/` にある画像の特徴点の出力画像は
`pict_push-ups_COCO/0_up/`

## output format

### pose_COCO/ にある特徴点の出力結果のフォーマット
各行は、1つの画像に対する出力。
18個の特徴点の `(x,y,score)` が並び、最後にファイル名がある。すなわち、以下の55列のデータ。：

```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

たとえば、`(x0, y0, score0)` は、検出した **鼻** の`(x座標, y座標, score)`、
`(x1, y1, score1)` は、検出した **首** の`(x座標, y座標, score)`。

`score` は、0以上1以下の実数値で、1が自信あり、0が自信なし。

鼻、首、以降の特徴点の並びは
[openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
参照。


## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita の日本語解説](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
