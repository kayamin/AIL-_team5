OpenPose output �r���ĕ���
============================

## directories, files

### pict_push-ups_orig/
�r���ĕ����̉摜�̒u����

#### pict_push-ups/0_up/
�r��L�΂��Ă����Ԃ̉摜

#### pict_push-ups/1_down/
�r���Ȃ��Ă����Ԃ̉摜

### pose_push-ups_COCO/
**OpenPose** �ɂ�� PoseKeyPoints(�����_) �̏o�͌��ʂ̒u����B
**COCO Model** �𗘗p�B

`0_up.csv` �� `1_down.csv` �ȂǁA`pict_push-ups/` �̉��ɂ���
�f�B���N�g������csv�t�@�C�� ���A���̃f�B���N�g���ɂ���摜��
�����_�̏o�͌��ʁB


### pict_push-ups_COCO/
**OpenPose** �ɂ�� PoseKeyPoints(�����_) �̏o�͉摜�̒u����B
���Ƃ��΁A`pict_push-ups/0_up/` �ɂ���摜�̓����_�̏o�͉摜��
`pict_push-ups_COCO/0_up/`

## output format

### pose_COCO/ �ɂ�������_�̏o�͌��ʂ̃t�H�[�}�b�g
�e�s�́A1�̉摜�ɑ΂���o�́B
18�̓����_�� `(x,y,score)` �����сA�Ō�Ƀt�@�C����������B���Ȃ킿�A�ȉ���55��̃f�[�^�B�F

```
x0, y0, score0, x1, y1, score1, ..., x17, y17, score17, filename
```

���Ƃ��΁A`(x0, y0, score0)` �́A���o���� **�@** ��`(x���W, y���W, score)`�A
`(x1, y1, score1)` �́A���o���� **��** ��`(x���W, y���W, score)`�B

`score` �́A0�ȏ�1�ȉ��̎����l�ŁA1�����M����A0�����M�Ȃ��B

�@�A��A�ȍ~�̓����_�̕��т�
[openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
�Q�ƁB


## References

-  [openpose tutorial output.md](https://github.com/CMU-Perceptual-Computing-Lab/openpose/blob/master/doc/output.md)
-  [qiita �̓��{����](https://qiita.com/nnn112358/items/ccd6330bed1e253d5ef9)
