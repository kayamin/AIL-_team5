OpenPose �ɂ��r���ĕ����摜�̉��
============================

## �� Directory Structure

### �� ��1���x��

�B�e�p�^�[�����Ƃ̃f�B���N�g���F

| Directory | Description |
| :-------- | :---------- | 
| `pict_push-ups/`            | �r���ĕ����摜(2017�N11��21���B�e) |
| `pict_push-ups-from-side/`  | ������B�e�����r���ĕ����摜(2017�N11��28���B�e) |
| `movie_push-ups/`           | �r���ĕ�������(2017�N11��21���B�e) |
| `movie_push-ups-from-side/` | ������B�e�����r���ĕ�������(2017�N11��28���B�e) |


### �� ��2���x��

�摜���/��͌��ʎ�ʂ��Ƃ̃f�B���N�g���F

| Directory | Description |
| :-------- | :---------- | 
| `0.movie/`       | �B�e��������A��1���x���̃f�B���N�g�����u����v�̏ꍇ�̂ݑ��� |
| `1.pict/`        | �B�e�����摜 or ����̊e�t���[������쐬�����Î~�摜 |
| `2-1.COCO-pose/` | OpenPose(COCO Model�𗘗p)�ɂ������_��**�o�͌���(�֐߂̍��W)** |
| `2-2.COCO-pict/` | OpenPose(COCO Model�𗘗p)�ɂ������_��**�o�͉摜** |


### �� ��3���x��

#### - ��1���x���̃f�B���N�g�����u�摜�v�̏ꍇ

`1.pict/` ����� `2-2.COCO-pict/` �ȉ���
�摜�̓��e���Ƃ̃f�B���N�g���ɂȂ�F

| Directory | Description |
| :-------- | :---------- | 
| `0_up/`             | �r��L�΂��Ă����Ԃ̉摜 |
| `1_down/`           | �r���Ȃ��Ă����Ԃ̉摜 |
| `Z_estimate-error/` | OpenPose���p������Ɏ��s�����摜�ȂǌP���f�[�^���珜���ׂ��摜 |


#### - ��1���x���̃f�B���N�g�����u����v�̏ꍇ

`1.pict/` ����� `2-2.COCO-pict/` �ȉ���
����t�@�C�����Ƃ̃f�B���N�g���ɂȂ�A
�f�B���N�g�����͓���t�@�C������g���q�����������̂Ƃ���F

| Directory | Description |
| :-------- | :---------- | 
| `aaaa/`   | `0.movie/aaaa.mp4`��`0.movie/aaaa.mov`�Ȃǂ̂����ꂩ����쐬�����Î~�摜 |
| `bbbb/`   | `0.movie/bbbb.mp4`��`0.movie/bbbb.mov`�Ȃǂ̂����ꂩ����쐬�����Î~�摜 |
|  ....     | .... |



## �� OpenPose �̏o�͌���(�֐߂̍��W)

`2-1.COCO-pose/` �ɂ���OpenPose �̏o�͌���(�֐߂̍��W)�ɂ��Ă܂Ƃ߂�B


### �� �t�@�C��

��2���x����`1.pict/` �̉��ɂ���f�B���N�g�����ɁA
�o�͌��ʂ�csv�t�@�C���Ƃ��ĕۑ��F

| FileName | Description |
| :-------- | :---------- | 
| `0_up.csv`   | `1.pict/0_up/` �ɂ���摜�̓����_�̏o�͌��� |
| `1_down.csv` | `1.pict/1_down/` �ɂ���摜�̓����_�̏o�͌��� |
|  ....     | .... |


### �� �t�H�[�}�b�g

�e�s�́A1�̉摜�ɑ΂���o�́B
18�̓����_�� `(x,y,score)` �����сA�Ō�Ƀt�@�C����������B���Ȃ킿�A�ȉ���55��̃f�[�^�F
```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

- `(x0, y0, score0)` �́A���o���� **�@** ��`(x���W, y���W, score)`
- `(x1, y1, score1)` �́A���o���� **��** ��`(x���W, y���W, score)`
- `(x2, y2, score1)` �́A���o���� **�E��** ��`(x���W, y���W, score)`
- �c
- `score` �́A0�ȏ�1�ȉ��̎����l�ŁA1�����M����A0�����M�Ȃ�
- `score` ���A0�̏ꍇ�͓����_�����o����Ă��炸�A`x`, `y` �Ƃ���0�ɂȂ�

�������A1�̓����_�������Ȃ������ꍇ�́A�t�@�C�����݂̂�1��̃f�[�^�ɂȂ�F
```
filename
```

�@�A��A�E���A�ȍ~�̓����_�̕��т́A�ȉ��̉摜���Q�ƁF  
![COCO model�̓����_�̕���](https://github.com/CMU-Perceptual-Computing-Lab/openpose/raw/master/doc/media/keypoints_pose.png)



## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita �̓��{����](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
