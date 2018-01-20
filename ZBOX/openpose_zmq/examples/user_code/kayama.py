import os
from flask import Flask, request, jsonify
from werkzeug import secure_filename
app = Flask(__name__)

UPLOAD_FOLDER = './uploads'
ALLOWED_EXTENSIONS = set(['png', 'jpg', 'jpeg', 'gif'])
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['SECRET_KEY'] = os.urandom(24)

def allowed_file(filename):
    return '.' in filename and \
        filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS

@app.route('/counter_status', methods=['GET'])
def pass_json():
    result = {
      "global_counter": 4,
      "status": 1
    }
    print(result)

    return jsonify(result)


@app.route('/send', methods=['GET', 'POST'])
def send():
    if request.method == 'POST':
        img_file = request.files['img_file']
        if img_file and allowed_file(img_file.filename):
            filename = secure_filename(img_file.filename)
            img_file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

            return jsonify(res='ok')
        else:
            return ''' <p>許可されていない拡張子です</p> '''

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=44400)