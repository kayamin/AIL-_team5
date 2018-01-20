import tfcoreml as tf_converter
tf_converter.convert(tf_model_path = 'livecount.pb',
                     mlmodel_path = 'livecount.mlmodel',
                     output_feature_names = ['softmax:0'])
