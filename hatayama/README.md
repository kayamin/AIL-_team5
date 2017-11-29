OpenPose �ɂ��r���ĕ����摜�̉��
============================

## directories, files

### �r���ĕ����摜(2017�N11��21���B�e)

- `pict_push-ups/`	�I���W�i���摜�̒u����
- `pict_push-ups/0_up/`	�r��L�΂��Ă����Ԃ̉摜
- `pict_push-ups/1_down/`	�r���Ȃ��Ă����Ԃ̉摜
- `pict_push-ups/Z_estimate-error/`	openpose���p������Ɏ��s�����摜�ȂǌP���f�[�^���珜���ׂ��摜

- `pict_push-ups_COCO-pose/`
`pict_push-ups`�ȉ��̉摜�ɑ΂���AOpenPose �ɂ�� PoseKeyPoints(�����_) ��
**�o�͌���(�֐߂̍��W)** �̒u����B
**COCO Model** �𗘗p�B  
`0_up.csv` �� `1_down.csv` �ȂǁA`pict_push-ups/` �̉��ɂ���
�f�B���N�g������csv�t�@�C�� ���A���̃f�B���N�g���ɂ���摜��
�����_�̏o�͌��ʁB

- `pict_push-ups_COCO-pict/`
`pict_push-ups`�ȉ��̉摜�ɑ΂���A
OpenPose �ɂ�� PoseKeyPoints(�����_) �� **�o�͉摜** �̒u����B**COCO Model** �𗘗p�B  
���Ƃ��΁A`pict_push-ups/0_up/` �ɂ���摜�̓����_�̏o�͉摜��
`pict_push-ups_COCO/0_up/`


### ������B�e�����r���ĕ����摜(2017�N11��28���B�e)
- `pict_push-ups-from-side/`	�I���W�i���摜
- `pict_push-ups-from-side_COCO-pose/`	`pict_push-ups-from-side/`�ȉ��̉摜�ɑ΂���o�͌��ʂ̒u����
- `pict_push-ups-from-side_COCO-pict/`	`pict_push-ups-from-side/`�ȉ��̉摜�ɑ΂���o�͉摜�̒u����



### �r���ĕ�������(2017�N11��21���B�e)

- `movie_push-ups/`	�I���W�i������̒u����
- `animation_push-ups/`	`movie_push-ups/` �ɂ��铮��̊e�t���[������쐬�����Î~�摜�̒u����
- `animation_push-ups_COCO-pose/`	`animation_push-ups/`�ȉ��̉摜�ɑ΂���o�͌��ʂ̒u����
- `animation_push-ups_COCO-pict/`	`animation_push-ups/`�ȉ��̉摜�ɑ΂���o�͉摜�̒u����


### ������B�e�����r���ĕ�������(2017�N11��28���B�e)
- `movie_push-ups-from-side/`	���@��
- `animation_push-ups-from-side/`	���@��
- `animation_push-ups-from-side_COCO-pose/`	���@��
- `animation_push-ups-from-side_COCO-pict/`	���@��




## output format

### `*_push-ups_COCO-pose/` �Ȃǂɂ�������_�̏o�͌��ʂ̃t�H�[�}�b�g
�e�s�́A1�̉摜�ɑ΂���o�́B
18�̓����_�� `(x,y,score)` �����сA�Ō�Ƀt�@�C����������B���Ȃ킿�A�ȉ���55��̃f�[�^�F
```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

- `(x0, y0, score0)` �́A���o���� **�@** ��`(x���W, y���W, score)`
- `(x1, y1, score1)` �́A���o���� **��** ��`(x���W, y���W, score)`
- �c
- `score` �́A0�ȏ�1�ȉ��̎����l�ŁA1�����M����A0�����M�Ȃ��B

�������A1�̓����_�������Ȃ������ꍇ�́A�t�@�C�����݂̂�1��̃f�[�^�ɂȂ�F
```
filename
```




�@�A��A�ȍ~�̓����_�̕��т�
[openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
�Q�ƁB


## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita �̓��{����](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
